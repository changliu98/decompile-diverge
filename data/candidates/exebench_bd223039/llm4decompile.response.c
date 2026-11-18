void clearMarker(char *s, char marker)
{
    char *pos = strchr(s, marker);
    if (pos)
        *pos = '\0';
}