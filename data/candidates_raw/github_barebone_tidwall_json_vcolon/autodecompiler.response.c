long jstp_rx_skip_value(char *src, long len, long offset)
{
    long o = offset;
    long result;

    if (o == len) return -(o + 1);
    switch(src[o])
    {
    case ':':
        result = o + 1;
        break;
    default:
        while(o < len)
        {
            int c = src[o];
            switch(c)
            {
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                result = o + 1;
                break;
            case ':':
                result = o + 1;
                break;
            default:
                result = -(o + 1);
                break;
            }
            o++;
        }
        result = -(o + 1);
    }
    return result;
}