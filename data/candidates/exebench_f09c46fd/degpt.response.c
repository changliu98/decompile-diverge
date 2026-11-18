void minmax(int *current_element, int array_size, int *minimum_value, int *maximum_value)
{
    // Update minimum value if current element is smaller
    if (*current_element < *minimum_value) {
        *minimum_value = *current_element;
    }
    // Update maximum value if current element is larger
    if (*maximum_value < *current_element) {
        *maximum_value = *current_element;
    }
}