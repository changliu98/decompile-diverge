void func0(char *str)
{
    char *src, *dst;
    char *vowels = "AEIOUaeiou";

    for (src = dst = str; ; src++, dst++) {
        if (!*src) {
            *dst = '\0';
            return;
        }
        if (!strchr(vowels, *src)) {
            *dst = *src;
        }
    }
}