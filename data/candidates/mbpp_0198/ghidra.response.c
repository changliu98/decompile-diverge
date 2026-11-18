double func0(int a,int b)

{
  double dVar1;
  double dVar2;
  double area;
  int b_local;
  int a_local;
  undefined8 local_10;
  
  if ((a < 0) || (b < 0)) {
    local_10 = DAT_00102018;
  }
  else {
    dVar1 = sqrt(DAT_00102010);
    dVar1 = DAT_00102010 * dVar1;
    dVar2 = pow((double)a,DAT_00102008);
    local_10 = (dVar1 * dVar2) / (double)(b << 2);
  }
  return local_10;
}