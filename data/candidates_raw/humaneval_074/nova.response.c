char *func0(char *str1, int n1, char *str2, int n2) {
    int i, j;
    int cont1 = 0, cont2 = 0;
    char *menor;

    for (i = 0; i < n1; i++) {
        cont1 += strlen(str1[i]);
    }

    for (j = 0; j < n2; j++) {
        cont2 += strlen(str2[j]);
    }

    if (cont1 < cont2) {
        menor = str1;
    } else if (cont1 > cont2) {
        menor = str2;
    } else {
        menor = str1;
    }

    return menor;
}