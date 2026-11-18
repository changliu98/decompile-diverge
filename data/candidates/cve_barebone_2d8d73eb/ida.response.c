void __cdecl EveAddVerdict(SCJsonBuilder *jb, const Packet *p)
{
  int proto; // [rsp+Ch] [rbp-14h]

  SCJbOpenObject(jb, "verdict");
  if ( PacketCheckAction(p, 0x1Cu) )
  {
    if ( EngineModeIsIPS() )
      SCJbSetFormatted(jb, "\"action\":\"drop\"");
    else
      SCJbSetFormatted(jb, "\"action\":\"alert\"");
    if ( PacketCheckAction(p, 4u) )
    {
      SCJbSetFormatted(jb, "\"reject-target\":\"to_client\"");
    }
    else if ( PacketCheckAction(p, 8u) )
    {
      SCJbSetFormatted(jb, "\"reject-target\":\"to_server\"");
    }
    else if ( PacketCheckAction(p, 0x10u) )
    {
      SCJbSetFormatted(jb, "\"reject-target\":\"both\"");
    }
    SCJbOpenArray(jb, "reject");
    proto = p->proto;
    if ( proto != 1 )
    {
      if ( proto == 6 )
      {
        SCJbAppendString(jb, "tcp-reset");
        goto LABEL_17;
      }
      if ( proto != 17 && proto != 58 )
        goto LABEL_17;
    }
    SCJbAppendString(jb, "icmp-prohib");
LABEL_17:
    SCJbClose(jb);
    goto LABEL_26;
  }
  if ( PacketCheckAction(p, 2u) && EngineModeIsIPS() )
  {
    SCJbSetFormatted(jb, "\"action\":\"drop\"");
  }
  else if ( PacketCheckAction(p, 0x80u) )
  {
    SCJbSetFormatted(jb, "\"action\":\"accept\"");
  }
  else if ( (p->alerts.alerts[p->alerts.cnt].action & 0x20) != 0 )
  {
    SCJbSetFormatted(jb, "\"action\":\"pass\"");
  }
  else
  {
    SCJbSetFormatted(jb, "\"action\":\"alert\"");
  }
LABEL_26:
  SCJbClose(jb);
}