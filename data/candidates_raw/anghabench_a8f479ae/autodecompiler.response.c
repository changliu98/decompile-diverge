static unsigned int _xte_chunk_count_for_byte_count(unsigned int in_byte_count)
{
    return ((in_byte_count * 85) / (64 * 1024)) + 1;
}