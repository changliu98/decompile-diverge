void __cdecl addItemToBag(int *item, int *roomBag, int nbDim)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < nbDim; ++i )
    roomBag[i] -= item[i];
}