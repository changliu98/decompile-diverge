int __cdecl func0(int deciNum)
{
  int octalNum = 0;
  int countval = 1;

  while (deciNum)
  {
    octalNum += countval * (deciNum % 8);
    countval *= 10;
    deciNum /= 8;
  }

  return octalNum;
}