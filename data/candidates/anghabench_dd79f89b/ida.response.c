int __cdecl hx711_get_gain_to_pulse(int gain)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < HX711_GAIN_MAX; ++i )
  {
    if ( *(_DWORD *)(hx711_gain_to_scale + 8LL * i) == gain )
      return *(_DWORD *)(hx711_gain_to_scale + 8LL * i + 4);
  }
  return 1;
}