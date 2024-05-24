#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h" // Подключаем заголовочный файл библиотеки QCustomPlot
#include <QTimer>
#include <QKeyEvent>
#include "Rectangle.h"
#include "solver_sde.h"

#define TIME_STEP 100

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
    int time;
    QCheckBox *checkbox; // Запуск и остановка таймера

    QVector<double> xData,yData,tData;
    QCustomPlot *phasePlot;
    double x,y;
    double t_step;
    int currentIndex;

    void initGraphs();

    MyRectangle *rect;
    Solver_sde *solv;
};




#endif // MAINWINDOW_H
