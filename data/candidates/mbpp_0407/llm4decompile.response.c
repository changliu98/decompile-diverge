int func0(int n)
{
 char nums[11];
 sprintf(nums, "%d", n);
 int i;
 for (i = strlen(nums) - 2; i >= 0; i--)
  if (nums[i] < nums[i + 1]) {
   char temp[11];
   strcpy(temp, nums + i);
   size_t len = strlen(temp);
   char min = temp[1];
   for (size_t j = 1; j < len; j++)
    if (temp[j] > temp[0] && temp[j] < min)
     min = temp[j];
   for (size_t j = 0; j < len; j++)
    if (temp[j] == min) {
     for (size_t k = j; k < len - 1; k++)
      temp[k] = temp[k + 1];
     temp[len - 1] = '\0';
     break;
    }
   qsort(temp, strlen(temp), sizeof(char), PTR_strcmp);
   nums[i] = min;
   strcpy(nums + i + 1, temp);
   return atoi(nums);
  }
 return 0;
}