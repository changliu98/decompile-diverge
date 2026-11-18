void gsm_hex_from_byte(char *hex,int val)

{
  int val_local;
  char *hex_local;
  
  *hex = "0123456789abcdef"[(int)(val >> 4 & 0xf)];
  hex[1] = "0123456789abcdef"[(int)(val & 0xf)];
  return;
}