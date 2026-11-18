__attribute__((used)) static int
bgp_vpn_route_print(netdissect_options *ndo,
                    const u_char *pptr, char *buf, u_int buflen)
{
    unsigned i;
    unsigned route_type;
    unsigned route_length;
    unsigned sg_length;
    unsigned addr_length;

    if (pptr + 2 > ndo->ndo_snapend) {
        goto trunc;
    }
    route_type = *pptr++;
    route_length = *pptr++;

    /* Print the type and length */
    snprintf(buf, buflen, "Route-Type: %s (%u), length: %u",
             tok2str(bgp_multicast_vpn_route_type_values, "Unknown", route_type),
             route_type, route_length);

    /* If there isn't enough data for the RD, then stop here. */
    switch (route_type) {
    case BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE:
        if (pptr + 8 > ndo->ndo_snapend) {
            goto trunc;
        }
        break;
    case BGP_MULTICAST_VPN_ROUTE_TYPE_SG:
    case BGP_MULTICAST_VPN_ROUTE_TYPE_SG_ORIG:
        if (pptr + 12 > ndo->ndo_snapend) {
            goto trunc;
        }
        break;
    case BGP_MULTICAST_VPN_ROUTE_TYPE_IGMP:
    case BGP_MULTICAST_VPN_ROUTE_TYPE_IGMP_SG:
        if (pptr + 8 > ndo->ndo_snapend) {
            goto trunc;
        }
        break;
    case BGP_MULTICAST_VPN_ROUTE_TYPE_IGMP_SG_ORIG:
        if (pptr + 8 > ndo->ndo_snapend) {
            goto trunc;
        }
        break;
    }

    /* Now we have enough data to print the RD */
    i = strlen(buf);
    switch (route_type) {
    case BGP_MULTICAST_VPN_ROUTE_TYPE_SOURCE:
        snprintf(buf + i, buflen - i, ", RD: %s, Originator %s",
                 bgp_vpn_rd_print(ndo, pptr),
                 bgp_vpn_ip_print(ndo, pptr + 8, (route_length - 8) * 8));
        break;
    case BGP_MULTICAST_VPN_ROUTE_TYPE_SG:
    case BGP_MULTICAST_VPN_ROUTE_TYPE_SG_ORIG:
        snprintf(buf + i, buflen - i, ", RD: %s, Source-AS %s",
                 bgp_vpn_rd_print(ndo, pptr),
                 as_printf(ndo, astostr, sizeof(astostr), EXTRACT_32BITS(pptr + 8)));
        break;
    case BGP_MULTICAST_VPN_ROUTE_TYPE_IGMP:
        snprintf(buf + i, buflen - i, ", RD: %s",
                 bgp_vpn_rd_print(ndo, pptr));
        pptr += 8;
        sg_length = bgp_vpn_sg_print(ndo, pptr, buf, buflen);
        addr_length = route_length - sg_length;
        if ((addr_length > 0 || addr_length == 0 && pptr + sg_length <= ndo->ndo_snapend) &&
            pptr + sg_length <= ndo->ndo_snapend) {
            snprintf(buf + strlen(buf), buflen - strlen(buf),
                     ", IGMP Group Address %s",
                     bgp_vpn_ip_print(ndo, pptr + sg_length, addr_length * 8));
        } else {
            goto trunc;
        }
        break;
    case BGP_MULTICAST_VPN_ROUTE_TYPE_IGMP_SG:
    case BGP_MULTICAST_VPN_ROUTE_TYPE_IGMP_SG_ORIG:
        snprintf(buf + i, buflen - i, ", RD: %s",
                 bgp_vpn_rd_print(ndo, pptr));
        pptr += 8;
        sg_length = bgp_vpn_sg_print(ndo, pptr, buf, buflen);
        break;
    case BGP_MULTICAST_VPN_ROUTE_TYPE_IGMP_SG_ORIG:
        snprintf(buf + i, buflen - i, ", RD: %s, Source-AS %s",
                 bgp_vpn_rd_print(ndo, pptr),
                 as_printf(ndo, astostr, sizeof(astostr), EXTRACT_32BITS(pptr + 8)));
        pptr += 8;
        sg_length = bgp_vpn_sg_print(ndo, pptr, buf, buflen);
        break;
    }

    return (route_length + 2);

trunc:
    ND_PRINT((ndo, "%s", tstr));
    return (-2);
}