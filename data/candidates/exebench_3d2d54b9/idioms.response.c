int foo(int param, void *val)
{
  switch (param) {
  case 9:
    ((struct sios_param *)val)->int_val = 0;
    break;
  default:
    ((struct sios_param *)val)->int_val = 0;
  }
  return 3;
}