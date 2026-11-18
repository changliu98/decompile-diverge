static int
parse_pattern(char *pattern, int ppos, int *plen, int *pstart, int *pend,
              int *preverse)
{
    int type;

    if (pattern[ppos] == '^') {
        ppos++;
        *preverse = 1;
    } else
        *preverse = 0;

    switch (pattern[ppos]) {
    case '%':
        ppos++;
        *plen = 2;
        switch (pattern[ppos]) {
        case 'd':
            type = 2;
            break;
        case 'c':
            type = 1;
            break;
        case 'C':
            type = 4;
            break;
        case 'i':
            type = 5;
            break;
        case 'p':
            type = 6;
            break;
        case 'P':
            type = 7;
            break;
        case 't':
            type = 9;
            break;
        default:
            *pstart = ppos;
            *pend = ppos;
            type = 8;
        }
        break;

    case '[':
        *pstart = ppos + 2;
        while (pattern[ppos] != '\0' && pattern[ppos] != ']')
            ppos++;

        if (pattern[ppos] == '\0') {

            *plen = ppos - *pstart + 1;
            type = 8;
        } else {

            *pend = ppos - 1;
            *plen = ppos - *pstart + 1;
            type = 8;
        }
        break;

    case ' ':
        *plen = 1;
        type = 3;
        break;

    default:
        *plen = 1;
        *pstart = ppos;
        *pend = ppos;
        type = 8;
    }

    return type;
}