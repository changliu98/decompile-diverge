char ** func0(char *text, int *count)
{
    char pattern[] = "[a-zA-Z]+";
    char *str = (char *)malloc(strlen(text) + 1);
    strcpy(str, text);

    regex_t regex;
    int reti = regcomp(&regex, pattern, 1);

    int i = 0;
    char *start = str;
    regmatch_t matches[1];
    while (reti = regexec(&regex, start, 1, matches, 0) == 0) {
        int start_index = matches[0].rm_so;
        int end_index = matches[0].rm_eo;
        char *word = (char *)malloc(end_index - start_index + 1);
        strncpy(word, start + start_index, end_index - start_index);
        word[end_index - start_index] = '\0';
        func0::words[i] = word;
        i++;
        start += end_index;
    }

    regfree(&regex);
    *count = i;
    return func0::words;
}