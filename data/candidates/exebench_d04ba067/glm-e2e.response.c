int itochar(int num, char *str) {
    char buffer[16];
    int i = 0;
    int j = 0;

    // Handle the case where the number is 0 separately, 
    // because the do-while loop would skip it entirely.
    if (num == 0) {
        str[j++] = '0';
        return j;
    }

    // Extract digits in reverse order
    do {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    } while (num != 0);

    // Reverse the digits and place them into the output string
    while (j < i) {
        str[j] = buffer[i - j - 1];
        j++;
    }

    return j;
}