// Performs the SubBytes transformation on the 4x4 state matrix
// by replacing each byte with its corresponding value from the AES S-box.
void SubBytes(BYTE (*matrix) [4])
{
    // Iterate through each column of the state matrix
    for (int col = 0; col < 4; col++) {
        // Iterate through each row within the current column
        for (int row = 0; row < 4; row++) {
            // Look up the S-box value using the high nibble as the row index
            // and the low nibble as the column index
            matrix[col][row] = aes_sbox[(int)(uint)matrix[col][row] >> 4][(int)(matrix[col][row] & 0xf)];
        }
    }
}