int SeekPoint(unsigned char *toc, int file_bytes, float percent)
{
    int seek;
    int p;
    float seek_tmp;
    float seek_a, seek_b;

    if(percent < 0.0) percent = 0.0;
    if(percent > 100.0) percent = 100.0;

    p = (int)percent;
    if(p >= 100) p = 99;

    seek_a = toc[p];
    if(p < 99) seek_b = toc[p + 1];
    else seek_b = 256.0;

    seek_tmp = seek_a + ((seek_b - seek_a) * (percent - (float)p));

    seek = (int)((seek_tmp / 256.0) * (float)file_bytes);

    return(seek);
}