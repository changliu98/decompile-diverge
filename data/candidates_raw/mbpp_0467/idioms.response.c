int deciToOctal(int deciNum)
{
  int octalNum = 0;
  int countval = 1;
  while (deciNum != 0)
  {
    octalNum += countval * (deciNum % 8);
    countval = countval * 10;
    deciNum = deciNum / 8;
  }
  return octalNum;
}