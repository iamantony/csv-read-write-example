#include <QList>
#include <QColor>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

QList<QRgb> GetPixels()
{
    QList<QRgb> pixels;
    pixels << qRgb(11, 255, 0) << qRgb(167, 209, 89) << qRgb(34, 55, 12);

    return pixels;
}

QList<QStringList> PixelsToStrings(const QList<QRgb>& pixels)
{
    QList<QStringList> strings;
    for (int i = 0; i < pixels.size(); ++i)
    {
        QStringList values;
        values << QString::number(qRed(pixels.at(i))) <<
                  QString::number(qGreen(pixels.at(i))) <<
                  QString::number(qBlue(pixels.at(i)));

        strings << values;
    }

    return strings;

}

void WriteToCSV(const QList<QStringList>& pixels)
{
    // Open csv-file
    QFile file("pixels.csv");
    file.open(QIODevice::Append | QIODevice::Text);

    // Write data to file
    QTextStream stream(&file);
    QString separator(",");
    for (int i = 0; i < pixels.size(); ++i)
    {
        stream << pixels.at(i).join(separator) << endl;
    }

    stream.flush();
    file.close();
}

QList<QStringList> ReadCSV()
{
    // Open csv-file
    QFile file("pixels.csv");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Read data from file
    QTextStream stream(&file);
    QList<QStringList> data;
    QString separator(",");
    while (stream.atEnd() == false)
    {
        QString line = stream.readLine();
        data << line.split(separator);
    }

    file.close();
    return data;
}

void Print(const QList<QStringList>& data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        qDebug() << data.at(i).join(", ");
    }
}

int main()
{
    QList<QRgb> pixels = GetPixels();
    QList<QStringList> pixelsStr = PixelsToStrings(pixels);
    WriteToCSV(pixelsStr);

    QList<QStringList> readData = ReadCSV();
    Print(readData);

    return 0;
}
