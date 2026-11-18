void leer_datos_instruccion(unsigned char inst_h, unsigned char inst_l, int *codigo, int *parametro, int *tipo)
{
    *tipo = 0;
    if((inst_h >> 2) % 2 == 1)
        *tipo = 1;

    *codigo = inst_h >> 3;
    *parametro = ((inst_h % 4) << 8) + inst_l;
}