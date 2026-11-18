char *func0(char *input, char *chars)
{
    char regex[10];
    sprintf(regex, "%s{2,}", chars);

    regex_t compiled_regex;
    if (regcomp(&compiled_regex, regex, 1)) {
        return NULL;
    }

    size_t index = 0;
    char *output = strdup(input);
    regmatch_t matches[1];

    while (1) {
        if (regexec(&compiled_regex, output + index, 1, matches, 0)) break;

        size_t match_start = index + matches->rm_so;
        char *match_end_ptr = output + match_start + 1;
        char *match_start_ptr = output + match_start + matches->rm_eo - matches->rm_so;

        memmove(match_end_ptr, match_start_ptr, strlen(output) - match_start - matches->rm_eo + matches->rm_so + 1);

        index = match_start + 1;
    }

    regfree(&compiled_regex);
    return output;
}