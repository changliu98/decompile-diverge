void decrypt(char *text)
{
    for (char *p = text; *p != '\0'; p++)
    {
        *p -= 13;
    }
}