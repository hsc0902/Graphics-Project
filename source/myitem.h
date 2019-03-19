#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QPen>
#include "draw.h"
#include <QGraphicsItem>
#include <math.h>

extern int shape_index;
extern int mode_index;
extern int fill_index;
extern int cut_index;
extern QPen pen_total;
extern QImage fillmap;


#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

class Myitem : public QGraphicsItem
{
public:
    explicit Myitem(QGraphicsItem *parent = 0);
protected:
    //QPainterPath shape()const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent*event);
    int type() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
public:
    int item_shape;
    QPointF points[100];
    int points_num;
    bool isdrawing;
    bool iscutting;
    bool bezier_adding;
    int selected_point_index;
    QPointF from_point;
    QPointF center_point;
};

#endif // MYITEM_H
