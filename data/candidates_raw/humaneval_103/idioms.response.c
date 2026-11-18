char *toBinary(int n, int m)
{
    int mid;
    if (n > m)
        return "1";
    mid = (n + m)/2;
    char *res = (char*)malloc(sizeof(char)*32 + 1);
    res[0] = '\0';
    int i = 31;
    res[32] = '\0';
    do
    {
        res[--i] = (char)(mid % 2 + '0');
        mid = mid / 2;
    } while (mid > 0);
    return &res[i+1];
}