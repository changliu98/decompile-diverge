void json_verdict(struct SCJsonBuilder *jb, struct Packet *p)
{
    int proto;
    json_begin(jb, "verdict");
    if (is_verdict(p, SC_VERDICT_ACTION)) {
        if (is_verdict(p, SC_VERDICT_ACTION_DROP))
            json_string(jb, "\"action\":\"drop\"");
        else
            json_string(jb, "\"action\":\"alert\"");
        if (is_verdict(p, SC_VERDICT_ACTION_TO_CLIENT))
            json_string(jb, "\"reject-target\":\"to_client\"");
        else if (is_verdict(p, SC_VERDICT_ACTION_TO_SERVER))
            json_string(jb, "\"reject-target\":\"to_server\"");
        else if (is_verdict(p, SC_VERDICT_ACTION_BOTH))
            json_string(jb, "\"reject-target\":\"both\"");
        json_begin(jb, "reject");
        switch (p->proto) {
        case SC_PROTO_TCP:
            json_string(jb, "tcp-reset");
            break;
        case SC_PROTO_UDP:
        case SC_PROTO_ICMP:
            json_string(jb, "icmp-prohib");
            break;
        case SC_PROTO_IP:
        case SC_PROTO_NONE:
            break;
        }
        json_end(jb);
    } else {
        if (is_verdict(p, SC_VERDICT_ACTION_DROP) &&
            is_verdict(p, SC_VERDICT_ACTION_TO_CLIENT))
            json_string(jb, "\"action\":\"drop\"");
        else if (is_verdict(p, SC_VERDICT_ACTION_ACCEPT))
            json_string(jb, "\"action\":\"accept\"");
        else if (p->alerts.alerts[p->alerts.cnt].action & SC_ACTION_PASS)
            json_string(jb, "\"action\":\"pass\"");
        else
            json_string(jb, "\"action\":\"alert\"");
    }
    json_end(jb);
}