void leer_datos_instruccion(unsigned char inst_h, unsigned char inst_l, int *codigo_inst, int *dir, int *I)
{
  *I = 0;
  if ( (inst_h & 0x10) == 0x10 )
    *I = 1;
  *codigo_inst = (inst_h & 0xe0) >> 3;
  *dir = (inst_h & 0x03) << 8;
  *dir = *dir + inst_l;
  return;
}