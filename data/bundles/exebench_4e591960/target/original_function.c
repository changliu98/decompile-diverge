void numconv(char* numstr)
{
        for( ; *numstr; *numstr++ -= '0')
                ;

        return;
}