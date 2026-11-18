#include <stdbool.h>

bool is_balanced_brackets(const char *brackets)
{
    int level = 0;

    for (int i = 0; brackets[i] != '\0'; ++i)
    {
        if (brackets[i] == '<')
            ++level;
        if (brackets[i] == '>')
            --level;

        // If at any point there are more closing brackets than opening ones
        if (level < 0)
            return false;
    }

    // Returns true if all opened brackets have been closed
    return level == 0;
}