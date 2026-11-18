void StoreUintptr(volatile int *flag, int val)
{
 int old = *flag;
 while (!(((old ^ (val)) & 1) == 0))
 {
  old = *flag;
 }
 *flag = val;
}