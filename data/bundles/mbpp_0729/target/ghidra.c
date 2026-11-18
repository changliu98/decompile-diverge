void func0(int *nums1,int *nums2,int *result,int size)

{
  int i;
  int size_local;
  int *result_local;
  int *nums2_local;
  int *nums1_local;
  
  for (i = 0; i < size; i = i + 1) {
    result[i] = nums1[i] + nums2[i];
  }
  return;
}