void foo(int *dipole, int x, int y)
{
    int dip_x = dipole[0];
    int dip_y = dipole[1];

    for (int i = 0; i < 2; i++) {
        int dip = ((x) ? 1 : 0) << 0 | ((y) ? 1 : 0) << 1 | ((dip_x) ? 1 : 0) << 2 | ((dip_y) ? 1 : 0) << 3 | ((1 >> i) ? 1 : 0) << 4;
        dipole[i + 2] = dip;
    }
}