/*
 * Direct-call crash harness for CVE-2016-4301 (libarchive, mtree device parsing).
 *
 * Target: parse_device() in libarchive/archive_read_support_format_mtree.c
 * Baseline crash: AddressSanitizer stack-buffer-overflow WRITE in parse_device
 *   (numbers[argc++] = ...; the bounds check "argc > MAX_PACK_ARGS" runs AFTER
 *   the write, so the 4th comma-separated number in a "fmt,n1,n2,n3,n4" device
 *   spec overflows the 3-element `numbers[MAX_PACK_ARGS]` stack array).
 *   CWE-787 (out-of-bounds WRITE).
 *
 * argv[1] is read into a HEAP buffer and passed as `val` to parse_device(),
 * exactly like the real caller (parse_device is invoked with the value text
 * of a mtree "device=" keyword). Everything below `parse_device` itself is
 * copied VERBATIM from libarchive so the crash occurs inside the real
 * function body, with no synthetic overflow anywhere else in this file.
 *
 * Real callees included verbatim:
 *   - la_strsep, mtree_atol / mtree_atol8 / mtree_atol10 / mtree_atol16,
 *     parsehex   (all static helpers from archive_read_support_format_mtree.c)
 *   - pack_find + the whole `formats[]` table + every pack_* function
 *     (verbatim from libarchive/archive_pack_dev.c / archive_pack_dev.h) so
 *     `pack_find()` behaves exactly like upstream. NOTE: none of the corpus
 *     inputs below ever reach `(*pack)(...)` (the crash / the "not enough
 *     arguments" paths both return before that call), but the real bodies
 *     are included anyway for faithfulness and so pack_find's function-
 *     pointer table links against real symbols, not stubs.
 *
 * Not real (by necessity, but NOT part of the fault):
 *   - `struct archive` is an opaque stand-in never dereferenced by
 *     parse_device (it only forwards the pointer to archive_set_error()).
 *   - `archive_set_error()` is a no-op stub (the real one formats a message
 *     into a struct archive that is otherwise unused here); it plays no
 *     role in the memory-safety bug.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <errno.h>

/* ------------------------------------------------------------------ */
/* Minimal libarchive surface parse_device() needs (archive.h subset) */
/* ------------------------------------------------------------------ */

struct archive {
	int _unused; /* opaque: parse_device only forwards the pointer */
};

#define	ARCHIVE_OK	  0	/* Operation was successful. */
#define	ARCHIVE_WARN	(-20)	/* Partial success. */

/* Linux value from archive_platform.h: ARCHIVE_ERRNO_FILE_FORMAT -> EINVAL */
#define	ARCHIVE_ERRNO_FILE_FORMAT	EINVAL

/* No-op stub: not part of the fault, never dereferences `a`. */
void
archive_set_error(struct archive *a, int error_number, const char *fmt, ...)
{
	(void)a; (void)error_number; (void)fmt;
}

/* ------------------------------------------------------------------ */
/* libarchive/archive_pack_dev.h  (verbatim)                          */
/* ------------------------------------------------------------------ */

typedef	dev_t pack_t(int, unsigned long [], const char **);

pack_t	*pack_find(const char *);
pack_t	 pack_native;

#define	major_netbsd(x)		((int32_t)((((x) & 0x000fff00) >>  8)))
#define	minor_netbsd(x)		((int32_t)((((x) & 0xfff00000) >> 12) | \
					   (((x) & 0x000000ff) >>  0)))
#define	makedev_netbsd(x,y)	((dev_t)((((x) <<  8) & 0x000fff00) | \
					 (((y) << 12) & 0xfff00000) | \
					 (((y) <<  0) & 0x000000ff)))

/* ------------------------------------------------------------------ */
/* libarchive/archive_pack_dev.c  (verbatim body, minus its #includes) */
/* ------------------------------------------------------------------ */

static	pack_t	pack_netbsd;
static	pack_t	pack_freebsd;
static	pack_t	pack_8_8;
static	pack_t	pack_12_20;
static	pack_t	pack_14_18;
static	pack_t	pack_8_24;
static	pack_t	pack_bsdos;
static	int	compare_format(const void *, const void *);

static const char iMajorError[] = "invalid major number";
static const char iMinorError[] = "invalid minor number";
static const char tooManyFields[] = "too many fields for format";

/* This is blatantly stolen from libarchive/archive_entry.c,
 * in an attempt to get this to play nice on MinGW... */
#if !defined(HAVE_MAJOR) && !defined(major)
/* Replacement for major/minor/makedev. */
#define major(x) ((int)(0x00ff & ((x) >> 8)))
#define minor(x) ((int)(0xffff00ff & (x)))
#define makedev(maj,min) ((0xff00 & ((maj)<<8)) | (0xffff00ff & (min)))
#endif

