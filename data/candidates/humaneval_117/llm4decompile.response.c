char** func0(char* s, int n, int* returnSize)
{
    char** arr = NULL;
    int cons = 0;
    int index = 0;
    int begin = 0;
    int len = strlen(s);
    char* t = (char*)malloc(len + 1);
    for (int i = 0; i <= len; ++i)
    {
        if (!isblank(s[i]) && s[i])
        {
            t[i - begin] = s[i];
            if (strchr("aeiouAEIOU", s[i]) == NULL && isalpha(s[i] & 0xFF))
                cons++;
        }
        else
        {
            if (cons == n)
            {
                t[i - begin] = 0;
                arr = (char**)realloc(arr, sizeof(char*) * (index + 1));
                arr[index] = (char*)malloc(strlen(t) + 1);
                strcpy(arr[index], t);
                index++;
            }
            begin = i + 1;
            cons = 0;
        }
    }
    free(t);
    *returnSize = index;
    return arr;
}