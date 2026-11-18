bool bit_array_load(BIT_ARRAY *ba, FILE *fp)
{
    uint64_t tmp;
    size_t size;
    word_index_t i;


    if (fread(&tmp, 1, 8, fp) != 8)
        return false;

    tmp = le64_to_cpu((uint8_t *)&tmp);
    bit_array_resize_critical(ba, (bit_index_t)tmp);


    size = (ba->num_of_bits + 7) / 8;
    if (fread(ba->words, 1, size, fp) != size)
        return false;


    for (i = 0; i < ba->num_of_words; i++)
        ba->words[i] = le64_to_cpu((uint8_t *)&ba->words[i]);

    _mask_top_word(ba);

    return true;
}