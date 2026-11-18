/* cve_barebone harness -- gpac CVE-2023-4778 / gf_bt_get_next heap READ overflow (CWE-125)
 *
 * Isolated reproduction: gf_bt_get_next() is called directly on a hand-built GF_BTParser
 * whose line_buffer is a HEAP allocation of exactly N bytes (the file input, minus a 1-byte
 * mode marker). gf_bt_check_line() -- the real function, copied verbatim below, and gf_bt_get_next's
 * very first statement -- is the trigger mechanism itself:
 *
 *   TRIGGER: line_pos == line_size == N at entry (the "string-based input, line already
 *   fully consumed" state). gf_bt_check_line's own while-loop condition (line_pos<line_size)
 *   is immediately false, its own "==" comment/size checks are skipped, so it falls straight
 *   into `if (parser->line_size == parser->line_pos) { if (!parser->gz_in) { done=1; return; } }`
 *   -- gz_in is NULL (string mode), so it returns with line_pos/line_size UNCHANGED (both N).
 *   Back in gf_bt_get_next, the loop's first statement reads
 *   `parser->line_buffer[parser->line_pos + i]` with line_pos=N, i=0 -- exactly one byte past
 *   the N-byte heap allocation, before either of the function's own bounds checks (both `==`,
 *   both AFTER an increment) ever runs. Heap-buffer-overflow READ inside gf_bt_get_next itself.
 *
 *   SAFE: line_pos=0 < line_size=N at entry, content[0] a plain non-delimiter, non-comment,
 *   non-whitespace byte. gf_bt_check_line's leading-whitespace-skip loop exits on the very
 *   first character (default case), its comment/reload block is skipped entirely (line_pos !=
 *   line_size), so it returns with the buffer untouched. gf_bt_get_next then walks the token
 *   normally: line_pos+i increases by exactly 1 per iteration (either `i++` or `line_pos+=1`
 *   in the quote branch), so its own `==` check is GUARANTEED to fire -- either at a delimiter
 *   byte mid-content or exactly when line_pos+i reaches line_size -- and the function returns
 *   cleanly, never touching line_buffer[N].
 *
 * gf_bt_check_line is real gpac code (verbatim) because its early-return behaviour on
 * gz_in==NULL IS what leaves the exhausted (line_pos==line_size) state gf_bt_get_next then
 * reads past. Everything it touches ONLY on its gzFile-backed "next_line:" reload path (zlib
 * wrappers, GF_List, #define/#if comment directives, logging) is unreachable for both of our
 * inputs (gz_in is always NULL, and neither input state satisfies `line_size==0` nor lets
 * check_line's own while-loop run past index 0 into that path) -- real-signature no-op stubs
 * for those keep the file self-contained without touching the actual crash mechanism.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>

/* ---- gpac base typedefs (real names, gpac/setup.h) ---- */
typedef unsigned int   u32;
typedef int             s32;
typedef unsigned char   u8;
typedef unsigned long long u64;
typedef long long        s64;
typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

/* ---- real error enum (gpac/tools.h, verbatim) ---- */
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

/* ---- opaque real types (real names; only ever used here as incomplete pointers --
 * neither gf_bt_check_line nor gf_bt_get_next dereferences their fields) ---- */
typedef struct GF_SceneLoader GF_SceneLoader;
typedef struct _tag_array GF_List;          /* real tag, gpac/list.h */
typedef struct GF_Proto GF_Proto;
typedef struct GF_Command GF_Command;
typedef struct GF_StreamContext GF_StreamContext;
typedef struct GF_AUContext GF_AUContext;
typedef void *gzFile;                       /* zlib opaque handle; gpac's own gf_gz* wrappers
                                              * already type it as void* (gpac/tools.h) */

/* ---- real macro (loader_bt.c, verbatim) ---- */
#define BT_LINE_SIZE	4000

/* ---- real struct (loader_bt.c, verbatim) ---- */
typedef struct
{
	char *name;
	char *value;
} BTDefSymbol;

