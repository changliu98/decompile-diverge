int * func0(char *values,int *size)

{
  ushort **ppuVar1;
  long lVar2;
  bool bVar3;
  int val;
  char *end;
  char *start;
  int count;
  int *size_local;
  char *values_local;
  
  count = 0;
  start = values;
  size_local = size;
  values_local = values;
  while (*start != '\0') {
    while( true ) {
      bVar3 = false;
      if (*start != '\0') {
        ppuVar1 = __ctype_b_loc();
        bVar3 = false;
        if (((*ppuVar1)[(int)*start] & 0x800) == 0) {
          bVar3 = *start != '-';
        }
      }
      if (!bVar3) break;
      start = start + 1;
    }
    if (*start == '\0') break;
    lVar2 = strtol(start,&end,10);
    if ((start == end) || ((*end != ',' && (*end != '\0')))) {
      while( true ) {
        bVar3 = false;
        if (*end != '\0') {
          bVar3 = *end != ',';
        }
        if (!bVar3) break;
        end = end + 1;
      }
    }
    else {
      func0::out[count] = (int)lVar2;
      count = count + 1;
    }
    start = end;
  }
  *size_local = count;
  return func0::out;
}