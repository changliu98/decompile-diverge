void copy_dice(int *dice,int *copy)

{
  int i;
  int *copy_local;
  int *dice_local;
  
  for (i = 0; i < 6; i = i + 1) {
    copy[i] = dice[i];
  }
  return;
}