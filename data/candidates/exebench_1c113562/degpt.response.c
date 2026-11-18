void fn_5(double *first_array, double *second_array, double *product_array, double *final_product)
{
    int index;
    // Loop through the first 10 elements of arrays a and b
    for (index = 0; index < 10; index = index + 1) {
        // Store the product of corresponding elements in sum array
        product_array[index] = first_array[index] * second_array[index];
    }
    // Note: This line uses 'i' which is now 10, leading to out-of-bounds access
    // Store the product of elements at index 10 in prod array (undefined behavior)
    final_product[index] = first_array[index] * second_array[index];
    return;
}