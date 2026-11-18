float Intersect(float *S,int i1,int i2,int N)

{
  float interS2;
  float interS1;
  float inter;
  int i;
  int N_local;
  int i2_local;
  int i1_local;
  float *S_local;
  float local_c;
  
  inter = 0.0;
  interS1 = 0.0;
  interS2 = 0.0;
  for (i = 0; i < N; i = i + 1) {
    if (S[i1 * N + i] == DAT_00102004) {
      if ((S[i2 * N + i] == DAT_00102004) && (!NAN(S[i2 * N + i]) && !NAN(DAT_00102004))) {
        inter = DAT_00102004 + inter;
      }
    }
    if ((S[i1 * N + i] == DAT_00102004) && (!NAN(S[i1 * N + i]) && !NAN(DAT_00102004))) {
      interS1 = DAT_00102004 + interS1;
    }
    if ((S[i2 * N + i] == DAT_00102004) && (!NAN(S[i2 * N + i]) && !NAN(DAT_00102004))) {
      interS2 = DAT_00102004 + interS2;
    }
  }
  if (interS1 < interS2) {
    interS2 = interS1;
  }
  local_c = inter / interS2;
  return local_c;
}