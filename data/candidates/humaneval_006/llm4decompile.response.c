int* func0(char* s, int* returnSize)
{
    int *all_levels = NULL;
    int level = 0;
    int max_level = 0;
    int count = 0;
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            level++;
            if (level > max_level) {
                max_level = level;
            }
        } else if (s[i] == ')') {
            level--;
            if (level == 0) {
                all_levels = (int *)realloc(all_levels, (long)(count + 1) * sizeof(int));
                all_levels[count] = max_level;
                max_level = 0;
                count++;
            }
        }
    }
    *returnSize = count;
    return all_levels;
}