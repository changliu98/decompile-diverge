void addItemToBag(int *item,int *roomBag,int nbDim)

{
  int i;
  int nbDim_local;
  int *roomBag_local;
  int *item_local;
  
  for (i = 0; i < nbDim; i = i + 1) {
    roomBag[i] = roomBag[i] - item[i];
  }
  return;
}