double avg(double *data, size_t size)
{
    size_t i;
    size_t num = size / sizeof(double);
    double sum = 0;

    for (i = 0; i < num; i++) {
        sum += data[i];
    }

    data[0] = sum / num;
    return sum;
}