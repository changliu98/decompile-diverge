void func0(int *a, int n, struct soma *s) {
    int i, soma = 0, produto = 1;

    for (i = 0; i < n; i++) {
        soma += a[i];
        produto *= a[i];
    }

    s->soma = soma;
    s->produto = produto;
}