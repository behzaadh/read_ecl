
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
    int length = 0;
    QMap<QString, QVector<QVariant> > out;
    // Skip HEADER
    length  += sizeof(qint32);
    QString keyword;
    int num    = 0;
    int wsize   = 0;
    for (int i = 0; i < ba.count(); i++)
    {
        // Read field name (keyword) and array size
        keyword = QString::fromStdString(ba.mid(length, 8*sizeof(quint8)).toStdString());
        keyword = keyword.simplified();
        keyword.replace( " ", "" );
        keyword.replace('+','_');
        length  += 8*sizeof(quint8);
        QDataStream numStream(ba.mid(length, sizeof(qint32)));
        numStream >> num;
        length  += sizeof(qint32);
        // Read and interpret data type
        QString dtype = QString::fromStdString(ba.mid(length, 4*sizeof(quint8)).toStdString());
        length  += 4*sizeof(quint8);
        if (dtype == "INTE")
            wsize = 4;
        else if (dtype == "REAL")
            wsize = 4;
        else if (dtype == "DOUB")
            wsize = 8;
        else if (dtype == "LOGI")
            wsize = 4;
        else if (dtype == "CHAR")
        {
            wsize = 1;
            num  *= 8;
        }
        // Skip next word
        length  += sizeof(qint32);
        // Read data array, which may be split into several consecutive
        // arrays
        QVector<QVariant> data;
        int remnum = num;

        while (remnum > 0)
        {
            // Read array size
            QDataStream numStream(ba.mid(length, sizeof(qint32)));
            int buflen;
            numStream >> buflen;
            length  += sizeof(qint32);
            int bufnum = buflen / wsize;
            // Read data and append to array
            if (dtype == "INTE")
            {
                for (int j = 0; j < bufnum; j++)
                {
                    QDataStream numStream(ba.mid(length, sizeof(qint32)));
                    int num_temp;
                    numStream >> num_temp;
                    data.append(num_temp);
                    length  += sizeof(qint32);
                }
            }
            else if (dtype == "CHAR")
            {
                for (int j = 0; j < bufnum; j++)
                {
                    QDataStream numStream(ba.mid(length, sizeof(quint8)));
                    quint8 num_temp;
                    numStream >> num_temp;
                    data.append(QString((char)num_temp));
                    length  += sizeof(quint8);
                }
            }
            else if (dtype == "LOGI")
            {
                for (int j = 0; j < bufnum; j++)
                {
                    QDataStream numStream(ba.mid(length, sizeof(qint32)));
                    int num_temp;
                    numStream >> num_temp;
                    data.append((bool)num_temp);
                    length  += sizeof(qint32);
                }
            }
            else if (dtype == "DOUB")
            {
                for (int j = 0; j < bufnum; j++)
                {
                    QDataStream numStream(ba.mid(length, sizeof(double)));
                    double num_temp;
                    numStream >> num_temp;
                    data.append(num_temp);
                    length  += sizeof(double);
                }
            }
            else if (dtype == "REAL")
            {
                for (int j = 0; j < bufnum; j++)
                {
                    QDataStream numStream(ba.mid(length, sizeof(qint32)));

                    qint32 num_temp;
                    numStream >> num_temp;
                    double num_temp_r = *reinterpret_cast<float*>(&num_temp);
                    data.append(num_temp_r);
                    length  += sizeof(qint32);
                }
            }

            length  += sizeof(qint32);
            remnum = remnum - bufnum;
        }
        // Special post-processing of the CHAR datatypes
        if (dtype == "CHAR")
        {
            QString str = "";
            QVector<QVariant> tempData;
            for (int j=0; j<data.count(); j++)
            {
                str.append(data[j].toString());
                if (remainder(j,7) == 0 && j != 0)
                {
                    tempData.append(str);
                    str.clear();
                }
            }

            data.clear();
            data = tempData;
        }
        // Add array to struct. If keyword already exists, append data.
        if (out.contains(keyword))
        {
            QVector<QVariant> value = out.values(keyword).first();
            value.append(data);
            out[keyword] = value;
        }
        else
            out[keyword] = data;
        // Skip next word
        length  += sizeof(qint32);
    }

    return out;
}
