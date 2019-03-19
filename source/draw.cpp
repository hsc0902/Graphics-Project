#include "draw.h"

void paintRect(QPainter *painter, int start_x, int start_y, int end_x, int end_y)
{
    if(start_x!=end_x&&start_y!=end_y)
    {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        pen.setBrush(Qt::gray);
        painter->setPen(pen);
        int w=end_x-start_x>0?end_x-start_x:start_x-end_x;
        int h=end_y-start_y>0?end_y-start_y:start_y-end_y;
        int x=min(start_x,end_x);
        int y=min(start_y,end_y);
        painter->drawRect(x,y,w,h);
    }
}

void paintexcircle(QPainter *painter, int start_x, int start_y, int width, int R_temp)
{
    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);
    pen.setBrush(Qt::gray);
    painter->setPen(pen);
    painter->drawEllipse(start_x-R_temp,start_y-R_temp,R_temp*2,R_temp*2);
    pen.setWidth(width);
    painter->setPen(pen);
    painter->drawPoint(start_x,start_y);
}

/*void paintPoints(QPainter *painter, int start_x, int start_y, int end_x, int end_y)
{
    if(start_x!=end_x&&start_y!=end_y)
    {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        pen.setBrush(Qt::gray);
        painter->setPen(pen);

        painter->drawEllipse(start_x-R_temp,start_y-R_temp,R_temp*2,R_temp*2);
        painter->drawEllipse(end_x-R_temp,end_y-R_temp,R_temp*2,R_temp*2);
        pen.setWidth(5);
        painter->setPen(pen);
        painter->drawPoint(start_x,start_y);
        painter->drawPoint(end_x,end_y);
    }
}*/

void paintline_0_1(QPainter *painter,int x0,int y0,int x1,int y1,int z0,int z1,bool reverse)
{
    int a,b,delta1,delta2,d,x,y ;
    a = y0 - y1;
    b = x1 - x0;
    d = 2 * a + b ;
    delta1 = 2 * a ;
    delta2 = 2 *( a + b);
    x = x0 ;
    y = y0 ;
    if(reverse==false)
        painter->drawPoint(z0*x, z1*y);
    else
        painter->drawPoint(z0*y, z1*x);
    while( x<x1  )
    {
        if( d<0 )
        {
            x ++;
            y ++;
            d+= delta2;
        }
        else
        {
            x++;
            d+= delta1;
        }
        if(reverse==false)
            painter->drawPoint(z0*x, z1*y);
        else
            painter->drawPoint(z0*y, z1*x);
     }
}

void paintline(QPainter *painter, int start_x, int start_y, int end_x, int end_y)
{
    if(start_x==end_x&&start_y==end_y)
        return;
    int x0,y0,x1,y1;
    if(start_x<end_x)
    {
        x0=start_x;
        y0=start_y;
        x1=end_x;
        y1=end_y;
    }
    else if(start_x>end_x)
    {
        x0=end_x;
        y0=end_y;
        x1=start_x;
        y1=start_y;
    }
    else
    {
        if(start_y<=end_y)
        {
            x0=start_x;
            y0=start_y;
            x1=end_x;
            y1=end_y;

        }
        else
        {
            x0=start_x;
            y1=start_y;
            x1=end_x;
            y0=end_y;
        }
        for(int y=y0;y<=y1;y++)
        {
            painter->drawPoint(x0, y);
        }
        return;
    }
    double dy_dx=(double)(y1-y0)/(x1-x0);
    if(dy_dx>=0&&dy_dx<=1)
    {
        paintline_0_1(painter,x0,y0,x1,y1,1,1,false);
    }
    else if(dy_dx>1)
    {
        paintline_0_1(painter,y0,x0,y1,x1,1,1,true);
    }
    else if(dy_dx<0&&dy_dx>=-1)
    {
        paintline_0_1(painter,x0,-y0,x1,-y1,1,-1,false);
    }
    else
    {
        paintline_0_1(painter,-y0,x0,-y1,x1,1,-1,true);

    }
    return;
}

void paintcircle(QPainter *painter, int start_x, int start_y, int end_x, int end_y)
{
    int x0=(start_x+end_x)/2;
    int y0=(start_y+end_y)/2;
    int R=min(start_x-end_x>0?start_x-end_x:end_x-start_x,start_y-end_y>0?start_y-end_y:end_y-start_y)/2;
    if(R<0)
        return;
    int x,y,deltax,deltay,d;
    x=0;y=R;d=1-R;
    deltax=3;
    deltay=5-R-R;
    painter->drawPoint(x+x0, y+y0);
    painter->drawPoint(-x+x0, -y+y0);
    painter->drawPoint(x+x0, -y+y0);
    painter->drawPoint(-x+x0, y+y0);
    painter->drawPoint(y+x0, x+y0);
    painter->drawPoint(-y+x0, x+y0);
    painter->drawPoint(y+x0, -x+y0);
    painter->drawPoint(-y+x0, -x+y0);
    while(x<y)
    {
        if(d<0)
        {
            d+=deltax;
            deltax+=2;
            deltay+=2;
            x++;
        }
        else
        {
            d+=deltay;
            deltax+=2;
            deltay+=4;
            x++;
            y--;
        }
        painter->drawPoint(x+x0, y+y0);
        painter->drawPoint(-x+x0, -y+y0);
        painter->drawPoint(x+x0, -y+y0);
        painter->drawPoint(-x+x0, y+y0);
        painter->drawPoint(y+x0, x+y0);
        painter->drawPoint(-y+x0, x+y0);
        painter->drawPoint(y+x0, -x+y0);
        painter->drawPoint(-y+x0, -x+y0);
    }
    return;
}

