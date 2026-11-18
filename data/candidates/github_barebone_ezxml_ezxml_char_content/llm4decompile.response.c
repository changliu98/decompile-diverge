void ezxml_char_content(ezxml_root_t root, char *s, size_t len, char t)
{
    ezxml_t xml = root->cur;
    char *tmp;
    size_t l;

    if (! xml || ! xml->name || ! len) return;

    s[len] = 0;
    tmp = ezxml_decode(s, root->ent, t);
    l = strlen(tmp);

    if (*xml->txt) {
        if (xml->flags & 0x40) xml->txt = realloc(xml->txt, strlen(xml->txt) + l + 1);
        else xml->txt = strcpy(malloc(strlen(xml->txt) + l + 1), xml->txt);
        strcpy(xml->txt + strlen(xml->txt) - l, tmp);
        if (tmp != s) free(tmp);
    }
    else xml->txt = tmp;

    if (xml->txt != s) ezxml_set_flag(xml, 0x40);
}