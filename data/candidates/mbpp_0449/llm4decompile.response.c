char* func0(int x1, int y1, int x2, int y2, int x3, int y3)
{
 int result;
 result = x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2);
 if (result==0)
  return "No";
 else
  return "Yes";
}