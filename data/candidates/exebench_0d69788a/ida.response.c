int __cdecl tens(int *v)
{
  int ret; // [rsp+1Ch] [rbp-14h]

  ret = 0;
  switch ( *v / 10 )
  {
    case 0:
      return 0;
    case 1:
      switch ( *v )
      {
        case 10:
          ret = 3;
          break;
        case 11:
          ret = 6;
          break;
        case 12:
          ret = 6;
          break;
        case 13:
          ret = 8;
          break;
        case 14:
          ret = 8;
          break;
        case 15:
          ret = 7;
          break;
        case 16:
          ret = 7;
          break;
        case 17:
          ret = 9;
          break;
        case 18:
          ret = 8;
          break;
        case 19:
          ret = 8;
          break;
        default:
          break;
      }
      *v = 0;
      return ret;
    case 2:
      ret = 6;
      goto LABEL_23;
    case 3:
      ret = 6;
      goto LABEL_23;
    case 4:
      ret = 5;
      goto LABEL_23;
    case 5:
      ret = 5;
      goto LABEL_23;
    case 6:
      ret = 5;
      goto LABEL_23;
    case 7:
      ret = 7;
      goto LABEL_23;
    case 8:
      ret = 6;
      goto LABEL_23;
    case 9:
      ret = 6;
      goto LABEL_23;
    default:
LABEL_23:
      *v %= 10;
      return ret;
  }
}