char * func0(char *a,char *b)

{
  char *__nptr;
  char *__nptr_00;
  double dVar1;
  double dVar2;
  char *local_58;
  double numb;
  double numa;
  int i_1;
  int i;
  char *b_modified;
  char *a_modified;
  char *end;
  char *b_local;
  char *a_local;
  char *local_10;
  
  b_local = b;
  a_local = a;
  __nptr = strdup(a);
  __nptr_00 = strdup(b_local);
  for (i = 0; __nptr[i] != '\0'; i = i + 1) {
    if (__nptr[i] == ',') {
      __nptr[i] = '.';
    }
  }
  for (i_1 = 0; __nptr_00[i_1] != '\0'; i_1 = i_1 + 1) {
    if (__nptr_00[i_1] == ',') {
      __nptr_00[i_1] = '.';
    }
  }
  dVar1 = strtod(__nptr,&end);
  if (*end == '\0') {
    dVar2 = strtod(__nptr_00,&end);
    if (*end == '\0') {
      free(__nptr);
      free(__nptr_00);
      if ((dVar1 != dVar2) || (NAN(dVar1) || NAN(dVar2))) {
        if (dVar1 <= dVar2) {
          local_58 = b_local;
        }
        else {
          local_58 = a_local;
        }
        local_10 = local_58;
      }
      else {
        local_10 = "None";
      }
    }
    else {
      free(__nptr);
      free(__nptr_00);
      local_10 = "Invalid input";
    }
  }
  else {
    free(__nptr);
    free(__nptr_00);
    local_10 = "Invalid input";
  }
  return local_10;
}