/*
 * cve_barebone direct-call harness for CVE-2021-32399 (Linux kernel, Bluetooth HCI)
 * target: hci_req_sync  (net/bluetooth/hci_request.c)  CWE-416 heap use-after-free
 *
 * The real bug: pre-fix hci_req_sync() tests the HCI_UP bit in hdev->flags
 * *before* taking hdev->req_lock (the very lock that the device-teardown path
 * also serializes on). That leaves an unsynchronized window: a concurrent
 * hci_unregister_dev()/hci_dev_do_close() teardown can free the hci_dev while
 * another thread's hci_req_sync() has already begun its own (lock-less)
 * HCI_UP check on that same object. Upstream reports for this class are
 * literally "use-after-free Read in hci_req_sync" at the
 * test_bit(HCI_UP, &hdev->flags) line. The fix
 * (e2cb6b891ad2b8caa9131e3be70f45243df82a80) simply moves that check to run
 * *after* hci_req_sync_lock(hdev), closing the race window.
 *
 * We cannot spin up real racing kernel threads in a self-contained harness,
 * so we reproduce the identical fault deterministically, single-threaded:
 * free() the hci_dev exactly as the racing teardown path would, then invoke
 * hci_req_sync() on it exactly as the (formerly racing) caller would. Its
 * very first memory access - test_bit(HCI_UP, &hdev->flags) - then reads
 * freed heap memory: the same read, same source line, same fault class the
 * real concurrent bug produces, without needing actual threads.
 *
 * Type vocabulary (struct hci_dev's `flags`/`req_lock` members, the "HCI
 * device flags" enum, hci_req_sync_lock()/hci_req_sync_unlock(), test_bit())
 * is copied verbatim/real-named from include/net/bluetooth/{hci.h,hci_core.h},
 * net/bluetooth/hci_request.h and include/asm-generic/bitops/non-atomic.h.
 * __hci_req_sync() (the real request-queue engine - unrelated machinery) and
 * the two locking primitives are minimal faithful stubs: in the TRIGGER case
 * the fault fires in hci_req_sync's own body before either is ever reached;
 * in the SAFE case they only need to be harmless no-ops so the rest of the
 * (verbatim) function body executes cleanly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* ---- include/asm-generic/int-ll64.h (verbatim typedef chain) ---- */
typedef unsigned char u8;
typedef unsigned int  u32;

/* ---- include/asm-generic/bitsperlong.h (verbatim, 64-bit target) ---- */
#define BITS_PER_LONG 64

/* ---- include/linux/bits.h (verbatim) ---- */
#define BIT_WORD(nr)  ((nr) / BITS_PER_LONG)

/* ---- include/asm-generic/bitops/non-atomic.h (verbatim) ---- */
static inline int test_bit(int nr, const volatile unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG - 1)));
}

/* ---- include/net/bluetooth/hci.h "HCI device flags" (verbatim, HCI_UP == 0) ---- */
enum {
	HCI_UP,
	HCI_INIT,
	HCI_RUNNING,

	HCI_PSCAN,
	HCI_ISCAN,
	HCI_AUTH,
	HCI_ENCRYPT,
	HCI_INQUIRY,

	HCI_RAW,

	HCI_RESET,
};

/* opaque: net/bluetooth/hci_request.h - struct hci_request is used only as a
 * function-pointer parameter type in hci_req_sync's own signature below and
 * is never dereferenced by its body, so no definition is needed. */
struct hci_request;

/* incidental: struct mutex's real internals are irrelevant here - locking is
 * stubbed to a no-op below (single-threaded harness, no real contention to
 * protect against; the vulnerability is the missing lock *ordering*, which
 * we reproduce structurally, not the mutex implementation itself). */
struct mutex {
	unsigned long __opaque[4];
};

/*
 * Minimal slice of the real struct hci_dev (include/net/bluetooth/hci_core.h)
 * carrying exactly the two members hci_req_sync()'s own body (after macro
 * expansion of hci_req_sync_lock/unlock just below) dereferences: `flags`
 * (the HCI_UP test) and `req_lock` (the serializing mutex). Real field
 * names/types preserved; the ~180 unrelated fields of the real struct are
 * omitted as not needed to reach or observe this fault.
 */
struct hci_dev {
	unsigned long flags;
	struct mutex  req_lock;
};

/* ---- net/bluetooth/hci_request.h (verbatim macros) ---- */
#define hci_req_sync_lock(hdev)   mutex_lock(&hdev->req_lock)
#define hci_req_sync_unlock(hdev) mutex_unlock(&hdev->req_lock)

/* incidental stubs: real kernel mutex_lock/unlock semantics are not needed
 * to reach or observe the fault (which fires before either runs, in the
 * TRIGGER case); harmless no-ops let the SAFE case execute the full body. */
static inline void mutex_lock(struct mutex *m)   { (void) m; }
static inline void mutex_unlock(struct mutex *m) { (void) m; }

