int func0(int deciNum)

{
  int remainder;
  int countval;
  int octalNum;
  int deciNum_local;
  
  octalNum = 0;
  countval = 1;
  for (deciNum_local = deciNum; deciNum_local != 0; deciNum_local = deciNum_local / 8) {
    octalNum = (deciNum_local % 8) * countval + octalNum;
    countval = countval * 10;
  }
  return octalNum;
}