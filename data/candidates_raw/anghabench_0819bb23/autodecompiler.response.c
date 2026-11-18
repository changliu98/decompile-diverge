float BETWEENF(float a, float b, float c)
{
    float tmp;
    if (a < b) tmp = b;
    else if (a > c) tmp = c;
    else tmp = a;
    return tmp;
}