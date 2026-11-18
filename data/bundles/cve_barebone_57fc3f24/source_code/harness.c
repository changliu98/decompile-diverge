/*
 * cve_57fc3f24 -- uftpd handle_PORT() direct-call ASAN harness.
 * CVE-2020-20276, fix commit 0fb2c031 (project troglobit/uftpd).
 *
 * Fix diff (src/ftpcmd.c, handle_PORT):
 *   -	sprintf(addr, "%d.%d.%d.%d", a, b, c, d);
 *   +	snprintf(addr, sizeof(addr), "%d.%d.%d.%d", a, b, c, d);
 *
 * `addr` is `char addr[INET_ADDRSTRLEN]` (16 bytes). `a,b,c,d,e,f` are parsed
 * from the attacker-controlled FTP "PORT" command argument via
 * `sscanf(str, "%d,%d,%d,%d,%d,%d", ...)` with NO range validation (any int,
 * including many-digit or negative values, is accepted). The unguarded
 * `sprintf(addr, "%d.%d.%d.%d", a, b, c, d)` then formats those ints back
 * into the fixed 16-byte stack buffer: supplying large-magnitude values for
 * a/b/c/d makes the formatted string exceed 15 chars + NUL, overflowing
 * `addr` on the stack -- CWE-787 (out-of-bounds WRITE). This is the very
 * first statement handle_PORT performs on `str` (before inet_aton/strlcpy/
 * send_msg/close/uev_io_stop are ever reached), so the fault is purely a
 * function of the two arguments and needs no elaborate object state.
 *
 * Same project as cve_02dfabe9 (compose_path, CWE-127); the minimal-stub
 * ctrl_t / strlcpy conventions established there are reused here.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ---- minimal faithful type stub: ctrl_t as declared in src/uftpd.h,
 * trimmed to the fields handle_PORT() actually reads/writes (sd, data_sd,
 * data_watcher, data_address, data_port). Real libuev's uev_t is an external
 * submodule dependency not vendored in source_code/; every crafted input
 * keeps ctrl->data_sd <= 0 so the `uev_io_stop(&ctrl->data_watcher)` branch
 * is never taken (dead for this bug), so an opaque placeholder is faithful
 * for that one incidental field -- the address-of expression still
 * type-checks and the call still links. ---- */
typedef struct { int x; } uev_t;

typedef struct {
	int   sd;
	int   data_sd;
	uev_t data_watcher;
	char  data_address[INET_ADDRSTRLEN];
	int   data_port;
} ctrl_t;

/* ---- incidental callee stubs (never on the crash path for TRIGGERING
 * inputs: the sprintf() overflow fires before any of these are reached).
 * uev_io_stop(): real libuev call, unreachable here (data_sd <= 0 always).
 * ERR/DBG: src/uftpd.h LOGIT-family macros -> real syslog plumbing,
 * incidental to the bug -- no-op stand-ins, same pattern as cve_02dfabe9.
 * send_msg(): real body only does socket I/O (send() + ERR()) after the
 * point of interest; a no-op stand-in is faithful for this incidental
 * callee (its own memory safety is not implicated). ---- */
static void uev_io_stop(uev_t *w) { (void)w; }
#define ERR(code, fmt, ...) do { } while (0)
#define DBG(fmt, ...)       do { } while (0)
static int send_msg(int sd, char *msg) { (void)sd; (void)msg; return 0; }

/* ---- strlcpy: uftpd normally gets this from its `lite` submodule; glibc on
 * this box (2.35) does not provide it. Canonical OpenBSD reference
 * implementation (Todd C. Miller, public domain) -- same stand-in used in
 * cve_02dfabe9, faithful for this incidental (non-buggy) callee. ---- */
static size_t strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}
	if (n == 0) {
		if (siz != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (size_t)(s - src - 1);
}

/* =====================  handle_PORT -- VERBATIM  =====================
 * Copied byte-for-byte from data_cve/cve_57fc3f24/target/original_function.c
 */
static void handle_PORT(ctrl_t *ctrl, char *str)
{
	int a, b, c, d, e, f;
	char addr[INET_ADDRSTRLEN];
	struct sockaddr_in sin;

	if (ctrl->data_sd > 0) {
		uev_io_stop(&ctrl->data_watcher);
		close(ctrl->data_sd);
		ctrl->data_sd = -1;
	}

	/* Convert PORT command's argument to IP address + port */
	sscanf(str, "%d,%d,%d,%d,%d,%d", &a, &b, &c, &d, &e, &f);
	sprintf(addr, "%d.%d.%d.%d", a, b, c, d);

	/* Check IPv4 address using inet_aton(), throw away converted result */
	if (!inet_aton(addr, &(sin.sin_addr))) {
		ERR(0, "Invalid address '%s' given to PORT command", addr);
		send_msg(ctrl->sd, "500 Illegal PORT command.\r\n");
		return;
	}

	strlcpy(ctrl->data_address, addr, sizeof(ctrl->data_address));
	ctrl->data_port = e * 256 + f;

	DBG("Client PORT command accepted for %s:%d", ctrl->data_address, ctrl->data_port);
	send_msg(ctrl->sd, "200 PORT command successful.\r\n");
}
/* =====================  end verbatim handle_PORT  ===================== */

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;

	FILE *fp = fopen(argv[1], "rb");
	if (!fp)
		return 0;

	if (fseek(fp, 0, SEEK_END) != 0) {
		fclose(fp);
		return 0;
	}
	long sz = ftell(fp);
	if (sz < 0)
		sz = 0;
	fseek(fp, 0, SEEK_SET);

	/* HEAP-allocate the raw input (the PORT command's comma-separated
	 * argument string, i.e. the FTP client's `str`) so ASAN instruments
	 * it; +1 for the NUL terminator sscanf()/sprintf() require. */
	char *str = (char *)malloc((size_t)sz + 1);
	if (!str) {
		fclose(fp);
		return 0;
	}
	size_t got = fread(str, 1, (size_t)sz, fp);
	fclose(fp);
	str[got] = '\0';

	ctrl_t ctrl;
	memset(&ctrl, 0, sizeof(ctrl));
	ctrl.sd = -1;      /* invalid fd: send_msg() stub ignores it anyway */
	ctrl.data_sd = 0;  /* <=0: skip the uev_io_stop/close() branch (dead for this bug) */

	handle_PORT(&ctrl, str);

	free(str);
	return 0;
}
