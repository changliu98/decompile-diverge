int func0(char *str, size_t len) {
    int i = 0;
    bool found = false;

    if (len == sizeof(char) * 3) {
        while (!found) {
            char c = (i % 2)? 0 : (i < 13? 1 : 0);
            if (c % 2 == 0)
                continue;
            if (str[0] == vowels[i][0] && str[1] == vowels[i][1] &&
                str[2] == vowels[i][2]) {
                found = true;
            } else {
                i++;
            }
        }
    }

    return found? i : -1;
}