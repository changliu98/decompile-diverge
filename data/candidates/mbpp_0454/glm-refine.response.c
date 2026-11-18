const char *func0(const char *text)
{
    char error_message[100];
    regex_t regex;
    int reti;

    // Compile the regular expression pattern
    // Note: The flag '1' corresponds to REG_EXTENDED
    if (regcomp(&regex, "\\w*z.\\w*", REG_EXTENDED))
    {
        fprintf(stderr, "Could not compile regex\n");
        return "Regex compile error";
    }

    // Execute the regular expression against the input text
    reti = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (reti == 0)
    {
        return "Found a match!";
    }
    else if (reti == REG_NOMATCH) // REG_NOMATCH is typically defined as 1
    {
        return "Not matched!";
    }
    else
    {
        // Handle any execution errors
        regerror(reti, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex match failed: %s\n", error_message);
        return "Regex match error";
    }
}