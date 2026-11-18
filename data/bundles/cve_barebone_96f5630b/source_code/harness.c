/* cve_barebone harness -- libvips CVE-2023-40032 / vips_utf8_strcasestr NULL-deref (CWE-476)
 * See scripts/gen_dc_cve_96f5630b.py for the full bug writeup. Summary: g_utf8_find_next_char()
 * legitimately returns NULL when its end-bounded advance reaches the haystack boundary; the
 * pre-fix inner loop never checked for that, so the following iteration's
 * g_utf8_get_char_validated(NULL, ...) -> g_utf8_get_char_extended(NULL, ...) dereferences NULL
 * as its very first statement -> SIGSEGV, caught by ASAN inside that callee with
 * vips_utf8_strcasestr on the stack as its caller.
 *
 * PROOF this can't misfire on plain ASCII: if needle and the matched haystack characters are
 * all single-byte, needle_len_bytes == needle_len (bytes == characters). The outer-loop guard
 * checked before entering the inner loop is `o <= len_bytes - needle_len_bytes`, i.e.
 * `o + needle_len <= len_bytes`. After successfully matching k+1 ASCII characters (k+1 <=
 * needle_len - 1, i.e. more needle characters remain), haystack_char sits at o+k+1 <=
 * o+needle_len-1 < len_bytes -- strictly before the boundary -- so the NULL-returning branch of
 * g_utf8_find_next_char can never fire while iterations remain. The bug therefore REQUIRES a
 * matched haystack character whose byte length exceeds its needle counterpart's, which is what
 * the three Unicode case pairs below (real UnicodeData.txt simple-lowercase mappings) supply.
 *
 * vips_utf8_strcasestr calls four GLib entry points; libvips links the real GLib, but this
 * harness is fully self-contained (`-lm` only), so they are reproduced here against the real
 * glib source semantics. g_utf8_find_next_char and g_utf8_get_char_extended are ON the crash
 * path (the bug lives in their interaction), so they are faithful ports of glib/gutf8.c, not
 * simplified stand-ins. g_unichar_tolower is a minimal faithful stub: identity + ASCII/Latin-1
 * case pairs + the three real Unicode simple-lowercase mappings this harness exercises
 * (KELVIN SIGN U+212A -> 'k', ANGSTROM SIGN U+212B -> 'å', OHM SIGN U+2126 -> 'ω'); their
 * *values* are incidental to the memory-safety mechanism -- only the equality of two
 * tolower() results decides control flow.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint32_t gunichar;

/* ---- g_utf8_skip: UTF-8 sequence length keyed by lead byte (glib/gutf8.c table, reproduced
 * as an equivalent branch ladder). ASCII and stray continuation bytes -> 1. ---- */
static int
utf8_skip( unsigned char lead )
{
	if( lead < 0xc0 )
		return( 1 );
	if( lead < 0xe0 )
		return( 2 );
	if( lead < 0xf0 )
		return( 3 );
	if( lead < 0xf8 )
		return( 4 );
	if( lead < 0xfc )
		return( 5 );
	if( lead < 0xfe )
		return( 6 );
	return( 1 );
}

/* g_utf8_next_char (glib/gutf8.h macro): unconditional one-character advance. Used only by
 * g_utf8_strlen()'s max<0 path, on the (fully-controlled, always nul-terminated) needle. */
static const char *
g_utf8_next_char_impl( const char *p )
{
	return( p + utf8_skip( (unsigned char) *p ) );
}

/* g_utf8_strlen (glib/gutf8.c) -- vips_utf8_strcasestr only ever calls it with max=-1. */
static long
g_utf8_strlen( const char *p, long max )
{
	long len = 0;

	if( max < 0 ) {
		while( *p ) {
			p = g_utf8_next_char_impl( p );
			len++;
		}
		return( len );
	}

	if( max == 0 || !*p )
		return( 0 );

	{
		const char *start = p;

		p = g_utf8_next_char_impl( p );
		while( p - start < max && *p ) {
			len++;
			p = g_utf8_next_char_impl( p );
		}
		if( p - start <= max )
			len++;
	}

	return( len );
}

/* g_utf8_find_next_char (glib/gutf8.c, verbatim logic). This is the function whose
 * documented NULL-on-boundary return the pre-fix vips_utf8_strcasestr didn't check. */
static const char *
g_utf8_find_next_char( const char *p, const char *end )
{
	if( end ) {
		for( ++p; p < end && ((unsigned char) *p & 0xc0) == 0x80; ++p )
			;
		return( (p >= end) ? NULL : p );
	}
	else {
		for( ++p; ((unsigned char) *p & 0xc0) == 0x80; ++p )
			;
		return( p );
	}
}

