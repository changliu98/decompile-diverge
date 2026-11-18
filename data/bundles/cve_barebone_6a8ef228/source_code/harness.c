/* cve_barebone direct-call harness for cve_6a8ef228 (troglobit/ssdp-responder)
 * Target: ssdp_recv  (ssdpd.c)
 * Bug class: off-by-one stack-buffer-overflow WRITE (CWE-787).
 *
 * fix_commit ce04b1f29a137198182f60bbb628d5ceb8171765 changed:
 *     -       char buf[MAX_PKT_SIZE];
 *     +       char buf[MAX_PKT_SIZE + 1];
 *              memset(buf, 0, sizeof(buf));
 *     -       len = recvfrom(sd, buf, sizeof(buf), MSG_DONTWAIT, &sa, &salen);
 *     +       len = recvfrom(sd, buf, sizeof(buf) - 1, MSG_DONTWAIT, &sa, &salen);
 *              if (len > 0) {
 *     -               buf[len] = 0;
 *     -
 *                      if (sa.sa_family != AF_INET)
 *
 * The vulnerable ssdp_recv() declares `char buf[MAX_PKT_SIZE]` (512 bytes, ssdp.h)
 * and calls `recvfrom(sd, buf, sizeof(buf), ...)`, which can fill and return the
 * FULL 512 bytes (valid indices 0..511). It then unconditionally does
 * `buf[len] = 0;` -- when a UDP datagram of >= 512 bytes arrives, len == 512 and
 * that store writes buf[512], one byte past the end of the 512-byte stack array.
 * The fix both grows the buffer by one byte AND shrinks the recv() request by one
 * byte, so the NUL terminator always lands in-bounds; it also drops the now-
 * redundant explicit store (memset() already zeroed the extra byte).
 *
 * Isolation: a UDP/AF_INET socket pair over loopback stands in for the real
 * multicast listener socket -- ssdp_recv() only ever calls recvfrom() on whatever
 * fd it is handed, so a plain bound UDP socket exercises it identically to the
 * real event loop (poll() -> ssdp_recv(ifs->in)). main() sends the raw input file
 * as ONE UDP datagram, so the file's bytes ARE the attacker-controlled packet.
 *
 * ssdp_recv() also reads `struct sockaddr sa` / `socklen_t salen` UNINITIALIZED
 * going into recvfrom() -- a real, separate latent bug in the original source
 * (unrelated to this CVE), preserved byte-for-byte below. It is harmless here: a
 * plain UDP/AF_INET peer address is always exactly sizeof(struct sockaddr_in) ==
 * sizeof(struct sockaddr) == 16 bytes on Linux/x86-64, so the kernel writes
 * exactly those 16 bytes into `sa` regardless of whatever garbage `salen` held on
 * entry -- it can neither overflow `sa` nor leave it partly written, so it cannot
 * manufacture a spurious crash independent of the real len==512 trigger.
 */
#define _GNU_SOURCE   /* strcasestr() */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

/* ---- ssdp.h (real names/values) ---- */
#define MAX_PKT_SIZE  512
#define SSDP_ST_ALL   "ssdp:all"
#define logit(lvl, fmt, args...) syslog(lvl, fmt, ##args)

/* ---- queue.h BSD LIST_* macros (verbatim, real names -- ssdp_recv's callee
 * find_outbound() needs LIST_FOREACH over the interface list) ---- */
#define LIST_HEAD(name, type)						\
struct name {								\
	struct type *lh_first;	/* first element */			\
}

#define LIST_HEAD_INITIALIZER(head)					\
	{ NULL }

#define LIST_ENTRY(type)						\
struct {								\
	struct type *le_next;	/* next element */			\
	struct type **le_prev;	/* address of previous next element */	\
}

#define	LIST_FIRST(head)		((head)->lh_first)
#define	LIST_END(head)			NULL
#define	LIST_NEXT(elm, field)		((elm)->field.le_next)

#define LIST_FOREACH(var, head, field)					\
	for((var) = LIST_FIRST(head);					\
	    (var)!= LIST_END(head);					\
	    (var) = LIST_NEXT(var, field))

/* ---- ssdpd.c real types/globals ssdp_recv's own body + find_outbound need ---- */
struct ifsock {
	LIST_ENTRY(ifsock) link;

	int stale;
	int mod;

	/*
	 * Sockets for inbound and outbound
	 *
	 * - The inbound is the multicast socket, shared between all ifaces
	 * - The outbound is bound to the iface address and a random port
	 */
	int in, out;

	/* Interface address and netmask */
	struct sockaddr_in addr;
	struct sockaddr_in mask;

	void (*cb)(int);
};

LIST_HEAD(, ifsock) il = LIST_HEAD_INITIALIZER();   /* always empty in this harness */

char uuid[42];

static char *supported_types[] = {
	SSDP_ST_ALL,
	"upnp:rootdevice",
	"urn:schemas-upnp-org:device:InternetGatewayDevice:1",
	uuid,
	NULL
};

/* Find interface in same subnet as sa -- VERBATIM from ssdpd.c. `il` is always
 * empty here, so this deterministically returns NULL for every call. */
static struct ifsock *find_outbound(struct sockaddr *sa)
{
	in_addr_t cand;
	struct ifsock *ifs;
	struct sockaddr_in *addr = (struct sockaddr_in *)sa;

	cand = addr->sin_addr.s_addr;
	LIST_FOREACH(ifs, &il, link) {
		in_addr_t a, m;

		a = ifs->addr.sin_addr.s_addr;
		m = ifs->mask.sin_addr.s_addr;
		if (a == htonl(INADDR_ANY) || m == htonl(INADDR_ANY))
			continue;

		if ((a & m) == (cand & m))
			return ifs;
	}

