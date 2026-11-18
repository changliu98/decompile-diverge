int inicializa(int *vetor, int tam, int *menor, int *maior) {
  int flag;
  if (tam % 2 == 0) {
    flag = 2;
    if (vetor[0] < vetor[1]) {
      *menor = vetor[0];
      *maior = vetor[1];
    } else {
      *menor = vetor[1];
      *maior = vetor[0];
    }
  } else {
    *menor = vetor[0];
    *maior = vetor[0];
    flag = 1;
  }
  return flag;
}