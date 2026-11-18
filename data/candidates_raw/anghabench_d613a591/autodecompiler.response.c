float hue_to_rgb(float p, float q, float t)
{
    float ret;
    if(t < 0.0) t++;
    else if(t > 1.0) t--;
    if(t < 1.0 / 6.0) {
        ret = p + (q - p) * 6.0 * t;
    } else if(t < 1.0 / 2.0) {
        ret = q;
    } else if(t < 2.0 / 3.0) {
        ret = p + (q - p) * (2.0 / 3.0 - t) * 6.0;
    } else {
        ret = p;
    }
    return ret;
}