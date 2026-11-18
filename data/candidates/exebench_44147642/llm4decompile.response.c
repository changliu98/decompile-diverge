void uppercase(int *chptr)
{
    int ch = *chptr;

    if ((ch >= 'a' && ch <= 'z') || (ch >= 'a' && ch <= 'z') || (ch >= 'a' && ch <= 'z'))
        *chptr = ch - 'a' + 'A';
}