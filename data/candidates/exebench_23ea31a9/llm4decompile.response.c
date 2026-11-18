char *
jstrescapecpy(char *pt, const char *spt)
{
    int i, j;

    if (spt == NULL) {
        *pt = '\0';
        return pt;
    }

    for (i = 0, j = 0; spt[i] != '\0'; i++) {
        if (spt[i] == '%') {
            pt[j++] = '_';
        } else if (spt[i] == '\'') {
            pt[j++] = '\\';
            pt[j++] = spt[i];
        } else if (spt[i] == '\\') {
            pt[j++] = '\\';
            pt[j++] = spt[i];
        } else {
            pt[j++] = spt[i];
        }
    }
    pt[j] = '\0';

    return pt;
}