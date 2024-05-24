#include "Rectangle.h"

MyRectangle::MyRectangle():
        angle(0),step_angle(1),
        x_center(0), y_center(0)
{
    QPen pen;
    QBrush brush1;
    brush1.setColor(Qt::black);
    brush1.setStyle(Qt::SolidPattern);
    pol1 << QPoint(x_center-50,y_center-3) << QPoint(x_center-50,y_center+3) << QPoint(x_center+50,y_center+3) << QPoint(x_center+50,y_center-3);

    QBrush brush2;
    brush2.setColor(Qt::gray);
    brush2.setStyle(Qt::SolidPattern);

    pol2 << QPoint(x_center-50,0) << QPoint(x_center-50,y_center-50) <<
           QPoint(x_center-100,y_center-50) << QPoint(x_center-120,y_center+50) <<
           QPoint(x_center-50,y_center+50);

    pol3 << QPoint(x_center+50,0) << QPoint(x_center+50,y_center-50) <<
           QPoint(x_center+100,y_center-50) << QPoint(x_center+120,y_center+50) <<
           QPoint(x_center+50,y_center+50);

    scene = new QGraphicsScene;
    p1 = scene->addPolygon(pol1, pen, brush1);
    p2 = scene->addPolygon(pol2, pen, brush2);
    p3 = scene->addPolygon(pol3, pen, brush2);


    QPolygon pol4;
    brush1.setColor(Qt::red);
    pol4 << QPoint(x_center-110,y_center+50) << QPoint(x_center-85,y_center+80) << QPoint(x_center-60,y_center+50);
    p4 = scene->addPolygon(pol4, pen, brush1);

    brush1.setColor(Qt::cyan);
    scene->addEllipse(x_center, y_center, 3, 3);
    scene->addEllipse(x_center, y_center-50, 3, 3);
    brush1.setColor(Qt::red);
    QPolygon pol5;
    pol5 << QPoint(x_center+110,y_center+50) << QPoint(x_center+85,y_center+80) << QPoint(x_center+60,y_center+50);
    p5 = scene->addPolygon(pol5, pen, brush1);
}

void MyRectangle::rotate_left()
{
    angle -= step_angle;

    update_rectangle();
}

void MyRectangle::rotate_right()
{
    angle += step_angle;
    update_rectangle();
}

void MyRectangle::update_rectangle()
{
    p1->setRotation(angle);
    p2->setRotation(angle);
    p3->setRotation(angle);
    p4->setRotation(angle);
    p5->setRotation(angle);
    scene->update();
}

void MyRectangle::update_color(int num, QColor color){
    QBrush brush;
    QPen pen;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    switch (num) {
        case 1:
            p2 = scene->addPolygon(pol2,pen,brush);
            break;
        case 2:
            p3 = scene->addPolygon(pol3,pen,brush);
            break;
    }
}
