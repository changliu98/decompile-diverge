
void cmatrix_from_frame(
    double *m,
    const double *v1,
    const double *v2,
    const double *v3
) {



 for (int i = 0; i < 3; i++) {
  m[(((i)*3)+(0))] = v1[i];
  m[(((i)*3)+(1))] = v2[i];
  m[(((i)*3)+(2))] = v3[i];

 }



}
