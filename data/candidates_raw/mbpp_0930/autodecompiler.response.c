char *test_regex(char *str)
{
    char *re = "ab*?";
    int err;
    regex_t regex;
    char *result;

    err = regcomp(&regex, re, 1);
    if (err) {
        result = "Error compiling regex";
        goto out;
    }

    err = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (!err)
        result = "Found a match!";
    else if (err == 1)
        result = "Not matched!";
    else
        result = "Regex match failed";

out:
    return result;
}