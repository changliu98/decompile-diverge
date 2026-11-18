static void func0(smallfelem out, smallfelem in1, smallfelem in2)
{
    long long t1 = (long long) in1[1] * (long long) in2[1] >> 14;
    int64_t t2 = (int64_t) in1[0] * (int64_t) in2[1] - (int64_t) in1[1] * (int64_t) in2[0];

    out[0] = (int16_t) (t2 >> 14);
    out[1] = (int16_t) (t1 + (t2 & 0x3FFF));
}