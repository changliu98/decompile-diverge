void leer_datos_instruccion(char arg1, char arg2, int *arg3, int *arg4, int *arg5) {
    *arg5 = 0;
    if ((arg1 >> 2) % 2 == 1) {
        *arg5 = 1;
    }
    *arg3 = arg1 >> 3;
    *arg4 = ((arg1 % 4) << 8) + arg2;
}