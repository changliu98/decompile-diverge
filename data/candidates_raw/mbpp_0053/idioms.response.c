char *isPalindrome(char *str)
{
    if (str[0] == str[(int)(strlen(str) - 1)])
        return "Equal";
    else
        return "Not Equal";
}