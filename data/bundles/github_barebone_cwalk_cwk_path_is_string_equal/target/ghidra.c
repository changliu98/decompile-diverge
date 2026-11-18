_Bool cwk_path_is_string_equal(char *first,char *second,size_t first_size,size_t second_size)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  bool bVar4;
  _Bool are_both_separators;
  size_t second_size_local;
  size_t first_size_local;
  char *second_local;
  char *first_local;
  _Bool local_9;
  
  if (first_size == second_size) {
    first_size_local = first_size;
    second_local = second;
    first_local = first;
    if (path_style == CWK_STYLE_UNIX) {
      iVar1 = strncmp(first,second,first_size);
      local_9 = iVar1 == 0;
    }
    else {
      while( true ) {
        bVar4 = false;
        if ((*first_local != '\0') && (bVar4 = false, *second_local != '\0')) {
          bVar4 = first_size_local != 0;
        }
        if (!bVar4) {
          return true;
        }
        pcVar3 = strchr(separators[path_style],(int)*first_local);
        bVar4 = false;
        if (pcVar3 != (char *)0x0) {
          pcVar3 = strchr(separators[path_style],(int)*second_local);
          bVar4 = pcVar3 != (char *)0x0;
        }
        iVar1 = tolower((int)*first_local);
        iVar2 = tolower((int)*second_local);
        if ((iVar1 != iVar2) && (!bVar4)) break;
        first_local = first_local + 1;
        second_local = second_local + 1;
        first_size_local = first_size_local - 1;
      }
      local_9 = false;
    }
  }
  else {
    local_9 = false;
  }
  return local_9;
}