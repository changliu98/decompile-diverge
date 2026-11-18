void GetWord(char *out,char *in,int max)

{
  bool bVar1;
  int count;
  int max_local;
  char *in_local;
  char *out_local;
  
  count = 0;
  in_local = in;
  while( true ) {
    bVar1 = false;
    if (*in_local < '!') {
      bVar1 = '\0' < *in_local;
    }
    out_local = out;
    if (!bVar1) break;
    in_local = in_local + 1;
  }
  while( true ) {
    if ((' ' < *in_local) || (bVar1 = false, *in_local < '\0')) {
      bVar1 = count < max + -1;
    }
    if (!bVar1) break;
    *out_local = *in_local;
    count = count + 1;
    in_local = in_local + 1;
    out_local = out_local + 1;
  }
  *out_local = '\0';
  return;
}