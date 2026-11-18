void sht1x_get_compensated_humid(float *p_humidity, float *p_temperature)
{
    const float C1 = -2.0468f;
    const float C2 = +0.0367f;
    const float C3 = -1.5955E-6f;

    const float T1 = +0.01f;
    const float T2 = +0.00008f;

    const float D1 = -39.65f;
    const float D2 = 0.01f;

    float rh = *p_humidity;
    float t = *p_temperature;
    float rh_lin;
    float rh_true;
    float t_C;

    t_C = D1 + (D2 * t);
    rh_lin = C3 * rh * rh + C2 * rh + C1;
    rh_true = (t_C - 25.f) *(T1 + (T2 * rh)) + rh_lin;

    if (rh_true > 100) {
        rh_true = 100;
    }
    if (rh_true < 0.1) {
        rh_true = 0.1;
    }

    *p_temperature = t_C;
    *p_humidity = rh_true;
}