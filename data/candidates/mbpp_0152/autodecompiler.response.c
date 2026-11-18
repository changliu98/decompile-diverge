void func0(int *vetor, int tam){
    if(tam < 3)
        return;

    int tamL = tam/2;
    int *esquerda = (int*)malloc(sizeof(int)*tamL);
    int *direita = (int*)malloc(sizeof(int)*(tam-tamL));

    int i, j;
    for(j=0; j<tamL; j++){
        esquerda[j] = vetor[j];
    }

    for(i=tamL; i<tam; i++){
        direita[i-tamL] = vetor[i];
    }

    func0(esquerda, tamL);
    func0(direita, tam-tamL);

    merge(esquerda, tamL, direita, tam-tamL, vetor);

    free(esquerda);
    free(direita);
}