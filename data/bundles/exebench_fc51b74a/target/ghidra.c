void joga(int jogada,int (*matriz) [3],int i)

{
  int i_local;
  int (*matriz_local) [3];
  int jogada_local;
  
  if (i % 2 == 0) {
    switch(jogada) {
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
      matriz[1][0] = -3;
      break;
    case 5:
      matriz[1][1] = -3;
      break;
    case 6:
      matriz[1][2] = -3;
      break;
    case 7:
      matriz[2][0] = -3;
      break;
    case 8:
      matriz[2][1] = -3;
      break;
    case 9:
      matriz[2][2] = -3;
    }
  }
  else {
    switch(jogada) {
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
      matriz[1][0] = -2;
      break;
    case 5:
      matriz[1][1] = -2;
      break;
    case 6:
      matriz[1][2] = -2;
      break;
    case 7:
      matriz[2][0] = -2;
      break;
    case 8:
      matriz[2][1] = -2;
      break;
    case 9:
      matriz[2][2] = -2;
    }
  }
  return;
}