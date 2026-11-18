int s_socketpair(int domain, int type, int protocol, int sv[2]) {
 return socketpair(domain&0xFF,type&0xFF,protocol,sv);
}