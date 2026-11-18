void __cdecl joga(int jogada, int (*matriz)[3], int i)
{
  // The switch statements map jogada 1-9 to indices 0-8.
  // Any other value hits the default case and returns early.
  if (jogada < 1 || jogada > 9)
    return;

  // 'matriz' is a pointer to an array of 3 ints. 
  // Treating it as a flat int* makes indexing the 3x3 board (0-8) cleaner.
  int *board = (int *)matriz;
  
  // i % 2 determines the player. 
  // Odd turns (Player 1) place -2. Even turns (Player 2) place -3.
  board[jogada - 1] = (i % 2) ? -2 : -3;
}