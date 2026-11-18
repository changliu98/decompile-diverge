static bool setsockopt_needs_rtnl(int optname) {
  switch (optname) {
    case IP_TOS:
    case IP_TTL:
    case IP_MULTICAST_TTL:
    case IP_MULTICAST_LOOP:
    case IP_ADD_MEMBERSHIP:
    case IP_DROP_MEMBERSHIP:
    case IP_MULTICAST_IF:
    case IP_MULTICAST_TTL:
    case IP_MULTICAST_LOOP:
    case IP_MULTICAST_IF:
    case IP_MULTICAST_EXCLUDE:
    case IP_MULTICAST_INCLUDE:
      return true;
    default:
      return false;
  }
}