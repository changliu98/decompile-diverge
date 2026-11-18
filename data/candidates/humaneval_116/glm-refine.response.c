// Helper function to count the number of set bits (1s) in an integer
int count_set_bits(int n) {
    int count = 0;
    while (n > 0) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// Sorts the array in ascending order based on the number of set bits.
// If two numbers have the same number of set bits, it sorts them by value in ascending order.
void __cdecl custom_sort_by_bit_count(int *arr, int size) {
    int i, j, temp;
    
    for (i = 0; i < size; ++i) {
        for (j = i + 1; j < size; ++j) {
            int bits_i = count_set_bits(arr[i]);
            int bits_j = count_set_bits(arr[j]);
            
            // Swap if arr[j] has fewer set bits than arr[i],
            // or if they have the same number of set bits but arr[j] is a smaller number.
            if (bits_j < bits_i || (bits_j == bits_i && arr[j] < arr[i])) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}