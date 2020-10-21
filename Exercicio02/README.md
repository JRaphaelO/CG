#Rasterizando Linhas

## Introdução
Esta atividade tem como intuito desenvolver funções, para a rasterização de pontos, linhas e triângulos, no projeto [02_mygl_framework](https://github.com/capagot/icg/tree/master/02_mygl_framework). Essas funções foram incluídas no arquivo [mygl.h](https://github.com/JRaphaelO/CG/blob/main/Exercicio02/mygl.h) e suas implementações podem ser encontradas no arquivo [mygl.c](https://github.com/JRaphaelO/CG/blob/main/Exercicio02/mygl.c). 

## Objetivo
Este trabalho tem como objetivo:
* O desenvolvimento de um algoritmo de rasterização utilizado na computação gráfica.

## Desenvolvimento

O desenvolvimento deste projeto, teve como inicio na construção das funcções PutPixel, DrawLine e DrawTriangle, com isso temos que foram criadas duas estruturas uma para armazenar as coordenadas de um ponto e outra para armazenar a cor do pixel, como podem ser vista logo abaixo.

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

### PutPixel

Sendo assim, podemos observar que a estrutura do ponto, além de possuir as coordenadas do pixel. O pixel ocupa 4 bytes de informação, sendo que cada byte representa um valor do RGBA, que vão de 0 à 255. Com isso temos que para o desenvolvimento da função PutPixel, que printa um pixel na tela, de acordo com a coordenada passada, será nescessário a passagem de um elemento do tipo Point para ela.

```C
void PutPixel(Point point) {
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 0] = point.color.red;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 1] = point.color.green;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 2] = point.color.blue;
    fb_ptr[4*point.x + 4*point.y*IMAGE_WIDTH + 3] = point.color.alpha;
}
```

Por fim, temos que o display é formado por um array de pixels, onde inicia em 0 e vai até WIDHT*HEIGHT, com isso temos que realizar um cálculo para encontrara coordenada do pixel a ser pintado, tendo ainda que cada pixel, equivale a 4 posições deste array. Então a imagem abaixo mostra como seria distribuído essas posições em tela para um display 6x3, para que o pixel o 15 seja preenchido é nescessário que seja passada as coordenadas (3,2), pois quando é utiizada na formula 4*x+4*y+WIDHT, o valor do pixel será selecionado, ai é somado a ele o valor da cor que será aplicado a este pixel.

![DISPLAY](https://i.imgur.com/gelB4t0.png)

### DrawLine

A função DrawLine recebe dois pontos e com o algoritmo do ponto médio, cria uma linha entre estes pontos. Nste algoritmo, ele verifica se a reta passa por um ponto entre dois pixels, com essa verificação ele verá qual será a proxima posição, para isso ele avalia se a reta passou por baixo do ponto médio, a proxima seleção será (x + 1, y), já que ele está a avançar no eixo x. Caso de passar acima a proxima seleção será o (x + 1, y +1). Este algoritmo faz com que a reta esteja mais próxima do ponto central selecionado. 

![Algoritmo do Ponto Medio](https://miro.medium.com/max/352/0*gp6fh4LdACBT-1_a.)

Sendo assim foi desenvolvido a partir do algoritmo do ponto médio, um script da função DrawLine foi desenvolvido. Onde ele generaliza para todos os octantes do plano cartesiano, já que para cada octante, existe a sua pecularieadade, como pode ser vista na imagem abaixo.

![Octantes](https://miro.medium.com/max/352/0*TNP9w-e76XMz5704.)

Para que a generalização deste algoritmo, é preciso analisar como se comportam os valores de x e y, nos octantes. Olhando para a imagem do plano cartesiano acima, quando temos o dx positivo, o valor de x incrementa a cada repetição do laço, enquanto o y tem que ser avaliado, pois seu o seu dy é positivo, y incrementa em 1 a cada vez que a reta passar pelo ponto médio, se não ele decrementa em 1. Fazendo essas analogias, foi possível gerar um script onde que ele sirva para cada um destes octantes, como pode ser visto abaixo.
```C
void DrawLine(Point point1, Point point2) {
    int dx, dy, D, increment_x = 1, increment_y = 1, i;
    dx = point2.x - point1.x;
    dy = point2.y - point1.y;

    if(dx < 0) increment_x = -1*increment_x;
    if(dy < 0) increment_y = -1*increment_y;

    dx = abs(dx);
    dy = abs(dy);

    Point point = point1;  

    if (dx > dy){
        D = (dy * 2) - dx;
        for (i = 0; i < dx; i++)
        {
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
       
        for (i = 0; i < dy; i++)
        {
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
```

### DrawTriangle
Na função DrawTriangle ela recebe três pontos, onde que utilizando das chamadas da função DrawLine, desenha triângulos na tela, como pode ser visto logo abaixo.

```C
void DrawTriangle(Point point1, Point point2, Point point3){
    DrawLine(point1, point2);
    DrawLine(point1, point3);
    DrawLine(point2, point3);
}
```

## Resultado
Com a criação das três funções, foi possível gerar pontos, retas e triângulos na tela. Além de tudo isso, temos que o pixel desenhado na retas utilizava a interpolação linear, para fazer o cálculo da cor daquele pixel. A seguir serão mostrados imagens que representam os resultados de cada função.

### PutPixel
* Point (Width/2, Height/2)

![Point](https://i.imgur.com/VmSNcsk.png)

* Multiples Points

![Multiple](https://i.imgur.com/3Wiql2H.png)
### DrawLine
* 4 linhas saindo do meio da tela.

![](https://i.imgur.com/INfoJg1.png)

* 8 Linhas saindo do meio da tela

![](https://i.imgur.com/5VeVII8.png)

### DrawTriangle

* 1 Triângulo

![](https://i.imgur.com/PduMlMD.png)

* 3 Triângulos

![](https://i.imgur.com/5b2i49c.png)

## Referências 

* Algumas das imagens utilizadas foram retiradas do artigo escrito por Bianca K. Amorim, onde pode ser encontrado (https://medium.com/@biancaamorimelo/rasteriza%C3%A7%C3%A3o-de-primitivas-em-opengl-8680a76fdda5).