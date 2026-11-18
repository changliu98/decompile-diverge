double dst_transform_push(double list[16], int *list_n, double x)
{
 if (*list_n < 16) {
  list[*list_n++] = x;
 }
 return x;
}