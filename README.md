# read_ecl
Read binary output data files (such as restart files) from Schlumberger's reservoir simulator, Eclipse. 

For more information: https://se.mathworks.com/matlabcentral/fileexchange/47607-read_ecl-m

## How to use?
QMap<QString, QVector<QVariant> > out = read_ecl(QString) returns a QMap Qt c++ containing all data from the binary file specified by 'filename'.
