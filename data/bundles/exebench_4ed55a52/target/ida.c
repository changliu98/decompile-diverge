void __cdecl shift_array(char *array)
{
  int v1; // ecx
  int element; // [rsp+0h] [rbp-Ch]

  for ( element = 0; array[element]; ++element )
  {
    v1 = element;
    array[v1] += 5;
  }
}