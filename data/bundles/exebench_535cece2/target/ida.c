void __cdecl copy_dice(int *dice, int *copy)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 6; ++i )
    copy[i] = dice[i];
}