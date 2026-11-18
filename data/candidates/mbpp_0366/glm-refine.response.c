int __cdecl func0(int *list_nums, size_t list_length)
{
    // Initialize max_product with the product of the first two elements
    int max_product = list_nums[0] * list_nums[1];

    // Iterate through the array, checking the product of adjacent elements
    for (size_t i = 1; i < list_length - 1; ++i)
    {
        int current_product = list_nums[i] * list_nums[i + 1];
        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    return max_product;
}