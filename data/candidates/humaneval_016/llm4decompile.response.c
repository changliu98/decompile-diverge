int func0(char *str)
{
    int char_map[256];
    int count = 0;
    int i;

    memset(char_map, 0, sizeof(char_map));

    for (i = 0; str[i] != '\0'; i++) {
        char c = tolower((unsigned char)str[i]);
        if (!char_map[c] && isalpha(c)) {
            char_map[c] = 1;
            count++;
        }
    }

    return count;
}