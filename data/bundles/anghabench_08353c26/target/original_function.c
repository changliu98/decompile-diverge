int clip_f15(int v)
{
    return v < -32767 ? -32767 :
           v >  32767 ?  32767 :
           v;
}