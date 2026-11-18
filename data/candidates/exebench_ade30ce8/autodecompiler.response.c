void cross_product(float result[3], const float v1[3], const float v2[3])
{
  result[0]=((float) (((*(unsigned int *) &v1[1]) ^ ((unsigned int) 1 << 31)) + (*(unsigned int *) &v2[2])) + ((float) (((*(unsigned int *) &v1[2]) ^ ((unsigned int) 1 << 31)) - (*(unsigned int *) &v2[1]))));
  result[1]=((float) (((*(unsigned int *) &v1[2]) ^ ((unsigned int) 1 << 31)) + (*(unsigned int *) &v2[0])) + ((float) (((*(unsigned int *) &v1[0]) ^ ((unsigned int) 1 << 31)) - (*(unsigned int *) &v2[2]))));
  result[2]=((float) (((*(unsigned int *) &v1[0]) ^ ((unsigned int) 1 << 31)) + (*(unsigned int *) &v2[1])) + ((float) (((*(unsigned int *) &v1[1]) ^ ((unsigned int) 1 << 31)) - (*(unsigned int *) &v2[0]))));
}