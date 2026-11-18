void __cdecl StrBracketMatch(
        const char *in,
        int *CommaPositions,
        int *Nargs,
        int *ClosingBracketPos,
        int MaxCommaPoses)
{
    char QuoteType = 0;
    int commapos = 0;
    int inpos = 0;
    int BracketLevel = 0;

    while (in[inpos])
    {
        if (QuoteType)
        {
            // Check for unescaped matching quote
            if (in[inpos] == QuoteType && in[inpos - 1] != '\\')
                QuoteType = 0;
        }
        else
        {
            switch (in[inpos])
            {
                case '\'':
                case '"':
                    QuoteType = in[inpos];
                    break;
                case '(':
                    if (++BracketLevel == 1 && CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
                        CommaPositions[commapos++] = inpos;
                    break;
                case ')':
                    if (!--BracketLevel)
                        goto LABEL_28; // Matched the outermost closing bracket
                    break;
                default:
                    // Record commas only at the first bracket level
                    if (in[inpos] == ',' && BracketLevel == 1 && CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
                        CommaPositions[commapos++] = inpos;
                    break;
            }
        }
        ++inpos;
    }

LABEL_28:
    if (in[inpos])
    {
        // Record the closing bracket position if space permits
        if (CommaPositions && (MaxCommaPoses < 0 || commapos < MaxCommaPoses))
            CommaPositions[commapos++] = inpos;

        if (Nargs)
            *Nargs = commapos - 1; // Subtract 1 because the closing bracket was also recorded

        if (ClosingBracketPos)
            *ClosingBracketPos = inpos;
    }
    else
    {
        // Reached end of string without finding a matching closing bracket
        if (Nargs)
            *Nargs = -1;

        if (ClosingBracketPos)
            *ClosingBracketPos = -1;
    }
}