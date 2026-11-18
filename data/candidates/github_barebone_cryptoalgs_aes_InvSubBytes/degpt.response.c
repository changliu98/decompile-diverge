void InvSubBytes(BYTE (*stateMatrix) [4])
{
    // Iterate over each column of the state matrix
    for (int colIndex = 0; colIndex < 4; colIndex++) {
        // Iterate over each row within the current column
        for (int rowIndex = 0; rowIndex < 4; rowIndex++) {
            // Apply the inverse S-box lookup to the current byte
            // Extract the high nibble for the row index and low nibble for the column index
            stateMatrix[colIndex][rowIndex] = aes_invsbox[(int)(uint)stateMatrix[colIndex][rowIndex] >> 4][(int)(stateMatrix[colIndex][rowIndex] & 0xf)];
        }
    }
}