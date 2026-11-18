int llc_shdlc_w_used(int ns, int dnr){
  if (dnr <= ns){
    return ns - dnr;
  }
  return (ns + 8 - dnr);
}