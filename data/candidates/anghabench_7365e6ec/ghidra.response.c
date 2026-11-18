int llc_shdlc_w_used(int ns,int dnr)

{
  int iVar1;
  int unack_count;
  int dnr_local;
  int ns_local;
  
  if (ns < dnr) {
    iVar1 = 8 - dnr;
  }
  else {
    iVar1 = -dnr;
  }
  unack_count = ns + iVar1;
  return unack_count;
}