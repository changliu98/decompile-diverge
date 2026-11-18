int get_hashmask(int *size)
{
 int i;

 for (i = 1; i < *size; i <<= 1)
  ;
 *size = i;
 return i - 1;
}