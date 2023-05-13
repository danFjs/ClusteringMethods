#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include <iostream>
#include <QtCharts/QChartView>
using namespace std;
QT_CHARTS_USE_NAMESPACE


class ChartView: public QChartView
{
    Q_OBJECT

public:
    explicit ChartView(QWidget *parent = 0);
    void addToChart(const int &x,const int &y);
    void addToChart(const vector<vector< float> > inputPoints);
    void addToChart(const vector<vector< float> > inputPoints, QRgb color);
    void repaint(const vector<vector< float> > inputPoints, QRgb color);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
private:
     QPointF m_lastMousePos;

};

#endif // CHARTVIEW_H
