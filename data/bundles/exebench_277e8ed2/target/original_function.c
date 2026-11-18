void calc_sth11(float *p_humidity, float *p_temperature)
{
    const float C1 = -2.0468;
    const float C2 = +0.0367;
    const float C3 = -0.0000015955;
    const float T1 = +0.01;
    const float T2 = +0.00008;

    const float d1 = -39.65f;
    const float d2 = +0.01;

    float rh = *p_humidity;
    float t = *p_temperature;
    float rh_lin;
    float rh_true;
    float t_C;

    t_C = t * d2 + d1;
    rh_lin = C3*rh*rh + C2*rh + C1;
    rh_true = (t_C-25)*(T1+T2*rh)+rh_lin;

    if (rh_true > 100) rh_true = 100;
    if (rh_true < 0.1) rh_true = 0.1;

    *p_temperature = t_C;
    *p_humidity = rh_true;
}