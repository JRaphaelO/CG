# Implementação do Pipeline Gráfico

## Introdução 
Esta atividade tem como intuito familiarizar com a estrutura do *pipeline* gráfico atráves da implementação de transformações geométricas. 
Para este projeto será utilizada como base o algoritimo [03_transformations](https://github.com/capagot/icg/tree/master/03_transformations),
as matrizes que serão modificadas na função **Display** disponibilizada no arquivo [main.cpp](https://github.com/JRaphaelO/CG/blob/main/Exercicio03/main.cpp).

## Objetivo
Este trabalho tem como objetivo:
* O desenvolvimento de transformações geométricas com a estrutura do *pipeline* gráfico.

## Desenvolvimento
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

<<<<<<< HEAD
Modificar a escala dos triângulos demonstrados na figura 2, para $(x, y, z) = (1/3, 3/2, 1)$, sendo assim temos que a matriz utilizada é:



## Resultado
=======
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

## Resultado
>>>>>>> ff848a5c0b87189ce2128e78a00d92ba23183515