/* Play games to come up with a suitable makedev() definition. */
#ifdef __QNXNTO__
/* QNX.  <sigh> */
#include <sys/netmgr.h>
#define apd_makedev(maj, min) makedev(ND_LOCAL_NODE, (maj), (min))
#elif defined makedev
/* There's a "makedev" macro. */
#define apd_makedev(maj, min) makedev((maj), (min))
#elif defined mkdev || ((defined _WIN32 || defined __WIN32__) && !defined(__CYGWIN__))
/* Windows. <sigh> */
#define apd_makedev(maj, min) mkdev((maj), (min))
#else
/* There's a "makedev" function. */
#define apd_makedev(maj, min) makedev((maj), (min))
#endif

/* exported */
dev_t
pack_native(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = apd_makedev(numbers[0], numbers[1]);
		if ((unsigned long)major(dev) != numbers[0])
			*error = iMajorError;
		else if ((unsigned long)minor(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}


static dev_t
pack_netbsd(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = makedev_netbsd(numbers[0], numbers[1]);
		if ((unsigned long)major_netbsd(dev) != numbers[0])
			*error = iMajorError;
		else if ((unsigned long)minor_netbsd(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}


#define	major_freebsd(x)	((int32_t)(((x) & 0x0000ff00) >> 8))
#define	minor_freebsd(x)	((int32_t)(((x) & 0xffff00ff) >> 0))
#define	makedev_freebsd(x,y)	((dev_t)((((x) << 8) & 0x0000ff00) | \
					 (((y) << 0) & 0xffff00ff)))

static dev_t
pack_freebsd(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = makedev_freebsd(numbers[0], numbers[1]);
		if ((unsigned long)major_freebsd(dev) != numbers[0])
			*error = iMajorError;
		if ((unsigned long)minor_freebsd(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}


#define	major_8_8(x)		((int32_t)(((x) & 0x0000ff00) >> 8))
#define	minor_8_8(x)		((int32_t)(((x) & 0x000000ff) >> 0))
#define	makedev_8_8(x,y)	((dev_t)((((x) << 8) & 0x0000ff00) | \
					 (((y) << 0) & 0x000000ff)))

static dev_t
pack_8_8(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = makedev_8_8(numbers[0], numbers[1]);
		if ((unsigned long)major_8_8(dev) != numbers[0])
			*error = iMajorError;
		if ((unsigned long)minor_8_8(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}


#define	major_12_20(x)		((int32_t)(((x) & 0xfff00000) >> 20))
#define	minor_12_20(x)		((int32_t)(((x) & 0x000fffff) >>  0))
#define	makedev_12_20(x,y)	((dev_t)((((x) << 20) & 0xfff00000) | \
					 (((y) <<  0) & 0x000fffff)))

static dev_t
pack_12_20(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = makedev_12_20(numbers[0], numbers[1]);
		if ((unsigned long)major_12_20(dev) != numbers[0])
			*error = iMajorError;
		if ((unsigned long)minor_12_20(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}


#define	major_14_18(x)		((int32_t)(((x) & 0xfffc0000) >> 18))
#define	minor_14_18(x)		((int32_t)(((x) & 0x0003ffff) >>  0))
#define	makedev_14_18(x,y)	((dev_t)((((x) << 18) & 0xfffc0000) | \
					 (((y) <<  0) & 0x0003ffff)))

static dev_t
pack_14_18(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = makedev_14_18(numbers[0], numbers[1]);
		if ((unsigned long)major_14_18(dev) != numbers[0])
			*error = iMajorError;
		if ((unsigned long)minor_14_18(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}


#define	major_8_24(x)		((int32_t)(((x) & 0xff000000) >> 24))
#define	minor_8_24(x)		((int32_t)(((x) & 0x00ffffff) >>  0))
#define	makedev_8_24(x,y)	((dev_t)((((x) << 24) & 0xff000000) | \
					 (((y) <<  0) & 0x00ffffff)))

static dev_t
pack_8_24(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = makedev_8_24(numbers[0], numbers[1]);
		if ((unsigned long)major_8_24(dev) != numbers[0])
			*error = iMajorError;
		if ((unsigned long)minor_8_24(dev) != numbers[1])
			*error = iMinorError;
	} else
		*error = tooManyFields;
	return (dev);
}


#define	major_12_12_8(x)	((int32_t)(((x) & 0xfff00000) >> 20))
#define	unit_12_12_8(x)		((int32_t)(((x) & 0x000fff00) >>  8))
#define	subunit_12_12_8(x)	((int32_t)(((x) & 0x000000ff) >>  0))
#define	makedev_12_12_8(x,y,z)	((dev_t)((((x) << 20) & 0xfff00000) | \
					 (((y) <<  8) & 0x000fff00) | \
					 (((z) <<  0) & 0x000000ff)))

