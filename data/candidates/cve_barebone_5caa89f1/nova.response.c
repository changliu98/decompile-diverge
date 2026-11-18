static char *Perl_my_setenv(const char *key, const char *value) {
    int key_size = strlen(key);
    int value_size;
    char *pair;

    if (value == NULL)
        value = "";

    value_size = strlen(value);

    pair = (char *)malloc(sizeof(char) * (key_size + value_size + 2));
    memcpy(pair, key, key_size);
    pair[key_size] = '=';
    memcpy(pair + key_size + 1, value, value_size);
    pair[key_size + value_size + 1] = '\0';

    return url_encode(pair);
}