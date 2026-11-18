int __cdecl ff_norm_qscale(int qscale, int type)
{
  int v3; // [rsp+14h] [rbp-4h]

  switch ( type )
  {
    case 128:
      v3 = (63 - qscale + 2) >> 2;
      break;
    case 129:
      v3 = qscale >> 1;
      break;
    case 130:
      v3 = qscale;
      break;
    case 131:
      v3 = qscale >> 2;
      break;
    default:
      v3 = qscale;
      break;
  }
  return v3;
}