static dev_t
pack_bsdos(int n, unsigned long numbers[], const char **error)
{
	dev_t dev = 0;

	if (n == 2) {
		dev = makedev_12_20(numbers[0], numbers[1]);
		if ((unsigned long)major_12_20(dev) != numbers[0])
			*error = iMajorError;
		if ((unsigned long)minor_12_20(dev) != numbers[1])
			*error = iMinorError;
	} else if (n == 3) {
		dev = makedev_12_12_8(numbers[0], numbers[1], numbers[2]);
		if ((unsigned long)major_12_12_8(dev) != numbers[0])
			*error = iMajorError;
		if ((unsigned long)unit_12_12_8(dev) != numbers[1])
			*error = "invalid unit number";
		if ((unsigned long)subunit_12_12_8(dev) != numbers[2])
			*error = "invalid subunit number";
	} else
		*error = tooManyFields;
	return (dev);
}

		/* list of formats and pack functions */
		/* this list must be sorted lexically */
static struct format {
	const char	*name;
	pack_t		*pack;
} formats[] = {
	{"386bsd",  pack_8_8},
	{"4bsd",    pack_8_8},
	{"bsdos",   pack_bsdos},
	{"freebsd", pack_freebsd},
	{"hpux",    pack_8_24},
	{"isc",     pack_8_8},
	{"linux",   pack_8_8},
	{"native",  pack_native},
	{"netbsd",  pack_netbsd},
	{"osf1",    pack_12_20},
	{"sco",     pack_8_8},
	{"solaris", pack_14_18},
	{"sunos",   pack_8_8},
	{"svr3",    pack_8_8},
	{"svr4",    pack_14_18},
	{"ultrix",  pack_8_8},
};

static int
compare_format(const void *key, const void *element)
{
	const char		*name;
	const struct format	*format;

	name = key;
	format = element;

	return (strcmp(name, format->name));
}


pack_t *
pack_find(const char *name)
{
	struct format	*format;

	format = bsearch(name, formats,
	    sizeof(formats)/sizeof(formats[0]),
	    sizeof(formats[0]), compare_format);
	if (format == 0)
		return (NULL);
	return (format->pack);
}

/* ------------------------------------------------------------------ */
/* libarchive/archive_read_support_format_mtree.c helpers (verbatim)  */
/* ------------------------------------------------------------------ */

/* strsep() is not in C90, but strcspn() is. */
/* Taken from http://unixpapa.com/incnote/string.html */
static char *
la_strsep(char **sp, const char *sep)
{
	char *p, *s;
	if (sp == NULL || *sp == NULL || **sp == '\0')
		return(NULL);
	s = *sp;
	p = s + strcspn(s, sep);
	if (*p != '\0')
		*p++ = '\0';
	*sp = p;
	return(s);
}

/*
 * Note that this implementation does not (and should not!) obey
 * locale settings; you cannot simply substitute strtol here, since
 * it does obey locale.
 */
static int64_t
mtree_atol8(char **p)
{
	int64_t	l, limit, last_digit_limit;
	int digit, base;

	base = 8;
	limit = INT64_MAX / base;
	last_digit_limit = INT64_MAX % base;

	l = 0;
	digit = **p - '0';
	while (digit >= 0 && digit < base) {
		if (l>limit || (l == limit && digit > last_digit_limit)) {
			l = INT64_MAX; /* Truncate on overflow. */
			break;
		}
		l = (l * base) + digit;
		digit = *++(*p) - '0';
	}
	return (l);
}

/*
 * Note that this implementation does not (and should not!) obey
 * locale settings; you cannot simply substitute strtol here, since
 * it does obey locale.
 */
static int64_t
mtree_atol10(char **p)
{
	int64_t l, limit, last_digit_limit;
	int base, digit, sign;

	base = 10;

	if (**p == '-') {
		sign = -1;
		limit = ((uint64_t)(INT64_MAX) + 1) / base;
		last_digit_limit = ((uint64_t)(INT64_MAX) + 1) % base;
		++(*p);
	} else {
		sign = 1;
		limit = INT64_MAX / base;
		last_digit_limit = INT64_MAX % base;
	}

	l = 0;
	digit = **p - '0';
	while (digit >= 0 && digit < base) {
		if (l > limit || (l == limit && digit > last_digit_limit))
			return (sign < 0) ? INT64_MIN : INT64_MAX;
		l = (l * base) + digit;
		digit = *++(*p) - '0';
	}
	return (sign < 0) ? -l : l;
}

