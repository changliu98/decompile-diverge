int endGCGdata(char* s, int *index)
{
    *index = 0;
    return (s[0] == '>' ? 1 : 0);
}