void ck_decrypt(char *input_string)
{
    // Iterate through the string until the null terminator is reached
    for (; *input_string; input_string++) {
        // Skip decryption for specific characters: 'p', '\', and 'S'
        if (*input_string != 'p' && *input_string != '\\' && *input_string != 'S') {
            // XOR each character with 0xf to decrypt it
            *input_string ^= 0xf;
        }
    }
}