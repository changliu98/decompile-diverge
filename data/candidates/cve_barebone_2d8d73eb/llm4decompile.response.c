void EveAddVerdict(SCJsonBuilder *jb, Packet *p)
{
    SCJbOpenObject(jb, "verdict");

    if (PacketCheckAction(p, 0x1c)) {
        if (EngineModeIsIPS()) {
            SCJbSetFormatted(jb, "\"action\":\"drop\"");
        } else {
            SCJbSetFormatted(jb, "\"action\":\"alert\"");
        }
        if (PacketCheckAction(p, 0x04)) {
            SCJbSetFormatted(jb, "\"reject-target\":\"to_client\"");
        } else if (PacketCheckAction(p, 0x08)) {
            SCJbSetFormatted(jb, "\"reject-target\":\"to_server\"");
        } else if (PacketCheckAction(p, 0x10)) {
            SCJbSetFormatted(jb, "\"reject-target\":\"both\"");
        }
        SCJbOpenArray(jb, "reject");
        if (p->proto == 1 || p->proto == 17 || p->proto == 18) {
            SCJbAppendString(jb, "icmp-prohib");
        } else if (p->proto == 6) {
            SCJbAppendString(jb, "tcp-reset");
        }
        SCJbClose(jb);
    } else if (PacketCheckAction(p, 0x02) && EngineModeIsIPS()) {
        SCJbSetFormatted(jb, "\"action\":\"drop\"");
    } else if (PacketCheckAction(p, 0x80)) {
        SCJbSetFormatted(jb, "\"action\":\"accept\"");
    } else if (p->alerts.alerts[p->alerts.cnt].action & 0x20) {
        SCJbSetFormatted(jb, "\"action\":\"pass\"");
    } else {
        SCJbSetFormatted(jb, "\"action\":\"alert\"");
    }

    SCJbClose(jb);
}