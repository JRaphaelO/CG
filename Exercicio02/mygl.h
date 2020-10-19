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
}Point, **P;

// Rasteriza um ponto na mémoria de vídeo
void PuPixel(Point point, Color color);

void DrawLine(Point point1, Point point2, Color color);

void DrawTriangle(Point point1, Point point2, Point point3, Color color);

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Declare aqui as funções que você implementar <<<
//

#endif  // MYGL_H
