int __cdecl do_map(char *b, int map, char c)
{
    // Default behavior: pass the character through untouched
    *b = c;

    switch ( c )
    {
        case 8: // Backspace (BS)
            if ( map & MAP_BS_TO_DEL )
                *b = 127; // Translate to Delete (DEL)
            return 1;

        case 10: // Line Feed (LF)
            if ( map & MAP_LF_TO_CR )
            {
                *b = 13;
                return 1;
            }
            if ( map & MAP_LF_TO_CRLF )
            {
                *b = 13;
                b[1] = 10;
                return 2;
            }
            if ( map & MAP_DROP_LF )
                return 0; // Character dropped
            return 1;

        case 13: // Carriage Return (CR)
            if ( map & MAP_CR_TO_LF )
            {
                *b = 10;
                return 1;
            }
            if ( map & MAP_CR_TO_CRLF )
            {
                *b = 13;
                b[1] = 10;
                return 2;
            }
            if ( map & MAP_DROP_CR )
                return 0; // Character dropped
            return 1;

        case 127: // Delete (DEL)
            if ( map & MAP_DEL_TO_BS )
                *b = 8; // Translate to Backspace (BS)
            return 1;

        default:
            return 1;
    }
}