/* ---- real struct (loader_bt.c, verbatim) ---- */
typedef struct
{
	GF_SceneLoader *load;
	Bool initialized;
	gzFile gz_in;
	u32 file_size, file_pos;

	/*create from string only*/
	GF_List *top_nodes;

	GF_Err last_error;
	u32 line;

	Bool done, in_com;
	u32 is_wrl;
	/*0: no unicode, 1: UTF-16BE, 2: UTF-16LE*/
	u32 unicode_type;

	GF_List *def_symbols;

	/*routes are not created in the graph when parsing, so we need to track insert and delete/replace*/
	GF_List *unresolved_routes, *inserted_routes, *peeked_nodes;
	GF_List *undef_nodes, *def_nodes;

	char *line_buffer;
	char cur_buffer[500];
	s32 line_size, line_pos, line_start_pos;

	u32 block_comment;

	/*set when parsing proto*/
	GF_Proto *parsing_proto;
	Bool is_extern_proto_field;

	/*current stream ID, AU time and RAP flag*/
	u32 stream_id;
	u32 au_time;
	Bool au_is_rap;

	/*current BIFS stream & AU*/
	GF_StreamContext *bifs_es;
	GF_AUContext *bifs_au;
	u32 base_bifs_id;
	GF_Command *cur_com;

	/*current OD stream & AU*/
	GF_StreamContext *od_es;
	GF_AUContext *od_au;
	u32 base_od_id;

	GF_List *scripts;

	u32 def_w, def_h;

} GF_BTParser;

/* strnicmp: gpac's own non-Windows compat #define (gpac/setup.h: "#define strnicmp
 * strncasecmp"); only reached inside gf_bt_check_line's dead #define/#if comment-directive
 * branch for both our inputs. */
#define strnicmp strncasecmp

/* ---- real macro (gpac/tools.h, verbatim) ---- */
#define GF_SAFEALLOC(__ptr, __struct) {\
		(__ptr) = (__struct *) gf_malloc(sizeof(__struct));\
		if (__ptr) {\
			memset((void *) (__ptr), 0, sizeof(__struct));\
		}\
	}

/* ---- incidental stubs: real exported signatures (gpac/tools.h, gpac/utf.h, gpac/list.h),
 * trivial no-op bodies. None of these are reachable for either the trigger or the safe
 * input (traced above) -- they exist only so the verbatim gf_bt_check_line/gf_bt_report
 * bodies, which reference them in branches gz_in==NULL never takes, link standalone. */
static void *gf_malloc(size_t size) { return malloc(size); }
static char *gf_strdup(const char *str) {
	if (!str) return NULL;
	size_t n = strlen(str) + 1;
	char *d = (char *) malloc(n);
	if (d) memcpy(d, str, n);
	return d;
}
static u64 gf_gzseek(void *file, u64 offset, int whence) { (void) file; (void) offset; (void) whence; return 0; }
static u64 gf_gztell(void *file) { (void) file; return 0; }
static int gf_gzeof(void *file) { (void) file; return 1; }
static int gf_gzgetc(void *file) { (void) file; return -1; }
static char *gf_gzgets(void *file, char *buf, int len) { (void) file; (void) buf; (void) len; return NULL; }
static u32 gf_utf8_wcstombs(char *dst, size_t dst_len, const unsigned short **srcp) {
	(void) dst; (void) dst_len; (void) srcp; return 0;
}
static void gf_set_progress(const char *title, u64 done, u64 total) { (void) title; (void) done; (void) total; }
static u32 gf_list_count(const GF_List *ptr) { (void) ptr; return 0; }
static GF_Err gf_list_add(GF_List *ptr, void *item) { (void) ptr; (void) item; return GF_OK; }
static void *gf_list_get(GF_List *ptr, u32 position) { (void) ptr; (void) position; return NULL; }

/* ---- real enums (gpac/tools.h, verbatim) -- GF_LOG_ERROR / GF_LOG_PARSER, referenced by
 * gf_bt_check_line's (dead, for us) "#define "-directive branch's GF_LOG(...) call. ---- */
