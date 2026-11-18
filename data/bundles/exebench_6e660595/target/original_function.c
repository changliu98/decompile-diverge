void
IdealTrack(unsigned long tracks,
    unsigned long top,
    unsigned long bot,
    unsigned long * ideal)
{
    unsigned long num;
    unsigned long den;

    num = (top * (tracks - bot)) + (bot * (top + 1));
    den = top + bot;

    if (den != 0) {
 *ideal = (unsigned long) ((unsigned long) num / (unsigned long) den);
    }
    else {
 *ideal = 1;
    }
}