#define UNICODE_VALID( Char ) \
	((Char) < 0x110000 && \
	 (((Char) & 0xFFFFF800) != 0xD800) && \
	 ((Char) < 0xFDD0 || (Char) > 0xFDEF) && \
	 ((Char) & 0xFFFE) != 0xFFFE)

/* g_utf8_get_char_extended (glib/gutf8.c, verbatim logic). Its FIRST statement
 * unconditionally dereferences `p` -- this is the crash site: once g_utf8_find_next_char
 * above has returned NULL and the pre-fix caller keeps looping, `p` here is NULL. */
static gunichar
g_utf8_get_char_extended( const char *p, long max_len )
{
	unsigned int i, len;
	gunichar min_code;
	gunichar wc = (unsigned char) *p;   /* <-- unconditional deref: the crash site */

	if( wc < 0x80 ) {
		return( wc );
	}
	else if( wc < 0xc0 ) {
		return( (gunichar) -1 );
	}
	else if( wc < 0xe0 ) {
		len = 2; wc &= 0x1f; min_code = 1 << 7;
	}
	else if( wc < 0xf0 ) {
		len = 3; wc &= 0x0f; min_code = 1 << 11;
	}
	else if( wc < 0xf8 ) {
		len = 4; wc &= 0x07; min_code = 1 << 16;
	}
	else if( wc < 0xfc ) {
		len = 5; wc &= 0x03; min_code = 1 << 21;
	}
	else if( wc < 0xfe ) {
		len = 6; wc &= 0x01; min_code = 1 << 26;
	}
	else {
		return( (gunichar) -1 );
	}

	if( max_len >= 0 && (long) len > max_len ) {
		for( i = 1; i < (unsigned int) max_len; i++ ) {
			if( (((const unsigned char *) p)[i] & 0xc0) != 0x80 )
				return( (gunichar) -1 );
		}
		return( (gunichar) -2 );
	}

	for( i = 1; i < len; i++ ) {
		unsigned char ch = ((const unsigned char *) p)[i];

		if( (ch & 0xc0) != 0x80 ) {
			if( ch )
				return( (gunichar) -1 );
			else
				return( (gunichar) -2 );
		}

		wc <<= 6;
		wc |= (ch & 0x3f);
	}

	if( wc < min_code )
		return( (gunichar) -1 );

	return( wc );
}

/* g_utf8_get_char_validated (glib/gutf8.c, verbatim logic). */
static gunichar
g_utf8_get_char_validated( const char *p, long max_len )
{
	gunichar result;

	if( max_len == 0 )
		return( (gunichar) -2 );

	result = g_utf8_get_char_extended( p, max_len );

	if( result == (gunichar) -1 || result == (gunichar) -2 )
		return( result );
	else if( !UNICODE_VALID( result ) )
		return( (gunichar) -1 );
	else
		return( result );
}

/* g_unichar_tolower (glib/guniprop.c) -- minimal faithful stub, see file header comment. */
static gunichar
g_unichar_tolower( gunichar c )
{
	if( c == 0x212Au ) return( 0x6Bu );     /* KELVIN SIGN -> LATIN SMALL LETTER K */
	if( c == 0x212Bu ) return( 0x00E5u );   /* ANGSTROM SIGN -> LATIN SMALL LETTER A WITH RING ABOVE */
	if( c == 0x2126u ) return( 0x03C9u );   /* OHM SIGN -> GREEK SMALL LETTER OMEGA */
	if( c >= 'A' && c <= 'Z' ) return( c + 32 );
	if( c >= 0xC0 && c <= 0xDE && c != 0xD7 ) return( c + 0x20 );  /* Latin-1 Supplement */
	return( c );
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace). */
__attribute__((noinline))
static const char *
vips_utf8_strcasestr( const char *haystack_start, const char *needle_start, 
	int len_bytes )
{
        int needle_len = g_utf8_strlen( needle_start, -1 );
        int needle_len_bytes = strlen( needle_start );

	const char *haystack;

	for( haystack = haystack_start; 
		haystack - haystack_start <= len_bytes - needle_len_bytes; 
		haystack = g_utf8_find_next_char( haystack, NULL ) ) {
                const char *needle_char;
                const char *haystack_char;
		int i;

                haystack_char = haystack;
                needle_char = needle_start;
                for( i = 0; i < needle_len; i++ ) {
			/* Haystack isn't necessarily null-terminated and
			 * might end half-way through a utf-8 character, so we
			 * need to be careful not to run off the end.
			 */
                        gunichar a = 
				g_utf8_get_char_validated( haystack_char, 
					haystack_start + len_bytes - haystack );
                        gunichar b = 
				g_utf8_get_char_validated( needle_char, -1 );

                        /* Invalid utf8? 
			 *
			 * gunichar is a uint32, so we can't compare < 0, we 
			 * have to look for -1 and -2 (the two possible error 
			 * values).
                         */
                        if( a == (gunichar) -1 ||
				a == (gunichar) -2 ||
				b == (gunichar) -1 ||
				b == (gunichar) -2 )
                                return( NULL );

                        /* End of haystack. There can't be a complete needle
                         * anywhere.
                         */
                        if( a == (gunichar) 0 )
                                return( NULL );

                        /* Mismatch.
                         */
                        if( g_unichar_tolower( a ) != g_unichar_tolower( b ) )
                                break;

                        haystack_char = 
				g_utf8_find_next_char( haystack_char, 
					haystack_start + len_bytes );
                        needle_char = 
				g_utf8_find_next_char( needle_char, NULL );
                }

                if( i == needle_len )
			/* Walked the whole of needle, so we must have found a 
			 * complete match.
			 */
                        return( haystack );
        }

        /* Walked the whole of haystack without finding a match.
         */
        return( NULL );
}

