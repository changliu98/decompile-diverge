void func0(char *key, char *plaintext, char *ciphertext) {
    char key_table[32];
    char key_table_inv[32];
    char key_table_inv_row[8];
    char key_table_inv_col[8];
    int i;

    for (i = 0; i < 32; i++)
        key_table[i] = ciphertext[i];

    while (1) {
        generate_key_table(key_table, key_table_inv, key_table_inv_row,
                           key_table_inv_col);
        if (check_key_table(key_table, key_table_inv, key_table[0]))
            break;
    }

    memset(ciphertext, 32, sizeof(char) * 32);

    for (i = 0; i < 32; i++)
        key[i] = key_table[i];

    for (i = 0; i < 32; i++)
        plaintext[i] = key_table_inv[i];

    memset(key_table, 32, sizeof(char) * 32);
    memset(key_table_inv, 32, sizeof(char) * 32);
}