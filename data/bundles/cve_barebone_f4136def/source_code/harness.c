/* cve_barebone direct-call harness for cve_f4136def (illumos-gate)
 * Target: smb_com_flush  (usr/src/uts/common/fs/smbsrv/smb_flush.c)
 * Bug class: CWE-476 NULL pointer dereference.
 *
 * smb_com_flush's SMB_COM_FLUSH handler looks up the caller-supplied fid and, if not the
 * "flush everything" sentinel (0xffff), calls smb_flush_file() on whatever ofile that fid names
 * -- with NO check of the ofile's f_ftype. smb_flush_file() then unconditionally dereferences
 * ofile->f_node->flags. Per smb_ktypes.h's own File-Type/Node/PipeInfo invariant table, an ofile
 * opened as SMB_FTYPE_MESG_PIPE (a named pipe, e.g. an NDR RPC endpoint) has f_node == NULL (it
 * uses f_pipe instead) -- so flushing a pipe fid dereferences NULL. Fix 6d1c73b5 replaces the
 * call with smb_ofile_flush(), which switches on of->f_ftype and only ever touches f_node for
 * SMB_FTYPE_DISK.
 *
 * TRIGGER: fid_ofile->f_ftype == SMB_FTYPE_MESG_PIPE, f_node == NULL (the real invariant for
 *          that ftype) -> smb_flush_file's `if (ofile->f_node->flags & ...)` reads through NULL.
 * SAFE:    fid_ofile->f_ftype == SMB_FTYPE_DISK, f_node a real, valid, heap smb_node_t -> the
 *          flush proceeds cleanly (smb_fsop_commit is an off-path no-op stand-in either way).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- cred_t: real typedef (usr/src/uts/common/sys/cred.h: "typedef struct cred cred_t;").
 * Opaque here -- f_cr/user_cr are stored and passed around but never dereferenced on this
 * path. ---- */
typedef struct cred cred_t;

/* ---- kmutex_t: real name (kernel sys/mutex.h). f_mutex is touched only by smb_com_flush's
 * OTHER branch (the flush-ALL-open-files loop over t_ofile_list), which this harness never
 * drives (every input takes the single-fid branch) -- a no-op stand-in is faithful. ---- */
typedef struct kmutex { int _unused; } kmutex_t;
static void mutex_enter(kmutex_t *m) { (void)m; }
static void mutex_exit(kmutex_t *m) { (void)m; }

/* ---- smb_llist_t / krw_t / smb_llist_* (smb_ktypes.h; RW_READER from sys/rwlock.h; the real
 * smb_llist_enter/head/next are macros expanding to rw_enter()/list_head()/list_next() over a
 * real doubly-linked-list-plus-rwlock -- irrelevant machinery for a harness that never actually
 * iterates a file list). Same off-path reasoning as f_mutex above -- no-op stand-ins. ---- */
typedef struct smb_llist { int _unused; } smb_llist_t;
typedef enum { RW_READER, RW_WRITER } krw_t;
static void smb_llist_enter(smb_llist_t *ll, krw_t mode) { (void)ll; (void)mode; }
static void smb_llist_exit(smb_llist_t *ll) { (void)ll; }
static void *smb_llist_head(smb_llist_t *ll) { (void)ll; return NULL; }
static void *smb_llist_next(smb_llist_t *ll, void *obj) { (void)ll; (void)obj; return NULL; }

/* ---- smb_node_t (smb_ktypes.h struct smb_node) trimmed to the ONE real field the bug reads
 * ("volatile int flags;", verbatim name+type) -- the struct's ~20 other fields (locks, hash
 * bucket linkage, oplock state, vnode pointer, ...) are never touched by smb_flush_file. ---- */
typedef struct smb_node {
	volatile int flags;
} smb_node_t;
#define NODE_FLAGS_WRITE_THROUGH	0x00100000	/* real value, smb_ktypes.h:661 */

/* ---- smb_ofile_t (smb_ktypes.h struct smb_ofile) trimmed to the real fields this call chain
 * touches: f_mutex (else-branch only), f_node (THE crash field), f_cr, f_ftype. ---- */
typedef struct smb_ofile {
	kmutex_t	f_mutex;
	smb_node_t	*f_node;
	cred_t		*f_cr;
	uint16_t	f_ftype;
} smb_ofile_t;

/* real SMB_FTYPE_* values (usr/src/uts/common/smbsrv/smb.h:647-648) */
#define SMB_FTYPE_DISK		0
#define SMB_FTYPE_MESG_PIPE	2

/* ---- smb_tree_t (smb_ktypes.h struct smb_tree) trimmed to the one field the else-branch
 * reads (t_ofile_list); never dereferenced on the path this harness drives. ---- */
typedef struct smb_tree {
	smb_llist_t	t_ofile_list;
} smb_tree_t;

