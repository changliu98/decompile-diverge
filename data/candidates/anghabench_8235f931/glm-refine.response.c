int __cdecl lowercase(int ch)
{
    if (ch < 'A' || ch > 'Z')
        return ch;
    else
        return ch - 'A' + 'a';
}