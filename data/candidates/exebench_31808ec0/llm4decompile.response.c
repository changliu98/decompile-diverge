void trataCoordenadas(char *linha, int *horizontal, int *vertical) {

    *vertical = linha[0] - 'a';

    if (linha[3] == '\0' || linha[3] == '\n') {
        *horizontal = (linha[2] - '1');
    } else {
        *horizontal = ((linha[2] - '0') * 10) + (linha[3] - '1');
    }
}