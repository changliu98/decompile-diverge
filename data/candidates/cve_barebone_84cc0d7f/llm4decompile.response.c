void faad_resetbits(bitfile *ld, int bits)
{
    int words;

    words = bits >> 5;

    ld->bytes_left = ld->buffer_size - (words * 4);


    ld->bufa = (ld->bytes_left >= 4) ? getdword(ld->start + words) :
        getdword_n(ld->start + words, ld->bytes_left);
    ld->bytes_left -= 4;


    ld->bufb = (ld->bytes_left >= 4) ? getdword(ld->start + words + 1) :
        getdword_n(ld->start + words + 1, ld->bytes_left);
    ld->bytes_left -= 4;

    ld->bits_left = 32 - (bits & 0x1f);
    ld->tail = ld->start + words + 2;
    ld->error = 0;
}