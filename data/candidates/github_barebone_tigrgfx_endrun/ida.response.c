void __cdecl endrun(Save *s)
{
  unsigned int runlen; // eax

  --s->runlen;
  literal(s, s->prev);
  if ( s->runlen < 0x43 )
  {
    if ( s->runlen < 0x23 )
    {
      if ( s->runlen < 0x13 )
      {
        if ( s->runlen < 0xB )
        {
          if ( s->runlen < 3 )
          {
            while ( 1 )
            {
              runlen = s->runlen;
              s->runlen = runlen - 1;
              if ( !runlen )
                break;
              literal(s, s->prev);
            }
          }
          else
          {
            encodelen(s, 0x101u, 0, s->runlen - 3);
          }
        }
        else
        {
          encodelen(s, 0x109u, 1u, s->runlen - 11);
        }
      }
      else
      {
        encodelen(s, 0x10Du, 2u, s->runlen - 19);
      }
    }
    else
    {
      encodelen(s, 0x111u, 3u, s->runlen - 35);
    }
  }
  else
  {
    encodelen(s, 0x115u, 4u, s->runlen - 67);
  }
}