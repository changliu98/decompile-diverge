void __cdecl a_store(volatile int *p, int x)
{
  signed __int32 vars0; // [rsp+Ch] [rbp+0h] BYREF

  *p = x;
  _InterlockedOr(&vars0, 0);
}