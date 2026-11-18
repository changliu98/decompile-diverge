bool __cdecl validateRegexSyntax(const char *regex)
{
    int parenDepth = 0;
    bool inCharClass = false;
    bool escaped = false;
    bool charClassHasContent = false;
    bool hasAtom = false;
    bool lastWasPipe = false;
    bool lastWasQuantifier = false;

    for (size_t i = 0; regex[i]; ++i)
    {
        char c = regex[i];

        // Handle escaped characters
        if (escaped)
        {
            escaped = false;
            hasAtom = true;
            lastWasPipe = false;
            lastWasQuantifier = false;
            continue;
        }
        
        if (c == '\\')
        {
            escaped = true;
            continue;
        }

        // Handle inside character class '['
        if (inCharClass)
        {
            if (c == ']')
            {
                if (!charClassHasContent)
                    return false;
                    
                inCharClass = false;
                hasAtom = true;
                lastWasPipe = false;
                lastWasQuantifier = false;
            }
            else
            {
                charClassHasContent = true;
            }
            continue;
        }

        // Handle normal regex characters
        switch (c)
        {
            case '[':
                inCharClass = true;
                charClassHasContent = false;
                break;

            case ']':
                return false;

            case '(':
                ++parenDepth;
                hasAtom = false;
                lastWasPipe = false;
                lastWasQuantifier = false;
                break;

            case ')':
                if (!parenDepth || !hasAtom)
                    return false;
                --parenDepth;
                hasAtom = true;
                lastWasPipe = false;
                lastWasQuantifier = false;
                break;

            case '|':
                if (!hasAtom)
                    return false;
                hasAtom = false;
                lastWasPipe = true;
                lastWasQuantifier = false;
                break;

            case '*':
            case '+':
            case '?':
                if (!hasAtom || lastWasQuantifier)
                    return false;
                lastWasPipe = false;
                lastWasQuantifier = true;
                break;

            default:
                hasAtom = true;
                lastWasPipe = false;
                lastWasQuantifier = false;
                break;
        }
    }

    // Ensure no dangling states are left open at the end of the string
    return !escaped && !inCharClass && !parenDepth && !lastWasPipe;
}