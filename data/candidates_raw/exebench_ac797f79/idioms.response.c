void takeItem(int *item, int *roomBag, int nbDim)
{
  int i;
  for (i = 0; i < nbDim; i++)
    roomBag[i] -= item[i];
}