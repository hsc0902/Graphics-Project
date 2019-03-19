#include"myitem.h"
#define pi 3.1415926535

int shape_index=0;
int mode_index=0;
int fill_index=0;
int cut_index=0;
QPen pen_total;
QImage fillmap;

Myitem::Myitem(QGraphicsItem *parent): QGraphicsItem(parent)
{
    item_shape=-1;
    points_num=0;
    isdrawing=false;
    iscutting=false;
    bezier_adding=false;
    selected_point_index=-1;
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

int Myitem::type() const
{
    return UserType + 1;
}

QRectF Myitem::boundingRect() const
{
    if(points_num>1)
    {
        qreal penWidth = 1;
        double left_bound=points[0].x();
        double up_bound=points[0].y();
        double right_bound=0;
        double down_bound=0;
        for(int i=0; i<points_num; i++)
        {
            left_bound=min(left_bound,points[i].x());
            up_bound=min(up_bound,points[i].y());
        }
        for(int i=0; i<points_num; i++)
        {
            right_bound=max(right_bound,points[i].x()-left_bound);
            down_bound=max(down_bound,points[i].y()-up_bound);
        }
        return QRectF(left_bound-penWidth/2-10, up_bound-penWidth/2-10, right_bound+penWidth+20, down_bound+penWidth+20);
    }
    else
    {
        return QRectF(-1, -1, 0, 0);       
    }
}

/*
QPainterPath Myitem::shape() const
{
    QPainterPath path;
    if(item_shape==5)
    {
        path.addRect(boundingRect());
        return path;
    }
    if(item_shape==1)
    {
        QPolygonF polygon;
        if((points[1].y()-points[0].y())/(points[1].x()-points[0].x())>-1&&(points[1].y()-points[0].y())/(points[1].x()-points[0].x())<1)
        {
            for(int i=0;i<points_num;i++)
            {
                QPointF point=points[i];
                point.ry()=points[i].y()+30;
                polygon.append(point);
            }
            for(int i=points_num-1;i>=0;i--)
            {
                QPointF point=points[i];
                point.ry()=points[i].y()-30;
                polygon.append(point);
            }
        }
        else
        {
            for(int i=0;i<points_num;i++)
            {
                QPointF point=points[i];
                point.rx()=points[i].x()+30;
                polygon.append(point);
            }
            for(int i=points_num-1;i>=0;i--)
            {
                QPointF point=points[i];
                point.rx()=points[i].x()-30;
                polygon.append(point);
            }
        }
        path.addPolygon(polygon);
    }
    else if(item_shape==2)
    {
       path.addEllipse(boundingRect());
    }
    else if(item_shape==3)
    {
        path.addEllipse(boundingRect());
    }
    else if(item_shape==4)
    {
        QPolygonF polygon;
        for(int i=0;i<points_num;i++)
        {
            polygon.append(points[i]);
        }
        path.addPolygon(polygon);
    }
    else if(item_shape==9)
    {
        path.addRect(boundingRect());
    }
    for(int i=0;i<points_num;i++)
    {
        QRectF rect(points[i].x()-20,points[i].y()-20,40,40);
        path.addRect(rect);
    }
    return path;
}
*/

void Myitem::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(item_shape==1)//直线
    {
        if(points_num==2)
        {
            paintline(painter, points[0].x(), points[0].y(), points[1].x(), points[1].y());
            if(isdrawing==true||isSelected()||iscutting==true)
            {
                paintexcircle(painter, points[0].x(), points[0].y(), 5, 10);
                paintexcircle(painter, points[1].x(), points[1].y(), 5, 10);
            }
        }
    }
    else if(item_shape==2)//圆
    {
        if(points_num==2)
        {
            paintcircle(painter, points[0].x(), points[0].y(), points[1].x(), points[1].y());
            if(isdrawing==true||isSelected()||iscutting==true)
            {
                paintexcircle(painter, points[0].x(), points[0].y(), 5, 10);
                paintexcircle(painter, points[1].x(), points[1].y(), 5, 10);
                paintRect(painter,points[0].x(), points[0].y(), points[1].x(), points[1].y());
            }
        }
    }
    else if(item_shape==3)//椭圆
    {
        if(points_num==2)
        {
            paintellipse(painter, points[0].x(), points[0].y(), points[1].x(), points[1].y());
            if(isdrawing==true||isSelected()||iscutting==true)
            {
                paintexcircle(painter, points[0].x(), points[0].y(), 5, 10);
                paintexcircle(painter, points[1].x(), points[1].y(), 5, 10);
                paintRect(painter,points[0].x(), points[0].y(), points[1].x(), points[1].y());
            }
        }
    }
    else if(item_shape==4)//多边形
    {
        if(points_num>=2)
        {
            for(int i=0;i<points_num-1;i++)
            {
                paintline(painter, points[i].x(), points[i].y(), points[i+1].x(), points[i+1].y());
            }
            if(isdrawing==false)
            {
                paintline(painter, points[points_num-1].x(), points[points_num-1].y(), points[0].x(), points[0].y());
            }
            if(isSelected()||isdrawing==true||iscutting==true)
            {
                for(int i=0;i<points_num;i++)
                {
                    paintexcircle(painter, points[i].x(), points[i].y(), 5, 10);
                }
            }
        }
    }
    else if(item_shape==5)//曲线
    {
        paintbezier(painter,points,points_num);
        if(isSelected()||isdrawing==true||iscutting==true||bezier_adding==true)
        {
            for(int i=0;i<points_num;i++)
            {
                paintexcircle(painter, points[i].x(), points[i].y(), 5, 10);
            }
        }
    }
    else if(item_shape==9)//裁剪框
    {
        if(points_num==2)
        {
            paintRect(painter,points[0].x(), points[0].y(), points[1].x(), points[1].y());
        }
    }
    else
        return;
}

void Myitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            setSelected(true);
            event->ignore();
        }
        else if (event->modifiers() == Qt::AltModifier)
        {

        }
        else
        {
            for(int i=0; i<points_num; i++)
            {
                double x0=points[i].x();
                double y0=points[i].y();
                double x=event->scenePos().x();
                double y=event->scenePos().y();
                if(sqrt(pow(x-x0,2)+pow(y-y0,2))<10)
                {
                    selected_point_index=i;
                }
            }
            if(mode_index==1&&item_shape==4&&selected_point_index!=-1&&isdrawing==true)//多边形绘制
            {
                points[points_num]=points[points_num-1];
                points_num++;
            }
            from_point=event->scenePos();
            center_point.rx()=boundingRect().x()+boundingRect().width()/2;
            center_point.ry()=boundingRect().y()+boundingRect().height()/2;
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        event->ignore();
    }
}

void Myitem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    fillmap.fill(Qt::white);
    if(mode_index==1&&item_shape==4&&selected_point_index!=-1&&isdrawing==true)//多边形绘制
    {
        points[points_num-1]=event->scenePos();
        update();
        center_point.rx()=boundingRect().x()+boundingRect().width()/2;
        center_point.ry()=boundingRect().y()+boundingRect().height()/2;
        event->accept();
    }
    else if(selected_point_index!=-1&&isdrawing==false)//编辑
    {
        points[selected_point_index]=event->scenePos();
        update();
        center_point.rx()=boundingRect().x()+boundingRect().width()/2;
        center_point.ry()=boundingRect().y()+boundingRect().height()/2;
        event->accept();
    }
    else if(selected_point_index==-1&&event->modifiers() != Qt::AltModifier)//平移
    {
        double delta_x=event->scenePos().x()-from_point.x();
        double delta_y=event->scenePos().y()-from_point.y();
        for(int i=0; i<points_num; i++)
        {
            points[i].rx()=delta_x+points[i].x();
            points[i].ry()=delta_y+points[i].y();
        }
        from_point=event->scenePos();
        update();
        center_point.rx()=boundingRect().x()+boundingRect().width()/2;
        center_point.ry()=boundingRect().y()+boundingRect().height()/2;
        event->accept();
    }
    else if(event->modifiers() == Qt::AltModifier)//旋转
    {
        QPointF v1,v2;
        v1.rx()=from_point.x()-center_point.x();
        v1.ry()=from_point.y()-center_point.y();
        v2.rx()=event->scenePos().x()-center_point.x();
        v2.ry()=event->scenePos().y()-center_point.y();
        double Theta=atan2(v2.y(),v2.x())-atan2(v1.y(),v1.x());
        if(Theta>pi)
            Theta=Theta-pi*2;
        if(Theta<-1*pi)
            Theta=Theta+pi*2;
        if(item_shape==1||item_shape==4||item_shape==5)
        {
            for(int i=0; i<points_num; i++)
            {
                double x0=points[i].x();
                double y0=points[i].y();
                points[i].rx()=center_point.x()+((x0-center_point.x())*cos(Theta))-((y0-center_point.y())*sin(Theta));
                points[i].ry()=center_point.y()+((x0-center_point.x())*sin(Theta))+((y0-center_point.y())*cos(Theta));
            }
        }
        /*if(item_shape==3)
        {
            if(Theta>0) {
                //Theta=pi/2;
                for(int i=0; i<points_num; i++)
                {
                    double x0=points[i].x();
                    double y0=points[i].y();
                    points[i].rx()=center_point.x()+((x0-center_point.x())*cos(Theta))-((y0-center_point.y())*sin(Theta));
                    points[i].ry()=center_point.y()+((x0-center_point.x())*sin(Theta))+((y0-center_point.y())*cos(Theta));
                }
            }
            else if(Theta<0) {
                //Theta=-pi/2;
                for(int i=0; i<points_num; i++)
                {
                    double x0=points[i].x();
                    double y0=points[i].y();
                    points[i].rx()=center_point.x()+((x0-center_point.x())*cos(Theta))-((y0-center_point.y())*sin(Theta));
                    points[i].ry()=center_point.y()+((x0-center_point.x())*sin(Theta))+((y0-center_point.y())*cos(Theta));
                }
            }
        }*/
        from_point=event->scenePos();
        update();
        event->accept();
    }
}

void Myitem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(mode_index==1&&selected_point_index!=-1&&isdrawing==true)//多边形绘制
        {
            points[points_num-1]=event->scenePos();
            if(points[points_num-1]==points[points_num-2])
                points_num--;
            else if(sqrt(pow(points[points_num-1].x()-points[0].x(),2)+pow(points[points_num-1].y()-points[0].y(),2))<10)
            {
                points_num--;
                isdrawing=false;
                selected_point_index=-1;
            }
            update();
            event->accept();
        }
        else if(selected_point_index!=-1&&isdrawing==false)
        {
            selected_point_index=-1;
            update();
        }
        else if(selected_point_index==-1)//平移
        {
            selected_point_index=-1;
            update();
        }

    }
}

void Myitem::wheelEvent(QGraphicsSceneWheelEvent*event)
{
    int delta=event->delta();
    double zoom_factor;
    if(delta==120)
        zoom_factor=1.1;
    else
        zoom_factor=0.9;
    double x0=center_point.x();
    double y0=center_point.y();
    for(int i=0; i<points_num; i++)
    {
        points[i].rx()=points[i].x()*zoom_factor+x0*(1-zoom_factor);
        points[i].ry()=points[i].y()*zoom_factor+y0*(1-zoom_factor);
    }
    update();
    event->accept();
}
