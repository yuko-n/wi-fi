#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <cmath>
#include <QList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    double getDBm (int i, int j, int x, int y);
    double PL1 (double d3d, double h);
    double PL2 (double dBP, double h, double d3d);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
