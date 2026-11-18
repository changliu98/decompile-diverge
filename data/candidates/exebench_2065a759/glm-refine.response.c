int __cdecl set_filename(char *to_name, char *from_name)
{
    for (; *from_name != '\0'; from_name++, to_name++)
    {
        if (*from_name == '/') // 47 is the ASCII code for '/'
        {
            *to_name = '\0';
            return 2;
        }
        *to_name = *from_name;
    }
    
    *to_name = '\0';
    return 1;
}