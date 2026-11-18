int func0(char *str, char *sub)
{
    int len = strlen(str);
    int sublen = strlen(sub);
    char *substr = (char *)malloc((sublen * 2 + 1) * sizeof(char));
    int i;
    for (i = 0; i < sublen; i++)
    {
        strncpy(substr, &sub[i], sublen - i);
        strncpy(&substr[sublen - i], sub, i);
        substr[sublen] = '\0';
        if (strstr(str, substr))
        {
            free(substr);
            return 1;
        }
    }
    free(substr);
    return 0;
}