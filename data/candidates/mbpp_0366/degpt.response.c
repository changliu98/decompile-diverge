int func0(int *numbers, size_t count)
{
    // Initialize max_product with the product of the first two elements
    int largest_adjacent_product = numbers[0] * numbers[1];
    // Iterate through the array to find the maximum product of adjacent elements
    for (size_t index = 1; index < count - 1; index++) {
        // Calculate the product of the current element and the next one
        int current_product = numbers[index] * numbers[index + 1];
        // Update max_product if the current product is greater
        if (largest_adjacent_product < current_product) {
            largest_adjacent_product = current_product;
        }
    }
    // Return the maximum product found
    return largest_adjacent_product;
}