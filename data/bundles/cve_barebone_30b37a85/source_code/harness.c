/* cve_barebone direct-call harness for cve_30b37a85 (libpcap rpcapd)
 * Target: daemon_AuthUserPwd  (rpcapd/daemon.c)
 * Bug class: NULL-pointer dereference (CWE-476).
 *
 * fix_commit 437b273761adedcbd880f714bfa44afeec186a31 added a NULL check on
 * crypt()'s return value before it is handed to strcmp(). See the module
 * docstring (gen_dc_cve_30b37a85.py) for the full analysis.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>          /* struct passwd -- the REAL type daemon_AuthUserPwd needs */

/* ---- portability.h (verbatim macro) ---- */
#define pcap_snprintf snprintf
/* ---- pcap/pcap.h (verbatim value) ---- */
#define PCAP_ERRBUF_SIZE 256

/* ---- byte accessor: NEVER reads past the actual input length (falls back to a fixed
 * filler instead) -- so a short/adversarial input file can't make the HARNESS itself
 * read out of bounds; only daemon_AuthUserPwd's own body is meant to fault. ---- */
static unsigned char vb_byte(const unsigned char *buf, size_t n, size_t idx, unsigned char fallback)
{
    return (idx < n) ? buf[idx] : fallback;
}

/* attacker-controlled "shadow/passwd database entry" for the one user getpwnam() ever
 * returns -- built by build_salt() in main(), read by getpwnam() below. */
static char g_salt[80];

/* ---- build_salt(): picks one of 4 malformed shapes (TRIGGER -> crypt() returns NULL)
 * or one of 4 well-formed shapes (SAFE -> crypt() returns non-NULL), driven entirely by
 * attacker-controlled input bytes (trig, variant, and -- for the "$9$" shape -- the
 * trailing payload bytes). ---- */
static void build_salt(int trig, unsigned char variant, const unsigned char *ibuf, size_t n)
{
    if (trig) {
        switch (variant % 4) {
        case 0: {
            /* unrecognized algorithm id ("9" is not in {1,5,6}) -> crypt() returns NULL
             * regardless of the filler that follows it. */
            char extra[9];
            size_t i;
            for (i = 0; i < 8; i++) {
                unsigned char b = vb_byte(ibuf, n, 34 + i, (unsigned char)('a' + i));
                extra[i] = (char)('a' + (b % 26));
            }
            extra[8] = '\0';
            snprintf(g_salt, sizeof(g_salt), "$9$%s", extra);
            break;
        }
        case 1:
            snprintf(g_salt, sizeof(g_salt), "$1");            /* "$id" with no closing '$' */
            break;
        case 2:
            g_salt[0] = '\0';                                  /* empty salt */
            break;
        case 3:
            snprintf(g_salt, sizeof(g_salt), "$");              /* lone '$' */
            break;
        }
    } else {
        switch (variant % 4) {
        case 0:
            snprintf(g_salt, sizeof(g_salt), "ab");              /* classic 2-char DES salt */
            break;
        case 1:
            snprintf(g_salt, sizeof(g_salt), "$1$abcdefgh$");    /* recognized id "1" (MD5) */
            break;
        case 2:
            snprintf(g_salt, sizeof(g_salt), "$6$saltsaltsalt$");/* recognized id "6" (SHA-512) */
            break;
        case 3:
            snprintf(g_salt, sizeof(g_salt), "XY");               /* classic 2-char DES salt */
            break;
        }
    }
}

/* ---- getpwnam(): incidental account lookup daemon_AuthUserPwd already calls. Always
 * "succeeds" (the missing-user case is a correctly-checked early return elsewhere in the
 * function, not this bug) and hands back a REAL <pwd.h> struct passwd whose pw_passwd is
 * the attacker-controlled g_salt build_salt() just built. Static storage reused across
 * calls mirrors real getpwnam()'s own documented contract. ---- */
struct passwd *getpwnam(const char *name)
{
    static struct passwd pw;
    static char pwname[32];
    size_t i;
    for (i = 0; i + 1 < sizeof(pwname) && name && name[i]; i++)
        pwname[i] = name[i];
    pwname[i] = '\0';
    pw.pw_name = pwname;
    pw.pw_passwd = g_salt;
    pw.pw_uid = 65534;             /* nobody; never read on the crash path (setuid stubbed) */
    pw.pw_gid = 65534;
    pw.pw_gecos = (char *)"";
    pw.pw_dir = (char *)"/nonexistent";
    pw.pw_shell = (char *)"/bin/false";
    return &pw;
}

