void addItemToBag(int *vector1, int *vector2, int nbDim)
{
 int i;

 for(i=0; i<nbDim; i++)
 {
  vector2[i] -= vector1[i];
 }
}