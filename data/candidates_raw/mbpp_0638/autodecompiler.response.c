int windchill_F(int temp_F, int windspeed){
    double ret;
    ret = 13.12 + 0.6215 * temp_F +
        -13.956 * pow(temp_F, 0.16) +
        0.418 * windspeed * pow(temp_F, 0.16);
    return (int)round(ret);
}