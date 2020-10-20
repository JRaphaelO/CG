#include "mygl.h"

Color CreateColor(int red, int green, int blue, int alpha) {
    Color color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;

    return color;
}

Point CreatePoint(int x, int y, Color color ) {
    Point point;
    point.x = x;
    point.y = y;
    point.color = color;

    return point;
}

int abs(int x) {
    if (x < 0) return -1*x;
    return x;
}

void PutPixel(Point point) {
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 0] = point.color.red;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 1] = point.color.green;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 2] = point.color.blue;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 3] = point.color.alpha;
}

void DrawLine(Point point1, Point point2) {
    int dx, dy, D, increment_x = 1, increment_y = 1, i;

    dx = point2.x - point1.x;
    dy = point2.y - point1.y;

    if(dx < 0) increment_x = -1*increment_x;
    if(dy < 0) increment_y = -1*increment_y;

    float dR = point2.color.red - point1.color.red;
    float dG = point2.color.green - point1.color.green;
    float dB = point2.color.blue - point1.color.blue;  
    float dA = point2.color.alpha - point1.color.alpha;

    dx = abs(dx);
    dy = abs(dy);

    Point point = point1;  

    if (dx > dy){
        D = (dy * 2) - dx;
        dR /= dx;
        dG /= dx;
        dB /= dx;
        dA /= dx;

        for (i = 0; i < dx; i++)
        {
            point.color.red += dR;
            point.color.green += dG;
            point.color.blue += dB;
            point.color.alpha += dA;

            PutPixel(point);
            if (D < 0)
                D += dy * 2;
            else {
                point.y += increment_y;
                D += (dy - dx) * 2;
            }
            point.x += increment_x;
        }
    } else {
        D = (dx * 2) - dy;
        dR /= dy;
        dG /= dy;
        dB /= dy;
        dA /= dy;

        for (i = 0; i < dy; i++)
        {
            point.color.red += dR;
            point.color.green += dG;
            point.color.blue += dB;
            point.color.alpha += dA;

            PutPixel(point);
            if (D < 0)
                D += dx * 2;
            else {
                point.x += increment_x;
                D += (dx - dy) * 2;
            }
            point.y += increment_y;
        }
    }
}

void DrawTriangle(Point point1, Point point2, Point point3){
    DrawLine(point1, point2);
    DrawLine(point1, point3);
    DrawLine(point2, point3);
}

void MyGlDraw(void) {
    Color color1 = CreateColor(255, 0, 255, 255);
    Color color2 = CreateColor(0, 255, 255, 255);
    Color color3 = CreateColor(255, 255, 0, 255);
    Color color4 = CreateColor(255, 255, 255, 255);
    Color color5 = CreateColor(255, 200, 200, 255);
    Color color6 = CreateColor(180, 250, 20, 255);
    Color color7 = CreateColor(55, 150, 200, 255);
    Color color8 = CreateColor(255, 200, 100, 255);
    Color color9 = CreateColor(255, 200, 255, 255);

    Point point1 = CreatePoint(IMAGE_WIDTH/2, IMAGE_HEIGHT/2, color1);
    Point point2 = CreatePoint(0, 0, color2);
    Point point3 = CreatePoint(IMAGE_WIDTH-1, 0, color3);
    Point point4 = CreatePoint(0, IMAGE_HEIGHT-1, color4);
    Point point5 = CreatePoint(IMAGE_WIDTH-1, IMAGE_HEIGHT-1, color5);
    Point point6 = CreatePoint(IMAGE_WIDTH/2, 0, color6);
    Point point7 = CreatePoint(IMAGE_WIDTH/2, IMAGE_HEIGHT-1, color7);
    Point point8 = CreatePoint(0, IMAGE_HEIGHT/2, color8);
    Point point9 = CreatePoint(IMAGE_WIDTH-1, IMAGE_HEIGHT/2, color9);

    PutPixel(point1);
    PutPixel(point2);
    PutPixel(point3);
    PutPixel(point4);
    PutPixel(point5);
    PutPixel(point6);
    PutPixel(point7);
    PutPixel(point8);
    PutPixel(point9);

    DrawLine(point1, point2);
    DrawLine(point1, point3);
    DrawLine(point1, point4);
    DrawLine(point1, point5);
    DrawLine(point1, point6);
    DrawLine(point1, point7);
    DrawLine(point1, point8);
    DrawLine(point1, point9);

    DrawTriangle(point1, point8, point3);
    DrawTriangle(point6, point4, point2);
    DrawTriangle(point7, point5, point9);
}
