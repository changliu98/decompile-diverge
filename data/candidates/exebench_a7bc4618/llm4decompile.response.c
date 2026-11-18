void remove_line_ending(char *text, char ending)
{
    char *found = strrchr(text, ending);
    if (found) {
        *found = '\0';
    }
}