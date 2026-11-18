unsigned int __cdecl ring_size_to_bytes(unsigned int ring_size)
{
    // 4 bytes per unit (e.g., converting number of 32-bit words to bytes)
    return ring_size * 4;
}