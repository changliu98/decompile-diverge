/* cve_barebone harness -- qemu hw/core/loader.c rom_copy() missing lower-bound check
 * (CVE fix commit 4f1c6cb2f9afafda05eab150fd2bd284edce6676), CWE-787 heap-buffer-overflow WRITE.
 *
 * Fix diff:
 *     -        if (rom->addr > end) {
 *     +        if (rom->addr > end || rom->addr < addr) {
 *                  break;
 *              }
 *
 * rom_copy() walks the global `roms` list looking for registered ROMs that overlap the
 * requested [addr, addr+size) window and memcpy()s their bytes into `dest`. The pre-fix
 * "break" guard only stops the walk once a ROM starts AFTER the window (rom->addr > end); it
 * never checks whether a ROM starts BEFORE the window (rom->addr < addr) while still
 * overlapping it (rom->addr + rom->romsize >= addr, so the earlier "entirely before" `continue`
 * doesn't skip it either). For such a ROM:
 *     d = dest + (rom->addr - addr);
 * `rom->addr - addr` is computed in `hwaddr` (uint64_t, unsigned) and UNDERFLOWS when
 * rom->addr < addr, wrapping to a huge value that -- added back to the `uint8_t *dest`
 * pointer -- lands `d` exactly (addr - rom->addr) bytes BEFORE `dest`. The very next lines
 * (`l = rom->datasize; ... memcpy(d, s, l);`) then write ROM data starting at that
 * before-the-buffer pointer: a heap-buffer-overflow WRITE, entirely inside rom_copy's own
 * body, from a ROM list state the caller doesn't control (registered ROMs / firmware images
 * can legitimately start before an on-demand copy window, e.g. the multiboot/mips_malta
 * kernel-load callers below).
 *
 * Real callers (both pass size == the dest allocation's own capacity):
 *   hw/i386/multiboot.c:214   rom_copy(mbs.mb_buf, mh_load_addr, mb_kernel_size)
 *   hw/mips/mips_malta.c:1358 rom_copy(memory_region_get_ram_ptr(bios_copy), ...)
 *
 * Isolated reproduction: rom_copy() is called directly on a hand-built one-entry `roms` list
 * (real struct Rom, real QTAILQ macros) -- no rom_add_file()/rom_add_blob() parsing involved,
 * just the post-registration list state the bug actually reads.
 *
 * TRIGGER: rom->addr = addr - k  (k in [1, rom->datasize]) -- overlapping-but-starts-before,
 *          the exact pre-fix-reachable state; upstream's fix breaks the loop before ever
 *          computing `d` for such a ROM.
 * SAFE:    rom->addr >= addr (in-range / exact match), OR rom->fw_file / rom->mr set
 *          (skipped via the earlier `continue`s), OR rom->addr entirely beyond the window
 *          (`break` before touching d/l) or entirely before with a gap (`continue`, the
 *          ALREADY-correct pre-fix skip) -- every safe path exits rom_copy without writing
 *          outside [dest, dest+size).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ---- hwaddr (include/exec/hwaddr.h, verbatim typedef) ---- */
typedef uint64_t hwaddr;

/* ---- QTAILQ tail-queue macros (include/qemu/queue.h, verbatim) -- rom_copy walks `roms`
 * with QTAILQ_FOREACH; the harness links its one Rom node in with the same tqh_first/
 * tqe_next fields the macro expands to, so no other QTAILQ_* macro is needed. ---- */
typedef struct QTailQLink {
    void *tql_next;
    struct QTailQLink *tql_prev;
} QTailQLink;

#define QTAILQ_HEAD(name, type)                                         \
union name {                                                            \
        struct type *tqh_first;       /* first element */               \
        QTailQLink tqh_circ;          /* link for circular backwards list */ \
}

#define QTAILQ_HEAD_INITIALIZER(head)                                   \
        { .tqh_circ = { NULL, &(head).tqh_circ } }

#define QTAILQ_ENTRY(type)                                              \
union {                                                                 \
        struct type *tqe_next;        /* next element */                \
        QTailQLink tqe_circ;          /* link for circular backwards list */ \
}

#define QTAILQ_FOREACH(var, head, field)                                \
        for ((var) = ((head)->tqh_first);                               \
                (var);                                                  \
                (var) = ((var)->field.tqe_next))

/* ---- MemoryRegion / AddressSpace (real names, include/exec/memory.h &
 * include/exec/address-spaces.h): rom_copy only tests rom->mr for non-NULL and never reads
 * rom->as at all, so both stay opaque (incomplete) -- real declarations, no invented fields. */
