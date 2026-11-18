void __cdecl func0(char *str)
{
    int n = strlen(str);
    
    // Selection sort algorithm
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (str[i] > str[j])
            {
                // Swap characters
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}