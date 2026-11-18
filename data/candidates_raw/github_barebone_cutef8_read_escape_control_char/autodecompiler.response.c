char read_escape_control_char(char c)
{
    char d;
    switch(c){
        case 'n': d = '\n'; break;
        case 't': d = '\t'; break;
        case 'r': d = '\r'; break;
        case 'e': d = '\e'; break;
        case 'b': d = '\b'; break;
        case 'f': d = '\f'; break;
        case 'v': d = '\v'; break;
        case 'a': d = '\a'; break;
        default:
            if (c >= '0' && c <= '7'){
                d = c - '0';
                int i;
                for (i = 0; i < 2 && (c + i) >= '0' && (c + i) <= '7'; ++i){
                    d = d * 8 + (c + i) - '0';
                }
            } else {
                d = c;
            }
    }
    return d;
}