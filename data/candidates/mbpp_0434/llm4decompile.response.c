const char *
func0(const char *text)
{
    regex_t re;
    int ret;

    ret = regcomp(&re, "ab+", 0x01);
    if (ret)
        return "Regex compilation failed!";

    ret = regexec(&re, text, 0, NULL, 0);
    regfree(&re);

    if (!ret)
        return "Found a match!";

    return "Not matched!";
}