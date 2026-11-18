void goertzel_filter_v1(short *delay, short input, short coefficient)
{
 short s1, s2;

 s1 = delay[1];
 s2 = delay[2];

 delay[2] = s1;
 delay[1] = (coefficient * s1 >> 14) - s2 + (input >> 7);
}