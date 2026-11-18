char** func0(char* txt, int* returnSize)
{
    int len = strlen(txt);
    int i, j, k;
    char** ans;
    char cur[100 + 1];
    memset(cur, 0, 100 + 1);
    j = 0;
    k = 0;
    if(strchr(txt, ' ') == NULL && strchr(txt, ',') == NULL)
    {
        int count = 0;
        for(i = 0; i < len; i++)
        {
            if(isalpha(txt[i]) && (txt[i] - 'a') % 2 == 1)
                count++;
        }
        ans = (char**)malloc(sizeof(char*));
        ans[0] = (char*)malloc(12);
        sprintf(ans[0], "%d", count);
        k = 1;
    }
    else
    {
        ans = (char**)malloc(sizeof(char*) * (len + 1));
        for(i = 0; i <= len; i++)
        {
            if(txt[i] == ' ' || txt[i] == ',' || txt[i] == '\0')
            {
                if(j > 0)
                {
                    cur[j] = '\0';
                    ans[k] = strdup(cur);
                    k++;
                    j = 0;
                }
            }
            else
            {
                cur[j] = txt[i];
                j++;
            }
        }
    }
    *returnSize = k;
    return ans;
}