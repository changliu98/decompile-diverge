void swi_coortrf2(double *xpo,double *xpn,double sineps,double coseps)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double x [3];
  double coseps_local;
  double sineps_local;
  double *xpn_local;
  double *xpo_local;
  
  dVar1 = xpo[1];
  dVar2 = xpo[2];
  dVar3 = xpo[1];
  dVar4 = xpo[2];
  *xpn = *xpo;
  xpn[1] = dVar1 * coseps + dVar2 * sineps;
  xpn[2] = -dVar3 * sineps + dVar4 * coseps;
  return;
}