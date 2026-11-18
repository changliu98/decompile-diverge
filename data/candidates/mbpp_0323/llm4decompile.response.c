void func0(int *arr, int n)
{
 int i, out_of_place = -1;
 for (i = 0; i < n; i++) {
  if (out_of_place >= 0 && ((arr[i] >= 0 && arr[out_of_place] < 0) || (arr[i] < 0 && arr[out_of_place] >= 0))) {
   right_rotate(arr, n, out_of_place, i);
   if (i - out_of_place >= 3)
    out_of_place += 2;
   else
    out_of_place = -1;
  }
  if (out_of_place == -1) {
   if (arr[i] >= 0 && i % 2 == 0)
    out_of_place = i;
   else if (arr[i] < 0 && i % 2 == 1)
    out_of_place = i;
  }
 }
}