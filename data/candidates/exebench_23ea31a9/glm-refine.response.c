char *__cdecl jstrescapecpy(char *pt, const char *spt)
{
    int i = 0;
    int j = 0;

    if (spt)
    {
        while (spt[i])
        {
            char c = spt[i];
            
            if (c == '%') // 37
            {
                pt[j++] = '_';
                i++;
            }
            else if (c == '\'') // 39
            {
                pt[j++] = '\\';
                pt[j++] = spt[i++];
            }
            else if (c == '\\') // 92
            {
                pt[j++] = '\\';
                pt[j++] = spt[i++];
            }
            else
            {
                pt[j++] = spt[i++];
            }
        }
        pt[j] = 0;
        return pt;
    }
    else
    {
        *pt = 0;
        return pt;
    }
}