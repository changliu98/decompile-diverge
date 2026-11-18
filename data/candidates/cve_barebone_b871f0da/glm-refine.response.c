void __cdecl arp_print(netdissect_options *ndo, const u_char *bp, u_int length, u_int caplen)
{
    const char *sep_str;
    const char *sender_proto_addr_str;
    const char *target_proto_addr_str;
    const char *sender_hw_addr_str;
    const char *target_hw_addr_str;
    ndo_printf_t ndo_printf;
    
    u_short hrd, pro, op, linkaddr;
    u_char hlen, plen;
    const u_char *sha, *spa, *tha, *tpa;

    // 1. Bounds Check: Ensure at least 8 bytes are available for the ARP header
    if (ndo->ndo_snapend - 8 > ndo->ndo_snapend || bp > ndo->ndo_snapend - 8)
    {
        ndo->ndo_printf(ndo, "%s", "[|ARP]");
        return;
    }

    // 2. Extract ARP Header Fields
    hrd = EXTRACT_16BITS(bp);          // Hardware type
    pro = EXTRACT_16BITS(bp + 2);      // Protocol type
    // hln = bp[4];                    // Hardware address length
    // pln = bp[5];                    // Protocol address length
    op = EXTRACT_16BITS(bp + 6);       // Operation code

    // 3. Hardware Type Routing
    if (hrd == 15) // IEEE 802
    {
        linkaddr = 1; // LINKADDR_802
    }
    else if (hrd == 19) // ATMARP
    {
        atmarp_print(ndo, bp, length, caplen);
        return;
    }
    else
    {
        linkaddr = 0; // LINKADDR_ETHERNET
    }

    hlen = bp[4];
    plen = bp[5];

    // 4. Bounds Check: Ensure the full ARP payload is captured
    // Equivalent to: bp + 8 + 2*hlen + plen <= ndo->ndo_snapend
    if (ndo->ndo_snapend - plen <= ndo->ndo_snapend &&
        bp + 2 * hlen + 8 + plen <= ndo->ndo_snapend - plen)
    {
        if (!ndo->ndo_eflag)
            ndo->ndo_printf(ndo, "ARP, ");

        // 5. Fast Path: Standard IPv4/IPv6 ARP without verbose output
        if ((pro == 2048 || pro == 4096) && plen == 4 && hlen != 0 && !ndo->ndo_vflag)
        {
            // Fall through directly to the verbose formatting block below
        }
        else
        {
            // 6. Verbose Path: Print Hardware and Protocol details
            const char *hrd_str = tok2str(&arphrd_values, "Unknown Hardware (%u)", hrd);
            const char *pro_str = tok2str(&ethertype_values, "Unknown Protocol (0x%04x)", pro);
            ndo->ndo_printf(ndo, "%s (len %u), %s (len %u)", hrd_str, hlen, pro_str, plen);

            if (!ndo->ndo_vflag)
                goto out; // Skip operation details if not verbose
        }

        // 7. Verbose Operation Formatting
        ndo_printf = ndo->ndo_printf;
        sep_str = ndo->ndo_vflag ? ", " : "";
        
        const char *op_str = tok2str(&arpop_values, "Unknown (%u)", op);
        ndo_printf(ndo, "%s%s ", sep_str, op_str);

        // Calculate payload pointers
        sha = bp + 8;
        spa = bp + 8 + hlen;
        tha = bp + 8 + hlen + plen;
        tpa = bp + 8 + 2 * hlen + plen;

        switch (op)
        {
            case 1: // ARP Request
                target_proto_addr_str = getname(ndo, tpa);
                ndo_printf(ndo, "who-has %s", target_proto_addr_str);
                
                if (isnonzero(tha, hlen))
                {
                    target_hw_addr_str = linkaddr_string(ndo, tha, linkaddr, hlen);
                    ndo_printf(ndo, " (%s)", target_hw_addr_str);
                }
                
                sender_proto_addr_str = getname(ndo, spa);
                ndo_printf(ndo, " tell %s", sender_proto_addr_str);
                break;

            case 2: // ARP Reply
                sender_proto_addr_str = getname(ndo, spa);
                sender_hw_addr_str = linkaddr_string(ndo, sha, linkaddr, hlen);
                ndo_printf(ndo, "%s is-at %s", sender_proto_addr_str, sender_hw_addr_str);
                break;

            case 3: // RARP Request
                target_hw_addr_str = linkaddr_string(ndo, tha, linkaddr, hlen);
                sender_hw_addr_str = linkaddr_string(ndo, sha, linkaddr, hlen);
                ndo_printf(ndo, "who-is %s tell %s", target_hw_addr_str, sender_hw_addr_str);
                break;

            case 4: // RARP Reply
                target_hw_addr_str = linkaddr_string(ndo, tha, linkaddr, hlen);
                target_proto_addr_str = getname(ndo, tpa);
                ndo_printf(ndo, "%s at %s", target_hw_addr_str, target_proto_addr_str);
                break;

            case 8: // InARP Request
                target_hw_addr_str = linkaddr_string(ndo, tha, linkaddr, hlen);
                sender_hw_addr_str = linkaddr_string(ndo, sha, linkaddr, hlen);
                ndo_printf(ndo, "who-is %s tell %s", target_hw_addr_str, sender_hw_addr_str);
                break;

            case 9: // InARP Reply
                sender_hw_addr_str = linkaddr_string(ndo, sha, linkaddr, hlen);
                sender_proto_addr_str = getname(ndo, spa);
                ndo_printf(ndo, "%s at %s", sender_hw_addr_str, sender_proto_addr_str);
                break;

            default:
                ndo->ndo_default_print(ndo, bp, caplen);
                return; // Return early to avoid printing length for unknown ops
        }

out:
        ndo->ndo_printf(ndo, ", length %u", length);
    }
    else
    {
        // 8. Truncated Packet Handling
        ndo->ndo_printf(ndo, "%s", "[|ARP]");
        ndo->ndo_default_print(ndo, bp, length);
    }
}