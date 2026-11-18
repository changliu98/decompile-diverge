int CalcOffsetAndShift(int col, int row, size_t *byte_offset, size_t *bit_offset)
{
    // Validate input range: x must be between 0 and 0x53 (83), y must be between 0 and 0x2f (47)
    if (((col < 0) || (col > 0x53)) || ((row < 0) || (row > 0x2f))) {
        return -1;
    }
    // Validate output pointers are not NULL
    if (byte_offset == NULL || bit_offset == NULL) {
        return -1;
    }
    // Calculate offset: x + (y / 8) * 0x54 (0x54 is 84, likely row width in bytes)
    *byte_offset = (size_t)(col + (row / 8) * 0x54);
    // Calculate bit shift within the byte: y % 8
    *bit_offset = (size_t)(row % 8);
    return 0;
}