#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QtDebug>
#include <QKeyEvent>
#include "myitem.h"
#include <QStack>

class Myscene : public QGraphicsScene
{
public:
    explicit Myscene(QGraphicsScene *parent = 0);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent*event);
    void keyPressEvent(QKeyEvent *event);
private:
    Myitem* Myitem_creating;
    QStack<Myitem*> Myitems;
    Myitem* cut_item;

    void fillpoint(int x, int y);//图元填充递归
    int over_flag;
    QImage scenemap;
    QStack<QPoint> fillpoints;
};

#endif // MYSCENE_H
