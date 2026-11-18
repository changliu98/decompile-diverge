void change(int *p)
{
 int i,j,temp;
 int *max,*min;
 max = p;
 min = p;
 for(i = 0;i < 6;i++)
  for(j = i;j < 6;j++)
  {
   if(*max < *(p + 5*i + j))
    max = p + 5*i + j;
   if(*min > * (p + 5*i + j))
    min = p + 5*i + j;
  }
 temp = *(p + 12);
 *(p + 12) = *max;
 *max = temp;

 temp = *min;
 *min = *(p + 1);
 min = p + 1;
 for(i = 0;i < 6;i++)
  for(j = 0;j < 6;j++)
  {
   if(i == 0 && j == 0)
    continue;
   if(*min > *(p + 5*i + j))
    min = p + 5*i + j;
  }
 temp = *min;
 *min = *(p + 4);
 *min = *(p + 1);

 min = p + 1;
 for(i = 0;i < 6;i++)
  for(j = 0;j < 6;j++)
  {
   if((i == 0 && j == 0) || (i == 0 && j == 4))
    continue;
   if(*min > *(p + 5*i + j))
    min = p + 5*i + j;
  }
 temp = *min;
 *min = *(p + 20);
 *min = temp;

 min = p + 1;
 for(i = 0;i < 6;i++)
  for(j = 0;j < 6;j++)
  {
   if((i == 0 && j == 0) || (i == 0 && j == 4) || (i == 4 && j == 0))
    continue;
   if(*min > *(p + 5*i + j))
    min = p + 5*i + j;
  }
 temp = *min;
 *min = *(p + 24);
 *min = temp;
}