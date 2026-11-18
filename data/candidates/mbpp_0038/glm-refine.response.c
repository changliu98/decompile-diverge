double __cdecl func0(int *arr, int size)
{
    int first_even = -1;
    int first_odd = -1;

    // Find the first even number in the array
    for (int i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            first_even = arr[i];
            break;
        }
    }

    // Find the first odd number in the array
    for (int i = 0; i < size; ++i) {
        if (arr[i] % 2 != 0) {
            first_odd = arr[i];
            break;
        }
    }

    // If either an even or an odd number was not found, return -1.0
    if (first_even == -1 || first_odd == -1)
        return -1.0;

    // Return the ratio of the first even number to the first odd number
    return (double)first_even / (double)first_odd;
}