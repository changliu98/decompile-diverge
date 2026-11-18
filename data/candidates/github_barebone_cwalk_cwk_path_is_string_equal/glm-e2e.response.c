bool cwk_path_is_string_equal(const char *first, const char *second, size_t first_size, size_t second_size)
{
    bool is_equal;
    bool is_separator_match;
    int first_lower;
    int second_lower;

    // If the sizes differ, the strings cannot be equal
    if (first_size != second_size) {
        is_equal = false;
        return is_equal;
    }

    // Check if the current style is Windows (case-insensitive)
    if (cwk_path_is_style_windows()) {
        is_equal = (cwk_path_to_lower(*first) == cwk_path_to_lower(*second));
        return is_equal;
    }

    // Unix style (case-sensitive) comparison loop
    while (*first != '\0' && *second != '\0' && first_size > 0) {
        // Check if both current characters are considered separators
        is_separator_match = cwk_path_is_separator(cwk_path_get_style_table(), *first);
        if (!is_separator_match) {
            is_separator_match = cwk_path_is_separator(cwk_path_get_style_table(), *second);
        }

        first_lower = cwk_path_to_lower(*first);
        second_lower = cwk_path_to_lower(*second);

        // If the characters don't match and they aren't both separators, strings are not equal
        if (first_lower != second_lower && !is_separator_match) {
            is_equal = false;
            return is_equal;
        }

        // Move to the next character
        first++;
        second++;
        first_size--;
    }

    is_equal = true;
    return is_equal;
}