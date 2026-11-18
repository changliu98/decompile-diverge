int
compare_path(char *s1, char *s2, size_t l1, size_t l2)
{
    char result;

    if (l1 != l2) {
 result = 0;
    } else if (path_style == 1) {
 result = !strncmp(s1, s2, l1);
    } else {
 for (;;) {
     if (!*s1 || !*s2 || l1 < 1) {
  break;
     }
     result = (strchr(separators[path_style], *s1) &&
        strchr(separators[path_style], *s2));
     if ((tolower(*s1) != tolower(*s2)) && !result) {
  result = 0;
  break;
     }
     s1++;
     s2++;
     l1--;
 }
    }

    return (int)result;
}