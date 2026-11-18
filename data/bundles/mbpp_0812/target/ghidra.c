char * func0(char *street)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  int length;
  char *street_local;
  
  sVar3 = strlen(street);
  iVar1 = (int)sVar3;
  if (4 < iVar1) {
    iVar2 = strcmp(street + (iVar1 + -4),"Road");
    if (iVar2 == 0) {
      street[iVar1 + -4] = '\0';
      strcat(street,"Rd.");
    }
  }
  return street;
}