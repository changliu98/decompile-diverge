void __cdecl clearIRQflag(char *flags)
{
    flags[5] = '0';
}