/* ================= driver =================
 * Input layout (fully hand-crafted, no ambiguity):
 *   byte[0]                       = needle_len (0..250)
 *   bytes[1 .. 1+needle_len)      = needle content (harness nul-terminates it)
 *   byte[1+needle_len]            = len_bytes (0..250)
 *   remaining bytes               = haystack content
 *
 * The harness copies exactly len_bytes bytes of haystack content into a heap buffer sized
 * len_bytes+1, with a trailing 0 sentinel -- so the OUTER loop's unbounded
 * g_utf8_find_next_char(p, NULL) walk (used to move to the next haystack offset) can never
 * run past the allocation. The INNER loop's per-character advance is always end-bounded
 * (haystack_start+len_bytes) and its comparison `p < end` short-circuits before the sentinel
 * byte is ever read, so the sentinel cannot mask the trigger.
 */
int
main( int argc, char **argv )
{
	FILE *fp;
	long ln;
	size_t n, got, pos;
	unsigned char *data;
	unsigned needle_len, len_bytes;
	char *needle, *haystack;
	size_t avail, use;
	const char *(* volatile fn)( const char *, const char *, int );
	const char *result;

	if( argc < 2 ) {
		fprintf( stderr, "usage: %s <input>\n", argv[0] );
		return( 2 );
	}

	fp = fopen( argv[1], "rb" );
	if( !fp ) {
		perror( "fopen" );
		return( 2 );
	}
	fseek( fp, 0, SEEK_END );
	ln = ftell( fp );
	fseek( fp, 0, SEEK_SET );
	if( ln < 0 )
		ln = 0;
	n = (size_t) ln;

	data = (unsigned char *) malloc( n ? n : 1 );   /* HEAP input, ASAN-guarded */
	if( !data ) {
		fclose( fp );
		return( 2 );
	}
	got = fread( data, 1, n, fp );
	fclose( fp );

	if( got < 1 ) {
		free( data );
		return( 0 );
	}
	pos = 0;
	needle_len = data[pos++];

	if( pos + needle_len > got ) {
		free( data );
		return( 0 );
	}
	needle = (char *) malloc( (size_t) needle_len + 1 );
	memcpy( needle, data + pos, needle_len );
	needle[needle_len] = '\0';
	pos += needle_len;

	if( pos >= got ) {
		free( data );
		free( needle );
		return( 0 );
	}
	len_bytes = data[pos++];

	avail = got - pos;
	use = ((size_t) len_bytes <= avail) ? (size_t) len_bytes : avail;

	haystack = (char *) malloc( (size_t) len_bytes + 1 );   /* the buffer len_bytes describes */
	memcpy( haystack, data + pos, use );
	if( use < len_bytes )
		memset( haystack + use, 0, len_bytes - use );
	haystack[len_bytes] = '\0';   /* boundary sentinel, see header comment */

	free( data );

	fn = vips_utf8_strcasestr;
	result = fn( haystack, needle, (int) len_bytes );
	(void) result;

	free( needle );
	free( haystack );

	return( 0 );
}
