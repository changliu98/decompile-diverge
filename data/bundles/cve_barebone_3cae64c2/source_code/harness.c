/* cve_barebone direct-call harness for CVE-2023-3291 (gpac reframe_mp3 ID3v2 demux)
 * Target: id3dmx_flush  (src/filters/reframe_mp3.c)
 * Bug class: CWE-787 heap-buffer-overflow WRITE (1-2 bytes past a gf_realloc'd scratch buffer).
 *
 * See the module docstring in scripts/gen_dc_cve_3cae64c2.py for the full bug writeup and the
 * exact provenance (verbatim slice vs minimal faithful stub) of every symbol below.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>   /* strcasecmp/strncasecmp -- real gpac stricmp/strnicmp (UNIX branch) */
#include <stdint.h>    /* uint64_t/uint32_t/uint16_t/uint8_t/int64_t/... -- real gpac setup.h (UNIX branch) also includes this before its own u8/u32/... typedefs */

/* ---- include/gpac/setup.h: fixed-width typedefs (UNIX/stdint.h branch), Bool, stricmp ---- */
/*! 64 bit unsigned integer*/
typedef uint64_t u64;
/*! 64 bit signed integer*/
typedef int64_t s64;
/*! 32 bit unsigned integer*/
typedef uint32_t u32;
/*! 32 bit signed integer*/
typedef int32_t s32;
/*! 16 bit unsigned integer*/
typedef uint16_t u16;
/*! 16 bit signed integer*/
typedef int16_t s16;
/*! 8 bit unsigned integer*/
typedef uint8_t u8;
/*! 8 bit signed integer*/
typedef int8_t s8;

typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

#define stricmp		strcasecmp
/*! use strnicmp */
#define strnicmp	strncasecmp

/* ---- include/gpac/tools.h: GF_4CC / GF_4CC_MSIZE / GF_Err ---- */
#define GF_4CC(a,b,c,d) ((((u32)a)<<24)|(((u32)b)<<16)|(((u32)c)<<8)|((u32)d))
#define GF_4CC_MSIZE	10

