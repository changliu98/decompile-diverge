// Function to sort three integer values pointed to by min, mid, and max pointers
// such that *min <= *mid <= *max after execution
int compare(int *smallest, int *middle, int *largest)
{
    // Ensure *min is less than or equal to *mid
    if (*middle < *smallest) {
        int swap_temp = *smallest;
        *smallest = *middle;
        *middle = swap_temp;
    }
    // Ensure *min is less than or equal to *max
    if (*largest < *smallest) {
        int swap_temp = *smallest;
        *smallest = *largest;
        *largest = swap_temp;
    }
    // Ensure *mid is less than or equal to *max
    if (*largest < *middle) {
        int swap_temp = *middle;
        *middle = *largest;
        *largest = swap_temp;
    }
    // Return 0 to indicate successful sorting
    return 0;
}