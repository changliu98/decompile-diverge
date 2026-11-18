void clamp(int *a,int *b,int max)

{
  int max_local;
  int *b_local;
  int *a_local;
  
  *b = *a / max + *b;
  *a = *a % max;
  return;
}