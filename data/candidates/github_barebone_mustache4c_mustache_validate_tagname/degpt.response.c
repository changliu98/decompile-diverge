int mustache_validate_tagname(char *name, size_t length)
{
    // Allow single-dot tag (e.g., ".") as valid
    if (length == 1 && *name == '.') {
        return 0;
    }
    // Reject tags that start or end with a dot
    if (*name == '.' || name[length - 1] == '.') {
        return -1;
    }
    // Iterate through each character in the tag name
    for (size_t index = 0; index < length; index++) {
        // Reject tags containing whitespace characters (space, tab, vertical tab, form feed)
        if (name[index] == ' ' || name[index] == '\t' || name[index] == '\v' || name[index] == '\f') {
            return -1;
        }
        // Reject tags containing consecutive dots ("..")
        if (name[index] == '.' && index + 1 < length && name[index + 1] == '.') {
            return -1;
        }
    }
    // Tag name is valid
    return 0;
}