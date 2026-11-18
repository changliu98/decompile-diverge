int func0(int *nums, int size)
{
    int i;
    int product = 1;

    for (i = 0; i < size; i++) {
        product *= nums[i];
    }

    return product;
}