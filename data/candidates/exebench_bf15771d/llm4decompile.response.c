int computesizes(int *nums, int *narray) {
  int i, twotoi, num, total, max, maxnum;

  i = 0;
  twotoi = 1;
  total = 0;
  max = 0;
  maxnum = 0;
  while (twotoi / 2 < *narray) {
    num = nums[i];
    if (num > 0) {
      total += num;
      if (total > twotoi / 2) {
        max = twotoi;
        maxnum = total;
      }
    }
    if (total == *narray) {
      break;
    }
    i++;
    twotoi *= 2;
  }
  *narray = max;
  return maxnum;
}