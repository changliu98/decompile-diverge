void __cdecl freduce_degree(limb *output)
{
  int i;
  
  for (i = 10; i <= 18; i++)
  {
    output[i - 10] += 19 * output[i];
  }
}