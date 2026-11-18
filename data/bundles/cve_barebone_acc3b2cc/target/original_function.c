int sock_initaddress(const char *host, const char *port,
    struct addrinfo *hints, struct addrinfo **addrinfo, char *errbuf, int errbuflen)
{
	int retval;

	/*
	 * We allow both the host and port to be null, but getaddrinfo()
	 * is not guaranteed to do so; to handle that, if port is null,
	 * we provide "0" as the port number.
	 *
	 * This results in better error messages from get_gai_errstring(),
	 * as those messages won't talk about a problem with the port if
	 * no port was specified.
	 */
	retval = getaddrinfo(host, port == NULL ? "0" : port, hints, addrinfo);
	if (retval != 0)
	{
		if (errbuf)
		{
			if (host != NULL && port != NULL) {
				/*
				 * Try with just a host, to distinguish
				 * between "host is bad" and "port is
				 * bad".
				 */
				int try_retval;

				try_retval = getaddrinfo(host, NULL, hints,
				    addrinfo);
				if (try_retval == 0) {
					/*
					 * Worked with just the host,
					 * so assume the problem is
					 * with the port.
					 *
					 * Free up the address info first.
					 */
					freeaddrinfo(*addrinfo);
					get_gai_errstring(errbuf, errbuflen,
					    "", retval, NULL, port);
				} else {
					/*
					 * Didn't work with just the host,
					 * so assume the problem is
					 * with the host.
					 */
					get_gai_errstring(errbuf, errbuflen,
					    "", retval, host, NULL);
				}
			} else {
				/*
				 * Either the host or port was null, so
				 * there's nothing to determine.
				 */
				get_gai_errstring(errbuf, errbuflen, "",
				    retval, host, port);
			}
		}
		return -1;
	}
	/*
	 * \warning SOCKET: I should check all the accept() in order to bind to all addresses in case
	 * addrinfo has more han one pointers
	 */

	/*
	 * This software only supports PF_INET and PF_INET6.
	 *
	 * XXX - should we just check that at least *one* address is
	 * either PF_INET or PF_INET6, and, when using the list,
	 * ignore all addresses that are neither?  (What, no IPX
	 * support? :-))
	 */
	if (((*addrinfo)->ai_family != PF_INET) &&
	    ((*addrinfo)->ai_family != PF_INET6))
	{
		if (errbuf)
			snprintf(errbuf, errbuflen, "getaddrinfo(): socket type not supported");
		freeaddrinfo(*addrinfo);
		*addrinfo = NULL;
		return -1;
	}

	/*
	 * You can't do multicast (or broadcast) TCP.
	 */
	if (((*addrinfo)->ai_socktype == SOCK_STREAM) &&
	    (sock_ismcastaddr((*addrinfo)->ai_addr) == 0))
	{
		if (errbuf)
			snprintf(errbuf, errbuflen, "getaddrinfo(): multicast addresses are not valid when using TCP streams");
		freeaddrinfo(*addrinfo);
		*addrinfo = NULL;
		return -1;
	}

	return 0;
}