void murcielagoCrypt(char *str) {
    int i, j;
    char *murcielago = "MURCIELAGOmurcielago";
    char *numeros = "01234567890123456789";

    for (i = 0; str[i] != '\0'; i++) {
        for (j = 0; murcielago[j] != '\0'; j++) {
            if (str[i] == murcielago[j]) {
                str[i] = numeros[j];
                break;
            }
        }
    }
}