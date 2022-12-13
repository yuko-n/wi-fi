#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int map_size = 1000;
    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap map(map_size, map_size);
    QPainter p(&map);

    for(int i = 0; i < map_size; i++){
        for(int j = 0; j < map_size; j++){
            double dBm = getDBm(i, j, 430, 509);
            if (dBm <= 44)
            {
                p.setPen(QColor(255, 14, 0));
            }
            else if (dBm > 44 && dBm <= 54)
            {
                p.setPen(QColor(255, 123, 0));
            }
            else if (dBm > 54 && dBm <= 64)
            {
                p.setPen(QColor(255, 235, 0));
            }
            else if (dBm > 64 && dBm <= 74)
            {
                p.setPen(QColor(127, 255, 0));
            }
            else if (dBm > 74 && dBm <= 84)
            {
                p.setPen(QColor(0, 255, 26));
            }
            else if (dBm > 84 && dBm <= 94)
            {
                p.setPen(QColor(0, 255, 144));
            }
            else if (dBm > 94 && dBm <= 104)
            {
                p.setPen(QColor(0, 255, 251));
            }
            else if (dBm > 104 && dBm <= 114)
            {
                p.setPen(QColor(0, 162, 255));
            }
            else if (dBm > 114 && dBm <= 124)
            {
                p.setPen(QColor(0, 73, 255));
            }
            else if (dBm > 124 && dBm <= 134)
            {
                p.setPen(QColor(3, 0, 255));
            }
            else if (dBm > 134)
            {
                p.setPen(QColor(Qt::black));
            }
            p.drawPoint(i, j);
        }
    }

    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

double MainWindow::PL1 (double d3d, double h)
{
    return (20*(log10(40 * 3.14 * d3d * 2.4/3)) + qMin((0.03 * pow(h, 1.72)), 10.0) * log10(d3d) - qMin((0.044 * pow(h, 1.72)), 14.77) + (0.002 * log10(h) * d3d));
}

double MainWindow::PL2 (double dBP, double h, double d3d)
{
    double pl1 = PL1(dBP, h);
    return (pl1 + 40*log10(d3d/dBP));
}

double MainWindow::getDBm (int x1, int y1, int x2, int y2)
{
    const double hBS = 150;
    const double hUT = 10;
    const double h = 50;
    double d3d = qSqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    double d2d = qSqrt(fabs(pow(d3d, 2) - pow((hBS-hUT), 2)));
    double dBP = (2 * 3.14 * hBS * hUT * 2.4 * pow(10, 9)) / (3 * pow(10, 8));


    if (d2d < 10)
    {
        return 1;
    }
    else if (d2d >= 10.0 && d2d <= dBP)
    {
        return PL1(d3d, h);
    }
    else if (d2d >= dBP && d2d <= 10000.0)
    {
        return PL2(dBP, h, d3d);
    }
    else
    {
        return 199;
    }

}
MainWindow::~MainWindow()
{
}

