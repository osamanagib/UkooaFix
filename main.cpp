#include <QApplication>
#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <qwt_matrix_raster_data.h>
#include <qwt_color_map.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_symbol.h>
#include <qwt_scale_widget.h>
#include <qwt_wheel.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include <qwt_picker_machine.h>
#include <QPushButton>
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

    //  QGuiApplication a(argc, argv);
    QApplication a(argc, argv);
    QwtPlot *plot = new QwtPlot();
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setBorderRadius(10);

    plot->setCanvas(canvas);
    plot->setCanvasBackground(QColor("LIGHTGRAY"));

    plot->enableAxis(QwtPlot::yRight);
    plot->enableAxis(QwtPlot::xTop);
    plot->setAxisTitle(QwtPlot::xBottom, "Xline");
    plot->setAxisTitle(QwtPlot::xTop, "Xline");
    plot->setAxisTitle(QwtPlot::yLeft, "Inline");
    plot->setAxisTitle(QwtPlot::yRight, "Inline");
    //    float minx = srv->getStations().first().x();
    //    float maxx = srv->getStations().last().x();
        plot->setAxisScale( QwtPlot::xBottom,3500,300);
    //    plot->setAxisScale( QwtPlot::xTop,minx,maxx );
    //    QwtScaleDraw *sd = axisScaleDraw( QwtPlot::yLeft );
    //    sd->setMinimumExtent( sd->extent( axisWidget( QwtPlot::yLeft )->font() ) );
    plot->plotLayout()->setAlignCanvasToScales( true );
    QFileDialog custDialog;
    QStringList names = custDialog.getOpenFileNames(NULL, ("Open Files..."),QString(), ("UKOOA Files (*.p190 *.p90);;All Files (*)"));

    // handle if the dialog was "Cancelled"
    if(names.isEmpty())
    {
        return 0;
    }
    qSort(names.begin(), names.end());
    QVector <QwtPlotCurve *> curves;
    foreach (QString name, names)
    {


        QwtPlotCurve *vCurve = new QwtPlotCurve;
       if(name.contains(QString( "NS1763")) || name.contains(QString("NS2029")))
        {
           QColor c = Qt::red;
            vCurve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::red,c , QSize( 2, 2 ) ) );
        }
        else
        {
           QColor c = Qt::green;
            vCurve->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::green,c , QSize( 2, 2 ) ) );
        }
        vCurve->setStyle( QwtPlotCurve::NoCurve );
        vCurve->setPen( Qt::gray );

        cout << name.toStdString() << endl;
        QVector<QPointF> curveData;

        //  m_nameLineLable->setText(m_names.at(0));
        QFile *ukFile = new QFile(QString(name));

        bool rt = ukFile->open(QIODevice::ReadOnly);

        cout << "return " << rt << endl;

        qint64 icount = 0;

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
            if(icount>=fileSize)
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
            QString shotNo = sData.mid(sPos+20,5);
            int shotNos;

            if(shotNo.contains("\n") || shotNo.contains("\r"))
            {
                shotNo = sData.mid(sPos+20,7);
                int shift1 = shotNo.indexOf("\r");
                int shift = shotNo.indexOf("\n");
                //    cout << shift1 << " " << shift << endl;
                QString tmp = shotNo.mid(0,shift1);
                tmp.append(shotNo.mid(shift+1,2));
                shotNos = tmp.toInt();
            }
            else
            {
                shotNos = sData.mid(sPos+20,5).toInt();
            }

            float shotYs;
            sPos = sData.indexOf(shot,0,Qt::CaseInsensitive);
            cr = sData.mid(sPos,56);
            if(cr.contains("\n"))
            {
                //       cout << " cr " << sPos << endl;
                sPos +=2;
            }

            QString shotY = sData.mid(sPos+56,9);
            //   cout << "shotx " << shotX.toStdString() << endl;
            if(shotY.contains("\n") || shotY.contains("\r"))
            {
                shotY = sData.mid(sPos+56,11);
                int shift1 = shotY.indexOf("\r");
                int shift = shotY.indexOf("\n");
                //           cout << shift1 << " " << shift << endl;
                QString tmp = shotY.mid(0,shift1);
                tmp.append(shotY.mid(shift+1,11));
                shotYs = tmp.toFloat();
            }
            else
            {
                shotYs = shotY.toFloat();
            }

            float shotXs;
            sPos = sData.indexOf(shot,0,Qt::CaseInsensitive);
            cr = sData.mid(sPos,47);
            if(cr.contains("\n"))
            {
                //       cout << " cr " << sPos << endl;
                sPos +=2;
            }

            QString shotX = sData.mid(sPos+47,9);
            //   cout << "shotx " << shotX.toStdString() << endl;
            if(shotX.contains("\n") || shotX.contains("\r"))
            {
                shotX = sData.mid(sPos+47,11);
                int shift1 = shotX.indexOf("\r");
                int shift = shotX.indexOf("\n");
                //           cout << shift1 << " " << shift << endl;
                QString tmp = shotX.mid(0,shift1);
                tmp.append(shotX.mid(shift+1,11));
                shotXs = tmp.toFloat();
            }
            else
            {
                shotXs = shotX.toFloat();
            }
            icount +=sPos+1;
            //     cout << shotNos << endl;
            float shotXt = shotXs - 757551.46;


            float shotYt = shotYs - 978769.0;
            float shotYr = shotYt * cosf(13.661f * M_PI/180.0f) + shotXt * sinf(13.661f * M_PI/180.0f);
            int shotYy = 981 + shotYr/25.0;
            float shotXr = shotXt * cosf(13.661f * M_PI/180.0f) - shotYt * sinf(13.661f * M_PI/180.0f);
            int shotXx = 2570 - shotXr/25.0;
            if(shotXx>0 && shotYy>0)
            {
                QPointF shotPoint(shotXx,shotYy);
                curveData.append(shotPoint);
              //  cout << " shot " << shotNos << " " << shotXs  << " " << shotYs << " "  << shotXx << " " << shotYy << endl;
            }



        }
        vCurve->setSamples(curveData);
        curves.append(vCurve);
        ukFile->close();
    }



    foreach (QwtPlotCurve *vCurve, curves)
    {

        vCurve->attach(plot);
    }

    //vCurve->setSamples();

    plot->replot();
    plot->show();

    return a.exec();

}
