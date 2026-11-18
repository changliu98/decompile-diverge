void set_page_data(int potval,char *buf)

{
  int blen;
  int len;
  uint *wordp;
  uint word;
  char *buf_local;
  int potval_local;
  
  *(int *)buf = potval;
  return;
}