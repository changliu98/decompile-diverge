void passByPointer(int *p)
{
  *p = 4;
  *p = *p * 4;
}