typedef struct MemoryRegion MemoryRegion;
typedef struct AddressSpace AddressSpace;

/* ---- struct Rom (hw/core/loader.c, real field names/order/types) ---- */
typedef struct Rom Rom;

struct Rom {
    char *name;
    char *path;

    size_t romsize;
    size_t datasize;

    uint8_t *data;
    MemoryRegion *mr;
    AddressSpace *as;
    int isrom;
    char *fw_dir;
    char *fw_file;

    bool committed;

    hwaddr addr;
    QTAILQ_ENTRY(Rom) next;
};

/* ---- the real global rom_copy reads (hw/core/loader.c, verbatim declaration) ---- */
static QTAILQ_HEAD(, Rom) roms = QTAILQ_HEAD_INITIALIZER(roms);

/* ================= TARGET (VERBATIM, byte-for-byte data_cve/cve_284f318f/target/original_function.c) =================
 * noinline: rom_copy has exactly one call site in this TU (main, through a volatile function
 * pointer below) and is an easy -O1 inline target; noinline is a pure codegen hint so ASAN's
 * backtrace keeps a distinct "rom_copy" frame -- it touches nothing in the pasted bytes below. */
__attribute__((noinline))
int rom_copy(uint8_t *dest, hwaddr addr, size_t size)
{
    hwaddr end = addr + size;
    uint8_t *s, *d = dest;
    size_t l = 0;
    Rom *rom;

    QTAILQ_FOREACH(rom, &roms, next) {
        if (rom->fw_file) {
            continue;
        }
        if (rom->mr) {
            continue;
        }
        if (rom->addr + rom->romsize < addr) {
            continue;
        }
        if (rom->addr > end) {
            break;
        }

        d = dest + (rom->addr - addr);
        s = rom->data;
        l = rom->datasize;

        if ((d + l) > (dest + size)) {
            l = dest - d;
        }

        if (l > 0) {
            memcpy(d, s, l);
        }

        if (rom->romsize > rom->datasize) {
            /* If datasize is less than romsize, it means that we didn't
             * allocate all the ROM because the trailing data are only zeros.
             */

            d += l;
            l = rom->romsize - rom->datasize;

            if ((d + l) > (dest + size)) {
                /* Rom size doesn't fit in the destination area. Adjust to avoid
                 * overflow.
                 */
                l = dest - d;
            }

            if (l > 0) {
                memset(d, 0x0, l);
            }
        }
    }

    return (d + l) - dest;
}

/* ==== end verbatim target function ==== */

static unsigned char vb_byte_at(const unsigned char *b, size_t n, size_t i)
{
    return (i < n) ? b[i] : 0;
}

