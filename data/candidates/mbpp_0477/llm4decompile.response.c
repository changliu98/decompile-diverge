void func0(const char *input, char *output)
{
    int i;
    for (i = 0; input[i] != '\0'; i++)
    {
        output[i] = (char) tolower((unsigned char) input[i]);
    }
    output[i] = '\0';
}