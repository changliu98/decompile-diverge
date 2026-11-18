void ft_div_mod(int a,int b,int *div,int *mod)

{
  int *mod_local;
  int *div_local;
  int b_local;
  int a_local;
  
  *div = a / b;
  *mod = a % b;
  return;
}