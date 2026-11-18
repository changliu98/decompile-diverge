const char *
func0(const char *text)
{
    regex_t re;
    int reti;
    const char *text_local;
    const char *patterns = "ab{3}";

    reti = regcomp(&re, patterns, 0x01);
    if (reti) {
        fprintf(PTR_stderr_00103ff8, "Could not compile regex\n");
        return "Regex compilation error";
    }
    reti = regexec(&re, text, 0, NULL, 0);
    regfree(&re);
    if (!reti) {
        return "Found a match!";
    }

    return "Not matched!";
}