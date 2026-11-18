int func0(char *s) {
    int i, j, k, l, m, n;
    int hash[256];

    memset(hash, 0, sizeof(hash));

    for (i = j = 0; s[i]; i++) {
        char c = tolower(s[i]);
        if (hash[c])
            continue;
        if (isvowel(c))
            hash[c] = 1;
        else
            j++;
    }

    return j;
}