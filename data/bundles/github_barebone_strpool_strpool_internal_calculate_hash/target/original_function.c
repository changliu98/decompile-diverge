static STRPOOL_U32 strpool_internal_calculate_hash( char const* string, int length, int ignore_case )
    {
    STRPOOL_U32 hash = 5381U; 

    if( ignore_case) 
        {
        for( int i = 0; i < length; ++i )
            {
            char c = string[ i ];
            c = ( c <= 'z' && c >= 'a' ) ? c - ( 'a' - 'A' ) : c;
            hash = ( ( hash << 5U ) + hash) ^ c;
            }
        }
    else
        {
        for( int i = 0; i < length; ++i )
            {
            char c = string[ i ];
            hash = ( ( hash << 5U ) + hash) ^ c;
            }
        }

    hash = ( hash == 0 ) ? 1 : hash; // We can't allow 0-value hash keys, but dupes are ok
    return hash;
    }