void __cdecl std::swap[abi:nn200000]<int>(int *ptr1, int *ptr2)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}