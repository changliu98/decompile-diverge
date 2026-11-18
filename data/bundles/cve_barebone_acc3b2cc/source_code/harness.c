/*
 * cve_barebone direct-call harness for CVE-2023-7256 (libpcap, sock_initaddress).
 *
 * CVE-2023-7256: sock_initaddress() calls getaddrinfo() and, on some failure paths,
 * an internal *retry* getaddrinfo() call that it then frees with freeaddrinfo() --
 * but on that particular path it does NOT reset the caller's `*addrinfo` out-param
 * back to NULL before returning -1. The function's own doc comment says the
 * 'addrinfo' variable "has to be deleted by the programmer by calling freeaddrinfo()
 * when it is no longer needed" without excluding the -1 (error) case, so a realistic
 * caller that frees whenever the out-param comes back non-NULL double-frees the
 * memory sock_initaddress already freed internally. This harness supplies exactly
 * that realistic caller pattern around ONE call to the (byte-for-byte, unmodified)
 * vulnerable function.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* ---- real project macro (pcap/pcap.h) ------------------------------------ */
#define PCAP_ERRBUF_SIZE 256

/*
 * Minimal faithful stub for pcap_fmt_errmsg_for_errno() (fmtutils.c). It is only
 * reached from get_gai_errstring()'s "#ifdef EAI_SYSTEM" branch, which is not on
 * the double-free trigger path (that path never gets EAI_SYSTEM back for our
 * numeric host/port inputs) -- an incidental callee, not the crash path, so it is
 * stubbed to the same signature and the same core behaviour (format into errbuf)
 * rather than reproducing its errno-string-appending tail.
 */
static void
pcap_fmt_errmsg_for_errno(char *errbuf, size_t errbuflen, int errnum,
    const char *fmt, ...)
{
	va_list ap;
	(void)errnum;
	va_start(ap, fmt);
	vsnprintf(errbuf, errbuflen, fmt, ap);
	va_end(ap);
}

/* ---- real callee, copied verbatim from source_code/sockutils.c ----------- */
static void
get_gai_errstring(char *errbuf, int errbuflen, const char *prefix, int err,
    const char *hostname, const char *portname)
{
	char hostport[PCAP_ERRBUF_SIZE];

	if (hostname != NULL && portname != NULL)
		snprintf(hostport, PCAP_ERRBUF_SIZE, "host and port %s:%s",
		    hostname, portname);
	else if (hostname != NULL)
		snprintf(hostport, PCAP_ERRBUF_SIZE, "host %s",
		    hostname);
	else if (portname != NULL)
		snprintf(hostport, PCAP_ERRBUF_SIZE, "port %s",
		    portname);
	else
		snprintf(hostport, PCAP_ERRBUF_SIZE, "<no host or port!>");
	switch (err)
	{
#ifdef EAI_ADDRFAMILY
		case EAI_ADDRFAMILY:
			snprintf(errbuf, errbuflen,
			    "%sAddress family for %s not supported",
			    prefix, hostport);
			break;
#endif

		case EAI_AGAIN:
			snprintf(errbuf, errbuflen,
			    "%s%s could not be resolved at this time",
			    prefix, hostport);
			break;

		case EAI_BADFLAGS:
			snprintf(errbuf, errbuflen,
			    "%sThe ai_flags parameter for looking up %s had an invalid value",
			    prefix, hostport);
			break;

		case EAI_FAIL:
			snprintf(errbuf, errbuflen,
			    "%sA non-recoverable error occurred when attempting to resolve %s",
			    prefix, hostport);
			break;

		case EAI_FAMILY:
			snprintf(errbuf, errbuflen,
			    "%sThe address family for looking up %s was not recognized",
			    prefix, hostport);
			break;

		case EAI_MEMORY:
			snprintf(errbuf, errbuflen,
			    "%sOut of memory trying to allocate storage when looking up %s",
			    prefix, hostport);
			break;

		/*
		 * RFC 2553 had both EAI_NODATA and EAI_NONAME.
		 *
		 * RFC 3493 has only EAI_NONAME.
		 *
		 * Some implementations define EAI_NODATA and EAI_NONAME
		 * to the same value, others don't.  If EAI_NODATA is
		 * defined and isn't the same as EAI_NONAME, we handle
		 * EAI_NODATA.
		 */
#if defined(EAI_NODATA) && EAI_NODATA != EAI_NONAME
		case EAI_NODATA:
			snprintf(errbuf, errbuflen,
			    "%sNo address associated with %s",
			    prefix, hostport);
			break;
#endif

		case EAI_NONAME:
			snprintf(errbuf, errbuflen,
			    "%sThe %s couldn't be resolved",
			    prefix, hostport);
			break;

		case EAI_SERVICE:
			snprintf(errbuf, errbuflen,
			    "%sThe service value specified when looking up %s as not recognized for the socket type",
			    prefix, hostport);
			break;

		case EAI_SOCKTYPE:
			snprintf(errbuf, errbuflen,
			    "%sThe socket type specified when looking up %s as not recognized",
			    prefix, hostport);
			break;

#ifdef EAI_SYSTEM
		case EAI_SYSTEM:
			/*
			 * Assumed to be UN*X.
			 */
			pcap_fmt_errmsg_for_errno(errbuf, errbuflen, errno,
			    "%sAn error occurred when looking up %s",
			    prefix, hostport);
			break;
#endif

#ifdef EAI_BADHINTS
		case EAI_BADHINTS:
			snprintf(errbuf, errbuflen,
			    "%sInvalid value for hints when looking up %s",
			    prefix, hostport);
			break;
#endif

#ifdef EAI_PROTOCOL
		case EAI_PROTOCOL:
			snprintf(errbuf, errbuflen,
			    "%sResolved protocol when looking up %s is unknown",
			    prefix, hostport);
			break;
#endif

#ifdef EAI_OVERFLOW
		case EAI_OVERFLOW:
			snprintf(errbuf, errbuflen,
			    "%sArgument buffer overflow when looking up %s",
			    prefix, hostport);
			break;
#endif

		default:
			snprintf(errbuf, errbuflen,
			    "%sgetaddrinfo() error %d when looking up %s",
			    prefix, err, hostport);
			break;
	}
}

