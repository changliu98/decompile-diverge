void encode_vector(char *encoded_string, int horizontal_value, int vertical_value)
{
    // Encode the high 3 bits of y into the first character (space-padded)
    encoded_string[0] = (char)(vertical_value >> 5) + ' ';
    // Encode the low 5 bits of y into the second character (offset by 0x60)
    encoded_string[1] = ((byte)vertical_value & 0x1f) + 0x60;
    // Encode the high 3 bits of x into the third character (space-padded)
    encoded_string[2] = (char)(horizontal_value >> 5) + ' ';
    // Encode the low 5 bits of x into the fourth character (offset by 0x40)
    encoded_string[3] = ((byte)horizontal_value & 0x1f) + 0x40;
    // Null-terminate the encoded string
    encoded_string[4] = '\0';
}