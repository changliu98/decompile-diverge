void __cdecl joga(int jogada, int (*matriz)[3], int i)
{
  if ( i % 2 )
  {
    switch ( jogada )
    {
      case 1:
        (*matriz)[0] = -2;
        break;
      case 2:
        (*matriz)[1] = -2;
        break;
      case 3:
        (*matriz)[2] = -2;
        break;
      case 4:
        (*matriz)[3] = -2;
        break;
      case 5:
        (*matriz)[4] = -2;
        break;
      case 6:
        (*matriz)[5] = -2;
        break;
      case 7:
        (*matriz)[6] = -2;
        break;
      case 8:
        (*matriz)[7] = -2;
        break;
      case 9:
        (*matriz)[8] = -2;
        break;
      default:
        return;
    }
  }
  else
  {
    switch ( jogada )
    {
      case 1:
        (*matriz)[0] = -3;
        break;
      case 2:
        (*matriz)[1] = -3;
        break;
      case 3:
        (*matriz)[2] = -3;
        break;
      case 4:
        (*matriz)[3] = -3;
        break;
      case 5:
        (*matriz)[4] = -3;
        break;
      case 6:
        (*matriz)[5] = -3;
        break;
      case 7:
        (*matriz)[6] = -3;
        break;
      case 8:
        (*matriz)[7] = -3;
        break;
      case 9:
        (*matriz)[8] = -3;
        break;
      default:
        return;
    }
  }
}