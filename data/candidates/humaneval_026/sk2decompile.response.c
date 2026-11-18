int* func0(int* nums, int numsSize, int* returnSize) {
  int* result = malloc(numsSize * sizeof(int));
  int* unique = calloc(numsSize, sizeof(int));
  int* dup = calloc(numsSize, sizeof(int));
  int uniqueSize = 0;
  int dupSize = 0;
  int resultSize = 0;
  for (int i = 0; i < numsSize; i++) {
    int num = nums[i];
    int isDup = 0;
    for (int j = 0; j < dupSize; j++) {
      if (dup[j] == num) {
        isDup = 1;
        break;
      }
    }
    if (isDup) {
      continue;
    }
    int isUnique = 0;
    for (int j = 0; j < uniqueSize; j++) {
      if (unique[j] == num) {
        isUnique = 1;
        break;
      }
    }
    if (isUnique) {
      dup[dupSize++] = num;
    } else {
      unique[uniqueSize++] = num;
    }
  }
  for (int i = 0; i < numsSize; i++) {
    int num = nums[i];
    int isDup = 0;
    for (int j = 0; j < dupSize; j++) {
      if (dup[j] == num) {
        isDup = 1;
        break;
      }
    }
    if (isDup) {
      continue;
    }
    result[resultSize++] = num;
  }
  *returnSize = resultSize;
  free(unique);
  free(dup);
  return result;
}