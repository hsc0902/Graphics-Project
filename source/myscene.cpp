#include <myscene.h>
Myscene::Myscene(QGraphicsScene *parent): QGraphicsScene(parent)
{
    cut_item=NULL;
    over_flag=0;
    scenemap=QImage(1260,540, QImage::Format_RGB32);
    fillmap=QImage(1260,540, QImage::Format_RGB32);
    fillmap.fill(Qt::white);
    scenemap.fill(Qt::white);
}

void Myscene::fillpoint(int x, int y)
{
    if((QColor)fillmap.pixel(x,y)==Qt::white&&(QColor)scenemap.pixel(x,y)==Qt::white)
    {
        QPoint point;
        point.rx()=x;
        point.ry()=y;
        QPainter painter;
        painter.begin(&fillmap);
        fillpoints.push(point);
        while(!fillpoints.empty())
        {
            QPoint point_pop;
            point_pop=fillpoints.pop();
            int a=point_pop.x();
            int b=point_pop.y();
            if(a<0||b<0||a>=1260||b>=540)
            {
                over_flag=1;
                fillpoints.clear();
                return;
            }
            if(a-1<0||b-1<0||a+1>=1260||b+1>=540)
            {
                over_flag=1;
                fillpoints.clear();
                return;
            }
            painter.setPen(pen_total);
            painter.drawPoint(a,b);
            if((QColor)fillmap.pixel(a,b-1)==Qt::white&&(QColor)scenemap.pixel(a,b-1)==Qt::white)
            {
                QPoint point_push3;
                point_push3.rx()=a;
                point_push3.ry()=b-1;
                fillpoints.push(point_push3);
            }
            if((QColor)fillmap.pixel(a-1,b)==Qt::white&&(QColor)scenemap.pixel(a-1,b)==Qt::white)
            {
                QPoint point_push1;
                point_push1.rx()=a-1;
                point_push1.ry()=b;
                fillpoints.push(point_push1);
            }
            if((QColor)fillmap.pixel(a,b+1)==Qt::white&&(QColor)scenemap.pixel(a,b+1)==Qt::white)
            {
                QPoint point_push4;
                point_push4.rx()=a;
                point_push4.ry()=b+1;
                fillpoints.push(point_push4);
            }
            if((QColor)fillmap.pixel(a+1,b)==Qt::white&&(QColor)scenemap.pixel(a+1,b)==Qt::white)
            {
                QPoint point_push2;
                point_push2.rx()=a+1;
                point_push2.ry()=b;
                fillpoints.push(point_push2);
            }
        }
        painter.end();
    }

}

void Myscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setBackgroundBrush(fillmap);
    update();
    if(fill_index==1)//填充
    {
        scenemap.fill(Qt::white);
        QPainter painter1;
        painter1.begin(&scenemap);
        render(&painter1);
        painter1.end();
        QImage temp=fillmap;
        fillpoint(event->scenePos().x(), event->scenePos().y());
        if(over_flag==1)
        {
            fillmap=temp;
            over_flag=0;
        }
        else
        {
            setBackgroundBrush(fillmap);
            update();
        }
        return;
    }
    QGraphicsScene::mousePressEvent(event);
    update();
    if(!Myitems.empty()&&Myitems.top()->isdrawing==true)
        return;
    if (!event->isAccepted())
    {
        if (event->button() == Qt::LeftButton)
        {
            if (mode_index==1&&event->modifiers()!=Qt::ControlModifier)
            {
                QPointF point = event->scenePos();
                Myitem_creating = new Myitem();
                Myitem_creating->isdrawing=true;
                Myitem_creating->item_shape=shape_index;
                Myitem_creating->points[0]=point;
                Myitem_creating->points_num++;
                addItem(Myitem_creating);
            }
            else if(mode_index==1&&event->modifiers()==Qt::ControlModifier)
            {
                if(!selectedItems().empty())
                {
                    Myitem *item= dynamic_cast<Myitem*>(selectedItems().front());
                    if(item->item_shape==5)
                    {
                        item->points_num++;
                        item->points[item->points_num-1]=item->points[item->points_num-2];
                        item->points[item->points_num-2]=event->scenePos();
                        update();
                    }
                }
            }
            else if(cut_index==1&&event->modifiers()==Qt::ControlModifier)
            {
                if(!selectedItems().empty())
                {
                    foreach (QGraphicsItem *item, items())
                    {
                        if(item!=selectedItems().front())
                        item->setVisible(false);
                    }
                    cut_item= dynamic_cast<Myitem*>(selectedItems().front());
                    cut_item->iscutting=true;
                    update();
                }
            }
            else if(cut_index==1)
            {
                QPointF point = event->scenePos();
                Myitem_creating = new Myitem();
                Myitem_creating->isdrawing=true;
                Myitem_creating->item_shape=9;
                Myitem_creating->points[0]=point;
                Myitem_creating->points_num++;
                addItem(Myitem_creating);
            }
        }
        else if (event->button() == Qt::RightButton)
        {
            if(!items(event->scenePos()).empty())
            {
                removeItem(items(event->scenePos()).front());
                return;
            }
        }
    }
}

void Myscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setBackgroundBrush(fillmap);
    update();
    if(fill_index==1)
        return;
    QGraphicsScene::mouseMoveEvent(event);
    update();
    if(!Myitems.empty()&&Myitems.top()->isdrawing==true)
        return;
    if (!event->isAccepted())
    {
        if (mode_index==1&&Myitem_creating!=NULL)
        {
            Myitem_creating->points[1]=event->scenePos();
            Myitem_creating->points_num=2;
            Myitem_creating->update();
            this->update();
        }
        if (cut_index==1&&Myitem_creating!=NULL)
        {
            Myitem_creating->points[1]=event->scenePos();
            Myitem_creating->points_num=2;
            Myitem_creating->update();
            this->update();
        }
    }
}

void Myscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setBackgroundBrush(fillmap);
    update();
    if(fill_index==1)
        return;
    QGraphicsScene::mouseReleaseEvent(event);
    update();
    if(!Myitems.empty()&&Myitems.top()->isdrawing==true)
        return;
    if (!event->isAccepted())
    {
        if (mode_index==1&&Myitem_creating!=NULL)
        {
            if(Myitem_creating->points_num==1||(Myitem_creating->points_num>1&&Myitem_creating->points[1]==Myitem_creating->points[0]))
            {
                removeItem(Myitem_creating);
            }
            else if(shape_index==1||shape_index==2||shape_index==3||shape_index==5)
            {
                Myitem_creating->isdrawing=false;
                Myitem_creating->update();
                this->update();
            }
            else if(shape_index==4)
            {
                if(Myitem_creating->points_num>1)
                    Myitems.push(Myitem_creating);
            }
            Myitem_creating=NULL;
        }
        else if(cut_index==1&&Myitem_creating!=NULL&&Myitem_creating->points_num==2)
        {
            if(cut_item!=NULL&&cut_item->item_shape==1)
            {
                double u1=0,u2=1;
                double xmin,xmax,ymin,ymax;
                double x1=cut_item->points[0].x(),y1=cut_item->points[0].y();
                double x2=cut_item->points[1].x(),y2=cut_item->points[1].y();
                double deltax=x2-x1,deltay=y2-y1;
                xmin=Myitem_creating->points[0].x()<Myitem_creating->points[1].x()?Myitem_creating->points[0].x():Myitem_creating->points[1].x();
                xmax=Myitem_creating->points[0].x()>Myitem_creating->points[1].x()?Myitem_creating->points[0].x():Myitem_creating->points[1].x();
                ymin=Myitem_creating->points[0].y()<Myitem_creating->points[1].y()?Myitem_creating->points[0].y():Myitem_creating->points[1].y();
                ymax=Myitem_creating->points[0].y()>Myitem_creating->points[1].y()?Myitem_creating->points[0].y():Myitem_creating->points[1].y();
                double r[4],q[4],p[4];
                q[0]=x1-xmin;
                q[1]=xmax-x1;
                q[2]=y1-ymin;
                q[3]=ymax-y1;
                p[0]=-1*deltax;
                p[1]=deltax;
                p[2]=-1*deltay;
                p[3]=deltay;
                if(deltax!=0&&deltay!=0)
                {
                    for(int i=0;i<4;i++)
                        r[i]=q[i]/p[i];
                    double u1max=0,u2min=1;
                    for(int i=0;i<4;i++)
                    {
                        if(p[i]<0)
                            u1max=r[i]>u1max?r[i]:u1max;
                        if(p[i]>0)
                            u2min=r[i]<u2min?r[i]:u2min;
                    }
                    u1=u1max;
                    u2=u2min;
                    if(u1>u2)
                    {
                        removeItem(cut_item);
                    }
                    else
                    {
                        cut_item->points[0].rx()=x1+u1*deltax;
                        cut_item->points[0].ry()=y1+u1*deltay;
                        cut_item->points[1].rx()=x1+u2*deltax;
                        cut_item->points[1].ry()=y1+u2*deltay;
                        cut_item->update();
                    }
                }
                else
                {
                    if(deltax==0)
                    {
                        if(q[0]<0||q[1]<0)
                        {
                            removeItem(cut_item);
                        }
                        else
                        {
                            r[2]=q[2]/p[2];
                            r[3]=q[3]/p[3];
                            double u1max=0,u2min=1;
                            for(int i=2;i<4;i++)
                            {
                                if(p[i]<0)
                                    u1max=r[i]>u1max?r[i]:u1max;
                                if(p[i]>0)
                                    u2min=r[i]<u2min?r[i]:u2min;
                            }
                            u1=u1max;
                            u2=u2min;
                            if(u1>u2)
                            {
                                removeItem(cut_item);
                            }
                            else
                            {
                                cut_item->points[0].rx()=x1+u1*deltax;
                                cut_item->points[0].ry()=y1+u1*deltay;
                                cut_item->points[1].rx()=x1+u2*deltax;
                                cut_item->points[1].ry()=y1+u2*deltay;
                                cut_item->update();
                            }
                        }
                    }
                    else if(deltay==0&&deltax!=0)
                    {
                        if(q[2]<0||q[3]<0)
                        {
                            removeItem(cut_item);
                        }
                        else
                        {
                            r[0]=q[0]/p[0];
                            r[1]=q[1]/p[1];
                            double u1max=0,u2min=1;
                            for(int i=0;i<2;i++)
                            {
                                if(p[i]<0)
                                    u1max=r[i]>u1max?r[i]:u1max;
                                if(p[i]>0)
                                    u2min=r[i]<u2min?r[i]:u2min;
                            }
                            u1=u1max;
                            u2=u2min;
                            if(u1>u2)
                            {
                                removeItem(cut_item);
                            }
                            else
                            {
                                cut_item->points[0].rx()=x1+u1*deltax;
                                cut_item->points[0].ry()=y1+u1*deltay;
                                cut_item->points[1].rx()=x1+u2*deltax;
                                cut_item->points[1].ry()=y1+u2*deltay;
                                cut_item->update();
                            }
                        }
                    }
                }
                cut_item->iscutting=false;
                cut_item->update();
                cut_item=NULL;
            }
            removeItem(Myitem_creating);
            Myitem_creating=NULL;
            foreach (QGraphicsItem *item, items())
            {
                item->setVisible(true);
            }
            update();
        }
    }
}

void Myscene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace)
    {
        while (!selectedItems().isEmpty())
        {
            removeItem(selectedItems().front());
        }
    }
    else
    {
        QGraphicsScene::keyPressEvent(event);
    }
}

void Myscene::wheelEvent(QGraphicsSceneWheelEvent*event)
{
    if(items(event->scenePos()).isEmpty())
    {
        event->accept();
        return;
    }
    else if(!Myitems.empty()&&Myitems.top()->isdrawing==true)
        return;
    else
    {
        QGraphicsScene::wheelEvent(event);
        if(event->isAccepted())
        {
            update();
        }
    }
}
