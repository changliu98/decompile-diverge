void escape(char s[], char t[])
{
    int i = 0;
    int j = 0;

    while (s[i] != '\0')
    {
        switch (t[j])
        {
            case '\n':
                s[i++] = '\\';
                s[i++] = 'n';
                break;
            case '\t':
                s[i++] = '\\';
                s[i++] = 't';
                break;
            case '\0':
                return;
            default:
                s[i++] = t[j];
                break;
        }
        ++j;
}

    return;
}