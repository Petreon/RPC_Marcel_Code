#include <stdio.h>
double Polrfm(double rpc[20], double l, double b, double h);

int main() {
  // Declaração do vetor para armazenar os valores double
  double coeficientes[20];

  // Abre o arquivo para leitura
  FILE *arquivo;
  arquivo = fopen("coef_a1.txt", "r");

  // Verifica se o arquivo foi aberto com sucesso
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return 1;
  }

  // Lê os valores double do arquivo e armazena no vetor
  int i;
  for (i = 0; i < 20; i++) {
    fscanf(arquivo, "%lf", &coeficientes[i]);
  }

  // Fecha o arquivo
  fclose(arquivo);

  // Imprime os valores do vetor (opcional)
  for (i = 0; i < 20; i++) {
    printf("\n %lf ", coeficientes[i]);
  }

  printf("\n");
  
	double l=0,b=0,h=0,resultado=0;
	resultado = Polrfm(coeficientes, l, b, h);

	printf("O resultado do polinomio : %lf\n", resultado);
  
  

  return 0;
}

double Polrfm(double rpc[20],double l,double b, double h) {
double somatorio;
somatorio=rpc[0]+(rpc[1]*l)+(rpc[2]*b)+(rpc[3]*h)+(rpc[4]*l*b)
        +(rpc[5]*l*h)+(rpc[6]*b*h)+(rpc[7]*l*l)+(rpc[8]*b*b)+(rpc[9]*h*h)
        +(rpc[10]*b*l*h)+(rpc[11]*l*l*l)+(rpc[12]*l*b*b)+(rpc[13]*l*h*h)+(rpc[14]*l*l*b)
        +(rpc[15]*b*b*b)+(rpc[16]*b*h*h)+(rpc[17]*l*l*h)+(rpc[18]*b*b*h)+(rpc[19]*h*h*h);
return somatorio;
};
