
void leer_datos_instruccion(unsigned char inst_h,unsigned char inst_l,int *codigo_inst,int *dir,int *I)
{
    *I = 0;

    if( (inst_h>>2)%2 == 1)
        *I = 1;

    *codigo_inst = inst_h>>3;

    *dir = 256*((int)inst_h%4) + (int)inst_l;
}
