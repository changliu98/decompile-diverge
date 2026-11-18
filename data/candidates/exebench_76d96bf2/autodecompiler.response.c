void goertzel_filter_v1(struct Lpfilt_state *st, short xin, short b)
{
    short yout;

    yout = ((long) st->d1 * b >> 14) - st->d2;
    st->d2 = st->d1;
    st->d1 = xin >> 7 + yout;
}