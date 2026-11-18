int rdbEncodeInteger(longlong inputValue, uchar *encodedBuffer)
{
    // Check if the value fits in an 8-bit signed integer (-128 to 127)
    if (inputValue >= -0x80 && inputValue <= 0x7f) {
        // Set the encoding header: RDB_ENCVAL prefix with INT8 type marker
        *encodedBuffer = (byte)(RDB_ENCVAL << 6) | (byte)RDB_ENC_INT8;
        // Store the 8-bit value in the next byte
        encodedBuffer[1] = (uchar)inputValue;
        // Return total encoded length (1 header + 1 value byte)
        return 2;
    }
    // Check if the value fits in a 16-bit signed integer (-32768 to 32767)
    if (inputValue >= -0x8000 && inputValue <= 0x7fff) {
        // Set the encoding header: RDB_ENCVAL prefix with INT16 type marker
        *encodedBuffer = (byte)(RDB_ENCVAL << 6) | (byte)RDB_ENC_INT16;
        // Store the least significant byte of the 16-bit value
        encodedBuffer[1] = (uchar)inputValue;
        // Store the most significant byte of the 16-bit value
        encodedBuffer[2] = (uchar)((ulong)inputValue >> 8);
        // Return total encoded length (1 header + 2 value bytes)
        return 3;
    }
    // Check if the value fits in a 32-bit signed integer (-2147483648 to 2147483647)
    if (inputValue >= -0x80000000 && inputValue <= 0x7fffffff) {
        // Set the encoding header: RDB_ENCVAL prefix with INT32 type marker
        *encodedBuffer = (byte)(RDB_ENCVAL << 6) | (byte)RDB_ENC_INT32;
        // Store the least significant byte of the 32-bit value
        encodedBuffer[1] = (uchar)inputValue;
        // Store the second least significant byte
        encodedBuffer[2] = (uchar)((ulong)inputValue >> 8);
        // Store the third least significant byte
        encodedBuffer[3] = (uchar)((ulong)inputValue >> 0x10);
        // Store the most significant byte
        encodedBuffer[4] = (uchar)((ulong)inputValue >> 0x18);
        // Return total encoded length (1 header + 4 value bytes)
        return 5;
    }
    // Return 0 if the value does not fit in any of the supported integer encodings
    return 0;
}