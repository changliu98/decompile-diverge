char * scnline(int key,char *p,int c)

{
  char local_24;
  int scnwidth;
  int c_local;
  char *p_local;
  int key_local;
  
  scnwidth = 8;
  p_local = p;
  key_local = key;
  while (scnwidth = scnwidth + -1, scnwidth != 0) {
    key_local = key_local << 1;
    local_24 = (char)c;
    if ((key_local & 0x80U) == 0) {
      local_24 = ' ';
    }
    *p_local = local_24;
    p_local = p_local + 1;
  }
  return p_local;
}