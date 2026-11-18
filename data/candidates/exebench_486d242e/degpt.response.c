void ck_encrypt(char *input_string)
{
    // Iterate through each character of the string until the null terminator
    for (; *input_string; input_string++) {
        // Skip encryption for specific characters: 'p', '\', and 'S'
        if (*input_string != 'p' && *input_string != '\\' && *input_string != 'S') {
            // XOR each character with 0xf to encrypt it
            *input_string ^= 0xf;
        }
    }
}