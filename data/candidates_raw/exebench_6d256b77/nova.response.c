float func0(float *matriz, int linhas, int colunas, int n) {
    float soma1 = 0, soma2 = 0, soma3 = 0;
    int i = 0;
    while (i < n) {
        if (matriz[i * n + n] == -1 && matriz[i * n + 0] == -1) {
            soma1 += 1;
        }
        if (matriz[i * n + n] == -1) {
            soma2 += 1;
        }
        if (matriz[i * n + 0] == -1) {
            soma3 += 1;
        }
        i++;
    }
    float resultado;
    if (soma3 < soma2) {
        resultado = soma1 / soma3;
    } else {
        resultado = soma1 / soma2;
    }
    return resultado;
}