static inline int unix_socketpair(int sock_type, int family, int protocol,
				  const char *name)
{
	return func0_addr(sock_type, family, protocol, name, 0);
}