	return NULL;
}

/* Off the crash path: ssdp_recv() only reaches send_message() through a non-NULL
 * `ifs` from find_outbound() above, which is provably always NULL here (`il` is
 * permanently empty) -- so this is dead code for every corpus input. Minimal
 * faithful stand-in (real name + real signature) rather than pulling in its own
 * real callees (compose_response/compose_notify/compose_addr), per the incidental-
 * callee rule. */
static void send_message(struct ifsock *ifs, char *type, struct sockaddr *sa)
{
	(void)ifs; (void)type; (void)sa;
}

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_6a8ef228/target/original_function.c */
/* ======================================================================================== */
static void ssdp_recv(int sd)
{
	ssize_t len;
	struct sockaddr sa;
	socklen_t salen;
	char buf[MAX_PKT_SIZE];

	memset(buf, 0, sizeof(buf));
	len = recvfrom(sd, buf, sizeof(buf), MSG_DONTWAIT, &sa, &salen);
	if (len > 0) {
		buf[len] = 0;

		if (sa.sa_family != AF_INET)
			return;

		if (strstr(buf, "M-SEARCH *")) {
			size_t i;
			char *ptr, *type;
			struct ifsock *ifs;
			struct sockaddr_in *sin = (struct sockaddr_in *)&sa;

			ifs = find_outbound(&sa);
			if (!ifs) {
				logit(LOG_DEBUG, "No matching socket for client %s", inet_ntoa(sin->sin_addr));
				return;
			}
			logit(LOG_DEBUG, "Matching socket for client %s", inet_ntoa(sin->sin_addr));

			type = strcasestr(buf, "\r\nST:");
			if (!type) {
				logit(LOG_DEBUG, "No Search Type (ST:) found in M-SEARCH *, assuming " SSDP_ST_ALL);
				type = SSDP_ST_ALL;
				send_message(ifs, type, &sa);
				return;
			}

			type = strchr(type, ':');
			if (!type)
				return;
			type++;
			while (isspace(*type))
				type++;

			ptr = strstr(type, "\r\n");
			if (!ptr)
				return;
			*ptr = 0;

			for (i = 0; supported_types[i]; i++) {
				if (!strcmp(supported_types[i], type)) {
					logit(LOG_DEBUG, "M-SEARCH * ST: %s from %s port %d", type,
					      inet_ntoa(sin->sin_addr), ntohs(sin->sin_port));
					send_message(ifs, type, &sa);
					return;
				}
			}

			logit(LOG_DEBUG, "M-SEARCH * for unsupported ST: %s from %s", type,
			      inet_ntoa(sin->sin_addr));
		}
	}
}
/* ==== end verbatim target function ==== */

/* ---- driver ---------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded) and sends it as ONE UDP
 * datagram over loopback into a socket bound to 127.0.0.1:<ephemeral port>. ssdp_recv()
 * is then called on the RECEIVING fd exactly as the real event loop would
 * (poll() -> ssdp_recv(ifs->in)): recvfrom() hands back whatever the sender put on the
 * wire, so the input file's raw bytes ARE the attacker-controlled UDP payload. A
 * payload of >= MAX_PKT_SIZE (512) bytes makes recvfrom() return len==512 (buf's own
 * size, its request cap) -> ssdp_recv's `buf[len] = 0;` writes buf[512], one byte past
 * the 512-byte stack array (CWE-787). A payload under 512 bytes returns len<512 and
 * stays in-bounds.
 */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
	long fsz = ftell(fp);
	if (fsz < 0) { fclose(fp); return 64; }
	if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

	size_t n = (size_t)fsz;
	unsigned char *ibuf = (unsigned char *)malloc(n ? n : 1);
	if (!ibuf) { fclose(fp); return 64; }
	size_t irn = n ? fread(ibuf, 1, n, fp) : 0;
	fclose(fp);
	(void)irn;

	int rsock = socket(AF_INET, SOCK_DGRAM, 0);
	if (rsock < 0) { perror("socket(r)"); free(ibuf); return 64; }

	struct sockaddr_in raddr;
	memset(&raddr, 0, sizeof(raddr));
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(0);
	raddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (bind(rsock, (struct sockaddr *)&raddr, sizeof(raddr)) != 0) {
		perror("bind"); close(rsock); free(ibuf); return 64;
	}
	socklen_t ralen = sizeof(raddr);
	if (getsockname(rsock, (struct sockaddr *)&raddr, &ralen) != 0) {
		perror("getsockname"); close(rsock); free(ibuf); return 64;
	}

	int ssock = socket(AF_INET, SOCK_DGRAM, 0);
	if (ssock < 0) { perror("socket(s)"); close(rsock); free(ibuf); return 64; }

	ssize_t sn = sendto(ssock, ibuf, n, 0, (struct sockaddr *)&raddr, sizeof(raddr));
	if (sn < 0) { perror("sendto"); close(ssock); close(rsock); free(ibuf); return 64; }

	/* Volatile function-pointer indirection: ssdp_recv is `static` with a single call
	 * site here, which -O1 would otherwise inline away -- collapsing it out of the ASAN
	 * backtrace. This changes nothing about how it's called (same fd, same semantics). */
	void (*volatile vb_call_ssdp_recv)(int) = ssdp_recv;
	vb_call_ssdp_recv(rsock);

	/* Only reached on a SAFE run (a triggering run aborts inside ssdp_recv above). */
	close(ssock);
	close(rsock);
	free(ibuf);
	return 0;
}
