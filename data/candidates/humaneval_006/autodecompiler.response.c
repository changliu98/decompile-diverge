int* func0(char* paren_string, int* num_levels) {
    int* level_sizes = NULL;
    int* level_members = NULL;
    int level = 0, max_level = 0, i = 0, num_colors = 0;

    for (i = 0; paren_string[i] != '\0'; i++) {
        char c = paren_string[i];
        switch (c) {
            case '(':
                level++;
                if (level > max_level) {
                    max_level = level;
                }
                break;
            case ')':
                level--;
                if (level == 0) {
                    level_sizes = realloc(level_sizes, (num_colors + 1) * sizeof(int));
                    level_sizes[num_colors++] = max_level;
                    max_level = 0;
                }
                break;
        }
    }

    *num_levels = num_colors;
    return level_sizes;
}