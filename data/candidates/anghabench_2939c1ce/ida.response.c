void __cdecl swapIntEndian(int *pInteger)
{
  char b; // [rsp+1h] [rbp-11h]
  char ba; // [rsp+1h] [rbp-11h]

  b = *(_BYTE *)pInteger;
  *(_BYTE *)pInteger = *((_BYTE *)pInteger + 3);
  *((_BYTE *)pInteger + 3) = b;
  ba = *((_BYTE *)pInteger + 1);
  *((_BYTE *)pInteger + 1) = *((_BYTE *)pInteger + 2);
  *((_BYTE *)pInteger + 2) = ba;
}