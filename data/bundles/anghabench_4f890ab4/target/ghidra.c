int ff_norm_qscale(int qscale,int type)

{
  int type_local;
  int qscale_local;
  int local_c;
  
  local_c = qscale;
  switch(type) {
  case 0x80:
    local_c = 0x41 - qscale >> 2;
    break;
  case 0x81:
    local_c = qscale >> 1;
    break;
  case 0x82:
    break;
  case 0x83:
    local_c = qscale >> 2;
  }
  return local_c;
}