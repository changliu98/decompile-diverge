char * func0(int num)

{
  int i;
  char *syb [13];
  int val [13];
  int num_local;
  
  memcpy(val,&DAT_00102010,0x34);
  memcpy(syb,&PTR_DAT_00103d70,0x68);
  func0::roman_num[0] = '\0';
  i = 0;
  num_local = num;
  while (0 < num_local) {
    for (; val[i] <= num_local; num_local = num_local - val[i]) {
      strcat(func0::roman_num,syb[i]);
    }
    i = i + 1;
  }
  return func0::roman_num;
}