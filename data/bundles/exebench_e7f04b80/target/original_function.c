int
deo_pipe(int *rend, int *wend)
{
    int in[2];

    if (pipe(in) != 0)
        return errno;

    *rend = in[0];
    *wend = in[1];
    return 0;
}