typedef enum
{
	/*!Message from any scripting engine used in the presentation (ECMAScript, MPEG-J, ...) (Info).*/
	GF_SCRIPT_INFO                                          = 3,
	/*!Indicates a send packet is not dispatched due to pending connections.*/
	GF_PENDING_PACKET					= 2,
	/*!Indicates the end of a stream or of a file (Info).*/
	GF_EOS								= 1,
	/*!
	\n\n
	*/
	/*!Operation success (no error).*/
	GF_OK								= 0,
	/*!\n*/
	/*!One of the input parameter is not correct or cannot be used in the current operating mode of the framework.*/
	GF_BAD_PARAM							= -1,
	/*! Memory allocation failure.*/
	GF_OUT_OF_MEM							= -2,
	/*! Input/Output failure (disk access, system call failures)*/
	GF_IO_ERR								= -3,
	/*! The desired feature or operation is not supported by the framework*/
	GF_NOT_SUPPORTED						= -4,
	/*! Input data has been corrupted*/
	GF_CORRUPTED_DATA						= -5,
	/*! A modification was attempted on a scene node which could not be found*/
	GF_SG_UNKNOWN_NODE						= -6,
	/*! The PROTO node interface does not match the nodes using it*/
	GF_SG_INVALID_PROTO						= -7,
	/*! An error occured in the scripting engine*/
	GF_SCRIPT_ERROR							= -8,
	/*! Buffer is too small to contain decoded data. Decoders shall use this error whenever they need to resize their output memory buffers*/
	GF_BUFFER_TOO_SMALL						= -9,
	/*! The bitstream is not compliant to the specfication it refers to*/
	GF_NON_COMPLIANT_BITSTREAM				= -10,
	/*! No filter could be found to handle the desired media type*/
	GF_FILTER_NOT_FOUND						= -11,
	/*! The URL is not properly formatted or cannot be found*/
	GF_URL_ERROR							= -12,
	/*! An service error has occured at the local side*/
	GF_SERVICE_ERROR						= -13,
	/*! A service error has occured at the remote (server) side*/
	GF_REMOTE_SERVICE_ERROR					= -14,
	/*! The desired stream could not be found in the service*/
	GF_STREAM_NOT_FOUND						= -15,
    /*! The URL no longer exists*/
    GF_URL_REMOVED                          = -16,

	/*! The IsoMedia file is not a valid one*/
	GF_ISOM_INVALID_FILE					= -20,
	/*! The IsoMedia file is not complete. Either the file is being downloaded, or it has been truncated*/
	GF_ISOM_INCOMPLETE_FILE					= -21,
	/*! The media in this IsoMedia track is not valid (usually due to a broken stream description)*/
	GF_ISOM_INVALID_MEDIA					= -22,
	/*! The requested operation cannot happen in the current opening mode of the IsoMedia file*/
	GF_ISOM_INVALID_MODE					= -23,
	/*! This IsoMedia track refers to media outside the file in an unknown way*/
	GF_ISOM_UNKNOWN_DATA_REF				= -24,

	/*! An invalid MPEG-4 Object Descriptor was found*/
	GF_ODF_INVALID_DESCRIPTOR				= -30,
	/*! An MPEG-4 Object Descriptor was found or added to a forbidden descriptor*/
	GF_ODF_FORBIDDEN_DESCRIPTOR				= -31,
	/*! An invalid MPEG-4 BIFS command was detected*/
	GF_ODF_INVALID_COMMAND					= -32,
	/*! The scene has been encoded using an unknown BIFS version*/
	GF_BIFS_UNKNOWN_VERSION					= -33,

	/*! The remote IP address could not be solved*/
	GF_IP_ADDRESS_NOT_FOUND					= -40,
	/*! The connection to the remote peer has failed*/
	GF_IP_CONNECTION_FAILURE				= -41,
	/*! The network operation has failed*/
	GF_IP_NETWORK_FAILURE					= -42,
	/*! The network connection has been closed*/
	GF_IP_CONNECTION_CLOSED					= -43,
	/*! The network operation has failed because no data is available*/
	GF_IP_NETWORK_EMPTY						= -44,

	/*! UDP connection did not receive any data at all. Signaled by client services to reconfigure network if possible*/
	GF_IP_UDP_TIMEOUT						= -46,

	/*! Authentication with the remote host has failed*/
	GF_AUTHENTICATION_FAILURE				= -50,
	/*! Not ready for execution, later retry is needed */
	GF_NOT_READY						= -51,
	/*! Bad configuration for the current context */
	GF_INVALID_CONFIGURATION				= -52,
	/*! The element has not been found */
	GF_NOT_FOUND							= -53,
	/*! Unexpected format of data */
	GF_PROFILE_NOT_SUPPORTED				= -54,
	/*! filter PID config requires new instance of filter */
	GF_REQUIRES_NEW_INSTANCE = -56,
	/*! filter PID config cannot be supported by this filter, no use trying to find an alternate input filter chain*/
	GF_FILTER_NOT_SUPPORTED = -57
} GF_Err;

const char *gf_error_to_string(GF_Err e);

/* ---- include/gpac/filters.h: opaque filter/pid/packet handles, property value/data ---- */
typedef struct __gf_filter GF_Filter;
typedef struct __gf_filter_pid GF_FilterPid;
typedef struct __gf_filter_pck GF_FilterPacket;

/* GF_FilterPid needs SOME concrete definition so main() can instantiate a dummy target pid;
 * id3dmx_flush itself never dereferences it (only forwards the pointer to the filter-graph
 * setters below, all of which are no-op stubs), so the real struct's ~15 fields are dropped. */
struct __gf_filter_pid { int _vb_unused; };

typedef struct __gf_prop_val GF_PropertyValue;

typedef struct
{
	/*! data pointer */
	u8 *ptr;
	/*! data size */
	u32 size;
} GF_PropData;

/* GF_PropertyValue (real name/tag, include/gpac/filters.h struct __gf_prop_val): trimmed to the
 * two union members id3dmx_flush's own body actually assigns via PROP_BOOL/PROP_DATA
 * (boolean, data) -- id3dmx_flush never uses PROP_STRING directly (only id3dmx_set_string does,
 * and that helper is off the crash path here, see below), so the other ~15 union members
 * (fractions, vectors, string lists, ...) are dropped. */
