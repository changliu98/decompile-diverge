static int PacketVerdict(JsonBuilder *builder, struct _Packet *p)
{
    SCJbOpenObject(builder, "verdict");

    if (PacketCheckAction(p, ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3))))
    {
        if (EngineModeIsIPS())
            SCJbSetFormatted(builder, "\"action\":\"drop\"");
        else
            SCJbSetFormatted(builder, "\"action\":\"alert\"");

        if (PacketCheckAction(p, (1 << 0)))
        {
            SCJbSetFormatted(builder, "\"reject-target\":\"to_client\"");
        }
        else if (PacketCheckAction(p, (1 << 3)))
        {
            SCJbSetFormatted(builder, "\"reject-target\":\"to_server\"");
        }
        else if (PacketCheckAction(p, (1 << 4)))
        {
            SCJbSetFormatted(builder, "\"reject-target\":\"both\"");
        }
        else
        {
            SCJbOpenArray(builder, "reject");
            switch (p->proto)
            {
                case 1:
                    SCJbAppendString(builder, "icmp-prohib");
                    break;
                case 6:
                    SCJbAppendString(builder, "tcp-reset");
                    break;
                case 17:
                    SCJbAppendString(builder, "icmp-prohib");
                    break;
                case 58:
                    SCJbAppendString(builder, "icmp-prohib");
                    break;
                default:
                    SCJbAppendString(builder, "icmp-prohib");
                    break;
            }
            SCJbClose(builder);
        }
    }
    else if (PacketCheckAction(p, (1 << 1)) && EngineModeIsIPS())
    {
        SCJbSetFormatted(builder, "\"action\":\"drop\"");
    }
    else if (PacketCheckAction(p, (1 << 7)))
    {
        SCJbSetFormatted(builder, "\"action\":\"accept\"");
    }
    else
    {
        if (p->flow[p->flow_id].flags & 0x20)
            SCJbSetFormatted(builder, "\"action\":\"pass\"");
        else
            SCJbSetFormatted(builder, "\"action\":\"alert\"");
    }

    return SCJbClose(builder);
}