static void put_user_word(short s, unsigned char *p)
{
    *p++ = s;
    *p++ = s >> 8;
}