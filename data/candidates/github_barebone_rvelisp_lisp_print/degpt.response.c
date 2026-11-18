void print(double x)

{
  FILE *__stream;
  uint32_t uVar1;
  double x_local;
  
  uVar1 = T(x);
  __stream = out;
  if (uVar1 == 0x7ff9) {
    uVar1 = ord(x);
    fprintf((FILE *)__stream,"<%s>",prim[uVar1].s);
  }
  else if (uVar1 == 0x7ffa) {
    uVar1 = ord(x);
    fprintf((FILE *)__stream,"%s",(long)cell + (ulong)uVar1);
  }
  else if (uVar1 == 0x7ffb) {
    uVar1 = ord(x);
    fprintf((FILE *)__stream,"\"%s\"",(long)cell + (ulong)uVar1);
  }
  else if (uVar1 == 0x7ffc) {
    printlist(x);
  }
  else if (uVar1 == 0x7ffe) {
    uVar1 = ord(x);
    fprintf((FILE *)__stream,"{%u}",(ulong)uVar1);
  }
  else if (uVar1 == 0x7fff) {
    uVar1 = ord(x);
    fprintf((FILE *)__stream,"[%u]",(ulong)uVar1);
  }
  else if (uVar1 == 0xffff) {
    fprintf((FILE *)out,"()");
  }
  else {
    fprintf((FILE *)out,"%.17lg",x);
  }
  return;
}