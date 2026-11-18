void __cdecl func0(int *nums1, int *nums2, int *result, int size)
{
  int i; // [rsp+0h] [rbp-20h]

  for ( i = 0; i < size; ++i )
    result[i] = nums2[i] + nums1[i];
}