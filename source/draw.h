#ifndef DRAW_H
#define DRAW_H

#include<math.h>
#include <QtDebug>
#include<QPainter>
#include<QPen>

#define min(a,b) (((a)<(b))?(a):(b))

void paintline_0_1(QPainter *painter,int x0,int y0,int x1,int y1,int z0,int z1,bool reverse);
void paintline(QPainter *painter, int start_x, int start_y, int end_x, int end_y);
void paintcircle(QPainter *painter, int start_x, int start_y, int end_x, int end_y);
void paintellipse(QPainter *painter, int start_x, int start_y, int end_x, int end_y);

void paintRect(QPainter *painter, int start_x, int start_y, int end_x, int end_y);
//void paintPoints(QPainter *painter, int start_x, int start_y, int end_x, int end_y);
void paintexcircle(QPainter *painter, int start_x, int start_y, int width, int R_temp);//辅助小圆

void paintbezier(QPainter *painter, QPointF*points, int point_num);

#endif // DRAW_H
