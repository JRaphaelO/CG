# Implementação do Pipeline Gráfico

## Introdução 
Esta atividade tem como intuito familiarizar com a estrutura do *pipeline* gráfico atráves da implementação de transformações geométricas. 
Para este projeto será utilizada como base o algoritimo [03_transformations](https://github.com/capagot/icg/tree/master/03_transformations),
as matrizes que serão modificadas na função **Display** disponibilizada no arquivo [main.cpp](https://github.com/JRaphaelO/CG/blob/main/Exercicio03/main.cpp).

## Objetivo
Este trabalho tem como objetivo:
* O desenvolvimento de transformações geométricas com a estrutura do *pipeline* gráfico.

## Resultado
* Para este trabalho foi instalado a biblioteca para a utilização do Glew, sendo assim foi utilizado no terminal o comando para instalar a biblioteca libglew-dev.
```shel
sudo apt-get install libglew-dev
```
* Com a instalação das bibliotecas, foi aberta a pasta dentro do shell e com isso foi utilizado o make para fazer a 
compilação do arquivo, sendo assim temos que a figura 1 demonstra o resultado da compilação.

```shel
make -f Makefile
```

![Compilação dos arquivos originais.](https://i.imgur.com/3MHtsnc.png)

* Após a execução do **make**, o arquivo é executado utilizando *./transform_gl* resultando dois triângulos na tela, como é demonstrado na figura 2.

![Resultado da primeira compilação.](https://i.imgur.com/CviNBtE.png)



### Escala

Modificar a escala dos triângulos demonstrados na figura 2, para $(x, y, z) = (1/3, 3/2, 1)$, sendo assim temos que a matriz utilizada é:



## Resultado

Modificar a escala dos triângulos demonstrados na figura 2, para $$ (x, y, z) = (1/3, 3/2, 1) $$, sendo assim temos que a matriz utilizada é:

```c++
// ( 1/3 3/2 1 ) = ( 0.33f 1.50f 1.00f ) 
float model_array1[16] = {0.33f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.50f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f};
```

Com isso temos que o resultado obtido pela modificação da escala, pode ser vista na figura 3.

![Exercicio escala.](https://i.imgur.com/8knRiHr.png)

### Translação

Modificar a translação dos triângulos demonstrados na figura 2, para (x, y, z) = (1, 0, 0), sendo assim temos que a matriz utilizada é:

```c++
// 1 0 0
float model_array2[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          1.0f, 0.0f, 0.0f, 1.0f};
```

Com isso temos que o resultado obtido pela modificação da escala, pode ser vista na figura 4.

![Exercicio Translação.](https://i.imgur.com/Xu2vOBw.png)

### Posição da Câmera

Neste parte temos que modificar a forma que os triângulos são projetados na tela, desta forma a matriz view será alterada para que isto ocorra. Sendo assim temos que calcular os vetores da base do espaço da câmera (xc, yc, zc), para formar a matriz B da base câmera e invertê-la, calculando a sua transposta. Na sequência, é determinada a matriz T que translada a base a câmera, fazendo a sua origem coincidir com a do espaço do universo. Por fim, a matriz view é dada pela multiplicação das matrizes Bt e T. A seguir serão mostrados como são cálculadas as matrizes Bt e T.

![Vetores da Câmera](https://i.imgur.com/4UUVO8H.png)

![Matriz B transposta](https://i.imgur.com/lq190qs.png)

![Matriz T](https://i.imgur.com/n7yaIe0.png)


Sendo assim temos que para a realizar os cálculos dos vetores da câmera, foram utilizadas as funções presentes na biblioteca [Matriz Library](https://github.com/JRaphaelO/MatrixOperations), sendo assim essas funções foram adicionadas ao código **main.cpp**, a fim de utilizar as suas funções. Sendo assim temos que esta biblioteca possui 4 funções, onde que a *create_matrix_bt* é a que foi chamada para a geração da matriz Bt.

Para a utilização desta função, o usuário precisa passar o vetor *d* e o vetor *up*, além de passar o vetor de saída, com isso temos que a função irá calcular os vetores (xc, yc, zc) e colocorá na matriz Bt de forma transposta, após isso os valores são passados para o vetor de sáida.

```c++
void create_matrix_bt(float *vector1, float *vector2, float *b_t)
{
  float zc[3], xc[3], yc[3];

  calculate_zc(vector1, zc);
  calculate_xc(vector2, zc, xc);
  calculate_xc(zc, xc, yc);

  float bt[16] = {xc[0], yc[0], zc[0], 0.0f,
                  xc[1], yc[1], zc[1], 0.0f,
                  xc[2], yc[2], zc[2], 0.0f,
                  0.00f, 0.00f, 0.0f, 1.0f};

  int l;
  for (l = 0; l < 16; l++)
    b_t[l] = bt[l];
}
```

Com isso temos que quando construírmos as matrizes Bt e T, será realizada a multiplicação de ambas para gerar a matriz view. Com isso temos que a imagem abaixo representa o resultado desta matriz quando calculada com a matrz de projeção feita acima.

![Exercicio Translação.](https://i.imgur.com/iPWmE0r.png)

### Transformação Livres
Foram feitas algumas transformações livres, onde que os valores das matrizes foram modificados com isso temos que serão apresentados os valores utilizados para e logo em seguida a imagem que é produzida, com isso temos:

* Transformação livre 1:
```c++
float model_array3[16] = {-1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          1.0f, 0.0f, 0.0f, 1.0f};
                          
float b_array2[16];
float p2[3]{1.0f, 0.9f, 2.5f};
float d2[3]{0.0f, 0.1f, -2.5f};
float u2[3]{0.0f, 1.0f, 0.0f};

float t_array2[16] = {1.00f, 0.00f, 0.00f, 0.00f,
                      0.00f, 1.00f, 0.00f, 0.00f,
                      0.00f, 0.00f, 1.00f, 0.00f,
                      -p2[0], -p2[1], -p2[2], 1.00f};
                      
float proj_array3[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, -1.2f,
                         0.0f, 0.0f, 0.83f, 0.0f};

```

![Transformação Livre 01](https://i.imgur.com/alfk0TZ.png)

* Transformação livre 2:
```c++
float model_array4[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, -1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          1.0f, 0.0f, 0.0f, 1.0f};
                          
float b_array3[16];
float p3[3]{0.5f, 0.5f, 1.5f};
float d3[3]{0.5f, -0.5f, -1.5f};
float u3[3]{0.0f, 1.0f, 0.0f};

create_matrix_bt(d3, u3, b_array3);

float t_array3[16] = {1.00f, 0.00f, 0.00f, 0.00f,
                      0.00f, 1.00f, 0.00f, 0.00f,
                      0.00f, 0.00f, 1.00f, 0.00f,
                      -p3[0], -p3[1], -p3[2], 1.00f};
                      
float proj_array3[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, -1.2f,
                         0.0f, 0.0f, 0.83f, 0.0f};
```

![Transformação Livre 02](https://i.imgur.com/bfHRMcb.png)

## Compilando e Executando

* Clone o projeto, com o comando:
```shell
git clone https://github.com/JRaphaelO/CG/
```

* Acesse a pasta do projeto:
```shell
cd CG/Exercicio03
```

* Execute o comando make para compilar:
```
make
```

* Por fim. execute o arquivo com:
```
./transform_gl
```



