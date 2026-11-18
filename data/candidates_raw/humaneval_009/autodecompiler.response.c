int *get_max_array(int *nums, int numsSize)
{
 if (numsSize < 1) {
  int *ret = NULL;
  return(ret);
 }

 int *ret, max;
 int i;

 ret = malloc(numsSize * sizeof(int));
 if (!ret)
  return(NULL);

 max = nums[0];
 for (i = 0; i < numsSize; i++) {
  if (nums[i] > max)
   max = nums[i];
  ret[i] = max;
 }
 return(ret);
}