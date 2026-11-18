void func0(char *key, char *encrypted_key) {
    int i;

    for (i = 0;; i++) {
        if (key[i]!= '\0') {
            int c = (key[i] - 'a' + 4) % 26 + 'a';
            encrypted_key[i] = c;
        } else {
            encrypted_key[i] = '\0';
            break;
        }
    }
}