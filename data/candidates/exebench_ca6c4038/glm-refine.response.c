void __cdecl cftf161(float *a, float *w)
{
  float y15i, y15r, y14i, y14r, y13i, y13r, y12i, y12r;
  float y11i, y11r, y10i, y10r, y9i, y9r, y8i, y8r;
  float y7i, y7r, y6i, y6r, y5i, y5r, y4i, y4r;
  float y3i, y3r, y2i, y2r, y1i, y1r, y0i, y0r;
  float x3i, x3r, x2i, x2r, x1i, x1r, x0i, x0r;
  float wk1i, wk1r, wn4r;

  wn4r = w[1];
  wk1r = w[2];
  wk1i = w[3];

  x0r = a[0] + a[16];
  x0i = a[1] + a[17];
  x1r = a[0] - a[16];
  x1i = a[1] - a[17];
  x2r = a[8] + a[24];
  x2i = a[9] + a[25];
  x3r = a[8] - a[24];
  x3i = a[9] - a[25];

  y0r = x0r + x2r;
  y0i = x0i + x2i;
  y4r = x0r - x2r;
  y4i = x0i - x2i;
  y8r = x1r - x3i;
  y8i = x1i + x3r;
  y12r = x1r + x3i;
  y12i = x1i - x3r;

  x0r = a[2] + a[18];
  x0i = a[3] + a[19];
  x1r = a[2] - a[18];
  x1i = a[3] - a[19];
  x2r = a[10] + a[26];
  x2i = a[11] + a[27];
  x3r = a[10] - a[26];
  x3i = a[11] - a[27];

  y1r = x0r + x2r;
  y1i = x0i + x2i;
  y5r = x0r - x2r;
  y5i = x0i - x2i;
  y9r = wk1r * (x1r - x3i) - wk1i * (x1i + x3r);
  y9i = wk1r * (x1i + x3r) + wk1i * (x1r - x3i);
  y13r = wk1i * (x1r + x3i) - wk1r * (x1i - x3r);
  y13i = wk1i * (x1i - x3r) + wk1r * (x1r + x3i);

  x0r = a[4] + a[20];
  x0i = a[5] + a[21];
  x1r = a[4] - a[20];
  x1i = a[5] - a[21];
  x2r = a[12] + a[28];
  x2i = a[13] + a[29];
  x3r = a[12] - a[28];
  x3i = a[13] - a[29];

  y2r = x0r + x2r;
  y2i = x0i + x2i;
  y6r = x0r - x2r;
  y6i = x0i - x2i;
  y10r = wn4r * ((x1r - x3i) - (x1i + x3r));
  y10i = wn4r * ((x1i + x3r) + (x1r - x3i));
  y14r = wn4r * ((x1r + x3i) + (x1i - x3r));
  y14i = wn4r * ((x1i - x3r) - (x1r + x3i));

  x0r = a[6] + a[22];
  x0i = a[7] + a[23];
  x1r = a[6] - a[22];
  x1i = a[7] - a[23];
  x2r = a[14] + a[30];
  x2i = a[15] + a[31];
  x3r = a[14] - a[30];
  x3i = a[15] - a[31];

  y3r = x0r + x2r;
  y3i = x0i + x2i;
  y7r = x0r - x2r;
  y7i = x0i - x2i;
  y11r = wk1i * (x1r - x3i) - wk1r * (x1i + x3r);
  y11i = wk1i * (x1i + x3r) + wk1r * (x1r - x3i);
  y15r = wk1r * (x1r + x3i) - wk1i * (x1i - x3r);
  y15i = wk1r * (x1i - x3r) + wk1i * (x1r + x3i);

  a[24] = (y12r - y14r) + (y13r - y15r);
  a[25] = (y12i - y14i) + (y13i - y15i);
  a[26] = (y12r - y14r) - (y13r - y15r);
  a[27] = (y12i - y14i) - (y13i - y15i);
  a[28] = (y12r + y14r) - (y13i + y15i);
  a[29] = (y12i + y14i) + (y13r + y15r);
  a[30] = (y12r + y14r) + (y13i + y15i);
  a[31] = (y12i + y14i) - (y13r + y15r);

  a[16] = (y8r + y10r) + (y9r + y11r);
  a[17] = (y8i + y10i) + (y9i + y11i);
  a[18] = (y8r + y10r) - (y9r + y11r);
  a[19] = (y8i + y10i) - (y9i + y11i);
  a[20] = (y8r - y10r) - (y9i - y11i);
  a[21] = (y8i - y10i) + (y9r - y11r);
  a[22] = (y8r - y10r) + (y9i - y11i);
  a[23] = (y8i - y10i) - (y9r - y11r);

  x2r = wn4r * ((y5r - (x0i - x2i)) - (y5i + (x0r - x2r)));
  x2i = wn4r * ((y5i + y7r) + (y5r - (x0i - x2i)));
  x3r = wn4r * ((y5r + y7i) - (y5i - y7r));
  x3i = wn4r * ((y5i - y7r) + (y5r + y7i));

  a[8]  = (y4r - y6i) + x2r;
  a[9]  = (y4i + y6r) + x2i;
  a[10] = (y4r - y6i) - x2r;
  a[11] = (y4i + y6r) - x2i;
  a[12] = (y4r + y6i) - x3i;
  a[13] = (y4i - y6r) + x3r;
  a[14] = (y4r + y6i) + x3i;
  a[15] = (y4i - y6r) - x3r;

  a[0] = (y0r + y2r) + (y1r + y3r);
  a[1] = (y0i + y2i) + (y1i + y3i);
  a[2] = (y0r + y2r) - (y1r + y3r);
  a[3] = (y0i + y2i) - (y1i + y3i);
  a[4] = (y0r - y2r) - (y1i - y3i);
  a[5] = (y0i - y2i) + (y1r - y3r);
  a[6] = (y0r - y2r) + (y1i - y3i);
  a[7] = (y0i - y2i) - (y1r - y3r);
}