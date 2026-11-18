unsigned int __cdecl ice_txd_use_count(unsigned int size)
{
    // The original expression ((85 * size) >> 20) + 1 
    // is a compiler-optimized integer division by 12288.
    return (size / 12288) + 1;
}