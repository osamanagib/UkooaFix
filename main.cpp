#include <QCoreApplication>
#include <QObject>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {}

public slots:
    void run()
    {
        // Do processing here

        emit finished();
    }

signals:
    void finished();
};
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile *ukFile = new QFile(QString("/Users/nagioi0a/Downloads/NS1763P1004.p190"));
    QFile *ukOut = new QFile("/Users/nagioi0a/Downloads/out.p190");
    bool rt = ukFile->open(QIODevice::ReadOnly);
    ukOut->open(QIODevice::WriteOnly);
    cout << "return " << rt << endl;
    //  char *data = new char[8200];
    //ukFile->read(data,10);
    qint64 icount = 0;
    //    while (!ukFile->atEnd())
    //    {
    //        if(!(icount%100))
    //        {
    //            cout << icount << endl;
    //            ukFile->read(data,8*(icount/100+1)+80);
    //        }
    qint64 fileSize = ukFile->size();
    char *data = new char[fileSize];
    ukFile->read(data,fileSize);
    QString sData = data;
    QString shot = "SNS";
    while (true)
    {
        ukFile->seek(icount);
        ukFile->read(data,fileSize);
        sData = data;;
        if(icount>fileSize)
        {
            break;
        }
        auto sPos = sData.indexOf(shot,0,Qt::CaseInsensitive);
        QString cr = sData.mid(sPos,20);
        if(cr.contains("\n"))
        {
            sPos +=2;
        }
        // auto shotNo  = sData.mid(sPos+20,sPos+5);
        auto shotNos = sData.mid(sPos+20,5).toInt();
        sPos +=27;
        cr = sData.mid(sPos,20);
        if(cr.contains("\n"))
        {
            sPos +=2;
        }
        auto shotx = sData.mid(sPos,8).toFloat();
        icount +=sPos+1;
        //     cout << shotNos << endl;
        cout << " shot " << shotNos << " " << shotx << " "  << shotNos << endl;
    }
    //        QString oData(data);
    //        int idx = oData.indexOf('\n');

    //       QString ooData = oData.mid(idx+1,80);
    //       QString oooData = oData.mid(0,idx-1);
    //       oooData.append(ooData);
    //        cout << oData.toStdString()  <<endl;
    //       // ukOut->write(oooData.toLatin1().data(),80);
    //      //  ukOut->write("\n",1);
    //        icount++;
    // //   }
    //    ukOut->flush();
    //    ukOut->close();
    return a.exec();

}
