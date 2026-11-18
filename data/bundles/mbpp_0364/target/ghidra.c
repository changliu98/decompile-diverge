int func0(char *str)

{
  int iVar1;
  int iVar2;
  undefined4 local_18;
  char *str_local;
  
  iVar1 = get_flip_with_starting_character(str,'0');
  iVar2 = get_flip_with_starting_character(str,'1');
  if (iVar1 < iVar2) {
    local_18 = get_flip_with_starting_character(str,'0');
  }
  else {
    local_18 = get_flip_with_starting_character(str,'1');
  }
  return local_18;
}