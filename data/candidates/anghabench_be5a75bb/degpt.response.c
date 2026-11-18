uint frag_num(uint i)

{
  uint i_local;
  
  return ((i & 0xfffffffc) + 3) - (i & 3);
}