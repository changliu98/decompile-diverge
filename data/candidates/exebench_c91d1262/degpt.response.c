int ISORegexp__get_cclass(char *pattern,int ppos,int *len,int *from,int *to,int *reverse)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  int *reverse_local;
  int *to_local;
  int *from_local;
  int *len_local;
  int ppos_local;
  char *pattern_local;
  int local_c;
  
  if (pattern[ppos] == '^') {
    ppos_local = ppos + 1;
    *reverse = 1;
  }
  else {
    *reverse = 0;
    ppos_local = ppos;
  }
  cVar1 = pattern[ppos_local];
  if (cVar1 == ' ') {
    *len = 1;
    local_c = 3;
  }
  else if (cVar1 == '%') {
    iVar2 = ppos_local + 1;
    *len = 2;
    switch(pattern[iVar2]) {
    case 'C':
      local_c = 4;
      break;
    default:
      *from = iVar2;
      *to = iVar2;
      local_c = 8;
      break;
    case 'P':
      local_c = 7;
      break;
    case 'c':
      local_c = 1;
      break;
    case 'd':
      local_c = 2;
      break;
    case 'i':
      local_c = 5;
      break;
    case 'p':
      local_c = 6;
      break;
    case 't':
      local_c = 9;
    }
  }
  else if (cVar1 == '[') {
    *from = ppos_local + 2;
    while( true ) {
      bVar3 = false;
      if (pattern[ppos_local] != '\0') {
        bVar3 = pattern[ppos_local] != ']';
      }
      if (!bVar3) break;
      ppos_local = ppos_local + 1;
    }
    *to = ppos_local + -1;
    *len = (ppos_local - *from) + 1;
    local_c = 8;
  }
  else {
    *len = 1;
    *from = ppos_local;
    *to = ppos_local;
    local_c = 8;
  }
  return local_c;
}