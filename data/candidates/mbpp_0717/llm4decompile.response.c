double func0(double *data, int len)
{
    int i;
    double avg, sum_deviation;

    if (len <= 1)
        return 0.0;

    avg = avg_calc(data, len);

    sum_deviation = 0.0;
    for (i = 0; i < len; i++)
        sum_deviation += (data[i] - avg) * (data[i] - avg);

    return sqrt(sum_deviation / (len - 1));
}