void numericCrypt(char *str) {
    const char *key1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 0x2004
    const char *key2 = "22233344455566677778889999"; // 0x200f

    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 0; key1[j] != '\0'; j++) {
            if (str[i] == key1[j]) {
                str[i] = key2[j];
                break;
            }
        }
    }
}