/* ---- crypt(): incidental library call daemon_AuthUserPwd already makes. Reproduces
 * crypt(3)'s own documented failure contract (NULL on a malformed/unrecognized salt) --
 * the exact real-world condition commit 437b2737 added a check for. `key` never affects
 * the outcome, matching the real bug: any password reaches the same unchecked
 * crypt()-into-strcmp() line; it's the STORED salt/hash's format crypt() rejects. ---- */
char *crypt(const char *key, const char *salt)
{
    static char out[128];
    (void)key;
    if (salt == NULL || salt[0] == '\0')
        return NULL;
    if (salt[0] == '$') {
        const char *p2 = strchr(salt + 1, '$');
        if (p2 == NULL)
            return NULL;                                    /* "$id" with no closing '$' */
        if (!((size_t)(p2 - (salt + 1)) == 1 &&
              (salt[1] == '1' || salt[1] == '5' || salt[1] == '6')))
            return NULL;                                    /* unrecognized algorithm id */
        snprintf(out, sizeof(out), "%s", salt);
        return out;
    }
    if (strlen(salt) < 2)
        return NULL;                                        /* traditional DES salt needs >=2 chars */
    snprintf(out, sizeof(out), "%.2sHASHED", salt);
    return out;
}

/* ---- setuid(): incidental; always "succeeds" purely so a SAFE run (which reaches past
 * the crash site) doesn't actually drop this process's privileges. Strictly after the
 * crash site, so it can never affect whether the bug fires. ---- */
int setuid(uid_t uid)
{
    (void)uid;
    return 0;
}

/* ---- pcap_fmt_errmsg_for_errno(): incidental error-formatting helper (fmtutils.c),
 * reached only from the setuid-failure branch, which the stub above never exercises;
 * minimal semantically-equivalent stand-in kept for linkage. ---- */
void pcap_fmt_errmsg_for_errno(char *errbuf, size_t errbuflen, int errnum, const char *fmt, ...)
{
    (void)fmt;
    if (errbuf && errbuflen)
        snprintf(errbuf, errbuflen, "errno %d", errnum);
}

/* ======================================================================================
 * TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_30b37a85/target/original_function.c
 * Compiled without _WIN32 (POSIX body) and without HAVE_GETSPNAM (user_password =
 * user->pw_passwd branch) -- both real, unmodified branches already in the file; the
 * vulnerable strcmp(user_password, crypt(...)) line is identical either way.
 * noinline: a pure codegen hint (dc_batch requires the target function's own name in the
 * ASAN backtrace); does not touch the function's own bytes.
 * ====================================================================================== */
__attribute__((noinline))
static int
daemon_AuthUserPwd(char *username, char *password, char *errbuf)
{
#ifdef _WIN32
	/*
	 * Warning: the user which launches the process must have the
	 * SE_TCB_NAME right.
	 * This corresponds to have the "Act as part of the Operating System"
	 * turned on (administrative tools, local security settings, local
	 * policies, user right assignment)
	 * However, it seems to me that if you run it as a service, this
	 * right should be provided by default.
	 *
	 * XXX - hopefully, this returns errors such as ERROR_LOGON_FAILURE,
	 * which merely indicates that the user name or password is
	 * incorrect, not whether it's the user name or the password
	 * that's incorrect, so a client that's trying to brute-force
	 * accounts doesn't know whether it's the user name or the
	 * password that's incorrect, so it doesn't know whether to
	 * stop trying to log in with a given user name and move on
	 * to another user name.
	 */
	HANDLE Token;
	if (LogonUser(username, ".", password, LOGON32_LOGON_NETWORK, LOGON32_PROVIDER_DEFAULT, &Token) == 0)
	{
		pcap_fmt_errmsg_for_win32_err(errbuf, PCAP_ERRBUF_SIZE,
		    GetLastError(), "LogonUser() failed");
		return -1;
	}

	// This call should change the current thread to the selected user.
	// I didn't test it.
	if (ImpersonateLoggedOnUser(Token) == 0)
	{
		pcap_fmt_errmsg_for_win32_err(errbuf, PCAP_ERRBUF_SIZE,
		    GetLastError(), "ImpersonateLoggedOnUser() failed");
		CloseHandle(Token);
		return -1;
	}

	CloseHandle(Token);
	return 0;

#else
	/*
	 * See
	 *
	 *	http://www.unixpapa.com/incnote/passwd.html
	 *
	 * We use the Solaris/Linux shadow password authentication if
	 * we have getspnam(), otherwise we just do traditional
	 * authentication, which, on some platforms, might work, even
	 * with shadow passwords, if we're running as root.  Traditional
	 * authenticaion won't work if we're not running as root, as
	 * I think these days all UN*Xes either won't return the password
	 * at all with getpwnam() or will only do so if you're root.
	 *
	 * XXX - perhaps what we *should* be using is PAM, if we have
	 * it.  That might hide all the details of username/password
	 * authentication, whether it's done with a visible-to-root-
	 * only password database or some other authentication mechanism,
	 * behind its API.
	 */
	struct passwd *user;
	char *user_password;
#ifdef HAVE_GETSPNAM
	struct spwd *usersp;
#endif

	// This call is needed to get the uid
	if ((user = getpwnam(username)) == NULL)
	{
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "Authentication failed: user name or password incorrect");
		return -1;
	}