void paintellipse(QPainter *painter, int start_x, int start_y, int end_x, int end_y)
{
    if(start_x==end_x&&start_y==end_y)
        return;
    int xc=(start_x + end_x)/2;
    int yc=(start_y + end_y)/2;
    int rx=(start_x - end_x>0?start_x - end_x:end_x-start_x)/2;
    int ry=(start_y - end_y>0?start_y - end_y:end_y-start_y)/2;
    if(rx<0)
        rx=-rx;
    if(ry<0)
        ry=-ry;
    if(rx>ry)
    {
        int x=0,y=ry;
        int p_4=4*ry*ry-4*rx*rx*ry+rx*rx;
        do
        {
            if(p_4<0)
            {
                painter->drawPoint(x+xc, y+yc);
                painter->drawPoint(-x+xc, y+yc);
                painter->drawPoint(x+xc, -y+yc);
                painter->drawPoint(-x+xc, -y+yc);
                p_4=p_4+8*ry*ry*(x+1)+4*ry*ry;
                x=x+1;
            }
            else
            {
                painter->drawPoint(x+xc, y+yc);
                painter->drawPoint(-x+xc, y+yc);
                painter->drawPoint(x+xc, -y+yc);
                painter->drawPoint(-x+xc, -y+yc);
                p_4=p_4+8*ry*ry*(x+1)-8*rx*rx*(y-1)+4*ry*ry;
                x=x+1;
                y=y-1;
            }
        }
        while(ry*ry*x<rx*rx*y);
        int p2_4=ry*ry*(2*x+1)*(2*x+1)+4*rx*rx*(y-1)*(y-1)-4*ry*ry*rx*rx;
        do
        {
            if(p2_4>=0)
            {
                painter->drawPoint(x+xc, y+yc);
                painter->drawPoint(-x+xc, y+yc);
                painter->drawPoint(x+xc, -y+yc);
                painter->drawPoint(-x+xc, -y+yc);
                p2_4=p2_4-8*rx*rx*(y-1)+4*rx*rx;
                y=y-1;
            }
            else
            {
                painter->drawPoint(x+xc, y+yc);
                painter->drawPoint(-x+xc, y+yc);
                painter->drawPoint(x+xc, -y+yc);
                painter->drawPoint(-x+xc, -y+yc);
                p2_4=p2_4+8*ry*ry*(x+1)-8*rx*rx*(y-1)+4*rx*rx;
                x=x+1;
                y=y-1;
            }
        }
        while(x<=rx&&y>=0);
        return;
    }
    else if(rx<ry)
    {
        int temp=rx;
        rx=ry;
        ry=temp;
        int x=0,y=ry;
        int p_4=4*ry*ry-4*rx*rx*ry+rx*rx;
        do
        {
            if(p_4<0)
            {
                painter->drawPoint(y+xc, x+yc);
                painter->drawPoint(-y+xc, x+yc);
                painter->drawPoint(y+xc, -x+yc);
                painter->drawPoint(-y+xc, -x+yc);
                p_4=p_4+8*ry*ry*(x+1)+4*ry*ry;
                x=x+1;
            }
            else
            {
                painter->drawPoint(y+xc, x+yc);
                painter->drawPoint(-y+xc, x+yc);
                painter->drawPoint(y+xc, -x+yc);
                painter->drawPoint(-y+xc, -x+yc);
                p_4=p_4+8*ry*ry*(x+1)-8*rx*rx*(y-1)+4*ry*ry;
                x=x+1;
                y=y-1;
            }
        }
        while(ry*ry*x<rx*rx*y);
        int p2_4=ry*ry*(2*x+1)*(2*x+1)+4*rx*rx*(y-1)*(y-1)-4*ry*ry*rx*rx;
        do
        {
            if(p2_4>=0)
            {
                painter->drawPoint(y+xc, x+yc);
                painter->drawPoint(-y+xc, x+yc);
                painter->drawPoint(y+xc, -x+yc);
                painter->drawPoint(-y+xc, -x+yc);

                p2_4=p2_4-8*rx*rx*(y-1)+4*rx*rx;
                y=y-1;
            }
            else
            {
                painter->drawPoint(y+xc, x+yc);
                painter->drawPoint(-y+xc, x+yc);
                painter->drawPoint(y+xc, -x+yc);
                painter->drawPoint(-y+xc, -x+yc);

                p2_4=p2_4+8*ry*ry*(x+1)-8*rx*rx*(y-1)+4*rx*rx;
                x=x+1;
                y=y-1;
            }
        }
        while(x<=rx&&y>=0);
        return;
    }
    else
    {
        return;
    }
}


QPointF Casteljau(double u, int i, int r, QPointF*points, int point_num)
{
    if(r==0)
    {
        return points[i];
    }
    else
    {
        return (1-u)*Casteljau(u,i,r-1,points,point_num)+u*Casteljau(u,i+1,r-1,points,point_num);
    }
}

void paintbezier(QPainter *painter, QPointF*points, int point_num)//曲线
{
    if(point_num==1)
        return;
    else if(point_num==2)
    {
        paintline(painter,points[0].x(),points[0].y(),points[1].x(),points[1].y());
    }
    else if(point_num>2)
    {
        for(double u=0;u<=1;u=u+0.001)
        {
            painter->drawPoint(Casteljau(u, 0, point_num-1, points, point_num));
        }
    }
}
