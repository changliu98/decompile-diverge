void __cdecl shift_array(char *array)
{
  for (int i = 0; array[i]; ++i)
  {
    array[i] += 5;
  }
}