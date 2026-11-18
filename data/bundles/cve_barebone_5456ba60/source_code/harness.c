/*
 * Direct-call crash harness for CVE-2018-14681 (libmspack, kwajd.c).
 *
 * Target: kwajd_read_headers()  -- embedded VERBATIM below, byte-for-byte
 * identical to dataset/cve_5456ba60/target/original_function.c.
 *
 * Bug class: CWE-787 (heap-buffer-overflow, WRITE). kwajd_read_headers()
 * allocates a 13-byte buffer for "filename.ext\0" (sys->alloc(sys,13)) but
 * the copy loops for the 9-byte filename field and the 4-byte extension
 * field can each run to their full, un-terminated length: 9 (filename) +
 * 1 ('.') + 4 (extension) = 14 bytes minimum, one past the 13-byte
 * allocation -- and the final NUL terminator can go one byte further
 * still. Real-world trace (this exact PoC family): filename bytes are all
 * non-NUL for all 9 iterations (fn ends at offset 9, in-bounds), the '.'
 * lands at offset 9 (in-bounds), then the extension loop writes offsets
 * 10, 11, 12 (in-bounds, offset 12 is the last valid byte of the 13-byte
 * allocation) and then offset 13 on its 4th iteration -- OUT OF BOUNDS.
 * ASan traps exactly there (kwajd.c:221, `for (i = 0; i < 4; i++, fn++) if
 * (!(*fn = buf[i])) break;`), matching case.json's baseline dedup_token
 * ("kwajd_read_headers--kwajd_open--kwajd_decompress") and summary
 * ("AddressSanitizer: heap-buffer-overflow ... kwajd.c:221:46 in
 * kwajd_read_headers").
 *
 * All type/macro/struct definitions below are copied verbatim (names and
 * values) from the real libmspack headers under
 * dataset/cve_5456ba60/source_code/libmspack/mspack/{system.h,kwaj.h,mspack.h}
 * -- only the minimal subset kwajd_read_headers() actually touches. The
 * mspack_system this harness supplies is a from-scratch in-memory
 * implementation (read/seek/tell backed by a HEAP buffer holding the raw
 * input file bytes, alloc()/free() forwarding straight to malloc()/free()
 * so the vulnerable 13-byte allocation is a real, ASan-tracked heap
 * chunk) -- this is the same role the real mspack_default_system (or a
 * custom caller-supplied system) plays for the real kwajd_open() caller;
 * we just skip everything above kwajd_read_headers() itself (the
 * mskwaj_decompressor wrapper, kwajd_open()'s own file-opening, etc.)
 * since the harness calls the target function directly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>   /* off_t */

/* ============================================================
 * From mspack/system.h -- endian-neutral little-endian field reads.
 * ============================================================ */
#define __egi32(a,n) ( ((((unsigned char *) a)[n+3]) << 24) | \
		       ((((unsigned char *) a)[n+2]) << 16) | \
		       ((((unsigned char *) a)[n+1]) <<  8) | \
		       ((((unsigned char *) a)[n+0])))
#define EndGetI32(a) __egi32(a,0)
#define EndGetI16(a) ((((a)[1])<<8)|((a)[0]))

/* ============================================================
 * From mspack/kwaj.h -- generic KWAJ header field offsets.
 * ============================================================ */
#define kwajh_Signature1 (0x00)
#define kwajh_Signature2 (0x04)
#define kwajh_CompMethod (0x08)
#define kwajh_DataOffset (0x0a)
#define kwajh_Flags      (0x0c)
#define kwajh_SIZEOF     (0x0e)

/* ============================================================
 * From mspack/mspack.h -- file I/O abstraction + KWAJ header struct
 * + error/seek/flag constants used by kwajd_read_headers().
 * ============================================================ */

/* A structure which represents an open file handle. The contents of this
 * structure are determined by the implementation of the
 * mspack_system::open() method. (verbatim from mspack.h) */
struct mspack_file {
  int dummy;
};

struct mspack_system {
  struct mspack_file * (*open)(struct mspack_system *self,
			       const char *filename,
			       int mode);
  void (*close)(struct mspack_file *file);
  int (*read)(struct mspack_file *file,
	      void *buffer,
	      int bytes);
  int (*write)(struct mspack_file *file,
	       void *buffer,
	       int bytes);
  int (*seek)(struct mspack_file *file,
	      off_t offset,
	      int mode);
  off_t (*tell)(struct mspack_file *file);
  void (*message)(struct mspack_file *file,
		  const char *format,
		  ...);
  void * (*alloc)(struct mspack_system *self,
		  size_t bytes);
  void (*free)(void *ptr);
  void (*copy)(void *src,
	       void *dest,
	       size_t bytes);
  void *null_ptr;
};

/* mspack_system::seek() modes */
#define MSPACK_SYS_SEEK_START  (0)
#define MSPACK_SYS_SEEK_CUR    (1)
#define MSPACK_SYS_SEEK_END    (2)