/* Parse a hex digit. */
static int
parsehex(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return c - 'a';
	else if (c >= 'A' && c <= 'F')
		return c - 'A';
	else
		return -1;
}

/*
 * Note that this implementation does not (and should not!) obey
 * locale settings; you cannot simply substitute strtol here, since
 * it does obey locale.
 */
static int64_t
mtree_atol16(char **p)
{
	int64_t l, limit, last_digit_limit;
	int base, digit, sign;

	base = 16;

	if (**p == '-') {
		sign = -1;
		limit = ((uint64_t)(INT64_MAX) + 1) / base;
		last_digit_limit = ((uint64_t)(INT64_MAX) + 1) % base;
		++(*p);
	} else {
		sign = 1;
		limit = INT64_MAX / base;
		last_digit_limit = INT64_MAX % base;
	}

	l = 0;
	digit = parsehex(**p);
	while (digit >= 0 && digit < base) {
		if (l > limit || (l == limit && digit > last_digit_limit))
			return (sign < 0) ? INT64_MIN : INT64_MAX;
		l = (l * base) + digit;
		digit = parsehex(*++(*p));
	}
	return (sign < 0) ? -l : l;
}

static int64_t
mtree_atol(char **p)
{
	if (**p != '0')
		return mtree_atol10(p);
	if ((*p)[1] == 'x' || (*p)[1] == 'X') {
		*p += 2;
		return mtree_atol16(p);
	}
	return mtree_atol8(p);
}

/* ------------------------------------------------------------------ */
/* TARGET FUNCTION — verbatim from target/original_function.c          */
/* ------------------------------------------------------------------ */

static int
parse_device(dev_t *pdev, struct archive *a, char *val)
{
#define MAX_PACK_ARGS 3
	unsigned long numbers[MAX_PACK_ARGS];
	char *p, *dev;
	int argc;
	pack_t *pack;
	dev_t result;
	const char *error = NULL;

	memset(pdev, 0, sizeof(*pdev));
	if ((dev = strchr(val, ',')) != NULL) {
		/*
		 * Device's major/minor are given in a specified format.
		 * Decode and pack it accordingly.
		 */
		*dev++ = '\0';
		if ((pack = pack_find(val)) == NULL) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Unknown format `%s'", val);
			return ARCHIVE_WARN;
		}
		argc = 0;
		while ((p = la_strsep(&dev, ",")) != NULL) {
			if (*p == '\0') {
				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
				    "Missing number");
				return ARCHIVE_WARN;
			}
			numbers[argc++] = (unsigned long)mtree_atol(&p);
			if (argc > MAX_PACK_ARGS) {
				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
				    "Too many arguments");
				return ARCHIVE_WARN;
			}
		}
		if (argc < 2) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Not enough arguments");
			return ARCHIVE_WARN;
		}
		result = (*pack)(argc, numbers, &error);
		if (error != NULL) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
			    "%s", error);
			return ARCHIVE_WARN;
		}
	} else {
		/* file system raw value. */
		result = (dev_t)mtree_atol(&val);
	}
	*pdev = result;
	return ARCHIVE_OK;
#undef MAX_PACK_ARGS
}

/* ------------------------------------------------------------------ */
/* Direct-call driver                                                  */
/* ------------------------------------------------------------------ */

int
main(int argc, char **argv)
{
	FILE *f;
	long sz;
	char *buf;
	size_t rd;
	struct archive a;
	dev_t dev;
	int r;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	sz = ftell(f);
	if (sz < 0) { fclose(f); return 1; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* Attacker-controlled data MUST live on the heap so ASAN's redzones
	 * catch the target function's own stack-array overflow distinctly
	 * from this buffer. */
	buf = (char *)malloc((size_t)sz + 1);
	if (!buf) { fclose(f); return 1; }
	rd = fread(buf, 1, (size_t)sz, f);
	fclose(f);
	buf[rd] = '\0';

	/* parse_device() is called on a single mtree "device=" VALUE token
	 * (val must not itself contain '\n'); strip any trailing newline so
	 * files written by common editors/echo behave like the real
	 * tokenizer's output. */
	while (rd > 0 && (buf[rd - 1] == '\n' || buf[rd - 1] == '\r')) {
		buf[--rd] = '\0';
	}

	memset(&a, 0, sizeof(a));
	r = parse_device(&dev, &a, buf);
	(void)r;

	free(buf);
	return 0;
}
