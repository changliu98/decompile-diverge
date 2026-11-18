void __cdecl leer_datos_instruccion(unsigned __int8 inst_h, unsigned __int8 inst_l, int *codigo_inst, int *dir, int *I)
{
  *I = 0;
  if ( ((int)inst_h >> 2) % 2 == 1 )
    *I = 1;
  *codigo_inst = (int)inst_h >> 3;
  *dir = inst_l + ((inst_h % 4) << 8);
}