#ifdef HAVE_GETSPNAM
	// This call is needed to get the password; otherwise 'x' is returned
	if ((usersp = getspnam(username)) == NULL)
	{
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "Authentication failed: user name or password incorrect");
		return -1;
	}
	user_password = usersp->sp_pwdp;
#else
	/*
	 * XXX - what about other platforms?
	 * The unixpapa.com page claims this Just Works on *BSD if you're
	 * running as root - it's from 2000, so it doesn't indicate whether
	 * macOS (which didn't come out until 2001, under the name Mac OS
	 * X) behaves like the *BSDs or not, and might also work on AIX.
	 * HP-UX does something else.
	 *
	 * Again, hopefully PAM hides all that.
	 */
	user_password = user->pw_passwd;
#endif

	if (strcmp(user_password, (char *) crypt(password, user_password)) != 0)
	{
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "Authentication failed: user name or password incorrect");
		return -1;
	}

	if (setuid(user->pw_uid))
	{
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "setuid");
		return -1;
	}

/*	if (setgid(user->pw_gid))
	{
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    errno, "setgid");
		return -1;
	}
*/
	return 0;

#endif

}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded). byte[0]'s LSB selects
 * TRIGGER (malformed salt -> crypt() returns NULL -> strcmp(user_password, NULL) SEGVs
 * inside daemon_AuthUserPwd's own unchecked line) vs SAFE (well-formed salt -> crypt()
 * returns non-NULL -> strcmp() completes normally, either branch of daemon_AuthUserPwd's
 * own subsequent logic returns cleanly). byte[1] selects among 4 salt shapes per class
 * for diversity. username/password (daemon_AuthUserPwd's own arguments) are constructed
 * from the remaining input bytes. */
int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    size_t n = (size_t)sz;
    unsigned char *ibuf = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
    if (!ibuf) { fclose(f); return 0; }
    size_t got = n ? fread(ibuf, 1, n, f) : 0;
    fclose(f);
    (void)got;

    unsigned char b0 = vb_byte(ibuf, n, 0, 0);
    unsigned char b1 = vb_byte(ibuf, n, 1, 0);
    int trig = b0 & 1;

    build_salt(trig, b1, ibuf, n);

    char *username = (char *)malloc(17);
    char *password = (char *)malloc(17);
    char *errbuf   = (char *)malloc(PCAP_ERRBUF_SIZE);
    if (!username || !password || !errbuf) {
        free(ibuf); free(username); free(password); free(errbuf);
        return 0;
    }
    size_t i;
    for (i = 0; i < 16; i++)
        username[i] = (char)('a' + (vb_byte(ibuf, n, 2 + i, (unsigned char)i) % 26));
    username[16] = '\0';
    for (i = 0; i < 16; i++)
        password[i] = (char)('A' + (vb_byte(ibuf, n, 18 + i, (unsigned char)i) % 26));
    password[16] = '\0';
    memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    /* volatile function pointer: forbid the compiler from proving-away/inlining the one
     * call site (daemon_AuthUserPwd is `static`; noinline above is the belt, this is the
     * suspenders -- neither touches its own bytes). */
    int (*volatile vb_call)(char *, char *, char *) = daemon_AuthUserPwd;
    int rv = vb_call(username, password, errbuf);
    (void)rv;

    /* Only reached on a SAFE run (a triggering run SEGVs inside strcmp, above). */
    free(ibuf);
    free(username);
    free(password);
    free(errbuf);
    return 0;
}
