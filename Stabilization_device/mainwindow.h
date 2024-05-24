#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h" // Подключаем заголовочный файл библиотеки QCustomPlot
#include <QTimer>
#include <QKeyEvent>
#include "Rectangle.h"
#include "solver_sde.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: // Слоты для наших сигналов
    void updateGraphs();
    void onCheckboxStateChanged(int state);
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int time, time_moment;
    bool active;
    QCheckBox *checkbox; // Запуск и остановка таймера

    QVector<double> xData,yData,tData;
    QCustomPlot *phasePlot;
    double x,y;
    double step;
    int currentIndex;

    void initGraphs();

    MyRectangle *rect;
    Solver_sde *solv;
};




#endif // MAINWINDOW_H
