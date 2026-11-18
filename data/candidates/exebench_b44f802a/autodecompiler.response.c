void YvVfilterCoef(double fc, double *f)
{
 double c1, c2, c3, b1, b2, b3, B;
 double m0, m1, m2, m1sq, m2sq, qsq, q, scale;

 m0 = 1.1687441584554972;
 m1 = 1.1071998872011433;
 m2 = 1.4073806908786947;
 m1sq = m1*m1;
 m2sq = m2*m2;

 if (fc < 3.5625) {
  q = -0.2555747234786546 + 0.5799094345233464*fc + 0.0570691021908287*fc*fc;
 }
 else {
  q = 2.5125 + 0.980016978054544*(fc - 3.5625);
 }
 qsq = q*q;
 scale = (m0 + q)*(m1sq + m2sq + 2.0*m1*q + qsq);

 b1 = (q*(((m0 + q)*(m1sq + m2sq)) + ((2.0*m0 + 4.0*m1)*q) + 3.0*qsq))/scale;
 b2 = (qsq*(m0 + 2.0*m1 + q))/scale;
 b3 = (qsq*fabs__bench(q))/scale;
 B = (m0*(m1sq + m2sq))/scale;

 f[0] = -fabs__bench(b3);
 f[1] = -fabs__bench(b2);
 f[2] = -fabs__bench(b1);
 f[3] = B;
 f[4] = -fabs__bench(b1);
 f[5] = -fabs__bench(b2);
 f[6] = -fabs__bench(b3);
}