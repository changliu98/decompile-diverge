void qr_getSize(unsigned int m, unsigned int n, unsigned int Q_size[2], unsigned int R_size[2], unsigned int *permSize)
{
 Q_size[0] = Q_size[1] = m;
 *permSize = n;
 R_size[0] = m;
 R_size[1] = n;
}