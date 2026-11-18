void calculate_crc(char *crc,char newval)

{
  char newval_local;
  char *crc_local;
  
  *crc = *crc ^ newval;
  return;
}