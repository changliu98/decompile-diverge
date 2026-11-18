void int2str(int value,int i,char *output)

{
  int j;
  char *output_local;
  int i_local;
  int value_local;
  
  output_local = output;
  for (i_local = i; i_local != 0; i_local = i_local / 10) {
    *output_local =
         (char)((long)((ulong)(uint)((int)((long)value / (long)i_local) >> 0x1f) << 0x20 |
                      (long)value / (long)i_local & 0xffffffffU) % 10) + '0';
    output_local = output_local + 1;
  }
  return;
}