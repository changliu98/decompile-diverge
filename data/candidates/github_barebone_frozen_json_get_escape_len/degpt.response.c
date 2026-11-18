int json_get_escape_len(char *s,int len)

{
  int iVar1;
  bool bVar2;
  int local_2c;
  int len_local;
  char *s_local;
  int local_c;
  
  switch(*s) {
  case '\"':
  case '/':
  case '\\':
  case 'b':
  case 'f':
  case 'n':
  case 'r':
  case 't':
    local_c = 1;
    if (len < 2) {
      local_c = -2;
    }
    break;
  default:
    local_c = -1;
    break;
  case 'u':
    if (len < 6) {
      local_2c = -2;
    }
    else {
      iVar1 = json_isxdigit((int)s[1]);
      bVar2 = false;
      if (iVar1 != 0) {
        iVar1 = json_isxdigit((int)s[2]);
        bVar2 = false;
        if (iVar1 != 0) {
          iVar1 = json_isxdigit((int)s[3]);
          bVar2 = false;
          if (iVar1 != 0) {
            iVar1 = json_isxdigit((int)s[4]);
            bVar2 = iVar1 != 0;
          }
        }
      }
      local_2c = -1;
      if (bVar2) {
        local_2c = 5;
      }
    }
    local_c = local_2c;
  }
  return local_c;
}