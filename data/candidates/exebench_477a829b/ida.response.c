void __cdecl std::swap[abi:nn200000]<int>(int *const ptrX, int *const ptrY)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *ptrX;
  *ptrX = *ptrY;
  *ptrY = temp;
}