/* ---- smb_request_t (smb_ktypes.h struct smb_request) trimmed to the 4 real fields
 * smb_com_flush/smb_flush_file actually touch, out of the real struct's ~80 fields (SMB1/SMB2
 * wire-protocol header state, mbuf reply/request chains, timestamps, ... all irrelevant
 * here). ---- */
typedef struct smb_request {
	uint16_t	smb_fid;
	struct smb_tree		*tid_tree;
	struct smb_ofile	*fid_ofile;
	cred_t		*user_cr;
} smb_request_t;

/* ---- smb_sdrc_t: real enum, verbatim (smb_ktypes.h:1833-1841). ---- */
typedef enum {
	SDRC_SUCCESS = 0,
	SDRC_ERROR,
	SDRC_DROP_VC,
	SDRC_NO_REPLY,
	SDRC_SR_KEPT,
	SDRC_NOT_IMPLEMENTED
} smb_sdrc_t;

/* real global, verbatim initializer (smb_init.c:69 / fksmb_init.c:59): int smb_flush_required = 1; */
int smb_flush_required = 1;

/* NT_STATUS_INVALID_HANDLE / ERRDOS / ERRbadfid: real values (ntstatus.h:235, doserror.h:43,57).
 * Referenced only by the "bad fid" branch of smb_com_flush's own body below -- this harness
 * always supplies a valid fid_ofile so that branch never executes, but the target's own bytes
 * name these symbols and must resolve for the file to compile. */
#define NT_STATUS_INVALID_HANDLE	0xC0000008
#define ERRDOS		0x01
#define ERRbadfid	6
typedef uint32_t DWORD;	/* real typedef, smbsrv/wintypes.h:44 */

/* smbsr_status / smbsr_error: real prototype + macro (smb_kproto.h:394-397 --
 * "#define smbsr_error(SR, ST, CL, CO) smbsr_status(SR, ST, CL, CO)"). Dead on this harness's
 * path (see above) -- faithful no-op stand-in. */
static void smbsr_status(smb_request_t *sr, DWORD st, uint16_t cl, uint16_t co)
{
	(void)sr; (void)st; (void)cl; (void)co;
}
#define smbsr_error(SR, ST, CL, CO)	smbsr_status(SR, ST, CL, CO)

/* smbsr_encode_empty_result: real prototype (smb_kproto.h). Its real body
 * (smb_dispatch.c:887-890) encodes an empty SMB reply into sr->reply, an mbuf chain --
 * entirely orthogonal to the f_node NULL-deref bug (only reached AFTER the flush already
 * ran to completion on a SAFE input; a TRIGGERING input crashes inside smb_flush_file before
 * ever getting here). Minimal faithful stand-in: always-succeeds. */
static int smbsr_encode_empty_result(smb_request_t *sr)
{
	(void)sr;
	return (0);
}

/* smb_ofile_lookup_by_fid: real prototype (smb_kproto.h). Never actually invoked -- this
 * harness always pre-populates sr->fid_ofile, and smbsr_lookup_file's real body (below,
 * verbatim) only calls this when fid_ofile is still NULL. */
static smb_ofile_t *smb_ofile_lookup_by_fid(smb_request_t *sr, uint16_t fid)
{
	(void)sr; (void)fid;
	return (NULL);
}

/* smbsr_lookup_file: REAL body, verbatim (smb_dispatch.c:1153-1158). */
static void
smbsr_lookup_file(smb_request_t *sr)
{
	if (sr->fid_ofile == NULL)
		sr->fid_ofile = smb_ofile_lookup_by_fid(sr, sr->smb_fid);
}

/* smb_ofile_getcred: REAL body, verbatim (smb_ofile.c:1169-1173). */
static cred_t *
smb_ofile_getcred(smb_ofile_t *of)
{
	return (of->f_cr);
}

/* smb_fsop_commit: real prototype (smb_kproto.h). Its real body (smb_fsops.c:2001-2013) is a
 * VFS-level file commit (ASSERTs on sr/tid_tree/snode + smb_vop_commit) entirely orthogonal to
 * the bug -- by the time it could run, f_node is already known non-NULL and the crash (if any)
 * already happened evaluating the `if` in smb_flush_file just above this call. Minimal
 * faithful stand-in: always-succeeds. */
static int
smb_fsop_commit(smb_request_t *sr, cred_t *cr, smb_node_t *snode)
{
	(void)sr; (void)cr; (void)snode;
	return (0);
}

/* ================= smb_flush_file: REAL body, verbatim (smb_flush.c:117-124) =================
 * The file's OTHER static function -- smb_com_flush's own body calls it directly, twice. THIS
 * is where the actual bug fires: it dereferences ofile->f_node->flags with no f_ftype guard.
 * noinline is a pure codegen hint (behavior byte-identical) so this real call boundary can't be
 * inlined away and vanish from the ASAN backtrace -- it does not touch the function's own
 * bytes. */
