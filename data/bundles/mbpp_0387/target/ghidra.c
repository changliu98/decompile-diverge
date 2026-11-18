char * func0(char *N)

{
  int iVar1;
  size_t sVar2;
  int l;
  char *N_local;
  char *local_10;
  
  sVar2 = strlen(N);
  iVar1 = (int)sVar2;
  if (((((N[iVar1 + -1] == '0') || (N[iVar1 + -1] == '2')) || (N[iVar1 + -1] == '4')) ||
      ((N[iVar1 + -1] == '6' || (N[iVar1 + -1] == '8')))) ||
     ((N[iVar1 + -1] == 'A' || ((N[iVar1 + -1] == 'C' || (N[iVar1 + -1] == 'E')))))) {
    local_10 = "Even";
  }
  else {
    local_10 = "Odd";
  }
  return local_10;
}