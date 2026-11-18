int __cdecl func0(int *L, int size)
{
  int i; // [rsp+Ch] [rbp-134h]
  char numStr[20]; // [rsp+10h] [rbp-130h] BYREF
  char temp[256]; // [rsp+30h] [rbp-110h] BYREF
  int sizea; // [rsp+134h] [rbp-Ch]
  int *La; // [rsp+138h] [rbp-8h]

  La = L;
  sizea = size;
  memset(temp, 0, sizeof(temp));
  for ( i = 0; i < sizea; ++i )
  {
    sprintf(numStr, "%d", (unsigned int)La[i]);
    strcat(temp, numStr);
  }
  return atoi(temp);
}