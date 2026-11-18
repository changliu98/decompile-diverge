int _get_poker_type(int a, int b, int c) {
  int card[3] = {a, b, c};
  int count = 0;
  int card_type[3];
  int i;
  int j;
  int flag;
  count = 0;
  memset(card_type, 0, sizeof(card_type));
  for (j = 0; j < 3; j++) {
    flag = 0;
    for (i = 0; i < j; i++) {
      if (card[i] == card[j]) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      count++;
    }
  }
  if (count == 3) {
    return 0;
  } else {
    return 4 - count;
  }
}