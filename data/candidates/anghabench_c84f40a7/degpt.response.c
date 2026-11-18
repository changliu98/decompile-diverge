int byte_row_gbk1(int input_byte)
{
    // Check if the byte is within the valid range for GBK high byte (0x81 to 0xFE)
    if ((input_byte < 0x81) || (0xfe < input_byte)) {
        return -1;
    }
    // Calculate and return the row index by subtracting the base value 0x81
    return input_byte - 0x81;
}