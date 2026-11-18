int __cdecl lowercase(int ch_0)
{
  if ( ch_0 < 65 || ch_0 > 90 )
    return ch_0;
  else
    return ch_0 - 65 + 97;
}