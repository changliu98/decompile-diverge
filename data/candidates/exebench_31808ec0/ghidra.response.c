void trataCoordenadas(char *linha,int *horizontal,int *vertical)

{
  int *vertical_local;
  int *horizontal_local;
  char *linha_local;
  
  *vertical = *linha + -0x61;
  if ((linha[3] == '\0') || (linha[3] == '\n')) {
    *horizontal = linha[2] + -0x31;
  }
  else {
    *horizontal = (linha[2] + -0x30) * 10 + (int)linha[3] + -0x31;
  }
  return;
}