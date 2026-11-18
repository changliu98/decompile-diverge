int func0(char *str)
{
    int i;
    int len = strlen(str);
    int count[26];
    int maxOcc = 0;
    memset(count, 0, sizeof(count));
    for (i = 0; i < len; i++)
        count[(int)(str[i] - 'a')]++;
    for (i = 0; i < 26; i++)
        if (count[i] > maxOcc)
            maxOcc = count[i];
    return len - maxOcc;
}