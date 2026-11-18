void EveAddVerdict(SCJb *jb, PACKET *p) {
  SCJbOpenObject(jb, "verdict");
  if (PacketCheckAction(p, 28)) {
    if (EngineModeIsIPS()) {
      SCJbSetFormatted(jb, "\"action\":\"drop\"");
    } else {
      SCJbSetFormatted(jb, "\"action\":\"alert\"");
    }
    if (PacketCheckAction(p, 4)) {
      SCJbSetFormatted(jb, "\"reject-target\":\"to_client\"");
    } else if (PacketCheckAction(p, 8)) {
      SCJbSetFormatted(jb, "\"reject-target\":\"to_server\"");
    } else if (PacketCheckAction(p, 16)) {
      SCJbSetFormatted(jb, "\"reject-target\":\"both\"");
    }
    SCJbOpenArray(jb, "reject");
    switch (p->Proto) {
      case 1:
      case 17:
      case 58:
      case 6:
        SCJbAppendString(jb, "icmp-prohib");
        break;
    }
    SCJbClose(jb);
  } else {
    if (PacketCheckAction(p, 2) && EngineModeIsIPS()) {
      SCJbSetFormatted(jb, "\"action\":\"drop\"");
    } else if (PacketCheckAction(p, 128)) {
      SCJbSetFormatted(jb, "\"action\":\"accept\"");
    } else if (p->Flow.Layer[p->Flow.LayerCount].Flags & 32) {
      SCJbSetFormatted(jb, "\"action\":\"pass\"");
    } else {
      SCJbSetFormatted(jb, "\"action\":\"alert\"");
    }
  }
  SCJbClose(jb);
}