void joga(int jogada, int *linha[], int i){
  if (i % 2 == 0){
    switch (jogada){
      case 1:
        linha[0][0] = -3;
        break;
      case 2:
        linha[0][1] = -3;
        break;
      case 3:
        linha[0][2] = -3;
        break;
      case 4:
        linha[1][0] = -3;
        break;
      case 5:
        linha[1][1] = -3;
        break;
      case 6:
        linha[1][2] = -3;
        break;
      case 7:
        linha[2][0] = -3;
        break;
      case 8:
        linha[2][1] = -3;
        break;
      case 9:
        linha[2][2] = -3;
        break;
    }
  }
  else{
    switch (jogada){
      case 1:
        linha[0][0] = -2;
        break;
      case 2:
        linha[0][1] = -2;
        break;
      case 3:
        linha[0][2] = -2;
        break;
      case 4:
        linha[1][0] = -2;
        break;
      case 5:
        linha[1][1] = -2;
        break;
      case 6:
        linha[1][2] = -2;
        break;
      case 7:
        linha[2][0] = -2;
        break;
      case 8:
        linha[2][1] = -2;
        break;
      case 9:
        linha[2][2] = -2;
        break;
    }
  }
}