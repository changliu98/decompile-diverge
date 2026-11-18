char ***get_cube(int x, int y, int z){
 char ***cube = (char ***)malloc(z * sizeof(char **));
 int i; int j; int k;
 for(i = 0; i < z; i++){
  cube[i] = (char **)malloc(y * sizeof(char *));
  for(j = 0; j < y; j++){
   cube[i][j] = (char *)malloc(x * sizeof(char));
   for(k = 0; k < x; k++){
    cube[i][j][k] = '*';
   }
  }
 }
 return cube;
}