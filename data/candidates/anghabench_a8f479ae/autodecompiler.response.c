static unsigned int ice_txd_use_count(unsigned int in_byte_count)
{
    return ((in_byte_count * 85) / (64 * 1024)) + 1;
}