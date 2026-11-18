int num_vowels(char *str, char *vowels)
{
    char *pv, *ps;
    int num = 0;

    ps = str;
    while (*ps) {
        pv = vowels;
        while (*pv) {
            if (*ps == *pv) {
                num++;
                break;
            }
            else {
                pv++;
            }
        }
        ps++;
    }

    return num;
}