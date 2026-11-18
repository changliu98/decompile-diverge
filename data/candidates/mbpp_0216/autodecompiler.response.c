int func0(int *set1,int len1,int *set2,int len2)
{
 int i,j,check = 1;
 for(i = 0;i < len2;i++)
 {
  char chk = 0;
  for(j = 0;j < len1;j++)
  {
   if(set2[i] == set1[j])
   {
    chk = 1;
    break;
   }
   else
   {
    continue;
   }
  }
  if(chk == 0)
  {
   check = 0;
   break;
  }
  else
  {
   continue;
  }
 }
 return check;
}