char*** func0(int l, int b, int h) {
 char*** cube = (char***) malloc(sizeof(char**) * h);
 for (int i = 0; i < h; i++) {
  cube[i] = (char**) malloc(sizeof(char*) * b);
  for (int j = 0; j < b; j++) {
   cube[i][j] = (char*) malloc(sizeof(char) * l);
   for (int k = 0; k < l; k++) {
    cube[i][j][k] = '*';
   }
  }
 }
 return cube;
}