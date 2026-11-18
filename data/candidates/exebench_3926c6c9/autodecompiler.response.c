void ne_pre_filter8_double(double *new_state, double *old_state, int *control)
{
    double dt=.01;
    double sigma=10, beta=2.6667, rho=28;
    double x, y, z, w;

    x = old_state[0] - old_state[7];
    y = old_state[1] - old_state[6];
    z = old_state[2] - old_state[5];
    w = old_state[3] - old_state[4];

    new_state[3] = old_state[3] - w/2;
    new_state[2] = old_state[2] - z/2;
    new_state[1] = old_state[1] - y/2;
    new_state[0] = old_state[0] - x/2;

    w = w*control[0]/16;
    z = z*control[1]/16;
    y = y*control[2]/16;
    x = x*control[3]/16;

    x += (rho*control[6]/16 + y*control[3]/16);
    y += (x*control[9]/16 + x*control[4]/16);
    y += (z*control[5]/16);
    z += (y*control[8]/16 + w*control[2]/16);
    w += (w*control[1]/16 + z*control[7]/16);

    new_state[0] += x/2;
    new_state[1] += y/2;
    new_state[2] += z/2;
    new_state[3] += w/2;

    new_state[4] = new_state[3] - w;
    new_state[5] = new_state[2] - z;
    new_state[6] = new_state[1] - y;
    new_state[7] = new_state[0] - x;
}