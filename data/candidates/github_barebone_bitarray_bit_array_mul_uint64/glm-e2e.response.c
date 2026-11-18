void bit_array_mul_uint64(struct BitArray *arr, uint64_t multiplier) {
    // If the array is empty or the multiplier is 1, there is nothing to do
    if (arr->length == 0 || multiplier == 1) {
        return;
    }

    // If the multiplier is 0, clear the array (likely via bit_array_clear_all)
    if (multiplier == 0) {
        // The original code calls a function at <bit_array_mul_uint64+0x43> 
        // which resolves to bit_array_clear_all based on the section list.
        bit_array_clear_all(arr);
        return;
    }

    // Iterate from the most significant bit down to 0
    for (uint64_t i = arr->length; i > 0; i--) {
        uint64_t bit_index = i - 1;
        uint64_t word_index = bit_index / 64;
        uint64_t bit_offset = bit_index % 64;

        // If the current bit is set
        if ((arr->data[word_index] >> bit_offset) & 1) {
            // Clear the bit
            arr->data[word_index] &= ~(1ULL << bit_offset);
            
            // Recursively call the internal multiplication helper
            _bit_array_mul_uint64(arr, bit_index, multiplier);
        }
    }
}