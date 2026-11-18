int __cdecl func0(int *arr, int size)
{
  char numStr[20];
  char temp[256];

  memset(temp, 0, sizeof(temp));
  
  for (int i = 0; i < size; ++i)
  {
    sprintf(numStr, "%u", (unsigned int)arr[i]);
    strcat(temp, numStr);
  }
  
  return atoi(temp);
}