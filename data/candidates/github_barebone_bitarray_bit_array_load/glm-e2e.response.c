int bit_array_load(BitArray *bitarr, FILE *stream) {
    uint64_t num_bits;
    uint64_t num_words;
    uint64_t i;

    // Read the 8-byte header (number of bits) from the stream
    if (fread(&num_bits, 1, 8, stream) != 8) {
        return 0;
    }

    // Convert from little-endian to CPU byte order
    num_bits = le64_to_cpu(num_bits);

    // Resize the bit array to accommodate the number of bits
    bit_array_resize(bitarr, num_bits);

    // Calculate the number of 64-bit words required to store the bits
    // Equivalent to: (num_bits + 7) / 8
    num_words = (bitarr->num_bits + 7) >> 3;

    // Read the exact number of words from the stream
    if (fread(bitarr->words, 1, num_words, stream) != num_words) {
        return 0;
    }

    // Convert each word from little-endian to CPU byte order
    for (i = 0; i < bitarr->num_words; i++) {
        bitarr->words[i] = le64_to_cpu(bitarr->words[i]);
    }

    // Recalculate internal state (e.g., hashes or masks) after loading
    bit_array_hash(bitarr, 0);

    return 1;
}