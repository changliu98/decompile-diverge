int matMultMV(double ablock[4][4], double avec[4], double bvec[4]) {
  double temp;
  double tt0, tt1, tt2, tt3;

  tt0 = ablock[0][0]*avec[0] + ablock[0][1]*avec[1] +
       ablock[0][2]*avec[2] + ablock[0][3]*avec[3];
  tt1 = ablock[1][0]*avec[0] + ablock[1][1]*avec[1] +
       ablock[1][2]*avec[2] + ablock[1][3]*avec[3];
  tt2 = ablock[2][0]*avec[0] + ablock[2][1]*avec[1] +
       ablock[2][2]*avec[2] + ablock[2][3]*avec[3];
  tt3 = ablock[3][0]*avec[0] + ablock[3][1]*avec[1] +
       ablock[3][2]*avec[2] + ablock[3][3]*avec[3];

  bvec[0] = tt0;
  bvec[1] = tt1;
  bvec[2] = tt2;
  bvec[3] = tt3;

  return(0);
}