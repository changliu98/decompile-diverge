int check_crc_flex(uchar *data_buffer, int buffer_length)
{
    // Validate input size; CRC calculation requires at least 3 bytes
    if (buffer_length < 3) {
        return -1;
    }

    // Initialize CRC register with all bits set to 1
    unsigned short crc_value = 0xffff;
    // Iterate through each byte of the input data
    while (buffer_length--) {
        // Update CRC using the Flex CRC algorithm:
        // 1. XOR the high byte of the current CRC with the current input byte
        // 2. Use the result as an index into the precomputed CRC lookup table
        // 3. Shift the CRC left by 8 bits and XOR with the table value
        crc_value = crc_value << 8 ^ crc_flex_table[(int)((int)(uint)crc_value >> 8 ^ (uint)*data_buffer++)];
    }

    // Return 0 if the final CRC matches the expected value (0x7070), otherwise return -1
    return crc_value == 0x7070 ? 0 : -1;
}