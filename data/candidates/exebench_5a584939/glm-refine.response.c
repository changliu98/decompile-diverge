int __cdecl path_source_set(int *cfg_flag, int value)
{
    // 0xFFFFFFF1 is a bitmask that clears bits 1, 2, and 3 
    // (e.g., ...1111 0001). It preserves all other configuration bits.
    const int FIELD_MASK = 0xE; // Binary: ...0000 1110

    *cfg_flag &= ~FIELD_MASK;   // Clear the target 3-bit field
    *cfg_flag |= value & FIELD_MASK; // Apply the new value to the field

    return *cfg_flag;
}