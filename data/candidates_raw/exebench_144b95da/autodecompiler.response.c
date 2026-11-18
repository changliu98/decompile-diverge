int
rsock_ipproto_to_int(const char *str, long len, int val)
{
    switch (len) {
      case 2:
# 5337 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "ip", len)) return IPPROTO_IP;
        if (!strncasecmp(str, "icmp", len)) return IPPROTO_ICMP;
        if (!strncasecmp(str, "igmp", len)) return IPPROTO_IGMP;
        if (!strncasecmp(str, "tcp", len)) return IPPROTO_TCP;
        if (!strncasecmp(str, "udp", len)) return IPPROTO_UDP;
        if (!strncasecmp(str, "raw", len)) return IPPROTO_RAW;



        break;

      case 3:
# 5376 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "ipv6", len)) return IPPROTO_IPV6;
        if (!strncasecmp(str, "icmpv6", len)) return IPPROTO_ICMPV6;



        break;

      case 4:
# 5391 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "none", len)) return IPPROTO_NONE;
        if (!strncasecmp(str, "dstopt", len)) return IPPROTO_DSTOPTS;



        break;

      case 5:



        if (!strncasecmp(str, "fragment", len)) return IPPROTO_FRAGMENT;



        break;

      case 6:



        if (!strncasecmp(str, "routing", len)) return IPPROTO_ROUTING;



        break;

      case 7:
# 5415 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "authen", len)) return IPPROTO_AUTH;



        break;

      case 8:



        if (!strncasecmp(str, "gre", len)) return IPPROTO_GRE;



        break;

      case 10:
# 5436 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "destination", len)) return IPPROTO_DSTOPTS;



        break;

      case 11:
# 5475 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "no_fragment", len)) return IPPROTO_FRAGMENT;



        break;

      case 12:
# 5490 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "hop_by_hop", len)) return IPPROTO_DSTOPTS;



        break;

      case 13:



        if (!strncasecmp(str, "fragmentation", len)) return IPPROTO_FRAGMENT;



        break;

      case 14:



        if (!strncasecmp(str, "encap_security", len)) return IPPROTO_ESP;



        break;

      case 15:
# 5514 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/rhomobile/rhodes/refs/heads/master/platform/shared/ruby/ext/socket/constdefs.c"
        if (!strncasecmp(str, "authentication", len)) return IPPROTO_AH;



        break;

      case 16:



        if (!strncasecmp(str, "router_alert", len)) return IPPROTO_DSTOPTS;



        break;

      default:
        return -1;
    }
    return -1;
}