typedef enum { GF_PROP_BOOL = 5, GF_PROP_DATA = 16 } GF_PropType;  /* verbatim values, filters.h */
struct __gf_prop_val {
	GF_PropType type;
	union {
		Bool boolean;
		GF_PropData data;
	} value;
};

#define PROP_BOOL(_val) (GF_PropertyValue){.type=GF_PROP_BOOL, .value.boolean = _val}
#define PROP_DATA(_val, _len) (GF_PropertyValue){.type=GF_PROP_DATA, .value.data.ptr = _val, .value.data.size=_len}

enum {
	GF_PROP_PID_COVER_ART = GF_4CC('P','C','O','V'),

};

/* ---- include/gpac/constants.h: the two ID3v2 frame ids id3dmx_flush compares against ---- */
enum {
	GF_ID3V2_FRAME_APIC = GF_4CC('A','P','I','C'),
	GF_ID3V2_FRAME_TXXX = GF_4CC('T','X','X','X'),

};

/* ---- GF_LOG: diagnostic-only, incidental to the bug -- no-op (arguments are never evaluated,
 * so GF_LOG_ERROR/GF_LOG_MEDIA don't even need separate definitions; kept for readability). ---- */
#define GF_LOG_ERROR 0
#define GF_LOG_MEDIA 0
#define GF_LOG(_ll, _lm, _args) ((void)0)

/* ---- gf_realloc/gf_free: real default (non-GPAC_MEMORY_TRACKING) bodies are bare
 * realloc()/free() wrappers (src/utils/alloc.c: MALLOC/REALLOC/FREE == malloc/realloc/free on
 * the STD_MALLOC config) -- reproduced verbatim in effect. ---- */
void *gf_realloc(void *ptr, size_t size) { return realloc(ptr, size); }
void gf_free(void *ptr) { free(ptr); }

/* ==========================================================================================
 * GF_BitStream: trimmed reimplementation of struct __tag_bitstream (src/utils/bitstream.c),
 * restricted to GF_BITSTREAM_READ over a plain memory buffer -- the only mode id3dmx_flush's
 * own gf_bs_new() call ever uses. Field names and the bit-extraction algorithm are copied
 * from the real implementation (that file unconditionally #defines NO_OPTS, so its real
 * gf_bs_read_int ALSO always decays to the same bit-by-bit MSB-first loop used here); the
 * FILE/callback/write/cache/emulation-prevention-byte machinery is dropped as dead code for
 * this mode. gf_bs_available / gf_bs_skip_bytes reproduce the exact GF_BITSTREAM_READ branch
 * of the real functions (skip: `bs->position += nbBytes;` clamped to bs->size; available:
 * `bs->size - bs->position`, 0 if position has run past size).
 * ========================================================================================== */
enum { GF_BITSTREAM_READ = 0 };   /* verbatim value, include/gpac/bitstream.h */

struct __tag_bitstream {
	const u8 *original;
	u64 size;
	u64 position;
	u32 current;
	u32 nbBits;
	u32 bsmode;
};
typedef struct __tag_bitstream GF_BitStream;

static u8 BS_ReadByte(GF_BitStream *bs)
{
	if (bs->position >= bs->size) return 0;
	return bs->original[bs->position++];
}

GF_BitStream *gf_bs_new(const u8 *buffer, u64 BufferSize, u32 mode)
{
	GF_BitStream *tmp = (GF_BitStream *) malloc(sizeof(GF_BitStream));
	if (!tmp) return NULL;
	tmp->original = buffer;
	tmp->size = BufferSize;
	tmp->bsmode = mode;
	tmp->nbBits = 8;
	tmp->current = 0;
	tmp->position = 0;
	return tmp;
}

void gf_bs_del(GF_BitStream *bs) { if (bs) free(bs); }

static u8 gf_bs_read_bit(GF_BitStream *bs)
{
	if (bs->nbBits == 8) {
		bs->current = BS_ReadByte(bs);
		bs->nbBits = 0;
	}
	bs->current <<= 1;
	bs->nbBits++;
	return (u8) ((bs->current & 0x100) >> 8);
}

