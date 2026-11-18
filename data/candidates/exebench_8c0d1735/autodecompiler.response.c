static int
and_peep2_qi(int b, char *c)
{
    *c = ((b & 0x5f) + 0x30);
    return b;
}