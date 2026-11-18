static uint32_t func0(uint32_t hash, const char *data, size_t data_len, uint32_t seed)
{
    if (!data) {
        hash = hash_str(hash, data, seed);
    } else {
        hash = hash_mem(hash, data, data_len, seed);
    }

    return hash_final(hash);
}