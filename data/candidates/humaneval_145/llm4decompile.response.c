int* func0(int* nums, int size)
{
    int i, j, k, temp, sum;
    char str[12];
    int *sumdigit = malloc(size * sizeof(int));

    for (i = 0; i < size; i++) {
        sprintf(str, "%d", abs(nums[i]));
        sum = 0;
        for (j = 1; j < strlen(str); j++)
            sum += str[j] - '0';
        sumdigit[i] = (nums[i] > 0 ? str[0] - '0' : -(str[0] - '0')) + sum;
    }

    for (i = 0; i < size; i++)
        for (j = 1; j < size; j++)
            if (sumdigit[j - 1] > sumdigit[j]) {
                temp = sumdigit[j];
                sumdigit[j] = sumdigit[j - 1];
                sumdigit[j - 1] = temp;

                temp = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = temp;
            }

    free(sumdigit);

    return nums;
}