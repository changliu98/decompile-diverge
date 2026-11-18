int get_hex (char * buf, unsigned int *num)
{
    int cpos = 0, done = 0;
    *num = 0;

    while (!done) {
        if ( buf[cpos] >= '0' && buf[cpos] <= '9' ) {
           *num = *num<<4;
           *num = *num + buf[cpos] - '0';
           }
        else if ( buf[cpos] >= 'A' && buf[cpos] <= 'F' ) {
            *num = *num<<4;
            *num = *num + buf[cpos] - 'A' + 10;
           }
        else if ( buf[cpos] >= 'a' && buf[cpos] <= 'f' ) {
            *num = *num<<4;
            *num = *num + buf[cpos] - 'a' + 10;
           }
        else
            done = 1;



        if (!done)
            cpos++;

        if (cpos >= 8)
            done = 1;
        }


    return cpos;
}