/* error codes */
#define MSPACK_ERR_OK          (0)
#define MSPACK_ERR_ARGS        (1)
#define MSPACK_ERR_OPEN        (2)
#define MSPACK_ERR_READ        (3)
#define MSPACK_ERR_WRITE       (4)
#define MSPACK_ERR_SEEK        (5)
#define MSPACK_ERR_NOMEMORY    (6)
#define MSPACK_ERR_SIGNATURE   (7)
#define MSPACK_ERR_DATAFORMAT  (8)
#define MSPACK_ERR_CHECKSUM    (9)
#define MSPACK_ERR_CRUNCH      (10)
#define MSPACK_ERR_DECRUNCH    (11)

/* KWAJ optional-header flag bits */
#define MSKWAJ_HDR_HASLENGTH    (0x01)
#define MSKWAJ_HDR_HASUNKNOWN1  (0x02)
#define MSKWAJ_HDR_HASUNKNOWN2  (0x04)
#define MSKWAJ_HDR_HASFILENAME  (0x08)
#define MSKWAJ_HDR_HASFILEEXT   (0x10)
#define MSKWAJ_HDR_HASEXTRATEXT (0x20)

/* A structure which represents a KWAJ compressed file. (verbatim field
 * list/types from mspack.h; only what kwajd_read_headers() writes to) */
struct mskwajd_header {
  unsigned short comp_type;
  off_t data_offset;
  int headers;
  off_t length;
  char *filename;
  char *extra;
  unsigned short extra_length;
};

/* ============================================================
 * TARGET FUNCTION -- embedded VERBATIM from
 * dataset/cve_5456ba60/target/original_function.c. Do not edit the body.
 * ============================================================ */

static int kwajd_read_headers(struct mspack_system *sys,
			      struct mspack_file *fh,
			      struct mskwajd_header *hdr)
{
    unsigned char buf[16];
    int i;

    /* read in the header */
    if (sys->read(fh, &buf[0], kwajh_SIZEOF) != kwajh_SIZEOF) {
	return MSPACK_ERR_READ;
    }

    /* check for "KWAJ" signature */
    if (((unsigned int) EndGetI32(&buf[kwajh_Signature1]) != 0x4A41574B) ||
	((unsigned int) EndGetI32(&buf[kwajh_Signature2]) != 0xD127F088))
    {
	return MSPACK_ERR_SIGNATURE;
    }

    /* basic header fields */
    hdr->comp_type    = EndGetI16(&buf[kwajh_CompMethod]);
    hdr->data_offset  = EndGetI16(&buf[kwajh_DataOffset]);
    hdr->headers      = EndGetI16(&buf[kwajh_Flags]);
    hdr->length       = 0;
    hdr->filename     = NULL;
    hdr->extra        = NULL;
    hdr->extra_length = 0;

    /* optional headers */

    /* 4 bytes: length of unpacked file */
    if (hdr->headers & MSKWAJ_HDR_HASLENGTH) {
	if (sys->read(fh, &buf[0], 4) != 4) return MSPACK_ERR_READ;
	hdr->length = EndGetI32(&buf[0]);
    }

    /* 2 bytes: unknown purpose */
    if (hdr->headers & MSKWAJ_HDR_HASUNKNOWN1) {
	if (sys->read(fh, &buf[0], 2) != 2) return MSPACK_ERR_READ;
    }

    /* 2 bytes: length of section, then [length] bytes: unknown purpose */
    if (hdr->headers & MSKWAJ_HDR_HASUNKNOWN2) {
	if (sys->read(fh, &buf[0], 2) != 2) return MSPACK_ERR_READ;
	i = EndGetI16(&buf[0]);
	if (sys->seek(fh, (off_t)i, MSPACK_SYS_SEEK_CUR)) return MSPACK_ERR_SEEK;
    }

    /* filename and extension */
    if (hdr->headers & (MSKWAJ_HDR_HASFILENAME | MSKWAJ_HDR_HASFILEEXT)) {
	off_t pos = sys->tell(fh);
	char *fn = (char *) sys->alloc(sys, (size_t) 13);

	/* allocate memory for maximum length filename */
	if (! fn) return MSPACK_ERR_NOMEMORY;
	hdr->filename = fn;

	/* copy filename if present */
	if (hdr->headers & MSKWAJ_HDR_HASFILENAME) {
	    if (sys->read(fh, &buf[0], 9) != 9) return MSPACK_ERR_READ;
	    for (i = 0; i < 9; i++, fn++) if (!(*fn = buf[i])) break;
	    pos += (i < 9) ? i+1 : 9;
	    if (sys->seek(fh, pos, MSPACK_SYS_SEEK_START))
		return MSPACK_ERR_SEEK;
	}

	/* copy extension if present */
	if (hdr->headers & MSKWAJ_HDR_HASFILEEXT) {
	    *fn++ = '.';
	    if (sys->read(fh, &buf[0], 4) != 4) return MSPACK_ERR_READ;
	    for (i = 0; i < 4; i++, fn++) if (!(*fn = buf[i])) break;
	    pos += (i < 4) ? i+1 : 4;
	    if (sys->seek(fh, pos, MSPACK_SYS_SEEK_START))
		return MSPACK_ERR_SEEK;
	}
	*fn = '\0';
    }

