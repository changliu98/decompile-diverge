float func0(float a, float b, float c)
{
    float s, area;
    if(a+b<=c || a+c<=b || b+c<=a)
    {
        return -1;
    }
    s = (a+b+c)/2;
    area = sqrtf(s*(s-a)*(s-b)*(s-c));
    return roundf(area*100)/100;
}