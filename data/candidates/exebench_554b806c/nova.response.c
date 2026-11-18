int is_empty(float *matriz, int tamanho) {
    int i;
    char parar;
    for (i = 0; i < tamanho; i++) {
        if (matriz[i] > -1) {
            parar = 0;
        } else {
            parar = 1;
            break;
        }
    }
    if (parar % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}