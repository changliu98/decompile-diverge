bool func0(char *s) {
    bool is_palindrome = true;
    if (strlen(s) < 4) {
        is_palindrome = false;
    } else {
        for (int i = 2; i < strlen(s); i++) {
            if (s[i] == s[i - 1] || s[i] == s[i - 2]) {
                is_palindrome = false;
                break;
            }
        }
    }
    return is_palindrome;
}