char *__cdecl func0(char **arr, int size)
{
  int i; // [rsp+0h] [rbp-10h]

  strcpy(func0_ans, " ");
  for ( i = 0; i < size; ++i )
  {
    strcat(func0_ans, " ");
    strcat(func0_ans, arr[i]);
  }
  return func0_ans;
}