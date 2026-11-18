static inline int func0(int sock_type, int family, int protocol,
				  const char *name)
{
	return func0_addr(sock_type, family, protocol, name, 0);
}