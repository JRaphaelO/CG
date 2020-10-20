#Rasterizando Linhas

## Introdução
Esta atividade tem como intuito desenvolver funções, para a rasterização de pontos, linhas e triângulos, no projeto [02_mygl_framework](https://github.com/capagot/icg/tree/master/02_mygl_framework). Essas funções foram incluídas no arquivo [mygl.h](https://github.com/JRaphaelO/CG/blob/main/Exercicio02/mygl.h) e suas implementações podem ser encontradas no arquivo [mygl.c](https://github.com/JRaphaelO/CG/blob/main/Exercicio02/mygl.c). 

## Objetivo
Este trabalho tem como objetivo:
* O desenvolvimento de um algoritmo de rasterização utilizado na computação gráfica.

## Desenvolvimento

O desenvolvimento deste projeto, teve como inicio na construção das funcções PutPixel, DrawLine e DrawTriangle, com isso temos que foram criadas duas estruturas uma para armazenar as coordenadas de um ponto e outra para armazenar a cor do pixel, como podem ser vista no script abaixo.

```C
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

```

Sendo assim, podemos observar que a estrutura do ponto, além de possuir as coordenadas do pixel, possui a cor dele. Com isso temos que para o desenvolvimento da função PutPixel, que printa um pixel na tela, de acordo com a coordenada passada, será nescessário a passagem de um elemento do tipo Point para ela. 

```C
            void PutPixel(Point point) {
                fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 0] = point.color.red;
                fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 1] = point.color.green;
                fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 2] = point.color.blue;
                fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 3] = point.color.alpha;
            }
```

Por fim, temos que o display é formado por um array de pixels, onde inicia em 0 e vai até WIDHT*HEIGHT, com isso temos que realizar um cálculo para encontrara coordenada do pixel a ser pintado, tendo ainda que cada pixel, equivale a 4 posições deste array. Então a imagem abaixo mostra como seria distribuído essas posições em tela para um display 6x3, para que o pixel o 15 seja preenchido é nescessário que seja passada as coordenadas (3,2), pois quando é utiizada na formula 4*x+4*y+WIDHT, o valor do pixel será selecionado, ai é somado a ele o valor da cor que será aplicado a este pixel.

![DISPLAY](https://imgur.com/gelB4t0)

## Resultado


