float get_color_value(int attr,float *c,float *b,float *g)

{
  float *g_local;
  float *b_local;
  float *c_local;
  int attr_local;
  float local_c;
  
  switch(attr & 0x3f) {
  case 9:
    local_c = *c;
    break;
  case 10:
    local_c = c[1];
    break;
  default:
    local_c = 0.0;
    break;
  case 0xc:
    local_c = c[2];
    break;
  case 0x11:
    local_c = *b;
    break;
  case 0x12:
    local_c = b[1];
    break;
  case 0x14:
    local_c = b[2];
    break;
  case 0x21:
    local_c = *g;
    break;
  case 0x22:
    local_c = g[1];
    break;
  case 0x24:
    local_c = g[2];
  }
  return local_c;
}