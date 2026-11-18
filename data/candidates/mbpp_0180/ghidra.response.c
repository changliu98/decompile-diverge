double func0(double slat,double slon,double elat,double elon)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dist;
  double elon_local;
  double elat_local;
  double slon_local;
  double slat_local;
  
  dVar1 = sin(slat);
  dVar2 = sin(elat);
  dVar3 = cos(slat);
  dVar4 = cos(elat);
  dVar5 = cos(slon - elon);
  dVar1 = acos(dVar1 * dVar2 + dVar3 * dVar4 * dVar5);
  return DAT_00102008 * dVar1;
}