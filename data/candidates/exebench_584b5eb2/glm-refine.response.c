char *__cdecl substitute(char *string, char chold, char chnew)
{
    char *cp;

    if (string) 
    {
        for (cp = string; *cp; ++cp) 
        {
            if (*cp == chold) 
            {
                *cp = chnew;
                break;
            }
        }
    }
    
    return string;
}