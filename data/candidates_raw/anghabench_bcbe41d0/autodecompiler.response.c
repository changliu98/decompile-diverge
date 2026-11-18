float BETWEENF(float a, float b, float c)
{
    float tmp;
    if (a > c) tmp = a;
    else if (c > b) tmp = b;
    else tmp = c;
    return(tmp);
}