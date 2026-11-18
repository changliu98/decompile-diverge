int descape(int *in,int *out)

{
  int *out_local;
  int *in_local;
  int local_c;
  
  if (*in == 0x5c) {
    switch(in[1]) {
    case 0x22:
      out[1] = 0x22;
      local_c = 1;
      break;
    default:
      goto LAB_00101301;
    case 0x27:
      out[1] = 0x27;
      local_c = 1;
      break;
    case 0x3f:
      out[1] = 0x3f;
      local_c = 1;
      break;
    case 0x61:
      out[1] = 7;
      local_c = 1;
      break;
    case 0x62:
      out[1] = 8;
      local_c = 1;
      break;
    case 0x66:
      out[1] = 0xc;
      local_c = 1;
      break;
    case 0x6e:
      out[1] = 10;
      local_c = 1;
      break;
    case 0x72:
      out[1] = 0xd;
      local_c = 1;
      break;
    case 0x74:
      out[1] = 9;
      local_c = 1;
      break;
    case 0x76:
      out[1] = 0xb;
      local_c = 1;
    }
  }
  else {
LAB_00101301:
    *out = *in;
    out[1] = in[1];
    local_c = 0;
  }
  return local_c;
}