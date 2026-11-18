void r2d(double *ra,double *dec,int *ih,double *am,char *isgn,int *id,double *amin)

{
  float fVar1;
  double dVar2;
  int ira;
  float hours;
  float deg;
  float rad;
  char iplus;
  char iminus;
  int *id_local;
  char *isgn_local;
  double *am_local;
  int *ih_local;
  double *dec_local;
  double *ra_local;
  
  fVar1 = DAT_00102040;
  dVar2 = (*ra / (double)DAT_00102040) / DAT_00102008;
  while (hours = (float)dVar2, DAT_00102010 < (double)hours) {
    dVar2 = (double)hours - DAT_00102010;
  }
  *ih = (int)dVar2;
  *am = (double)(hours - (float)(int)dVar2) * DAT_00102018;
  *am = DAT_00102020 + *am;
  if (DAT_00102018 <= *am) {
    *am = *am - DAT_00102018;
    *ih = *ih + 1;
  }
  if (0x17 < *ih) {
    *ih = *ih + -0x18;
  }
  if (0.0 < *dec || *dec == 0.0) {
    *isgn = '+';
  }
  else {
    *isgn = '-';
    *dec = -*dec;
  }
  dVar2 = *dec;
  *id = (int)(dVar2 / (double)fVar1);
  *amin = (double)((float)(dVar2 / (double)fVar1) - (float)*id) * DAT_00102018;
  return;
}