u32 gf_bs_read_int(GF_BitStream *bs, u32 nBits)
{
	u32 ret = 0;
	while (nBits-- > 0) {
		ret <<= 1;
		ret |= gf_bs_read_bit(bs);
	}
	return ret;
}

u32 gf_bs_read_u8(GF_BitStream *bs) { return (u32) BS_ReadByte(bs); }

u32 gf_bs_read_u16(GF_BitStream *bs)
{
	u32 ret = BS_ReadByte(bs);
	ret <<= 8;
	ret |= BS_ReadByte(bs);
	return ret;
}

u32 gf_bs_read_u32(GF_BitStream *bs)
{
	u32 ret = BS_ReadByte(bs);
	ret <<= 8; ret |= BS_ReadByte(bs);
	ret <<= 8; ret |= BS_ReadByte(bs);
	ret <<= 8; ret |= BS_ReadByte(bs);
	return ret;
}

u32 gf_bs_read_data(GF_BitStream *bs, u8 *data, u32 nbBytes)
{
	if (bs->position + nbBytes > bs->size) return 0;
	memcpy(data, bs->original + bs->position, nbBytes);
	bs->position += nbBytes;
	return nbBytes;
}

u64 gf_bs_available(GF_BitStream *bs)
{
	if (bs->size < bs->position) return 0;
	return bs->size - bs->position;
}

void gf_bs_skip_bytes(GF_BitStream *bs, u64 nbBytes)
{
	if (!bs || !nbBytes) return;
	bs->position += nbBytes;
	if (bs->position > bs->size) bs->position = bs->size;
}

/* ---- src/media_tools/av_parsers.c: gf_id3_read_size, VERBATIM ---- */
u32 gf_id3_read_size(GF_BitStream *bs)
{
	u32 size = 0;
	gf_bs_read_int(bs, 1);
	size |= gf_bs_read_int(bs, 7);
	size<<=7;
	gf_bs_read_int(bs, 1);
	size |= gf_bs_read_int(bs, 7);
	size<<=7;
	gf_bs_read_int(bs, 1);
	size |= gf_bs_read_int(bs, 7);
	size<<=7;
	gf_bs_read_int(bs, 1);
	size |= gf_bs_read_int(bs, 7);
	return size;
}


/* ---- src/utils/error.c: gf_4cc_to_str, VERBATIM (incl. its rolling static buffers) ---- */
#define NB_4CC_BUF	10
static char szTYPE_BUF[NB_4CC_BUF][GF_4CC_MSIZE];
static u32 buf_4cc_idx=0;

const char *gf_4cc_to_str(u32 type)
{
	u32 ch, i;
	char *szTYPE = szTYPE_BUF[buf_4cc_idx];
	char *name = (char *)szTYPE;
	if (!type) return "00000000";
	buf_4cc_idx++;
	if (buf_4cc_idx>=NB_4CC_BUF)
		buf_4cc_idx=0;

	for (i = 0; i < 4; i++) {
		ch = type >> (8 * (3-i) ) & 0xff;
		if ( ch >= 0x20 && ch <= 0x7E ) {
			*name = ch;
			name++;
		} else {
			sprintf(name, "%02X", ch);
			name += 2;
		}
	}
	*name = 0;
	return (const char *) szTYPE;
}


/* ---- Everything below is genuinely off the crash path for the crafted inputs this harness
 * feeds id3dmx_flush (the overflow fires on the unconditional `_buf[fsize+2]=0` store, before
 * any tag dispatch runs): real signatures, no-op/constant-return minimal faithful stubs. ---- */
static s32 gf_itags_find_by_id3tag(u32 id3tag) { (void) id3tag; return -1; }
static const char *gf_itags_get_name(u32 tag_idx) { (void) tag_idx; return NULL; }

static void id3dmx_set_string(GF_FilterPid *apid, char *name, u8 *buf, Bool is_dyn)
{
	(void) apid; (void) name; (void) buf; (void) is_dyn;
}

