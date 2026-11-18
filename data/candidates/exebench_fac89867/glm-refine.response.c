void __cdecl ne_post_filter16_double(double *_x, const double *_y, const int *_f)
{
  double diff[8];
  double fwd[8];
  double bwd[8];
  double half[8];

  // Phase 1: Calculate differences and half-differences
  diff[0] = _y[0] - _y[15];
  diff[1] = _y[1] - _y[14];
  diff[2] = _y[2] - _y[13];
  diff[3] = _y[3] - _y[12];
  diff[4] = _y[4] - _y[11];
  diff[5] = _y[5] - _y[10];
  diff[6] = _y[6] - _y[9];
  diff[7] = _y[7] - _y[8];

  half[0] = _y[0] - diff[0] / 2.0;
  half[1] = _y[1] - diff[1] / 2.0;
  half[2] = _y[2] - diff[2] / 2.0;
  half[3] = _y[3] - diff[3] / 2.0;
  half[4] = _y[4] - diff[4] / 2.0;
  half[5] = _y[5] - diff[5] / 2.0;
  half[6] = _y[6] - diff[6] / 2.0;
  half[7] = _y[7] - diff[7] / 2.0;

  // Phase 2: Forward filtering
  fwd[7] = diff[7] - diff[6] * (double)_f[15] / 16.0;
  fwd[6] = diff[6] - fwd[7] * (double)_f[8]  / 16.0 - diff[5] * (double)_f[16] / 16.0;
  fwd[5] = diff[5] - fwd[6] * (double)_f[9]  / 16.0 - diff[4] * (double)_f[17] / 16.0;
  fwd[4] = diff[4] - fwd[5] * (double)_f[10] / 16.0 - diff[3] * (double)_f[18] / 16.0;
  fwd[3] = diff[3] - fwd[4] * (double)_f[11] / 16.0 - diff[2] * (double)_f[19] / 16.0;
  fwd[2] = diff[2] - fwd[3] * (double)_f[12] / 16.0 - diff[1] * (double)_f[20] / 16.0;
  fwd[1] = diff[1] - fwd[2] * (double)_f[13] / 16.0 - diff[0] * (double)_f[21] / 16.0;
  fwd[0] = 16.0 * (diff[0] - fwd[1] * (double)_f[14] / 16.0) / (double)_f[7];

  // Phase 3: Backward scaling
  bwd[7] = 16.0 * fwd[7] / (double)_f[0];
  bwd[6] = 16.0 * fwd[6] / (double)_f[1];
  bwd[5] = 16.0 * fwd[5] / (double)_f[2];
  bwd[4] = 16.0 * fwd[4] / (double)_f[3];
  bwd[3] = 16.0 * fwd[3] / (double)_f[4];
  bwd[2] = 16.0 * fwd[2] / (double)_f[5];
  bwd[1] = 16.0 * fwd[1] / (double)_f[6];
  bwd[0] = 16.0 * fwd[0] / (double)_f[7];

  // Phase 4: Output reconstruction
  _x[0]  = bwd[0] / 2.0 + half[0];
  _x[1]  = bwd[1] / 2.0 + half[1];
  _x[2]  = bwd[2] / 2.0 + half[2];
  _x[3]  = bwd[3] / 2.0 + half[3];
  _x[4]  = bwd[4] / 2.0 + half[4];
  _x[5]  = bwd[5] / 2.0 + half[5];
  _x[6]  = bwd[6] / 2.0 + half[6];
  _x[7]  = bwd[7] / 2.0 + half[7];
  _x[8]  = _x[7] - bwd[7];
  _x[9]  = _x[6] - bwd[6];
  _x[10] = _x[5] - bwd[5];
  _x[11] = _x[4] - bwd[4];
  _x[12] = _x[3] - bwd[3];
  _x[13] = _x[2] - bwd[2];
  _x[14] = _x[1] - bwd[1];
  _x[15] = _x[0] - bwd[0];
}