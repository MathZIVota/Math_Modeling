#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TIME_STEP 100
#define TIME_INTERVAL 1500

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      x(1.0), y(0.0), step(0.01), currentIndex(0)
//       active(false)
{
    ui->setupUi(this);
    initGraphs(); // Вызовем функцию отрисовки графиков

    timer = new QTimer(this);
    time = 0;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGraphs()));
    timer->start(TIME_STEP);

    checkbox = ui->Pusk;
    checkbox->setChecked(true);
    connect(checkbox, &QCheckBox::stateChanged, this, &MainWindow::onCheckboxStateChanged);

    ui->label->clear();
    ui->label_2->clear();

    rect = new MyRectangle;
    ui->graphicsView->setScene(rect->scene);
    solv = new Solver_sde;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGraphs()
{
    // Создание графика
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(tData, xData);
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->yAxis->setLabel("x");
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();

    // Создаем второй график для фазового портрета
    phasePlot = new QCustomPlot(this);
    phasePlot->addGraph();
    phasePlot->graph(0)->setLineStyle(QCPGraph::lsNone); // Устанавливаем стиль линии
    phasePlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,1)); // Устанавливаем стиль точки
    phasePlot->graph(0)->setData(xData, yData);
    phasePlot->xAxis->setLabel("x");
    phasePlot->yAxis->setLabel("y");
    phasePlot->xAxis->setRange(-1.5,1.5);
    phasePlot->yAxis->setRange(-1.5,1.5);
    //для вызова обновления оси y, phasePlot->yAxis->rescale();
    //для вызова обновления обеих осей, phasePlot->rescaleAxes();

    phasePlot->replot();
    ui->verticalLayout->addWidget(phasePlot);
}



/*
void MainWindow::plotGraphs()
{
    double x = 1.0, y = 0.0; // Начальные условия
    double step = 0.01; // Шаг интегрирования
    QVector<double> xData, yData, tData; // Массивы для хранения данных

    for (int t = 0; t <= 2000; ++t) // Примерное количество итераций
    {
        xData.push_back(x);
        yData.push_back(y);
        tData.push_back(t * step);
        eulerMethod(x, y, step);
    }

    // Создание графика
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(tData, xData);
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->yAxis->setLabel("x");
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();

    // Создаем второй график для фазового портрета
    QCustomPlot *phasePlot = new QCustomPlot(this);
    phasePlot->addGraph();
    phasePlot->graph(0)->setData(xData, yData);
    phasePlot->xAxis->setLabel("x");
    phasePlot->yAxis->setLabel("y");
    phasePlot->rescaleAxes();
    phasePlot->replot();

    ui->verticalLayout->addWidget(phasePlot); // Добавляем фазовый портрет в layout
}*/

void MainWindow::updateGraphs() // Новая функция
{
    rect->p4->setVisible(false);
    rect->p5->setVisible(false);
    solv->eulerMethod(x, y, rect->angle, step);
    rect->update_rectangle();
    /*rect->p1->setPos(x,y);
    rect->p2->setPos(x,y);
    rect->p3->setPos(x,y);*/
    ui->label_2->setText(QString::number(90-rect->angle)+" "+QString::number(3.14/180*(90-rect->angle)));

    xData.push_back(x);
    yData.push_back(y);
    tData.push_back(currentIndex * step);
    currentIndex++;

    ui->customPlot->graph(0)->addData(tData.last(), xData.last());
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();

    //phasePlot->graph(0)->clearData();

    phasePlot->graph(0)->addData(xData.last(), yData.last());
    phasePlot->rescaleAxes();
    //phasePlot->yAxis->rescale();
    phasePlot->replot();

    ui->label->setText(QString::number((double)time/1000)+" sec");

    time += TIME_STEP;
}

void MainWindow::onCheckboxStateChanged(int state)
{
    // Функция изменения состояния чекбокса.
    if (state == Qt::Checked) {
        timer->start(); // Если чекбокс активен, запускаем таймер
        checkbox->setText("Запущен");
    } else {
        timer->stop(); // Если неактивен, останавливаем таймер
        checkbox->setText("Отключен");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    QBrush brush;
    brush.setColor(Qt::red);
    switch (event->key()) {
        case Qt::Key_Right:
            solv->f1 += solv->u1;
            rect->p4->setVisible(true);
            //rect->update_color(1,Qt::red);
            break;
        case Qt::Key_Left:
            solv->f2 += solv->u2;
            rect->p5->setVisible(true);
            //rect->update_color(2,Qt::red);
            break;
    }

    //rect->update_color(1,Qt::blue);
    //rect->update_color(2,Qt::blue);
}

