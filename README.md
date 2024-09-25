<h1>This is an RPC algorithm Based on a Monography from Marcel Emanuelli Rotunno</h1>

<h2>Source</h2>
<p>
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

</p>

<h2>Executing with CMAKE</h2>
<p>
1. Install CMAKE <br>
2. Create a build folder in the RPC_MARCEL_CODE root <br>
3. Enter in build folder <br>
4. start the cmake build,COMMAND: $ cmake .. <br>
5. build the program: $ cmake --build . <br>
</p>

<h2>Example how to compile the tests using g++</h2>
<p>
 g++ -g -Wall -I ..\includes\Eigen\Eigen -I ..\headers\ -I ..\headers\utils\ .\mainWork.cpp .\utils\RandPerm.cpp -o teste
</p>