GF_Err gf_filter_pid_raw_new(GF_Filter *filter, const char *url, const char *local_file, const char *mime_type, const char *fext, const u8 *probe_data, u32 probe_size, Bool trust_mime, GF_FilterPid **out_pid) { (void) filter; (void) url; (void) local_file; (void) mime_type; (void) fext; (void) probe_data; (void) probe_size; (void) trust_mime; if (out_pid) *out_pid = NULL; return GF_OK; }
GF_Err gf_filter_pid_set_property(GF_FilterPid *PID, u32 prop_4cc, const GF_PropertyValue *value) { (void) PID; (void) prop_4cc; (void) value; return GF_OK; }
GF_Err gf_filter_pid_set_property_dyn(GF_FilterPid *PID, char *name, const GF_PropertyValue *value) { (void) PID; (void) name; (void) value; return GF_OK; }
void gf_filter_pid_set_name(GF_FilterPid *PID, const char *name) { (void) PID; (void) name; }
void gf_filter_pid_set_eos(GF_FilterPid *PID) { (void) PID; }
GF_FilterPacket *gf_filter_pck_new_alloc(GF_FilterPid *PID, u32 data_size, u8 **data) { (void) PID; (void) data_size; (void) data; return NULL; }
GF_Err gf_filter_pck_send(GF_FilterPacket *pck) { (void) pck; return GF_OK; }
GF_Err gf_filter_pck_set_framing(GF_FilterPacket *pck, Bool is_start, Bool is_end) { (void) pck; (void) is_start; (void) is_end; }
const char *gf_error_to_string(GF_Err e) { (void) e; return "GF_OK"; }

/* ==========================================================================================
 * TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_3cae64c2/target/original_function.c
 * ========================================================================================== */
void id3dmx_flush(GF_Filter *filter, u8 *id3_buf, u32 id3_buf_size, GF_FilterPid *audio_pid, GF_FilterPid **video_pid_p)
{
	GF_BitStream *bs = gf_bs_new(id3_buf, id3_buf_size, GF_BITSTREAM_READ);
	char *sep_desc;
	char *_buf=NULL;
	u32 buf_alloc=0;
	gf_bs_skip_bytes(bs, 3);
	/*u8 major = */gf_bs_read_u8(bs);
	/*u8 minor = */gf_bs_read_u8(bs);
	/*u8 unsync = */gf_bs_read_int(bs, 1);
	u8 ext_hdr = gf_bs_read_int(bs, 1);
	gf_bs_read_int(bs, 6);
	u32 size = gf_id3_read_size(bs);


	if (ext_hdr) {

	}

	while (size && (gf_bs_available(bs)>=10) ) {
		char *buf;
		char szTag[1024];
		char *sep;
		s32 tag_idx;
		u32 pic_size;
		//u32 pic_type;
		u32 ftag = gf_bs_read_u32(bs);
		u32 fsize = gf_id3_read_size(bs);
		/*u16 fflags = */gf_bs_read_u16(bs);

		size -= 10;
		if (!fsize)
			break;

		if (size<fsize) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[MP3Dmx] Broken ID3 frame tag %s, size %d but remaining bytes %d\n", gf_4cc_to_str(ftag), fsize, size));
			break;
		}

		if (buf_alloc<=fsize) {
			_buf = gf_realloc(_buf, fsize+3);
			buf_alloc = fsize+3;
		}
		//read into _buf+1 so that buf+1 is always %2 mem aligned as it can be loaded as unsigned short
		gf_bs_read_data(bs, _buf+1, fsize);
		_buf[fsize+1]=0;
		_buf[fsize+2]=0;
		buf = _buf+1;

		tag_idx = gf_itags_find_by_id3tag(ftag);

		if (ftag==GF_ID3V2_FRAME_TXXX) {
			sep = memchr(buf, 0, fsize);
			if (sep) {
				if (!stricmp(buf+1, "comment")) {
					id3dmx_set_string(audio_pid, "comment", sep+1, GF_FALSE);
				} else {
					strcpy(szTag, "tag_");
					strncat(szTag, buf+1, 1019);
					id3dmx_set_string(audio_pid, szTag, sep+1, GF_TRUE);
				}
			}
		} else if (ftag == GF_ID3V2_FRAME_APIC) {
			//first char is text encoding
			//then mime
			sep = memchr(buf+1, 0, fsize-1);
			/*pic_type = sep[1];*/
			sep_desc = memchr(sep+2, 0, fsize-1);

			if (sep_desc) {
				GF_Err e;
				pic_size = (u32) ( (sep_desc + 1) - buf);
				pic_size = fsize - pic_size;

				if (video_pid_p) {
					e = gf_filter_pid_raw_new(filter, NULL, NULL, buf+1, NULL, sep_desc+1, pic_size, GF_FALSE, video_pid_p);
					if (e) {
						GF_LOG(GF_LOG_ERROR, GF_LOG_MEDIA, ("[MP3Dmx] error setting up video pid for cover art: %s\n", gf_error_to_string(e) ));
					}
					if (*video_pid_p) {
						u8 *out_buffer;
						GF_FilterPacket *dst_pck;
						gf_filter_pid_set_name(*video_pid_p, "CoverArt");
						gf_filter_pid_set_property(*video_pid_p, GF_PROP_PID_COVER_ART, &PROP_BOOL(GF_TRUE));
						dst_pck = gf_filter_pck_new_alloc(*video_pid_p, pic_size, &out_buffer);
						if (dst_pck) {
							gf_filter_pck_set_framing(dst_pck, GF_TRUE, GF_TRUE);
							memcpy(out_buffer, sep_desc+1, pic_size);
							gf_filter_pck_send(dst_pck);
						}

						gf_filter_pid_set_eos(*video_pid_p);
					}
				} else {
					gf_filter_pid_set_property(audio_pid, GF_PROP_PID_COVER_ART, &PROP_DATA(sep_desc+1, pic_size) );
				}
			}
		} else if (tag_idx>=0) {
			const char *tag_name = gf_itags_get_name((u32) tag_idx);
			id3dmx_set_string(audio_pid, (char *) tag_name, buf+1, GF_FALSE);
		} else {
			sprintf(szTag, "tag_%s", gf_4cc_to_str(ftag));
			if ((ftag>>24) == 'T') {
				id3dmx_set_string(audio_pid, szTag, buf+1, GF_TRUE);
			} else {
				gf_filter_pid_set_property_dyn(audio_pid, szTag, &PROP_DATA(buf, fsize) );
			}
		}
		size -= fsize;
	}
	gf_bs_del(bs);
	if (_buf) gf_free(_buf);
}
/* ==== end verbatim target function ==== */