typedef enum
{
	/*! Disable all Log message*/
	GF_LOG_QUIET = 0,
	/*! Log message describes an error*/
	GF_LOG_ERROR,
	/*! Log message describes a warning*/
	GF_LOG_WARNING,
	/*! Log message is informational (state, etc..)*/
	GF_LOG_INFO,
	/*! Log message is a debug info*/
	GF_LOG_DEBUG
} GF_LOG_Level;
typedef enum
{
	/*! Log message from the core library (init, threads, network calls, etc)*/
	GF_LOG_CORE = 0,
	/*! Log message from a raw media parser (BIFS, LASeR, A/V formats)*/
	GF_LOG_CODING,
	/*! Log message from a bitstream parser (IsoMedia, MPEG-2 TS, OGG, ...)*/
	GF_LOG_CONTAINER,
	/*! Log message from the network/service stack (messages & co)*/
	GF_LOG_NETWORK,
	/*! Log message from the HTTP stack*/
	GF_LOG_HTTP,
	/*! Log message from the RTP/RTCP stack (TS info) and packet structure & hinting (debug)*/
	GF_LOG_RTP,
	/*! Log message from a codec*/
	GF_LOG_CODEC,
	/*! Log message from any textual (XML, ...) parser (context loading, etc)*/
	GF_LOG_PARSER,
	/*! Generic log message from a filter (not from filter core library)*/
	GF_LOG_MEDIA,
	/*! Log message from the scene graph/scene manager (handling of nodes and attribute modif, DOM core)*/
	GF_LOG_SCENE,
	/*! Log message from the scripting engine APIs - does not cover alert() in the script code itself*/
	GF_LOG_SCRIPT,
	/*! Log message from event handling*/
	GF_LOG_INTERACT,
	/*! Log message from compositor*/
	GF_LOG_COMPOSE,
	/*! Log message from the compositor, indicating media object state*/
	GF_LOG_COMPTIME,
	/*! Log for video object cache */
	GF_LOG_CACHE,
	/*! Log message from multimedia I/O devices (audio/video input/output, ...)*/
	GF_LOG_MMIO,
	/*! Log for runtime info (times, memory, CPU usage)*/
	GF_LOG_RTI,
	/*! Log for memory tracker*/
	GF_LOG_MEMORY,
	/*! Log for audio compositor*/
	GF_LOG_AUDIO,
	/*! Generic Log for modules*/
	GF_LOG_MODULE,
	/*! Log for threads and mutexes */
	GF_LOG_MUTEX,
	/*! Log for threads and condition */
	GF_LOG_CONDITION,
	/*! Log for all HTTP streaming */
	GF_LOG_DASH,
	/*! Log for all messages from filter core library (not from a filter) */
	GF_LOG_FILTER,
	/*! Log for filter scheduler only */
	GF_LOG_SCHEDULER,
	/*! Log for all ROUTE message */
	GF_LOG_ROUTE,
	/*! Log for all messages coming from script*/
	GF_LOG_CONSOLE,
	/*! Log for all messages coming the application, not used by libgpac or the modules*/
	GF_LOG_APP,

	/*! special value used to set a level for all tools*/
	GF_LOG_ALL,
	GF_LOG_TOOL_MAX = GF_LOG_ALL,
} GF_LOG_Tool;

/* GPAC_DISABLE_LOG: real gpac build-config macro (gpac/tools.h). With it defined, gpac's own
 * GF_LOG macro (tools.h) expands to gf_log_check_error(_ll,_lm) -- copied verbatim below,
 * along with a trivial (never-really-invoked-for-us) body for that function -- instead of
 * the full va_list-based logger. This strips gf_bt_report's logging block too (same guard). */
#define GPAC_DISABLE_LOG
void gf_log_check_error(u32 ll, u32 lt) { (void) ll; (void) lt; }
#define GF_LOG(_ll, _lm, __args) gf_log_check_error(_ll, _lm);

/* ---- real function (loader_bt.c, verbatim) ---- */
static GF_Err gf_bt_report(GF_BTParser *parser, GF_Err e, char *format, ...)
{
#ifndef GPAC_DISABLE_LOG
	if (format && gf_log_tool_level_on(GF_LOG_PARSER, e ? GF_LOG_ERROR : GF_LOG_WARNING)) {
		char szMsg[2048];
		va_list args;
		va_start(args, format);
		vsnprintf(szMsg, 2048, format, args);
		va_end(args);
		GF_LOG((u32) (e ? GF_LOG_ERROR : GF_LOG_WARNING), GF_LOG_PARSER, ("[BT/WRL Parsing] %s (line %d)\n", szMsg, parser->line));
	}
#endif
	if (e) parser->last_error = e;
	return e;
}

/* ---- real function (loader_bt.c, verbatim) -- gf_bt_get_next's first statement, and the
 * actual trigger mechanism: its early-return on gz_in==NULL leaves line_pos==line_size
 * (the trigger state) or line_pos<line_size (the safe state) exactly as gf_bt_get_next
 * received it. ---- */
