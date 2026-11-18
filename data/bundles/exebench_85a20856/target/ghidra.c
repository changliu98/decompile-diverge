void changeValues(int *n,float *a,char *c)

{
  char *c_local;
  float *a_local;
  int *n_local;
  
  *n = *n + 1;
  *a = DAT_00102004 + *a;
  *c = *c + '\x04';
  return;
}