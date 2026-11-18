unsigned long
div10quickm(unsigned long *t)
{
 unsigned long quick;

 quick = *t % 10;
 *t = *t / 10;
 return quick;
}