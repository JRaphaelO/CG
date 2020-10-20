#ifndef MYGL_H
#define MYGL_H

#include <string.h>

#include "core.h"
#include "frame_buffer.h"

typedef struct Color
{
    int red;
    int green;
    int blue;
    int alpha;
}Color;

typedef struct Point
{
    int x;
    int y;
    Color color;
}Point, **P;

// Rasteriza um ponto na mémoria de vídeo
void PuPixel(Point point);

// Rasteriza uma linha na mémoria de vídeo.
void DrawLine(Point point1, Point point2);

// Rasteriza um triângulo na memória de vídeo.
void DrawTriangle(Point point1, Point point2, Point point3);

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

#endif  // MYGL_H
