void mpeg3video_calc_mv(int *pred, int r_size, int motion_code, int motion_r, int full_pel_vector)
{
    int lim = 16 << r_size;
    int vec;

    if (full_pel_vector)
        vec = *pred >> 1;
    else
        vec = *pred;

    if (motion_code > 0)
    {
        vec += ((motion_code - 1) << r_size) + motion_r + 1;
        if (vec >= lim)
            vec -= lim << 1;
    }
    else if (motion_code < 0)
    {
        vec -= ((-motion_code - 1) << r_size) + motion_r + 1;
        if (vec < -lim)
            vec += lim << 1;
    }

    if (full_pel_vector)
        vec <<= 1;

    *pred = vec;
}