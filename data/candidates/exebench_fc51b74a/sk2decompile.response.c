void joga(int posicao, int tab[][3], int cont) {
  if (cont % 2 == 0) {
    switch (posicao) {
      case 1:
        tab[0][0] = -3;
        break;
      case 2:
        tab[0][1] = -3;
        break;
      case 3:
        tab[0][2] = -3;
        break;
      case 4:
        tab[1][0] = -3;
        break;
      case 5:
        tab[1][1] = -3;
        break;
      case 6:
        tab[1][2] = -3;
        break;
      case 7:
        tab[2][0] = -3;
        break;
      case 8:
        tab[2][1] = -3;
        break;
      case 9:
        tab[2][2] = -3;
        break;
    }
  } else {
    switch (posicao) {
      case 1:
        tab[0][0] = -2;
        break;
      case 2:
        tab[0][1] = -2;
        break;
      case 3:
        tab[0][2] = -2;
        break;
      case 4:
        tab[1][0] = -2;
        break;
      case 5:
        tab[1][1] = -2;
        break;
      case 6:
        tab[1][2] = -2;
        break;
      case 7:
        tab[2][0] = -2;
        break;
      case 8:
        tab[2][1] = -2;
        break;
      case 9:
        tab[2][2] = -2;
        break;
    }
  }
}