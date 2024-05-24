#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <QGraphicsScene>
#include <QPoint>
#include <QTransform>
#include <QPainter>
#include <QObject>
#include <iostream>
#include <QGraphicsPolygonItem>
#include <QKeyEvent>

class MyRectangle : public QGraphicsScene
{
public:
    MyRectangle();
    QGraphicsScene *scene;
    QPolygon pol1, pol2, pol3;
    QGraphicsPolygonItem *p1, *p2, *p3, *p4, *p5;
    double angle;
    double step_angle;
    double x_center, y_center;

    void rotate_left();
    void rotate_right();
    void update_rectangle();
    void update_color(int num, QColor color);
};

#endif // RECTANGLE_H
