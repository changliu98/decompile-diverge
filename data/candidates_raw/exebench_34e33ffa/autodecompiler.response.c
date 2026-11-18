static int _float_to_int(float f, int *i, char **endptr, int base, int flags)
{
 *i = (int)f;
 return 1;
}