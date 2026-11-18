float hpluck(float xin, float *q)
{
    int ip;
    float yout;
    q[0] += 0.5;
    if (q[0] > q[1])
        q[0] = 1.0;
    ip = (int)q[0];
    yout = q[7] * (1.0 - q[8]) + q[ip] * q[8];
    q[6] = q[ip];
    q[ip] = q[2] * q[ip] + q[3] * q[4];
    q[4] = q[ip];
    q[ip] = q[5] * q[10] + q[4] * (1.0 - q[10]) + q[9];
    q[5] = q[ip] + xin;
    q[ip] = q[5];
    return (yout);
}