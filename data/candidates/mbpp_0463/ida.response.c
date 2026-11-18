int __cdecl func0(int *arr, int n)
{
  int v3; // [rsp+0h] [rbp-34h]
  int v4; // [rsp+4h] [rbp-30h]
  int temp; // [rsp+8h] [rbp-2Ch]
  int i; // [rsp+Ch] [rbp-28h]
  int flag; // [rsp+10h] [rbp-24h]
  int max_so_far; // [rsp+14h] [rbp-20h]
  int min_ending_here; // [rsp+18h] [rbp-1Ch]
  int max_ending_here; // [rsp+1Ch] [rbp-18h]

  max_ending_here = 1;
  min_ending_here = 1;
  max_so_far = 0;
  flag = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( arr[i] <= 0 )
    {
      if ( arr[i] )
      {
        temp = max_ending_here;
        if ( arr[i] * min_ending_here <= 1 )
          v3 = 1;
        else
          v3 = arr[i] * min_ending_here;
        max_ending_here = v3;
        min_ending_here = arr[i] * temp;
      }
      else
      {
        max_ending_here = 1;
        min_ending_here = 1;
      }
    }
    else
    {
      max_ending_here *= arr[i];
      if ( arr[i] * min_ending_here >= 1 )
        v4 = 1;
      else
        v4 = arr[i] * min_ending_here;
      min_ending_here = v4;
      flag = 1;
    }
    if ( max_so_far < max_ending_here )
      max_so_far = max_ending_here;
  }
  if ( flag || max_so_far )
    return max_so_far;
  else
    return 0;
}