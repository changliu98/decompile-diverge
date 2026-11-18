void __cdecl addItemToBag(int *item, int *roomBag, int nbDim)
{
  // Loop through each dimension up to nbDim
  for (int i = 0; i < nbDim; ++i)
  {
    // Subtract the item's value from the bag's remaining capacity for this dimension
    roomBag[i] -= item[i];
  }
}