/* ---- driver ---------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded), then derives every rom_copy
 * argument AND the one hand-built Rom list entry from those bytes:
 *   byte0  mode:    bit0 -> trigger(1)/safe(0); bits1-2 -> safe sub-scenario (0..3);
 *                   bit3 -> "beyond window" vs "before-with-gap" for sub-scenario 3
 *   byte1  sz_byte  -> dest_size  = 16 + sz_byte%241            in [16,256]
 *   byte2  addr_byte-> addr       = 0x1000 + addr_byte%64       (requested window base)
 *   byte3  k_byte    -> trigger offset  k  = 1 + k_byte%dsize   in [1,dsize]  (see below)
 *                       safe in-range offset kk = k_byte%5      in [0,4]
 *   byte4  l_byte    -> dsize (rom->datasize == rom->romsize)   = 1 + l_byte%12  in [1,12]
 *   byte5..           -> rom->data payload bytes (content is incidental; only addr/datasize
 *                        drive the bug), zero-padded if the file is short.
 * A short/empty file zero-extends every field -> mode=0 -> a trivial in-range SAFE call.
 */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 2; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 2; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 2; }

    size_t n = (size_t)fsz;
    unsigned char *ibuf = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
    if (!ibuf) { fclose(fp); return 2; }
    size_t got = n ? fread(ibuf, 1, n, fp) : 0;
    fclose(fp);

    unsigned char mode      = vb_byte_at(ibuf, got, 0);
    unsigned char sz_byte   = vb_byte_at(ibuf, got, 1);
    unsigned char addr_byte = vb_byte_at(ibuf, got, 2);
    unsigned char k_byte    = vb_byte_at(ibuf, got, 3);
    unsigned char l_byte    = vb_byte_at(ibuf, got, 4);

    int trigger   = mode & 1;
    int safe_kind = (mode >> 1) & 3;
    int gap_kind  = (mode >> 3) & 1;

    size_t dest_size = 16 + (size_t)(sz_byte % 241);           /* [16,256] */
    hwaddr addr       = 0x1000 + (hwaddr)(addr_byte % 64);      /* requested window base */
    size_t dsize       = 1 + (size_t)(l_byte % 12);              /* [1,12] */

    /* Destination buffer: rom_copy's real callers always pass size == the dest allocation's
     * own capacity (see the two call sites cited above) -- same invariant here. */
    uint8_t *dest = (uint8_t *)malloc(dest_size);
    if (!dest) { free(ibuf); return 2; }
    memset(dest, 0xAA, dest_size);

    /* rom->data: a second, independent heap allocation (the registered ROM's own backing
     * store); content is incidental to the bug (only rom->addr/datasize matter), filled from
     * whatever input bytes remain for realism. */
    uint8_t *romdata = (uint8_t *)malloc(dsize);
    if (!romdata) { free(dest); free(ibuf); return 2; }
    for (size_t i = 0; i < dsize; i++) {
        romdata[i] = vb_byte_at(ibuf, got, 5 + i);
    }

    Rom node;
    memset(&node, 0, sizeof(node));
    node.romsize  = dsize;      /* == datasize: keeps the (romsize>datasize) zero-fill branch
                                  * inert, isolating every trigger/safe case to the ONE line
                                  * (`d = dest + (rom->addr - addr)`) the fix's added check
                                  * guards. */
    node.datasize = dsize;
    node.data     = romdata;
    node.isrom    = 1;

    if (trigger) {
        /* <-- the exact pre-fix-reachable state: a ROM that starts BEFORE the requested
         * window (rom->addr < addr) but still overlaps it. k is capped to [1,dsize] so
         * rom->addr + rom->romsize (== rom->addr + dsize) is always >= addr -- i.e. this ROM
         * is NEVER caught by the earlier "entirely before" `continue`, so control always
         * reaches the vulnerable line. */
        hwaddr k = 1 + (hwaddr)(k_byte % dsize);       /* [1,dsize] */
        node.addr = addr - k;
    } else {
        switch (safe_kind) {
        case 0: {   /* in-range: rom->addr in [addr, addr+4], comfortably inside the window
                     * and far from dest_size's tail -- the `(d+l) > (dest+size)` clip is
                     * never taken (kk+dsize <= 4+12 = 16 <= dest_size, the minimum), so this
                     * exercises the SAME memcpy() as the trigger case, just in-bounds. */
            hwaddr kk = (hwaddr)(k_byte % 5);           /* [0,4] */
            node.addr = addr + kk;
            break;
        }
        case 1:     /* rom->fw_file set -> the first `continue`, never reaches rom->addr at all */
            node.addr    = addr;
            node.fw_file = "firmware.bin";              /* any non-NULL string, real field */
            break;
        case 2:     /* rom->mr set -> the second `continue` (mr is only tested, never derefed) */
            node.addr = addr;
            node.mr   = (MemoryRegion *)(void *)(uintptr_t)1;
            break;
        default:    /* safe_kind == 3 */
            if (gap_kind) {
                /* rom->addr > end -> `break`, before `d`/`l` are ever touched */
                node.addr = addr + (hwaddr)dest_size + 0x100;
            } else {
                /* rom->addr + rom->romsize < addr -> `continue` -- the ALREADY-correct
                 * pre-fix skip for a ROM that is entirely before the window WITH A GAP
                 * (unlike the trigger case, which overlaps); addr is always >= 0x1000, far
                 * bigger than romsize+0x100 (<=268), so this never underflows. */
                node.addr = addr - (hwaddr)(node.romsize + 0x100);
            }
            break;
        }
    }

    /* Link the single node into `roms` the way QTAILQ_FOREACH walks it (tqh_first / the
     * entry's own tqe_next) -- the real registration path is rom_add_file()/rom_add_blob()'s
     * QTAILQ_INSERT_TAIL(&roms, rom, next); building the post-registration list state
     * directly (rather than replaying that unrelated allocation/bookkeeping code) is the
     * isolation this harness is for. */
    roms.tqh_first     = &node;
    node.next.tqe_next = NULL;

    /* volatile function pointer: forbid the compiler from inlining rom_copy (its one call
     * site here is an easy -O1 inline target despite __attribute__((noinline)), a codegen
     * hint, not a hard guarantee) and dropping its frame from the ASAN backtrace. */
    int (* volatile fn)(uint8_t *, hwaddr, size_t) = rom_copy;
    int rc = fn(dest, addr, dest_size);
    (void)rc;

    /* Only reached on a SAFE run (a triggering run aborts inside rom_copy, above). */
    free(romdata);
    free(dest);
    free(ibuf);
    return 0;
}
