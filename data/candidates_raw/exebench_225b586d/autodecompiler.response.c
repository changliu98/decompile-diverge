static int _is_right_bracket(char *str, int *pos)
{
 *pos = 0;
 return str[0] == '>' ? 1 : 0;
}