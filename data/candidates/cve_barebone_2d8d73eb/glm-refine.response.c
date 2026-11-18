define ACTION_ACCEPT      0x80

void __cdecl EveAddVerdict(SCJsonBuilder *jb, const Packet *p)
{
  SCJbOpenObject(jb, "verdict");

  // Check for Reject/Drop action combination
  if ( PacketCheckAction(p, ACTION_DROP_ALT) )
  {
    if ( EngineModeIsIPS() )
      SCJbSetFormatted(jb, "\"action\":\"drop\"");
    else
      SCJbSetFormatted(jb, "\"action\":\"alert\"");

    // Determine reject target direction
    if ( PacketCheckAction(p, ACTION_REJECT) )
    {
      SCJbSetFormatted(jb, "\"reject-target\":\"to_client\"");
    }
    else if ( PacketCheckAction(p, ACTION_REJECT_DST) )
    {
      SCJbSetFormatted(jb, "\"reject-target\":\"to_server\"");
    }
    else if ( PacketCheckAction(p, ACTION_REJECT_BOTH) )
    {
      SCJbSetFormatted(jb, "\"reject-target\":\"both\"");
    }

    // Determine reject mechanism based on L4 protocol
    SCJbOpenArray(jb, "reject");
    uint8_t proto = p->proto;
    
    if ( proto == IPPROTO_TCP )
    {
      SCJbAppendString(jb, "tcp-reset");
    }
    else if ( proto == IPPROTO_ICMPv4 || proto == IPPROTO_UDP || proto == IPPROTO_ICMPv6 )
    {
      SCJbAppendString(jb, "icmp-prohib");
    }
    
    SCJbClose(jb);
  }
  else
  {
    // Evaluate remaining non-reject verdict actions
    if ( PacketCheckAction(p, ACTION_DROP) && EngineModeIsIPS() )
    {
      SCJbSetFormatted(jb, "\"action\":\"drop\"");
    }
    else if ( PacketCheckAction(p, ACTION_ACCEPT) )
    {
      SCJbSetFormatted(jb, "\"action\":\"accept\"");
    }
    else if ( (p->alerts.alerts[p->alerts.cnt].action & ACTION_PASS) != 0 )
    {
      SCJbSetFormatted(jb, "\"action\":\"pass\"");
    }
    else
    {
      SCJbSetFormatted(jb, "\"action\":\"alert\"");
    }
  }

  SCJbClose(jb);
}