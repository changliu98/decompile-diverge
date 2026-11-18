int get_num_of_sub_boxes(int n)
{
  if (n == 1)
    return 1;
  else
    return pow(2, n - 2);
}