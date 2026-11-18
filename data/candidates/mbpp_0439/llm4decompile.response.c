int func0(int *L, int size)
{
 int i;
 char numStr[20];
 char temp[256];
 memset(temp, 0, 256);

 for(i = 0; i < size; i++)
 {
  sprintf(numStr, "%d", L[i]);
  strcat(temp, numStr);
 }

 return atoi(temp);
}