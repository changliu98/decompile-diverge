int func0(int num)
{
    int i;
    int len;
    char numstr[20];
    int isPalindrome;

    for (i = num + 1; i < 2147483647; i++) {
        sprintf(numstr, "%d", i);
        len = strlen(numstr);

        isPalindrome = 1;
        int j;
        for (j = 0; j < len / 2; j++) {
            if (numstr[j] != numstr[len - 1 - j]) {
                isPalindrome = 0;
                break;
            }
        }

        if (isPalindrome) {
            return i;
        }
    }

    return -1;
}