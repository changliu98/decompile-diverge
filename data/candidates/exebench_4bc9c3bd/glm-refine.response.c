int __cdecl escape(char *fmt, int percent, size_t *len)
{
    char *src = fmt;
    char *dst = fmt;
    char c;

    while ((c = *src) != '\0')
    {
        if (c != '\\')
        {
            *dst++ = c;
            src++;
            continue;
        }

        // Handle escape sequences
        char next = src[1];
        src += 2; // Consume backslash and next character

        switch (next)
        {
            case '\0':
                *dst++ = '\\';
                *dst = '\0';
                *len = dst - fmt;
                return 0;

            case '\'':
            case '\\':
                *dst++ = next;
                break;

            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
            {
                // Octal escape sequence
                int max_digits = 3;
                if (!percent && next == '0')
                    max_digits = 4;

                int value = 0;
                int digits_read = 0;
                
                // Re-evaluate the first character as part of the octal sequence
                src--;
                while (digits_read < max_digits && *src >= '0' && *src <= '7')
                {
                    value = value * 8 + (*src - '0');
                    src++;
                    digits_read++;
                }

                if (percent && value == '%')
                {
                    *dst++ = '%';
                    *dst++ = '%';
                }
                else
                {
                    *dst++ = (char)value;
                }
                break;
            }

            case 'a': *dst++ = '\a'; break;
            case 'b': *dst++ = '\b'; break;
            case 'c':
                if (percent)
                {
                    *dst++ = 'c';
                }
                else
                {
                    *dst = '\0';
                    *len = dst - fmt;
                    return 1;
                }
                break;
            case 'f': *dst++ = '\f'; break;
            case 'n': *dst++ = '\n'; break;
            case 'r': *dst++ = '\r'; break;
            case 't': *dst++ = '\t'; break;
            case 'v': *dst++ = '\v'; break;

            default:
                *dst++ = next;
                break;
        }
    }

    *dst = '\0';
    *len = dst - fmt;
    return 0;
}