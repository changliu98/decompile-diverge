void fn_5(double *array_x, double *array_y, double *product_array, double *final_product)
{
    int index;
    // Loop through the first 10 elements of arrays a and b
    for (index = 0; index < 10; index = index + 1) {
        // Calculate the product of corresponding elements and store in sum array
        product_array[index] = array_x[index] * array_y[index];
    }
    // Calculate the product of the 11th elements (index 10) and store in prod
    // Note: This line is outside the loop and uses the final value of i (10)
    final_product[index] = array_x[index] * array_y[index];
    return;
}