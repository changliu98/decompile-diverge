void shiftarray(int *queue)
{
 int i;
 for(i = 0; ; i++)
 {
  if(i >= 10) break;
  queue[i] = queue[i + 1];
 }
 queue[9] = -1;
}