int findMaxXor(int *nums, int numsSize)
{
    int i, j;
    int max_xor = 0;

    for (i = 0; i < numsSize; i++)
    {
        for (j = i + 1; j < numsSize; j++)
        {
            max_xor += (nums[i] ^ nums[j]);
        }
    }

    return max_xor;
}