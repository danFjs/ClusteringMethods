#include "chartview.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QTimer>
#include <QtMath>
#include <QtCore/QRandomGenerator>
#include <QApplication>
using namespace std;
ChartView::ChartView(QWidget *parent):
    QChartView(new QChart(), parent)
{
    this->setMouseTracking(true);

    /*QScatterSeries *series0 = new QScatterSeries();

    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);


    QScatterSeries *series2 = new QScatterSeries();
    series2->setName("scatter2");
    series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series2->setMarkerSize(15.0);


    _timer = new QTimer();


connect(_timer, &QTimer::timeout, this, [series0, this]()
{
    series0->append(_x++, QRandomGenerator::global()->bounded(10));
});

_timer->start(1000);


    *series2 << QPointF(1, 5) << QPointF(4, 6) << QPointF(6, 3) << QPointF(9, 5);


    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);
    chart()->addSeries(series2);

    chart()->setTitle("DisplayChart");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);

    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);*/
}

void ChartView::addToChart(const vector<vector< float> > inputPoints,const QRgb color){
    QScatterSeries *inputSeries = new QScatterSeries;
    inputSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    inputSeries->setMarkerSize(15.0);
    inputSeries->color().setRgb(color);
    for(int i=0; i<inputPoints.size();++i){

            inputSeries->append(inputPoints[i][0],inputPoints[i][1]);

    }
    setRenderHint(QPainter::Antialiasing);
    chart() ->addSeries(inputSeries);
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);



}

void ChartView::addToChart(const vector<vector< float> > inputPoints){
    QScatterSeries *inputSeries = new QScatterSeries;
    inputSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    inputSeries->setMarkerSize(15.0);
    for(int i=0; i<inputPoints.size();++i){

            inputSeries->append(inputPoints[i][0],inputPoints[i][1]);

    }
    setRenderHint(QPainter::Antialiasing);
    chart() ->addSeries(inputSeries);
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);



}
void ChartView::repaint(const vector<vector< float> > inputPoints, QRgb color){
    QScatterSeries *inputSeries = new QScatterSeries;
    inputSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    inputSeries->setMarkerSize(15.0);
    inputSeries->color().setRgb(color);
    for(int i=0; i<inputPoints.size();++i){

            inputSeries->append(inputPoints[i][0],inputPoints[i][1]);

    }
    setRenderHint(QPainter::Antialiasing);
    chart() ->addSeries(inputSeries);
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);



}
void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QApplication::setOverrideCursor(QCursor(Qt::SizeAllCursor));
        m_lastMousePos = event->pos();
        event->accept();
    }
    if (event->button() == Qt::MiddleButton)
    {
        chart()->zoomReset();
        event->accept();
    }

    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
            {
                auto dPos = event->pos() - m_lastMousePos;
                chart()->scroll(-dPos.x(), dPos.y());

                m_lastMousePos = event->pos();
                event->accept();

                QApplication::restoreOverrideCursor();
            }

    QChartView::mouseMoveEvent(event);
}
void ChartView::wheelEvent(QWheelEvent* event){
    float delta = event->angleDelta().y();
    if(delta > 0){
        chart()->zoomIn();
    }else if(delta <0){
        chart()->zoomOut();
    }

    QChartView::wheelEvent(event);
}
