void __cdecl BinaryFiles__swap_bytes32(unsigned int *value)
{
    unsigned int v = *value;
    
    *value = ((v >> 24) & 0xFF) |          // Move byte 3 to byte 0
             ((v >> 8)  & 0xFF00) |        // Move byte 2 to byte 1
             ((v << 8)  & 0xFF0000) |      // Move byte 1 to byte 2
             ((v << 24) & 0xFF000000);     // Move byte 0 to byte 3
}