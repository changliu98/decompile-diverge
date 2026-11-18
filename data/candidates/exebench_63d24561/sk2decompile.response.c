int zmlt_(doublereal *ar, doublereal *ai, doublereal *br, doublereal *bi,
          doublereal *cr, doublereal *ci) {
  doublereal ca;
  doublereal cb;
  ca = *ar * *br - *ai * *bi;
  cb = *ar * *bi + *ai * *br;
  *cr = ca;
  *ci = cb;
  return 0;
}