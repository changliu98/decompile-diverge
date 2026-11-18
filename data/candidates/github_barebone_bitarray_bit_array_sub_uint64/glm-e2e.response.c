Function signature inferred from the assembly
int bit_array_sub_uint64(struct BitArray *bitarr, uint64_t value) {
    int ret;

    // If the value to subtract is 0, no operation is needed
    if (value == 0) {
        ret = 1;
        goto end;
    }

    // If the least significant word is greater than or equal to the value,
    // simply subtract it from the least significant word.
    if (bitarr->words[0] >= value) {
        bitarr->words[0] -= value;
        ret = 1;
        goto end;
    }

    // Otherwise, an underflow will occur. We need to borrow from higher words.
    // Calculate the remaining amount to subtract after underflowing the 0th word.
    value -= bitarr->words[0];

    // Traverse the words array to find a word to borrow from
    for (size_t i = 1; i < bitarr->num_words; i++) {
        if (bitarr->words[i] > 0) {
            // Borrow 1 from this word
            bitarr->words[i]--;

            // Set all words we skipped over to UINT64_MAX (all 1s)
            while (i > 0) {
                i--;
                bitarr->words[i] = UINT64_MAX;
            }

            // Subtract the remaining value from the now-borrowed least significant word
            bitarr->words[0] = (UINT64_MAX - value) - 1;
            ret = 1;
            goto end;
        }
    }

    // If we finish the loop without returning, the bit array underflowed entirely
    ret = 0;

end:
    return ret;
}