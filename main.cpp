
#include <QApplication>
#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <math.h>

QMap<QString, QVector<QVariant> > read_ecl(const QByteArray &ba);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMap<QString, QVector<QVariant> > output = read_ecl("C:/Users/behzadh/Desktop/RESTART.X0000");

    return a.exec();
}


QMap<QString, QVector<QVariant> > read_ecl(const QString &filename)
{
	QFile file("C:/Users/behzadh/Desktop/New folder (2)/RESTART.X0000");
    if (!file.open(QIODevice::ReadOnly))
    {
        return 0;
    }
	
	QByteArray ba = file.readAll();
        int l = 0;
    QMap<QString, QVector<double> > out;

    // Skip HEADER
    l += sizeof(qint32);
    QString keyword;
    int     num   = 0;
    int     wsize = 0;

    while (l < ba.count())
    {
        // Read field name (keyword) and array size
        keyword = QString::fromStdString(ba.mid(l, 8 * sizeof(quint8)).toStdString());
        keyword = keyword.simplified();
        keyword.replace(" ", "");
        keyword.replace('+', '_');
        l += 8 * sizeof(quint8);
        QDataStream numStream(ba.mid(l, sizeof(qint32)));
        numStream >> num;
        l += sizeof(qint32);

        // Read and interpret data type
        QString dtype = QString::fromStdString(ba.mid(l, 4 * sizeof(quint8)).toStdString());
        l += 4 * sizeof(quint8);

        if (dtype == "INTE")
        {
            wsize = 4;
        }
        else if (dtype == "REAL")
        {
            wsize = 4;
        }
        else if (dtype == "DOUB")
        {
            wsize = 8;
        }
        else if (dtype == "LOGI")
        {
            wsize = 4;
        }
        else if (dtype == "CHAR")
        {
            wsize = 1;
            num  *= 8;
        }

        // Skip next word
        l += sizeof(qint32);

        // Read data array, which may be split into several consecutive
        // arrays
        QVector<double> data;
        int remnum = num;

        while (remnum > 0)
        {
            // Read array size
            QDataStream numStream(ba.mid(l, sizeof(qint32)));
            int buflen;
            numStream >> buflen;
            l += sizeof(qint32);
            int bufnum = buflen / wsize;
            QDataStream stream(ba.mid(l, bufnum * wsize));

            if (dtype == "REAL")
            {
                for (int j = 0; j < bufnum; j++)
                {
                    qint32 num_temp;
                    stream >> num_temp;
                    double num_temp_r = *reinterpret_cast<float *>(&num_temp);
                    data.append(num_temp_r);
                }
            }

            l     += sizeof(qint32) + bufnum * wsize;
            remnum = remnum - bufnum;
        }

        out[keyword] = data;

        // Skip next word
        l += sizeof(qint32);
    }

    return out;
}