/* ---- real callee, copied verbatim from source_code/sockutils.c ----------- */
static int sock_ismcastaddr(const struct sockaddr *saddr)
{
	if (saddr->sa_family == PF_INET)
	{
		struct sockaddr_in *saddr4 = (struct sockaddr_in *) saddr;
		if (IN_MULTICAST(ntohl(saddr4->sin_addr.s_addr))) return 0;
		else return -1;
	}
	else
	{
		struct sockaddr_in6 *saddr6 = (struct sockaddr_in6 *) saddr;
		if (IN6_IS_ADDR_MULTICAST(&saddr6->sin6_addr)) return 0;
		else return -1;
	}
}

/* ---- TARGET FUNCTION -- byte-for-byte copy of target/original_function.c - */
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

/* -------------------------------------------------------------------------
 * main(): heap-allocates argv[1], derives (host, port) from its bytes, and
 * calls sock_initaddress() exactly once -- the direct-call target.
 *
 * File format: "<host>\n<port>" (either field may be empty, meaning NULL,
 * matching sock_initaddress's own documented "host and port may both be
 * null" contract). Both fields are attacker-controlled bytes copied out of
 * the on-disk input into their own heap allocations (ASAN-guarded).
 * ------------------------------------------------------------------------- */
int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 0; }
	rewind(f);

	char *buf = (char *)malloc((size_t)sz + 1);
	if (!buf) { fclose(f); return 0; }
	size_t rd = fread(buf, 1, (size_t)sz, f);
	fclose(f);
	buf[rd] = '\0';

	/* split into host field / port field on the first '\n' */
	const char *host_src;
	size_t host_len;
	const char *port_src = NULL;
	size_t port_len = 0;
	char *nl1 = (char *)memchr(buf, '\n', rd);
	if (nl1) {
		host_src = buf;
		host_len = (size_t)(nl1 - buf);
		port_src = nl1 + 1;
		size_t rem = rd - host_len - 1;
		char *nl2 = (char *)memchr(port_src, '\n', rem);
		port_len = nl2 ? (size_t)(nl2 - port_src) : rem;
	} else {
		host_src = buf;
		host_len = rd;
	}

	char *host = NULL;
	if (host_len > 0) {
		host = (char *)malloc(host_len + 1);
		if (!host) { free(buf); return 0; }
		memcpy(host, host_src, host_len);
		host[host_len] = '\0';
	}

	char *port = NULL;
	if (port_len > 0) {
		port = (char *)malloc(port_len + 1);
		if (!port) { free(buf); free(host); return 0; }
		memcpy(port, port_src, port_len);
		port[port_len] = '\0';
	}

	free(buf);

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	/*
	 * Every host in this corpus is a numeric literal, so force getaddrinfo()
	 * to resolve it purely locally (no DNS lookup) for full offline
	 * determinism. AI_NUMERICSERV is deliberately NOT set: the "safe" inputs
	 * use a valid numeric port and the "triggering" inputs use a bogus
	 * non-numeric service name that /etc/services can never resolve, which
	 * is the deterministic, glibc-version-independent way to make the
	 * *first* getaddrinfo() call fail (a purely-numeric-but-out-of-range
	 * port string is silently truncated mod 65536 by glibc instead of
	 * rejected, so it does not work as a failure trigger).
	 */
	hints.ai_flags = AI_NUMERICHOST;

	struct addrinfo *addrinfo = NULL;
	char *errbuf = (char *)malloc(PCAP_ERRBUF_SIZE);
	if (errbuf)
		errbuf[0] = '\0';

	int retval = sock_initaddress(host, port, &hints, &addrinfo, errbuf,
	    PCAP_ERRBUF_SIZE);

	fprintf(stderr,
	    "sock_initaddress: retval=%d addrinfo=%p host=%s port=%s errbuf=%s\n",
	    retval, (void *)addrinfo, host ? host : "(null)",
	    port ? port : "(null)", errbuf ? errbuf : "(null)");

	/*
	 * The realistic-caller half of CVE-2023-7256: sock_initaddress()'s own
	 * doc comment says the out-param "has to be deleted ... by calling
	 * freeaddrinfo() when it is no longer needed" without excluding the -1
	 * (error) return, so a caller frees whenever the out-param comes back
	 * non-NULL. On the vulnerable path (initial getaddrinfo() fails, the
	 * internal "just the host" retry succeeds, sock_initaddress() frees
	 * that result but does not reset *addrinfo to NULL before returning
	 * -1) that is exactly the block sock_initaddress() already freed
	 * internally -- a double free.
	 */
	if (addrinfo != NULL)
		freeaddrinfo(addrinfo);

	free(host);
	free(port);
	free(errbuf);
	return 0;
}
