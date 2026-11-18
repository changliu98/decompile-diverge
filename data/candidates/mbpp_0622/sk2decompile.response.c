float findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                             int nums2Size) {
  int i, j, pre, cur, count;
  i = 0;
  j = 0;
  pre = -1;
  cur = -1;
  count = 0;
  while (count < nums1Size + 1) {
    count++;
    if (i == nums1Size) {
      pre = cur;
      cur = nums2[0];
      break;
    } else if (j == nums1Size) {
      pre = cur;
      cur = nums1[0];
      break;
    }
    pre = cur;
    if (nums1[i] <= nums2[j]) {
      cur = nums1[i];
      i++;
    } else {
      cur = nums2[j];
      j++;
    }
  }
  return (pre + cur) / 2.0;
}