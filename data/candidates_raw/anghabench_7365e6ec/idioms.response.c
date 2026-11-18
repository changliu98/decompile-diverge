int get_num_of_bits(int ns, int dnr){
  if (dnr <= ns){
    return ns - dnr;
  }
  return (ns + 8 - dnr);
}