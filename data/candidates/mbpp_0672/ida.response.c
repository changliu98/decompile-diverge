int __cdecl func0(int num1, int num2, int num3)
{
  if ( num1 >= num2 && num1 >= num3 )
    return num1;
  if ( num2 < num1 || num2 < num3 )
    return num3;
  return num2;
}