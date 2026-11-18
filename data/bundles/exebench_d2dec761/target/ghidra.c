void leer_datos_instruccion(uchar inst_h,uchar inst_l,int *codigo_inst,int *dir,int *I)

{
  int *I_local;
  int *dir_local;
  int *codigo_inst_local;
  uchar inst_l_local;
  uchar inst_h_local;
  
  *I = 0;
  if ((uint)((int)(uint)inst_h >> 2) % 2 == 1) {
    *I = 1;
  }
  *codigo_inst = (int)(uint)inst_h >> 3;
  *dir = ((uint)inst_h % 4) * 0x100 + (uint)inst_l;
  return;
}