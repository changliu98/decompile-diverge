int is_integer( char *str ) {
    int i, len, chk;
    len = strlen( str );
    while( *str == ' ' ) {
        str++;
        len--;
    }
    if( len < 2 ) {
        chk = -1;
    } else if( *str == '+' || *str == '-' ) {
        for( i = 1; i < len; i++ ) {
            if( *( str + i ) < '0' || *( str + i ) > '9' ) {
                chk = 0;
                break;
            } else {
                chk = 1;
                i++;
            }
        }
    } else {
        for( i = 0; i < len; i++ ) {
            if( *( str + i ) < '0' || *( str + i ) > '9' ) {
                chk = 0;
                break;
            } else {
                chk = 1;
                i++;
            }
        }
    }
    return chk;
}