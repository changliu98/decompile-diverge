__attribute__((noinline))
void EveAddVerdict(SCJsonBuilder *jb, const Packet *p)
{
    SCJbOpenObject(jb, "verdict");

    /* add verdict info */
    if (PacketCheckAction(p, ACTION_REJECT_ANY)) {
        // check rule to define type of reject packet sent
        if (EngineModeIsIPS()) {
            JB_SET_STRING(jb, "action", "drop");
        } else {
            JB_SET_STRING(jb, "action", "alert");
        }
        if (PacketCheckAction(p, ACTION_REJECT)) {
            JB_SET_STRING(jb, "reject-target", "to_client");
        } else if (PacketCheckAction(p, ACTION_REJECT_DST)) {
            JB_SET_STRING(jb, "reject-target", "to_server");
        } else if (PacketCheckAction(p, ACTION_REJECT_BOTH)) {
            JB_SET_STRING(jb, "reject-target", "both");
        }
        SCJbOpenArray(jb, "reject");
        switch (p->proto) {
            case IPPROTO_UDP:
            case IPPROTO_ICMP:
            case IPPROTO_ICMPV6:
                SCJbAppendString(jb, "icmp-prohib");
                break;
            case IPPROTO_TCP:
                SCJbAppendString(jb, "tcp-reset");
                break;
        }
        SCJbClose(jb);

    } else if (PacketCheckAction(p, ACTION_DROP) && EngineModeIsIPS()) {
        JB_SET_STRING(jb, "action", "drop");
    } else if (PacketCheckAction(p, ACTION_ACCEPT)) {
        JB_SET_STRING(jb, "action", "accept");
    } else if (p->alerts.alerts[p->alerts.cnt].action & ACTION_PASS) {
        JB_SET_STRING(jb, "action", "pass");
    } else {
        // TODO make sure we don't have a situation where this wouldn't work
        JB_SET_STRING(jb, "action", "alert");
    }

    /* Close verdict */
    SCJbClose(jb);
}