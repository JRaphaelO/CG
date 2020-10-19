#include "mygl.h"

void PutPixel(Point point, Color color) {
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 0] = color.red;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 1] = color.green;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 2] = color.blue;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 3] = color.alpha;
}


void MidPointLine(int xi, int yi, int xf, int yf, Color color, int isInvert, int isSpecial) {
    int dx = xf - xi;
    int dy = yf - yi;

    int D = 2 * dy - dx;
    int inc_L = 2 * dy;
    int inc_NE = 2 * (dy - dx);

    Point point;

    if (isSpecial)
    {
        point.x = xi;
        point.y = yi;
    }
    else {
        point.x = xi;
        point.y = yi;
    }

    if (isInvert){
        Point aux;
        aux.x = point.y;
        aux.y = point.x;
        PutPixel(aux, color);
    }
    else 
        PutPixel(point, color);

    while ( point.x < xf)
    {
        if (D <= 0) 
            D += inc_L;
        else {
            D += inc_NE;

            if (isSpecial) point.y--;
            else point.y++;
        }

        point.x ++;

        if (isInvert){
            Point aux;
            aux.x = point.y;
            aux.y = point.x;
            PutPixel(aux, color);
        }
        else 
            PutPixel(point, color);
    }

}

void DrawLine(Point point1, Point point2, Color color) {
    float dx = point2.x - point1.x;
    float dy = point2.y - point1.y;

    float m = dy/dx;

    if ((m >= 0 && m <= 1 && point1.x < point2.x) || (dy == 0 && point1.x < point2.x)) // Octante 1 
        MidPointLine(point1.x, point1.y, point2.x, point2.y, color, 0, 0);
    
    else if ((m > 1 && m < INFINITO && point1.y < point2.y) || (dx == 0 && point1.y < point2.y)) // Octante 2
        MidPointLine(point1.y, point1.x, point2.y, point2.x, color, 1, 0);
    
    else if (m < -1 && m > -INFINITO && point1.y < point2.y) // Octante 3
        MidPointLine(point1.y, point2.x, point2.y, point1.x, color, 1, 1);

    else if (m <= 0 && m >= -1 && point2.x < point1.x) // Octante 4
        MidPointLine(point2.x, point1.y, point1.x, point2.y, color, 0, 1);

    else if ((m > 0 && m <= 1 && point2.x < point1.x) || (dy == 0 && point2.x < point1.x)) // Octante 5
        MidPointLine(point2.x, point2.y, point1.x, point1.y, color, 0, 0);
    
    else if ((m > 1 && m < INFINITO && point2.y < point1.y) || (dx == 0 && point2.y < point1.y)) // Octante 6
        MidPointLine(point2.y, point2.x, point1.y, point1.x, color, 1, 0);
    
    else if (m < -1 && m > -INFINITO && point2.y < point1.y) // Octante 7
        MidPointLine(point2.y, point1.x, point1.y, point2.x, color, 1, 1);
    
    else if (m < 0 && m >= -1 && point1.x < point2.x) // Octante 8
        MidPointLine(point1.x, point2.y, point2.x, point1.y, color, 0, 1);
}


void DrawTriangle(Point point1, Point point2, Point point3, Color color) {
    DrawLine(point1, point2, color);
    DrawLine(point2, point3, color);
    DrawLine(point3, point1, color);
}

// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {

    struct Point point;
    point.x = 15;
    point.y = 23;

    struct Color colorPurple;
    colorPurple.red = 255;
    colorPurple.green = 0;
    colorPurple.blue = 255;
    colorPurple.alpha = 255;

    Color color;
    // point.x = rand() % IMAGE_WIDTH;
    // point.y = rand() % IMAGE_HEIGHT;
    color.red = rand() % 256;
    color.green = rand() % 256;
    color.blue = rand() % 256;
    color.alpha = rand() % 256;
    
    PutPixel(point, color);

    struct Point point1;
    struct Point point2;
    struct Point point3;
    
    point1.x = 142;
    point1.y = 80;

    point2.x = 500;
    point2.y = 350;

    DrawLine(point1, point2, color);

    point1.x = 203;
    point1.y = 48;

    point2.x = 27;
    point2.y = 48;

    point3.x = 450;
    point3.y = 490;

    DrawTriangle(point1, point2, point3, color);
}