    /* 2 bytes: extra text length then [length] bytes of extra text data */
    if (hdr->headers & MSKWAJ_HDR_HASEXTRATEXT) {
	if (sys->read(fh, &buf[0], 2) != 2) return MSPACK_ERR_READ;
	i = EndGetI16(&buf[0]);
	hdr->extra = (char *) sys->alloc(sys, (size_t)i+1);
	if (! hdr->extra) return MSPACK_ERR_NOMEMORY;
	if (sys->read(fh, hdr->extra, i) != i) return MSPACK_ERR_READ;
	hdr->extra[i] = '\0';
	hdr->extra_length = i;
    }
    return MSPACK_ERR_OK;
}

/* ============================================================
 * Direct-call driver: an in-memory mspack_system backed by a HEAP buffer
 * holding the raw input file bytes (attacker-controlled data lives on the
 * heap, as required), plus main() which reads argv[1] and calls
 * kwajd_read_headers() exactly once.
 * ============================================================ */

struct mem_file {
    struct mspack_file base;   /* must be first: cast-compatible with mspack_file* */
    const unsigned char *data;
    long len;
    long pos;
};

static struct mspack_file *mem_open(struct mspack_system *self,
                                     const char *filename, int mode) {
    (void)self; (void)filename; (void)mode;
    return NULL; /* not used: the harness constructs the mem_file itself */
}

static void mem_close(struct mspack_file *file) { (void)file; }

static int mem_read(struct mspack_file *file, void *buffer, int bytes) {
    struct mem_file *mf = (struct mem_file *) file;
    long avail = mf->len - mf->pos;
    long n;
    if (avail < 0) avail = 0;
    n = (bytes < avail) ? bytes : avail;
    if (n < 0) n = 0;
    if (n > 0) memcpy(buffer, mf->data + mf->pos, (size_t) n);
    mf->pos += n;
    return (int) n;
}

static int mem_write(struct mspack_file *file, void *buffer, int bytes) {
    (void)file; (void)buffer; (void)bytes;
    return -1; /* kwajd_read_headers() never calls write() */
}

static int mem_seek(struct mspack_file *file, off_t offset, int mode) {
    struct mem_file *mf = (struct mem_file *) file;
    long newpos;
    switch (mode) {
        case MSPACK_SYS_SEEK_START: newpos = (long) offset; break;
        case MSPACK_SYS_SEEK_CUR:   newpos = mf->pos + (long) offset; break;
        case MSPACK_SYS_SEEK_END:   newpos = mf->len + (long) offset; break;
        default: return -1;
    }
    if (newpos < 0) return -1;
    mf->pos = newpos;
    return 0;
}

static off_t mem_tell(struct mspack_file *file) {
    struct mem_file *mf = (struct mem_file *) file;
    return (off_t) mf->pos;
}

static void mem_message(struct mspack_file *file, const char *format, ...) {
    (void)file; (void)format; /* discard library messages */
}

static void *mem_alloc(struct mspack_system *self, size_t bytes) {
    (void)self;
    return malloc(bytes); /* the vulnerable 13-byte allocation goes through here */
}

static void mem_free(void *ptr) { free(ptr); }

static void mem_copy(void *src, void *dest, size_t bytes) { memcpy(dest, src, bytes); }

static struct mspack_system mem_system = {
    mem_open, mem_close, mem_read, mem_write, mem_seek, mem_tell,
    mem_message, mem_alloc, mem_free, mem_copy, NULL
};

int main(int argc, char **argv) {
    FILE *f;
    long fsize;
    unsigned char *heap_buf;
    size_t got;
    struct mem_file mf;
    struct mskwajd_header hdr;
    int rc;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 1; }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    fsize = ftell(f);
    if (fsize < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

    /* attacker-controlled input MUST live on the heap so ASan can catch
     * any overflow of buffers derived from it */
    heap_buf = (unsigned char *) malloc((size_t) (fsize > 0 ? fsize : 1));
    if (!heap_buf) { fclose(f); return 1; }
    got = fread(heap_buf, 1, (size_t) fsize, f);
    fclose(f);
    (void) got;

    mf.data = heap_buf;
    mf.len  = fsize;
    mf.pos  = 0;

    memset(&hdr, 0, sizeof(hdr));

    rc = kwajd_read_headers(&mem_system, (struct mspack_file *) &mf, &hdr);
    fprintf(stderr, "kwajd_read_headers() rc=%d\n", rc);

    /* if the function returned OK/READ-past-optional-headers it may have
     * allocated hdr.filename/hdr.extra: free them (real callers do too,
     * via kwajd_close()/mspack_default_system.free) */
    if (hdr.filename) mem_free(hdr.filename);
    if (hdr.extra) mem_free(hdr.extra);
    free(heap_buf);
    return 0;
}
