Optimized and annotated for reverse engineering
void __cdecl stack4_push(unsigned __int64 *s, unsigned __int64 e)
{
    // Shift the current state of the stack/accumulator left by 4 bits (equivalent to * 16)
    // and bitwise OR it with the new element 'e'.
    // This implies 'e' is expected to be a 4-bit value (0x0 to 0xF).
    *s = (*s << 4) | (e & 0xF);
}