__attribute__((noinline))
static void
smb_flush_file(struct smb_request *sr, struct smb_ofile *ofile)
{
	sr->user_cr = smb_ofile_getcred(ofile);

	if ((ofile->f_node->flags & NODE_FLAGS_WRITE_THROUGH) == 0)
		(void) smb_fsop_commit(sr, sr->user_cr, ofile->f_node);
}

/* ================= TARGET (byte-for-byte, data_cve/cve_f4136def/target/original_function.c)
 * ================= noinline so it can't be folded into main() and vanish from the backtrace;
 * called through a volatile function pointer in main() for the same reason. */
__attribute__((noinline))
smb_sdrc_t
smb_com_flush(smb_request_t *sr)
{
	smb_ofile_t	*file;
	smb_llist_t	*flist;
	int		rc;

	if (smb_flush_required == 0) {
		rc = smbsr_encode_empty_result(sr);
		return ((rc == 0) ? SDRC_SUCCESS : SDRC_ERROR);
	}

	if (sr->smb_fid != 0xffff) {
		smbsr_lookup_file(sr);
		if (sr->fid_ofile == NULL) {
			smbsr_error(sr, NT_STATUS_INVALID_HANDLE,
			    ERRDOS, ERRbadfid);
			return (SDRC_ERROR);
		}

		smb_flush_file(sr, sr->fid_ofile);
	} else {
		flist = &sr->tid_tree->t_ofile_list;
		smb_llist_enter(flist, RW_READER);
		file = smb_llist_head(flist);
		while (file) {
			mutex_enter(&file->f_mutex);
			smb_flush_file(sr, file);
			mutex_exit(&file->f_mutex);
			file = smb_llist_next(flist, file);
		}
		smb_llist_exit(flist);
	}

	rc = smbsr_encode_empty_result(sr);
	return ((rc == 0) ? SDRC_SUCCESS : SDRC_ERROR);
}

/* ================= driver =================
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded). Byte 0 selects TRIGGER (even) vs
 * SAFE (odd): a real SMB client picks which ftype of fid it flushes simply by choosing which
 * kind of object it opened before sending SMB_COM_FLUSH -- a named pipe (SMB_FTYPE_MESG_PIPE,
 * f_node NULL by the real illumos invariant) crashes; a disk file (SMB_FTYPE_DISK, f_node a
 * real valid node) does not. Remaining bytes seed the SAFE node's ->flags word, exercising both
 * arms of smb_flush_file's WRITE_THROUGH check (smb_fsop_commit is a no-op stand-in either
 * way, so both arms are safe).
 */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 2; }
	fseek(fp, 0, SEEK_END);
	long ln = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (ln < 0) ln = 0;
	size_t n = (size_t)ln;

	unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
	if (!data) { fclose(fp); return 2; }
	size_t got = fread(data, 1, n, fp);
	fclose(fp);

	unsigned char mode = (got > 0) ? data[0] : 0;
	int trigger = ((mode & 1) == 0);   /* even mode byte -> TRIGGER */

	smb_ofile_t *ofile = (smb_ofile_t *)malloc(sizeof(smb_ofile_t));
	memset(ofile, 0, sizeof(*ofile));
	ofile->f_cr = NULL;
	smb_node_t *node = NULL;

	if (trigger)
	{
		/* SMB_FTYPE_MESG_PIPE ofile: real illumos invariant (smb_ktypes.h's own
		 * File-Type/Node/PipeInfo table) is f_node == NULL for this ftype. */
		ofile->f_ftype = SMB_FTYPE_MESG_PIPE;
		ofile->f_node = NULL;
	}
	else
	{
		/* SMB_FTYPE_DISK ofile: f_node is a real, valid, heap-allocated node. */
		ofile->f_ftype = SMB_FTYPE_DISK;
		node = (smb_node_t *)malloc(sizeof(smb_node_t));
		int flagseed = 0;
		size_t i;
		for (i = 1; i < got && i < 5; i++)
			flagseed = (flagseed << 8) | data[i];
		node->flags = flagseed;
		ofile->f_node = node;
	}

	smb_request_t sr;
	memset(&sr, 0, sizeof(sr));
	sr.smb_fid = 7;            /* != 0xffff -> the single-fid branch (SMB_COM_FLUSH on one fid) */
	sr.tid_tree = NULL;        /* never dereferenced on this branch */
	sr.fid_ofile = ofile;      /* pre-populated -> smbsr_lookup_file's real body is a no-op */
	sr.user_cr = NULL;

	/* volatile function pointer: forbid the compiler from proving the call away / folding
	 * smb_com_flush into main's own frame despite __attribute__((noinline)). */
	smb_sdrc_t (* volatile fn)(smb_request_t *) = smb_com_flush;
	smb_sdrc_t rc = fn(&sr);
	(void)rc;

	/* Only reached on a SAFE run (a triggering run aborts inside smb_flush_file above). */
	free(data);
	if (node) free(node);
	free(ofile);
	return 0;
}
