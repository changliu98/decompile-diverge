int func0(char *s) {
  char *str = s;
  int map[256];
  memset(map, 0, sizeof(map));
  map['I'] = 1;
  map['V'] = 5;
  map['X'] = 10;
  map['L'] = 50;
  map['C'] = 100;
  map['D'] = 500;
  map['M'] = 1000;
  int sum = 0;
  int len = strlen(str);
  int i;
  for (i = 0; i < len; i++) {
    if (i > 0 && map[str[i]] > map[str[i - 1]]) {
      sum += map[str[i]] - 2 * map[str[i - 1]];
    } else {
      sum += map[str[i]];
    }
  }
  return sum;
}