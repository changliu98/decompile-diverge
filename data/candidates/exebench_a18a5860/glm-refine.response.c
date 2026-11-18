void __cdecl jsonny_clear(char *s, size_t *len)
{
    // Reset the tracked string length to 0
    *len = 0;
    
    // Null-terminate the string buffer to mark it as empty
    *s = '\0';
}