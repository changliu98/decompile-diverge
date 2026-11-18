BOOL is_bool_str(char *str,BOOL *pbool)

{
  int iVar1;
  BOOL BVar2;
  int64 iVar3;
  double dVar4;
  double vdouble;
  int64 vint;
  BOOL *pbool_local;
  char *str_local;
  BOOL local_c;
  
  if ((str == (char *)0x0) || (pbool == (BOOL *)0x0)) {
    local_c = 0;
  }
  else {
    iVar1 = strcasecmp(str,"true");
    if (((iVar1 == 0) || (iVar1 = strcasecmp(str,"yes"), iVar1 == 0)) ||
       (iVar1 = strcasecmp(str,"on"), iVar1 == 0)) {
      *pbool = 1;
      local_c = 1;
    }
    else {
      iVar1 = strcasecmp(str,"false");
      if (((iVar1 == 0) || (iVar1 = strcasecmp(str,"no"), iVar1 == 0)) ||
         (iVar1 = strcasecmp(str,"off"), iVar1 == 0)) {
        *pbool = 0;
        local_c = 1;
      }
      else {
        BVar2 = is_integer(str);
        if (BVar2 == 0) {
          BVar2 = is_float(str);
          if (BVar2 == 0) {
            local_c = 0;
          }
          else {
            dVar4 = atof(str);
            *pbool = (uint)(dVar4 != 0.0);
            local_c = 1;
          }
        }
        else {
          iVar3 = atoi64(str);
          *pbool = (uint)(iVar3 != 0);
          local_c = 1;
        }
      }
    }
  }
  return local_c;
}