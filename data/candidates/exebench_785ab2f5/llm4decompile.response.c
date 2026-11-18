void numericCrypt(char *str)
{
    int i, j;
    char *crypt = "OIZEASGTBq";
    char *num = "01234567890";

    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; crypt[j] != '\0'; j++)
        {
            if (str[i] == crypt[j])
            {
                str[i] = num[j];
                break;
            }
        }
    }
}