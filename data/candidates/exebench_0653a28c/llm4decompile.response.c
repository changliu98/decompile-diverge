void reverse(char *li)
{
    char *left = li;
    char *right = li;
    char temp;

    while (*right++)
        ;
    right -= 2;

    while (left < right) {
        temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}