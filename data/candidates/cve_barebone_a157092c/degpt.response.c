void * get_register(int name,int copy)

{
  yankreg_T *pyVar1;
  void *pvVar2;
  char_u *pcVar3;
  int i;
  yankreg_T *reg;
  int copy_local;
  int name_local;
  long *local_10;
  
  get_yank_register(name,0);
  local_10 = alloc(0x18);
  pyVar1 = y_current;
  if (local_10 == (long *)0x0) {
    local_10 = (long *)0x0;
  }
  else {
    *local_10 = (long)y_current->y_array;
    local_10[1] = pyVar1->y_size;
    local_10[2] = *(long *)&pyVar1->y_type;
    if (copy == 0) {
      y_current->y_array = (char_u **)0x0;
    }
    else {
      if (local_10[1] == 0) {
        *local_10 = 0;
      }
      else {
        pvVar2 = alloc(local_10[1] << 3);
        *local_10 = (long)pvVar2;
      }
      if (*local_10 != 0) {
        for (i = 0; (long)i < local_10[1]; i = i + 1) {
          pcVar3 = vim_strsave(y_current->y_array[i]);
          *(char_u **)(*local_10 + (long)i * 8) = pcVar3;
        }
      }
    }
  }
  return local_10;
}