void gf_bt_check_line(GF_BTParser *parser)
{
reload_line:
	while (parser->line_pos < parser->line_size) {
		switch (parser->line_buffer[parser->line_pos]) {
		case ' ':
		case '\t':
		case '\n':
		case '\r':
			parser->line_pos++;
			continue;
		case '\0':
			parser->line_pos = parser->line_size;
		default:
			break;
		}
		break;
	}

	if (parser->line_pos < parser->line_size) {
		if (parser->line_buffer[parser->line_pos]=='#') {
			parser->line_size = parser->line_pos;
		}
		else if ((parser->line_buffer[parser->line_pos]=='/') && (parser->line_buffer[parser->line_pos+1]=='/') ) {
			parser->line_size = parser->line_pos;
		}
	}

	if (parser->line_size == parser->line_pos) {
		/*string based input - done*/
		if (!parser->gz_in) {
			parser->done = 1;
			return;
		}

next_line:
		parser->line_start_pos = (s32) gf_gztell(parser->gz_in);
		parser->line_buffer[0] = 0;
		if (parser->unicode_type) {
			u8 c1, c2;
			unsigned short wchar;
			unsigned short l[BT_LINE_SIZE];
			unsigned short *dst = l;
			Bool is_ret = 0;
			u32 last_space_pos, last_space_pos_stream;
			u32 go = BT_LINE_SIZE - 1;
			last_space_pos = last_space_pos_stream = 0;
			while (go && !gf_gzeof(parser->gz_in) ) {
				c1 = gf_gzgetc(parser->gz_in);
				c2 = gf_gzgetc(parser->gz_in);
				/*Little-endian order*/
				if (parser->unicode_type==2) {
					if (c2) {
						wchar = c2;
						wchar <<=8;
						wchar |= c1;
					}
					else wchar = c1;
				} else {
					wchar = c1;
					if (c2) {
						wchar <<= 8;
						wchar |= c2;
					}
				}
				*dst = wchar;
				if (wchar=='\r') is_ret = 1;
				else if (wchar=='\n') {
					dst++;
					break;
				}
				else if (is_ret) {
					u32 fpos = (u32) gf_gztell(parser->gz_in);
					gf_gzseek(parser->gz_in, fpos-2, SEEK_SET);
					break;
				}
				if (wchar==' ') {
					//last_space_pos_stream = (u32) gf_gztell(parser->gz_in);
					last_space_pos = (u32) (dst - l);
				}
				dst++;
				go--;

			}
			*dst = 0;
			/*long line, rewind stream to last space*/
			if (!go) {
				u32 rew_pos = (u32)  (gf_gztell(parser->gz_in) - 2*(dst - &l[last_space_pos]) );
				gf_gzseek(parser->gz_in, rew_pos, SEEK_SET);
				l[last_space_pos+1] = 0;
			}
			/*check eof*/
			if (l[0]==0xFFFF) {
				parser->done = 1;
				return;
			}
			/*convert to mbc string*/
			dst = l;
			gf_utf8_wcstombs(parser->line_buffer, BT_LINE_SIZE, (const unsigned short **) &dst);

			if (!strlen(parser->line_buffer) && gf_gzeof(parser->gz_in)) {
				parser->done = 1;
				return;
			}
		} else {
			if ((gf_gzgets(parser->gz_in, parser->line_buffer, BT_LINE_SIZE) == NULL)
			        || (!strlen(parser->line_buffer) && gf_gzeof(parser->gz_in))) {
				parser->done = 1;
				return;
			}
			/*watchout for long lines*/
			if (1 + strlen(parser->line_buffer) == BT_LINE_SIZE) {
				u32 rew, pos, go;
				rew = 0;
				go = 1;
				while (go) {
					switch (parser->line_buffer[strlen(parser->line_buffer)-1]) {
					case ' ':
					case ',':
					case '[':
					case ']':
						go = 0;
						break;
					default:
						parser->line_buffer[strlen(parser->line_buffer)-1] = 0;
						rew++;
						break;
					}
				}
				pos = (u32) gf_gztell(parser->gz_in);
				gf_gzseek(parser->gz_in, pos-rew, SEEK_SET);
			}
		}


		while (1) {
			char c;
			u32 len = (u32) strlen(parser->line_buffer);
			if (!len) break;
			c = parser->line_buffer[len-1];
			if (!strchr("\n\r\t", c)) break;
			parser->line_buffer[len-1] = 0;
		}


		parser->line_size = (u32) strlen(parser->line_buffer);
		parser->line_pos = 0;
		parser->line++;

		{
			u32 pos = (u32) gf_gztell(parser->gz_in);
			if (pos>=parser->file_pos) {
				parser->file_pos = pos;
				if (parser->line>1) gf_set_progress("BT Parsing", pos, parser->file_size);
			}
		}

		while ((parser->line_buffer[parser->line_pos]==' ') || (parser->line_buffer[parser->line_pos]=='\t'))
			parser->line_pos++;
		if ( (parser->line_buffer[parser->line_pos]=='#')
		        || ( (parser->line_buffer[parser->line_pos]=='/') && (parser->line_buffer[parser->line_pos+1]=='/')) ) {

			if (parser->line==1) {
				if (strstr(parser->line_buffer, "VRML")) {
					if (strstr(parser->line_buffer, "VRML V2.0")) parser->is_wrl = 1;
					/*although not std, many files use this*/
					else if (strstr(parser->line_buffer, "VRML2.0")) parser->is_wrl = 1;
					else {
						gf_bt_report(parser, GF_NOT_SUPPORTED, "%s: VRML Version Not Supported", parser->line_buffer);
						return;
					}
				}
				else if (strstr(parser->line_buffer, "X3D")) {
					if (strstr(parser->line_buffer, "X3D V3.0")) parser->is_wrl = 2;
					else {
						gf_bt_report(parser, GF_NOT_SUPPORTED, "%s: X3D Version Not Supported", parser->line_buffer);
						return;
					}
				}
			}
			if (!strnicmp(parser->line_buffer+parser->line_pos, "#define ", 8) && !parser->block_comment) {
				char *buf, *sep;
				parser->line_pos+=8;
				buf = parser->line_buffer+parser->line_pos;
				sep = strchr(buf, ' ');
				if (sep && (sep[1]!='\n') ) {
					BTDefSymbol *def;
					GF_SAFEALLOC(def, BTDefSymbol);
					if (!def) {
						GF_LOG(GF_LOG_ERROR, GF_LOG_PARSER, ("Fail to allocate DEF node\n"));
						return;
					}
					sep[0] = 0;
					def->name = gf_strdup(buf);
					sep[0] = ' ';
					buf = sep+1;
					while (strchr(" \t", buf[0])) buf++;
					def->value = gf_strdup(buf);
					gf_list_add(parser->def_symbols, def);
				}
			}
			else if (!strnicmp(parser->line_buffer+parser->line_pos, "#if ", 4)) {
				u32 len = 0;
				parser->line_pos+=4;
				while (1) {
					if (parser->line_pos+(s32)len==parser->line_size) break;
					if (strchr(" \n\t", parser->line_buffer[parser->line_pos+len]))
						break;
					len++;
				}
				if (len) {
					if (len==1) {
						if (!strnicmp(parser->line_buffer+parser->line_pos, "0", 1)) {
							parser->block_comment++;
						}
					} else {
						u32 i, count;
						char *keyWord = NULL;
						count = gf_list_count(parser->def_symbols);
						for (i=0; i<count; i++) {
							BTDefSymbol *def = (BTDefSymbol *)gf_list_get(parser->def_symbols, i);
							if (!strnicmp(parser->line_buffer+parser->line_pos, def->name, len)) {
								keyWord = def->value;
								break;
							}
						}
						if (keyWord && !strcmp(keyWord, "0")) {
							parser->block_comment++;
						}
					}
				}
			}
			else if (!strnicmp(parser->line_buffer+parser->line_pos, "#endif", 6)) {
				if (parser->block_comment) parser->block_comment--;
			}
			else if (!strnicmp(parser->line_buffer+parser->line_pos, "#else", 5)) {
				if (parser->block_comment)
					parser->block_comment--;
				else
					parser->block_comment++;
			}
			else if (!strnicmp(parser->line_buffer+parser->line_pos, "#size", 5)) {
				char *buf;
				parser->line_pos+=6;
				buf = parser->line_buffer+parser->line_pos;
				while (strchr(" \t", buf[0]))
					buf++;
				sscanf(buf, "%dx%d", &parser->def_w, &parser->def_h);
			}
			goto next_line;
		}

		if (parser->block_comment)
			goto next_line;

		/*brute-force replacement of defined symbols (!!FIXME - no mem checking done !!)*/
		if (parser->line_pos < parser->line_size) {
			u32 i, count;
			count = gf_list_count(parser->def_symbols);
			while (1) {
				Bool found = 0;
				for (i=0; i<count; i++) {
					u32 symb_len, val_len, copy_len;
					BTDefSymbol *def = (BTDefSymbol *)gf_list_get(parser->def_symbols, i);
					char *start = strstr(parser->line_buffer, def->name);
					if (!start) continue;
					symb_len = (u32) strlen(def->name);
					if (!strchr(" \n\r\t,[]{}\'\"", start[symb_len])) continue;
					val_len = (u32) strlen(def->value);
					copy_len = (u32) strlen(start + symb_len) + 1;
					memmove(start + val_len, start + symb_len, sizeof(char)*copy_len);
					memcpy(start, def->value, sizeof(char)*val_len);
					parser->line_size = (u32) strlen(parser->line_buffer);
					found = 1;
				}
				if (!found) break;
			}
		}
	}
	if (!parser->line_size) {
		if (!gf_gzeof(parser->gz_in))
			//avoid recursion
			goto reload_line;
		else
			parser->done = 1;
	}
	else if (!parser->done && (parser->line_size == parser->line_pos))
		//avoid recursion
		goto reload_line;
}

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline so the heap-buffer-overflow keeps its own stack frame (dc_batch requires the
 * target function name in the ASAN backtrace). */
