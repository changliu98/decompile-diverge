int func0(char *date)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  char str_year [5];
  char str_day [3];
  char str_month [3];
  int i;
  int yy;
  int dd;
  int mm;
  char *date_local;
  int local_c;
  
  sVar3 = strlen(date);
  if (sVar3 == 10) {
    for (i = 0; i < 10; i = i + 1) {
      if ((i == 2) || (i == 5)) {
        if (date[i] != '-') {
          return 0;
        }
      }
      else if ((date[i] < '0') || ('9' < date[i])) {
        return 0;
      }
    }
    str_month[0] = *date;
    str_month[1] = date[1];
    str_month[2] = '\0';
    str_day[0] = date[3];
    str_day[1] = date[4];
    str_day[2] = '\0';
    str_year[0] = date[6];
    str_year[1] = date[7];
    str_year[2] = date[8];
    str_year[3] = date[9];
    str_year[4] = '\0';
    iVar1 = atoi(str_month);
    iVar2 = atoi(str_day);
    atoi(str_year);
    if ((iVar1 < 1) || (0xc < iVar1)) {
      local_c = 0;
    }
    else if ((iVar2 < 1) || (0x1f < iVar2)) {
      local_c = 0;
    }
    else if (((((iVar1 == 4) || (iVar1 == 6)) || (iVar1 == 9)) || (iVar1 == 0xb)) && (iVar2 == 0x1f)
            ) {
      local_c = 0;
    }
    else if ((iVar1 == 2) && (0x1d < iVar2)) {
      local_c = 0;
    }
    else {
      local_c = 1;
    }
  }
  else {
    local_c = 0;
  }
  return local_c;
}