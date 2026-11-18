void func0(int number,char *result)

{
  int pos;
  int num [13];
  char *rep [13];
  char *result_local;
  int number_local;
  
  memcpy(rep,&PTR_DAT_00103d70,0x68);
  memcpy(num,&DAT_00102040,0x34);
  pos = 0;
  *result = '\0';
  number_local = number;
  while (0 < number_local) {
    for (; num[pos] <= number_local; number_local = number_local - num[pos]) {
      strcat(result,rep[pos]);
    }
    if (0 < number_local) {
      pos = pos + 1;
    }
  }
  return;
}