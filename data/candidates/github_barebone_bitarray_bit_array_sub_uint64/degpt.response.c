char bit_array_sub_uint64(BIT_ARRAY *bit_array, uint64_t subtrahend)
{
    // If the value to subtract is zero, no change is needed; return success.
    if (subtrahend == 0) {
        return 1;
    }
    // If the current bit array value is less than the value to subtract,
    // we need to borrow from higher-order words.
    else if (*bit_array->words < subtrahend) {
        uint64_t current_lsw_value = *bit_array->words;
        // Iterate through higher-order words to find a non-zero word to borrow from.
        for (word_addr_t word_index = 1; word_index < bit_array->num_of_words; word_index++) {
            if (bit_array->words[word_index] != 0) {
                // Borrow from the current word: decrement it.
                bit_array->words[word_index]--;
                // Set all lower-order words to their maximum value (all 1s)
                // to represent the borrowed amount.
                for (; word_index != 0; word_index--) {
                    bit_array->words[word_index] = 0xffffffffffffffff;
                }
                // Adjust the least significant word:
                // The borrowed amount is (value - wVar1).
                // We subtract this from the max value + 1 (represented as 0xfffffffffffffffe + 1).
                *bit_array->words = 0xfffffffffffffffe - (subtrahend - current_lsw_value);
                return 1;
            }
        }
        // If no non-zero word was found, underflow occurred; return failure.
        return 0;
    }
    // If the current bit array value is greater than or equal to the value to subtract,
    // simply subtract the value from the least significant word.
    else {
        *bit_array->words -= subtrahend;
        return 1;
    }
}