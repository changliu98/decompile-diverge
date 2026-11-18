void func0(int *game,int *guess,int *out,int length)

{
  int iVar1;
  int i;
  int length_local;
  int *out_local;
  int *guess_local;
  int *game_local;
  
  for (i = 0; i < length; i = i + 1) {
    iVar1 = abs(game[i] - guess[i]);
    out[i] = iVar1;
  }
  return;
}