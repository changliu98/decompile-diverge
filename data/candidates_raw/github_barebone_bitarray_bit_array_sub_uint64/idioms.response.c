static inline char bit_array_set(struct bit_array *bitarr, unsigned long value)
{
    if (value == 0)
        return 1;
    if (bitarr->words[0] >= value) {
        bitarr->words[0] -= value;
        return 1;
    }
    else {
        value -= bitarr->words[0];
        for (word_addr_t i = 1; i < bitarr->num_of_words; i++) {
            if (bitarr->words[i] != 0) {
                bitarr->words[i]--;
                for (word_addr_t j = i; j > 0; j--)
                    bitarr->words[j] = -1;
                bitarr->words[0] = -1 - value - 1;
                return 1;
            }
        }
    }
    return 0;
}