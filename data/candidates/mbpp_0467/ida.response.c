int __cdecl func0(int deciNum)
{
  int countval; // [rsp+4h] [rbp-Ch]
  int octalNum; // [rsp+8h] [rbp-8h]

  octalNum = 0;
  countval = 1;
  while ( deciNum )
  {
    octalNum += countval * (deciNum % 8);
    countval *= 10;
    deciNum /= 8;
  }
  return octalNum;
}