void __cdecl IdealTrack(unsigned __int64 tracks, unsigned __int64 top, unsigned __int64 bot, unsigned __int64 *ideal)
{
  if ( bot + top )
    *ideal = ((top + 1) * bot + (tracks - bot) * top) / (bot + top);
  else
    *ideal = 1LL;
}