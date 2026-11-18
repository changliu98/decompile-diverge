int is_right_open(char* s, int *index)
{
    *index = 0;
    return (s[0] == '>' ? 1 : 0);
}