bool bit_array_sub_uint64(BIT_ARRAY *bitarr, uint64_t value) {
    if (value == 0) {
        return true;
    }

    if (value <= bitarr->words[0]) {
        bitarr->words[0] -= value;
        return true;
    }

    uint64_t diff = value - bitarr->words[0];
    word_addr_t i = 1;
    while (i < bitarr->num_of_words && bitarr->words[i] == 0) {
        i++;
    }

    if (i == bitarr->num_of_words) {
        return false;
    }

    bitarr->words[i]--;
    while (i > 0) {
        bitarr->words[i] = (uint64_t) 0xffffffffffffffff;
        i--;
    }

    bitarr->words[0] = (uint64_t) 0xffffffffffffffff - diff;
    return true;
}