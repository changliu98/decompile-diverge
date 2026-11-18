bool func0(const char *str) {
    int len = strlen(str);
    int i = 0;
    bool is_palindrome;

    while (i < len / 2) {
        if (str[i] != str[len - 1 - i]) {
            is_palindrome = false;
            break;
        }
        i++;
    }
    
    // If the loop finishes without breaking, it's a palindrome
    if (i >= len / 2) {
        is_palindrome = true;
    }

    return is_palindrome;
}