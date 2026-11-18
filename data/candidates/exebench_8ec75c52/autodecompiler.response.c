void strupr(char *s)
{
    for(;;)
    {
        if (*s == '\0')
            return;

        switch(*s)
        {
        case 'a':
            *s -= 32;
            break;
        case 'b':
            *s -= 32;
            break;
        case 'c':
            *s -= 32;
            break;
        case 'd':
            *s -= 32;
            break;
        case 'e':
            *s -= 32;
            break;
        case 'f':
            *s -= 32;
            break;
        case 'g':
            *s -= 32;
            break;
        case 'h':
            *s -= 32;
            break;
        case 'i':
            *s -= 32;
            break;
        case 'j':
            *s -= 32;
            break;
        case 'k':
            *s -= 32;
            break;
        case 'l':
            *s -= 32;
ed:
            break;
        case 'm':
            *s -= 32;
            break;
        case 'n':
            *s -= 32;
            break;
        case 'o':
            *s -= 32;
            break;
        case 'p':
            *s -= 32;
            break;
        case 'q':
            *s -= 32;
            break;
        case 'r':
            *s -= 32;
            break;
        case 's':
            *s -= 32;
            break;
        case 't':
            *s -= 32;
            break;
        case 'u':
            *s -= 32;
            break;
        case 'v':
            *s -= 32;
ed:
            break;
        case 'w':
            *s -= 32;
            break;
        case 'x':
            *s -= 32;
            break;
        case 'y':
            *s -= 32;
            break;
        case 'z':
            *s -= 32;
            break;
        default:
            break;
        }
        s++;
    }
}