__attribute__((noinline))
char *gf_bt_get_next(GF_BTParser *parser, Bool point_break)
{
	u32 has_quote;
	Bool go = 1;
	s32 i;
	gf_bt_check_line(parser);
	i=0;
	has_quote = 0;
	while (go) {
		if (parser->line_buffer[parser->line_pos + i] == '\"') {
			if (!has_quote) has_quote = 1;
			else has_quote = 0;
			parser->line_pos += 1;

			if (parser->line_pos+i==parser->line_size) break;
			continue;
		}
		if (!has_quote) {
			switch (parser->line_buffer[parser->line_pos + i]) {
			case 0:
			case ' ':
			case '\t':
			case '\r':
			case '\n':
			case '{':
			case '}':
			case ']':
			case '[':
			case ',':
				go = 0;
				break;
			case '.':
				if (point_break) go = 0;
				break;
			}
			if (!go) break;
		}
		parser->cur_buffer[i] = parser->line_buffer[parser->line_pos + i];
		i++;
		if (parser->line_pos+i==parser->line_size) break;
	}
	parser->cur_buffer[i] = 0;
	parser->line_pos += i;
	return parser->cur_buffer;
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
	if (argc < 2) return 0;
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) return 0;
	fseek(fp, 0, SEEK_END);
	long fsz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (fsz < 1) { fclose(fp); return 0; }

	unsigned char *filebuf = (unsigned char *) malloc((size_t) fsz);
	if (!filebuf) { fclose(fp); return 0; }
	size_t got = fread(filebuf, 1, (size_t) fsz, fp);
	fclose(fp);
	if (got < 2) { free(filebuf); return 0; }         /* need >=1 mode byte + >=1 content byte */

	unsigned char mode = filebuf[0];
	size_t content_len = got - 1;

	/* HEAP-allocate the attacker-controlled line buffer -- EXACTLY content_len bytes, so
	 * index content_len (one past the end) sits in ASAN's redzone. */
	char *line_buffer = (char *) malloc(content_len);
	if (!line_buffer) { free(filebuf); return 0; }
	memcpy(line_buffer, filebuf + 1, content_len);
	free(filebuf);

	GF_BTParser *parser = (GF_BTParser *) calloc(1, sizeof(GF_BTParser));
	if (!parser) { free(line_buffer); return 0; }

	parser->gz_in = NULL;               /* "create from string only" -- gf_bt_check_line's done=1 path */
	parser->line_buffer = line_buffer;
	parser->line_size = (s32) content_len;

	if (mode == 'T') {
		/* TRIGGER (CVE-2023-4778): the line is already fully "consumed" -- line_pos ==
		 * line_size. gf_bt_check_line leaves this untouched (see header comment), so
		 * gf_bt_get_next's first, unchecked read runs one byte past line_buffer. */
		parser->line_pos = (s32) content_len;
	} else {
		/* SAFE: normal in-bounds token scan starting at the beginning of the buffer. */
		parser->line_pos = 0;
	}

	/* volatile function pointer: forbid the compiler from proving the call away. */
	char *(* volatile fn)(GF_BTParser *, Bool) = gf_bt_get_next;
	char *tok = fn(parser, GF_FALSE);
	(void) tok;

	free(line_buffer);
	free(parser);
	return 0;
}
