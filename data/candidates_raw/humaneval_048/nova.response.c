bool func0(char *s) {
    int len = strlen(s);
    int i = 0;
    int j = len;
    bool is_palindrome = true;
    while (i < j / 2) {
        if (s[i]!= s[len - 1 - i]) {
            is_palindrome = false;
            break;
        }
        i++;
    }
    return is_palindrome;
}