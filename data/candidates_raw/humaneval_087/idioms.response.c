struct pos *get_all_pos(int **board, int board_size, int *row_size, int val, int *return_size){
  struct pos *out = (pos *)malloc(sizeof(pos)*40);
  int i; int j; int count = 0;
  for(i = 0; i < board_size; i++){
    for(j = row_size[i]-1; j >= 0; j--){
      if(board[i][j] == val){
        out[count].x = i;
        out[count].y = j;
        count++;
      }
    }
  }
  *return_size = count;
  return out;
}