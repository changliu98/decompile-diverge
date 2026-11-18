void normalize(float *data, int n)
{
    float min, max;
    int i;

    min = data[0];
    max = data[0];

    for (i = 1; ; i++) {
 if (i >= n) break;
 if (data[i] < min) min = data[i];
 if (data[i] > max) max = data[i];
    }

    for (i = 0; ; i++) {
 if (i >= n) break;
 data[i] = (data[i] - min) / (max - min);
    }
}