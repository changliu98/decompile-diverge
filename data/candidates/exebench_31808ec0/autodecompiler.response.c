void trataCoordenadas(char *position, int *row, int *col) {
    *col = position[0] - 'a';
    if (position[3] == '\0' || position[3] == '\n') {

        *row = position[2] - '1';
        return;
    }
    *row = (position[2] - '0') * 10 + (position[3] - '0') - 1;
}