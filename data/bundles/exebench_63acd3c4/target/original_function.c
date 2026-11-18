void func3 (int i, int *j)
{
 if (i > 0)
 {
  (*j)++;
  return;
 }
 else (*j)--;
 return;
}