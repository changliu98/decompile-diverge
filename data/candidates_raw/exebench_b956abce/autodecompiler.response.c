void set_ip_src(struct in_addr src, char *packet) {
 struct ip *ip = (struct ip*) packet;
 ip->ip_src = src;
}