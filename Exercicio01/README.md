# Compilando e Executando um Programa OpenGL Moderno.

## Introdução
Esta atividade tem como intuito compilar o [01_hello_world_gl](https://github.com/capagot/icg/tree/master/01_hello_world_gl) com o uso da OpenGL 3.3, desenvolvido por [Cristian Pagot](https://github.com/capagot). Para isso foi utilizado o ambiente de terminal Ubuntu com Windows Subsystem for Linux (WSL), sendo que erros foram encontrados durante a execução deste projeto. Após as correções destes erros, quando executado o programa irá apresentar um triângulo colorido.

## Objetivo
Este trabalho tem como objetivo:
* Verificar se o ambiente de desenvolvimento em OpenGL 3.3 está corretamente configurado no computador;
* Familiarizar com a estrutura de um programa OpenGL modern.

## Desenvolvimento

*Para o ambiente de desenvolvimento foi escolhido o Ubuntu WSL, que pode ser encontrado em <https://ubuntu.com/wsl>, com isto será possível ter todos os comandos do Ubuntu dentro deste terminal.

*Com a instalação do ambiente do Ubuntu, foi instalada as bibliotecas para a utilização da OpenGL, sendo assim foram instaladas as bibliotecas libglu1-mesa-dev freeglut3-dev mesa-common-dev.

```shell
sudo apt-get update
``` 

```shell
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
``` 

* Com a instalação das bibliotecas, foi aberta a pasta dentro do shell e com isso foi utilizado o make para fazer a compilação do arquivo. 

```shell
make -f Makefile
``` 

![Resultado da compilação](https://github.com/JRaphaelO/CG/blob/main/Exercicio01/images/compile.png?raw=true)

* Após a execução do make, foi gerado um arquivo executável, porém, quando executada foi encontrado o erro: freeglut cant open display. Isto ocorre porque o Ubuntu WSL não possui uma parte gráfica acoplada a ele.

![Erro Cant Display](https://github.com/JRaphaelO/CG/blob/main/Exercicio01/images/erro_xlaunch.png?raw=true)

* Para corrigir este erro é só instalar o [xlaunch](https://sourceforge.net/projects/xming/) e após a sua instalação, no shell do Ubuntu realizar os seguintes comandos:

```shell
sudo apt-get install vim-gtk
``` 

```shell
export DISPLAY=:0
``` 

## Resultado
Após estes comandos, temos que o resultado foi de um triangulo colorido, sendo assim a OpenGL 3.3 foi instalada com sucesso.

![Reseultado Final](https://github.com/JRaphaelO/CG/blob/main/Exercicio01/images/executavel.png?raw=true)

