void SHUF(uchar *input_buffer, uchar *output_buffer)
{
    // Shuffle bytes from input buffer b to output buffer b2
    // Mapping indices: 8, 11, 12, 15, 2, 1, 6, 5, 10, 9, 14, 13, 0, 7, 4, 3

    output_buffer[0] = input_buffer[8];   // Index 0 <- Index 8
    output_buffer[1] = input_buffer[0xb]; // Index 1 <- Index 11
    output_buffer[2] = input_buffer[0xc]; // Index 2 <- Index 12
    output_buffer[3] = input_buffer[0xf]; // Index 3 <- Index 15
    output_buffer[4] = input_buffer[2];   // Index 4 <- Index 2
    output_buffer[5] = input_buffer[1];   // Index 5 <- Index 1
    output_buffer[6] = input_buffer[6];   // Index 6 <- Index 6
    output_buffer[7] = input_buffer[5];   // Index 7 <- Index 5
    output_buffer[8] = input_buffer[10];  // Index 8 <- Index 10
    output_buffer[9] = input_buffer[9];   // Index 9 <- Index 9
    output_buffer[10] = input_buffer[0xe];// Index 10 <- Index 14
    output_buffer[0xb] = input_buffer[0xd];// Index 11 <- Index 13
    output_buffer[0xc] = input_buffer[0]; // Index 12 <- Index 0
    output_buffer[0xd] = input_buffer[7]; // Index 13 <- Index 7
    output_buffer[0xe] = input_buffer[4]; // Index 14 <- Index 4
    output_buffer[0xf] = input_buffer[3]; // Index 15 <- Index 3
}