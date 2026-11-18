void func0(int a[], int n)
{
  int out_of_place = -1;
  int index = 0;
  for (index = 0; index < n; index++)
  {
    if (out_of_place >= 0 &&
        ((a[index] >= 0 && a[out_of_place] < 0) ||
         (a[index] < 0 && a[out_of_place] >= 0)))
    {
      right_rotate(a, n, out_of_place, index);
      if (index - out_of_place > 2)
        out_of_place += 2;
      else
        out_of_place = -1;
    }
    if (out_of_place == -1 &&
        ((a[index] >= 0 && index % 2 == 0) ||
         (a[index] < 0 && index % 2 == 1)))
      out_of_place = index;
  }
}