/* incidental stub for the real (large, unrelated) request-queue engine in
 * net/bluetooth/hci_request.c; only its signature is load-bearing here -
 * the crash never reaches it (TRIGGER) or it just needs to return cleanly
 * (SAFE). */
int
__hci_req_sync(struct hci_dev *hdev,
	       int (*func)(struct hci_request *req, unsigned long opt),
	       unsigned long opt, u32 timeout, u8 *hci_status)
{
	(void) hdev; (void) func; (void) opt; (void) timeout;
	if (hci_status != NULL) {
		*hci_status = 0;
	}
	return 0;
}

/* ===================================================================== */
/* ==== TARGET FUNCTION: hci_req_sync (VERBATIM, net/bluetooth/hci_request.c) ==== */
/* ===================================================================== */
int hci_req_sync(struct hci_dev *hdev, int (*req)(struct hci_request *req,
						  unsigned long opt),
		 unsigned long opt, u32 timeout, u8 *hci_status)
{
	int ret;

	if (!test_bit(HCI_UP, &hdev->flags))
		return -ENETDOWN;

	/* Serialize all requests */
	hci_req_sync_lock(hdev);
	ret = __hci_req_sync(hdev, req, opt, timeout, hci_status);
	hci_req_sync_unlock(hdev);

	return ret;
}
/* ===================================================================== */
/* ==== END TARGET FUNCTION ==== */
/* ===================================================================== */

static int
dummy_req_cb(struct hci_request *req, unsigned long opt)
{
	(void) req; (void) opt;
	return 0;
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		return 0;
	}

	FILE *f = fopen(argv[1], "rb");
	if (f == NULL) {
		return 0;
	}

	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 0) {
		sz = 0;
	}

	/* HEAP-allocated, ASAN-guarded attacker-controlled input buffer */
	unsigned char *buf = (unsigned char *) malloc(sz ? (size_t) sz : 1);
	size_t n = fread(buf, 1, (size_t) sz, f);
	fclose(f);

	/* FDP-style byte consumption */
	unsigned char mode    = (n > 0) ? buf[0] : 0;   /* bit0: trigger vs safe  */
	unsigned char up_bit  = (n > 1) ? buf[1] : 0;   /* bit0: HCI_UP set?      */
	unsigned char b2      = (n > 2) ? buf[2] : 0;
	unsigned char b3      = (n > 3) ? buf[3] : 0;
	unsigned char b4      = (n > 4) ? buf[4] : 0;
	unsigned char b5      = (n > 5) ? buf[5] : 0;
	unsigned char want_st = (n > 6) ? buf[6] : 0;   /* bit0: pass hci_status? */
	free(buf);

	unsigned long opt     = ((unsigned long) b2 << 8) | b3;
	u32           timeout = ((u32) b4 << 8) | b5;

	/* indirect call through a volatile pointer keeps hci_req_sync a real,
	 * non-inlined frame so it appears by name in the ASAN crash stack. */
	int (*volatile call_hci_req_sync)(struct hci_dev *,
					   int (*)(struct hci_request *, unsigned long),
					   unsigned long, u32, u8 *) = hci_req_sync;

	u8 status = 0;
	u8 *status_arg = (want_st & 1) ? &status : NULL;

	if (mode & 1) {
		/*
		 * TRIGGER (CVE-2021-32399): simulate the racing teardown that
		 * the missing lock-before-check let through - free hdev, then
		 * let hci_req_sync() run its unsynchronized HCI_UP check on
		 * it, exactly like the (formerly racing) real-world caller.
		 */
		struct hci_dev *hdev = (struct hci_dev *) malloc(sizeof(struct hci_dev));
		if (hdev == NULL) {
			return 0;
		}
		hdev->flags = (up_bit & 1) ? 1UL : 0UL;
		free(hdev);                                   /* the racing teardown */

		call_hci_req_sync(hdev, dummy_req_cb, opt, timeout, status_arg);
		/* unreachable: ASAN aborts on the heap-use-after-free read above */
		return 0;
	}

	/*
	 * SAFE: a live, correctly sized hci_dev. Exercises both the early
	 * -ENETDOWN return (HCI_UP clear) and the full lock/sync/unlock path
	 * (HCI_UP set), never touching freed or undersized memory.
	 */
	struct hci_dev *hdev = (struct hci_dev *) malloc(sizeof(struct hci_dev));
	if (hdev == NULL) {
		return 0;
	}
	hdev->flags = (up_bit & 1) ? 1UL : 0UL;
	memset(&hdev->req_lock, 0, sizeof(hdev->req_lock));

	int ret = call_hci_req_sync(hdev, dummy_req_cb, opt, timeout, status_arg);
	fprintf(stderr, "ret=%d mode=%u up=%u\n", ret, (unsigned) mode, (unsigned) up_bit);

	free(hdev);
	return 0;
}
