 # ![lfsr logo](http://www.efoto.eng.uerj.br/images/LFSR.png) RPC Processing Module for Satelite Imagery

## Objective
 - The objective of this module is to add the satelite image processing feature to the [E-Foto](https://github.com/lfsruerj/e-foto-tests) software

## Workflow Diagram of the Main Function:
- lorem ipsilum dolor sit ment
## Guidelines
- lorem ipsulum dolor amet sic 

## Understanding Parameters' Names

To minimize the declaration of various names and to make the code more organized, various Structures were created as listed in `sources/structs.h`.
For example:

```cpp
typedef struct Coordinates
{
    Eigen::MatrixXd Lat;
    Eigen::MatrixXd Long;
    Eigen::MatrixXd Height;
} Coordinates;
```

Variables' names are longer then usually seen so that the code can be semanthicaly understood, as in:

```cpp
    Coordinates SpacialInterssectionReturn;
    SpacialInterssectionReturn.Long = Long;
```

Functions' names are also longer so that the users can easily find the functions that suit theirs needs sinmply by reading its names as in `Coordinates SpacialInterssection()`.

## Source

R842 Rotunno, Marcel Emanuelli.

Interseção espacial pelo modelo de funções racionais para
um par estereoscópico de imagens sensoriadas em nível
orbital / Marcel Emanuelli Rotunno. – 2014.
47f.
Orientador: Guilherme Lucio Abelha Mota
Orientador: Jorge Luís Nunes e Silva Brito
Projeto Final (Graduação) - Universidade do Estado do Rio
de Janeiro, Faculdade de Engenharia.
Bibliografia p.47

1. Engenharia Cartográfica. 2. Imagens de sensoriamento
   remoto. 3. Satélite de imagens. I. Mota, Guilherme Lucio
   Abelha. II. Brito, Jorge Luis Nines e Silva. III. Universidade do
   Estado do Rio de Janeiro. IV. Título.

CDU 62:528.9

[lfsr-logo]: (http://www.efoto.eng.uerj.br/images/LFSR.png)
