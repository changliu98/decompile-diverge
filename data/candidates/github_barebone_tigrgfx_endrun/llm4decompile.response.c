void endrun(Save *s)
{
    s->runlen--;
    literal(s, s->prev);
    if (s->runlen > 66)
        encodelen(s, 277, 4, s->runlen - 67);
    else if (s->runlen > 34)
        encodelen(s, 273, 3, s->runlen - 35);
    else if (s->runlen > 18)
        encodelen(s, 269, 2, s->runlen - 19);
    else if (s->runlen > 10)
        encodelen(s, 265, 1, s->runlen - 11);
    else if (s->runlen > 2)
        encodelen(s, 257, 0, s->runlen - 3);
    else
        while (s->runlen--)
            literal(s, s->prev);
}