int func0(int deciNum)
{
 int remainder, countval = 1, octalNum = 0;

 while (deciNum != 0)
 {
  remainder = deciNum % 8;
  octalNum = octalNum + remainder * countval;
  countval = countval * 10;
  deciNum = deciNum / 8;
 }
 return octalNum;
}