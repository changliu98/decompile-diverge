/* cve_barebone direct-call harness for CVE-2019-14196 (u-boot net/nfs.c)
 * Target: nfs_lookup_reply
 * Bug class: CWE-787 stack-buffer-overflow WRITE.
 *
 * See the generator script's module docstring for the full analysis. In short: the
 * function's first statement, memcpy(&rpc_pkt.u.data[0], pkt, len), copies a caller-
 * supplied `len` bytes into the 1152-byte stack-local `rpc_pkt` with NO check of `len`
 * against that capacity anywhere in the function -- the exact "unbounded memcpy" the
 * official fix's own commit title names, just on the statement the patch didn't reach.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>   /* ntohl */

/* ---- include/common.h (real u-boot typedef) ---- */
typedef unsigned char uchar;

/* ---- include/log.h: debug() is a no-op when _DEBUG is undefined (the real default) ---- */
#define debug(fmt, ...) do { } while (0)

/* ==== net/nfs.h, verbatim ==== */
#define NFS_FHSIZE      32
#define NFS3_FHSIZE     64

#define NFS_READ_SIZE	1024	/* biggest power of two that fits Ether frame */
#define NFS_MAX_ATTRS	26

/* Values for Accept State flag on RPC answers (See: rfc1831) */
enum rpc_accept_stat {
	NFS_RPC_SUCCESS = 0,	/* RPC executed successfully */
	NFS_RPC_PROG_UNAVAIL = 1,	/* remote hasn't exported program */
	NFS_RPC_PROG_MISMATCH = 2,	/* remote can't support version # */
	NFS_RPC_PROC_UNAVAIL = 3,	/* program can't support procedure */
	NFS_RPC_GARBAGE_ARGS = 4,	/* procedure can't decode params */
	NFS_RPC_SYSTEM_ERR = 5	/* errors like memory allocation failure */
};

struct rpc_t {
	union {
		uint8_t data[NFS_READ_SIZE + (6 + NFS_MAX_ATTRS) *
			sizeof(uint32_t)];
		struct {
			uint32_t id;
			uint32_t type;
			uint32_t rpcvers;
			uint32_t prog;
			uint32_t vers;
			uint32_t proc;
			uint32_t data[1];
		} call;
		struct {
			uint32_t id;
			uint32_t type;
			uint32_t rstatus;
			uint32_t verifier;
			uint32_t v2;
			uint32_t astatus;
			uint32_t data[NFS_READ_SIZE / sizeof(uint32_t) +
				NFS_MAX_ATTRS];
		} reply;
	} u;
} __attribute__((packed));

/* ==== net/nfs.c file-scope statics + #defines nfs_lookup_reply touches, verbatim ==== */
#define NFS_RPC_ERR	1
#define NFS_RPC_DROP	124

static unsigned long rpc_id;
static char filefh[NFS3_FHSIZE]; /* NFSv2 / NFSv3 file handle */
static int filefh3_length;	/* (variable) length of filefh when NFSv3 */

#define NFSV2_FLAG 1
#define NFSV3_FLAG 1 << 1
static char supported_nfs_versions = NFSV2_FLAG | NFSV3_FLAG;

/* ==== target function, byte-for-byte from target/original_function.c ==== */
static int nfs_lookup_reply(uchar *pkt, unsigned len)
{
	struct rpc_t rpc_pkt;

	debug("%s\n", __func__);

	memcpy(&rpc_pkt.u.data[0], pkt, len);

	if (ntohl(rpc_pkt.u.reply.id) > rpc_id)
		return -NFS_RPC_ERR;
	else if (ntohl(rpc_pkt.u.reply.id) < rpc_id)
		return -NFS_RPC_DROP;

	if (rpc_pkt.u.reply.rstatus  ||
	    rpc_pkt.u.reply.verifier ||
	    rpc_pkt.u.reply.astatus  ||
	    rpc_pkt.u.reply.data[0]) {
		switch (ntohl(rpc_pkt.u.reply.astatus)) {
		case NFS_RPC_SUCCESS: /* Not an error */
			break;
		case NFS_RPC_PROG_MISMATCH:
			/* Remote can't support NFS version */
			switch (ntohl(rpc_pkt.u.reply.data[0])) {
			/* Minimal supported NFS version */
			case 3:
				debug("*** Warning: NFS version not supported: Requested: V%d, accepted: min V%d - max V%d\n",
				      (supported_nfs_versions & NFSV2_FLAG) ?
						2 : 3,
				      ntohl(rpc_pkt.u.reply.data[0]),
				      ntohl(rpc_pkt.u.reply.data[1]));
				debug("Will retry with NFSv3\n");
				/* Clear NFSV2_FLAG from supported versions */
				supported_nfs_versions &= ~NFSV2_FLAG;
				return -NFS_RPC_PROG_MISMATCH;
			case 4:
			default:
				puts("*** ERROR: NFS version not supported");
				debug(": Requested: V%d, accepted: min V%d - max V%d\n",
				      (supported_nfs_versions & NFSV2_FLAG) ?
						2 : 3,
				      ntohl(rpc_pkt.u.reply.data[0]),
				      ntohl(rpc_pkt.u.reply.data[1]));
				puts("\n");
			}
			break;
		case NFS_RPC_PROG_UNAVAIL:
		case NFS_RPC_PROC_UNAVAIL:
		case NFS_RPC_GARBAGE_ARGS:
		case NFS_RPC_SYSTEM_ERR:
		default: /* Unknown error on 'accept state' flag */
			debug("*** ERROR: accept state error (%d)\n",
			      ntohl(rpc_pkt.u.reply.astatus));
			break;
		}
		return -1;
	}

	if (supported_nfs_versions & NFSV2_FLAG) {
		memcpy(filefh, rpc_pkt.u.reply.data + 1, NFS_FHSIZE);
	} else {  /* NFSV3_FLAG */
		filefh3_length = ntohl(rpc_pkt.u.reply.data[1]);
		if (filefh3_length > NFS3_FHSIZE)
			filefh3_length  = NFS3_FHSIZE;
		memcpy(filefh, rpc_pkt.u.reply.data + 2, filefh3_length);
	}

	return 0;
}
/* Indirect call through a volatile pointer: guarantees a real CALL instruction (and hence
 * a genuine stack frame + return address) survives -O1, so nfs_lookup_reply cannot be
 * folded into main() and vanish from the ASAN backtrace. Touches nothing in the target's
 * own body above. */
static int (*volatile vb_target)(uchar *, unsigned) = nfs_lookup_reply;

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 1;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

    /* HEAP-allocate the raw packet (ASAN-guarded): pkt's own allocation is exactly `n`
     * bytes, and we pass len==n, so the memcpy's SOURCE (read from pkt) never goes out
     * of bounds -- only the DESTINATION (write into the fixed-size stack rpc_pkt) can. */
    uchar *pkt = (uchar *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
    if (!pkt) { fclose(f); return 1; }
    size_t n = sz > 0 ? fread(pkt, 1, (size_t)sz, f) : 0;
    fclose(f);

    int ret = vb_target(pkt, (unsigned)n);
    free(pkt);
    return ret < 0 ? 0 : ret;
}