/* ---- driver -----------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded) and hands it to id3dmx_flush as the
 * raw id3_buf/id3_buf_size -- exactly the real call site's contract (reframe_mp3.c buffers up
 * one ID3v2 tag's bytes off the MP3 stream, then flushes it through this same signature). The
 * crafted corpus (scripts/gen_dc_cve_3cae64c2.py) encodes real ID3v2-shaped bytes (3-byte
 * magic, version, flags, a synchsafe 28-bit tag size, then 10-byte-header framed sub-frames
 * each with its own synchsafe size) so id3dmx_flush's own parsing drives every branch --
 * nothing about the trigger condition is hardcoded here, it all comes from the file. */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
	long fsz = ftell(fp);
	if (fsz < 0) { fclose(fp); return 64; }
	if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

	size_t n = (size_t) fsz;
	u8 *ibuf = (u8 *) malloc(n ? n : 1);
	if (!ibuf) { fclose(fp); return 64; }
	size_t rn = n ? fread(ibuf, 1, n, fp) : 0;
	fclose(fp);

	struct __gf_filter_pid dummy_pid;
	memset(&dummy_pid, 0, sizeof(dummy_pid));
	GF_FilterPid *audio_pid = &dummy_pid;

	/* Call through a volatile function pointer so id3dmx_flush (a single-call-site function --
	 * LLVM's inliner would otherwise fold it straight into main() at -O1) can't be inlined away
	 * and disappear as a distinct ASAN backtrace frame. This changes nothing about HOW it's
	 * called (same arguments, same semantics) or its own bytes. */
	void (*volatile vb_call_id3dmx_flush)(GF_Filter *, u8 *, u32, GF_FilterPid *, GF_FilterPid **)
		= id3dmx_flush;

	vb_call_id3dmx_flush(NULL, ibuf, (u32) rn, audio_pid, NULL);

	/* Only reached on a SAFE run (a triggering run aborts inside the call above). */
	free(ibuf);
	return 0;
}
