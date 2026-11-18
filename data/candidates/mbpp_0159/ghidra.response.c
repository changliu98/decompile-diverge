char * func0(char *month,int days)

{
  int iVar1;
  char *season;
  int days_local;
  char *month_local;
  
  iVar1 = strcmp(month,"January");
  if (((iVar1 == 0) || (iVar1 = strcmp(month,"February"), iVar1 == 0)) ||
     (iVar1 = strcmp(month,"March"), iVar1 == 0)) {
    season = "winter";
  }
  else {
    iVar1 = strcmp(month,"April");
    if (((iVar1 == 0) || (iVar1 = strcmp(month,"May"), iVar1 == 0)) ||
       (iVar1 = strcmp(month,"June"), iVar1 == 0)) {
      season = "spring";
    }
    else {
      iVar1 = strcmp(month,"July");
      if (((iVar1 == 0) || (iVar1 = strcmp(month,"August"), iVar1 == 0)) ||
         (iVar1 = strcmp(month,"September"), iVar1 == 0)) {
        season = "summer";
      }
      else {
        season = "autumn";
      }
    }
  }
  iVar1 = strcmp(month,"March");
  if (((iVar1 == 0) && (0x13 < days)) ||
     (((iVar1 = strcmp(month,"June"), iVar1 == 0 && (0x14 < days)) ||
      ((iVar1 = strcmp(month,"September"), iVar1 == 0 && (0x15 < days)))))) {
    iVar1 = strcmp(month,"March");
    if (iVar1 == 0) {
      season = "spring";
    }
    iVar1 = strcmp(month,"June");
    if (iVar1 == 0) {
      season = "summer";
    }
    iVar1 = strcmp(month,"September");
    if (iVar1 == 0) {
      season = "autumn";
    }
  }
  else {
    iVar1 = strcmp(month,"December");
    if ((iVar1 == 0) && (0x14 < days)) {
      season = "winter";
    }
  }
  return season;
}