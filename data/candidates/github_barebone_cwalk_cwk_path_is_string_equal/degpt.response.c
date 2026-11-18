// Checks if two path strings are equal based on the current path style.
// Returns true if the paths are equal, false otherwise.
_Bool cwk_path_is_string_equal(char *path1, char *path2, size_t path1_len, size_t path2_len)
{
    // If the lengths of the two strings differ, they cannot be equal.
    if (path1_len != path2_len) {
        return false;
    }

    // For Unix-style paths, perform a case-sensitive comparison.
    if (path_style == CWK_STYLE_UNIX) {
        return strncmp(path1, path2, path1_len) == 0;
    }

    // For case-insensitive styles (e.g., Windows), compare character by character.
    for (size_t i = 0; i < path1_len; i++) {
        // Convert current characters to lowercase for comparison.
        char char1 = tolower((int)path1[i]);
        char char2 = tolower((int)path2[i]);
        
        // Check if the current characters are path separators.
        bool is_sep_char1 = strchr(separators[path_style], path1[i]) != NULL;
        bool is_sep_char2 = strchr(separators[path_style], path2[i]) != NULL;
        
        // If characters differ and neither is a separator, the paths are not equal.
        if (char1 != char2 && !is_sep_char1 && !is_sep_char2) {
            return false;
        }
    }

    // All characters matched according to the rules.
    return true;
}