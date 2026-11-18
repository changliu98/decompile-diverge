char **func0(int *id, int cant, char **nombres) {
    char **nombres_aux = (char **)malloc(sizeof(char) * 2 * cant);
    int i = 0, j = 0;
    while (j < cant) {
        sprintf(nombres_aux[i++], "Hilo %d\n", id[j++]);
        nombres_aux[i++] = nombres[j];
    }
    return nombres_aux;
}