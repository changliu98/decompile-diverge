int descape(uchar *in, uchar *out)
{
    if (in[0] == '\\')
    {
        switch (in[1])
        {
            case 'a':
                out[1] = '\a';
                break;
            case 'b':
                out[1] = '\b';
                break;
            case 'f':
                out[1] = '\f';
                break;
            case 'n':
                out[1] = '\n';
                break;
            case 'r':
                out[1] = '\r';
                break;
            case 't':
                out[1] = '\t';
                break;
            case 'v':
                out[1] = '\v';
                break;
            case '\\':
                out[1] = '\\';
                break;
            case '\'':
                out[1] = '\'';
                break;
            case '\"':
                out[1] = '\"';
                break;
            case '\?':
                out[1] = '\?';
                break;
            default:
                return 0;
        }
        return 1;
    }
    else
    {
        out[0] = in[0];
        out[1] = in[1];
        return 0;
    }
}