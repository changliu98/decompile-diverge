/* cve_barebone direct-call harness for CVE-2023-4682 (gpac)
 * Target: AVI_read_audio  (src/media_tools/avilib.c)
 * Bug class: heap-based buffer overflow (OSV CWE-122; the concrete manifestation
 *   reproduced here is a heap-buffer-overflow WRITE, CWE-787).
 *
 * Root cause in AVI_read_audio's own body (no fix-diff bounds check exists
 * anywhere upstream of this function -- callers just pass whatever `audio_posb`/
 * index state the AVI parser has accumulated):
 *
 *   int left = (int) (AVI->track[AVI->aptr].audio_index[...].len - AVI->track[AVI->aptr].audio_posb);
 *   ...
 *   if (bytes<left) todo = bytes; else todo = left;
 *   ...
 *   avi_read(AVI->fdes, audbuf+nr, todo)          // avi_read's `len` param is u32
 *
 * `len` (u64) and `audio_posb` (int) are subtracted in u64 arithmetic; when
 * audio_posb > len the u64 result wraps to a huge value, and the `(int)` cast
 * truncates it back to a small NEGATIVE `left`. Since `bytes` (positive) is never
 * `< left` (negative), `todo` is assigned that same negative int. Passed into
 * avi_read()'s `u32 len` parameter, the negative `todo` becomes a ~4-billion-byte
 * unsigned length, so `gf_fread(audbuf+nr, len-r, fd)` (== libc fread) is asked to
 * fill `audbuf` far past its allocated size -- ASAN's fread interceptor flags the
 * out-of-bounds WRITE range against the destination heap buffer.
 *
 * This is reachable purely by direct-call state (audio_posb/len/audio_index are
 * ordinary struct fields we set up here); no elaborate parser state is needed.
 *
 * The vulnerable function only touches primitive/struct fields plus the local
 * static helper avi_read() (copied verbatim, itself calling gf_fseek/gf_fread) and
 * the GF_LOG error-log macro. gf_fseek/gf_fread are gpac's generic file-I/O
 * wrappers (their real bodies dispatch on a GF_FileIO virtualization we never
 * construct here); for a plain FILE* they reduce to fseeko64()/fread(), so a thin
 * faithful stub reproduces their real behaviour for our case. GF_LOG is stubbed
 * as a no-op (real macro just logs; irrelevant to the bug and never reached before
 * the ASAN abort fires inside avi_read's fread call on triggering inputs).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ==== real gpac primitive typedefs (include/gpac/setup.h, GPAC_CONFIG_LINUX arm) ==== */
typedef uint64_t u64;
typedef int64_t s64;
typedef uint32_t u32;
typedef int32_t s32;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint8_t u8;
typedef int8_t s8;

/* ==== real struct/typedefs AVI_read_audio needs, copied verbatim from
 * include/gpac/internal/avilib.h (names/fields unchanged) ==== */
#define AVI_MAX_TRACKS 8

typedef struct
{
	u64 key;
	u64 pos;
	u64 len;
} video_index_entry;

typedef struct
{
	u64 pos;
	u64 len;
	u64 tot;
} audio_index_entry;

typedef struct _avisuperindex_entry {
	u64 qwOffset;           // absolute file offset
	u32 dwSize;                  // size of index chunk at this offset
	u32 dwDuration;              // time span in stream ticks
} avisuperindex_entry;

typedef struct _avistdindex_entry {
	u32 dwOffset;                // qwBaseOffset + this is absolute file offset
	u32 dwSize;                  // bit 31 is set if this is NOT a keyframe
} avistdindex_entry;

typedef struct _avistdindex_chunk {
	char           fcc[4];                 // ix##
	u32 dwSize;                 // size of this chunk
	u16 wLongsPerEntry;         // must be sizeof(aIndex[0])/sizeof(DWORD)
	u8  bIndexSubType;          // must be 0
	u8  bIndexType;             // must be AVI_INDEX_OF_CHUNKS
	u32  nEntriesInUse;          //
	char           dwChunkId[4];           // '##dc' or '##db' or '##wb' etc..
	u64 qwBaseOffset;       // all dwOffsets in aIndex array are relative to this
	u32  dwReserved3;            // must be 0
	avistdindex_entry *aIndex;
} avistdindex_chunk;

typedef struct _avisuperindex_chunk {
	char           fcc[4];
	u32  dwSize;                 // size of this chunk
	u16 wLongsPerEntry;         // size of each entry in aIndex array (must be 8 for us)
	u8  bIndexSubType;          // future use. must be 0
	u8 bIndexType;             // one of AVI_INDEX_* codes
	u32 nEntriesInUse;          // index of first unused member in aIndex array
	char           dwChunkId[4];           // fcc of what is indexed
	u32 dwReserved[3];          // meaning differs for each index type/subtype.
	avisuperindex_entry *aIndex;           // where are the ix## chunks
	avistdindex_chunk **stdindex;          // the ix## chunks itself (array)
} avisuperindex_chunk;

typedef struct track_s
{
	int   a_fmt;             /* Audio format, see #defines below */
	int   a_chans;           /* Audio channels, 0 for no audio */
	int   a_rate;            /* Rate in Hz */
	int   a_bits;            /* bits per audio sample */
	int   mp3rate;           /* mp3 bitrate kbs*/
	int   a_vbr;             /* 0 == no Variable BitRate */
	int   padrate;	      /* byte rate used for zero padding */

	int   audio_strn;        /* Audio stream number */
	u64  audio_bytes;       /* Total number of bytes of audio data */
	int   audio_chunks;      /* Chunks of audio data in the file */

	char   audio_tag[4];      /* Tag of audio data */
	int   audio_posc;        /* Audio position: chunk */
	int   audio_posb;        /* Audio position: byte within chunk */

	u64  a_codech_off;       /* absolut offset of audio codec information */
	u64  a_codecf_off;       /* absolut offset of audio codec information */

	audio_index_entry *audio_index;
	avisuperindex_chunk *audio_superindex;

} track_t;

typedef struct
{
	u32  bi_size;
	u32  bi_width;
	u32  bi_height;
	u16  bi_planes;
	u16  bi_bit_count;
	u32  bi_compression;
	u32  bi_size_image;
	u32  bi_x_pels_per_meter;
	u32  bi_y_pels_per_meter;
	u32  bi_clr_used;
	u32  bi_clr_important;
} alBITMAPINFOHEADER;

typedef struct
{
	u16  w_format_tag;
	u16  n_channels;
	u32  n_samples_per_sec;
	u32  n_avg_bytes_per_sec;
	u16  n_block_align;
	u16  w_bits_per_sample;
	u16  cb_size;
} alWAVEFORMATEX;

typedef struct
{
	u32 fcc_type;
	u32 fcc_handler;
	u32 dw_flags;
	u32 dw_caps;
	u16 w_priority;
	u16 w_language;
	u32 dw_scale;
	u32 dw_rate;
	u32 dw_start;
	u32 dw_length;
	u32 dw_initial_frames;
	u32 dw_suggested_buffer_size;
	u32 dw_quality;
	u32 dw_sample_size;
	u16 dw_left;
	u16 dw_top;
	u16 dw_right;
	u16 dw_bottom;
} alAVISTREAMHEADER;

typedef struct
{
	FILE *fdes;              /* File descriptor of AVI file */
	int   mode;              /* 0 for reading, 1 for writing */

	int   width;             /* Width  of a video frame */
	int   height;            /* Height of a video frame */
	double fps;               /* Frames per second */
	char   compressor[8];     /* Type of compressor, 4 bytes + padding for 0 byte */
	char   compressor2[8];     /* Type of compressor, 4 bytes + padding for 0 byte */
	u32   video_strn;        /* Video stream number */
	int   video_frames;      /* Number of video frames */
	char   video_tag[4];      /* Tag of video data */
	int   video_pos;         /* Number of next frame to be read
			       (if index present) */
	alAVISTREAMHEADER video_stream_header;

	u32 max_len;    /* maximum video chunk present */

	track_t track[AVI_MAX_TRACKS];  // up to AVI_MAX_TRACKS audio tracks supported

	s64  pos;               /* position in file */
	int   n_idx;             /* number of index entries actually filled */
	int   max_idx;           /* number of index entries actually allocated */

	s64  v_codech_off;      /* absolut offset of video codec (strh) info */
	s64  v_codecf_off;      /* absolut offset of video codec (strf) info */

	u8 (*idx)[16]; /* index entries (AVI idx1 tag) */

	video_index_entry *video_index;
	avisuperindex_chunk *video_superindex;  /* index of indices */
	int is_opendml;           /* set to 1 if this is an odml file with multiple index chunks */

	s64  last_pos;          /* Position of last frame written */
	u32 last_len;   /* Length of last frame written */
	int must_use_index;       /* Flag if frames are duplicated */
	s64  movi_start;
	int total_frames;         /* total number of frames if dmlh is present */

	u32 anum;            // total number of audio tracks
	u32 aptr;            // current audio working track
	char *index_file;    // read the avi index from this file

	alBITMAPINFOHEADER *bitmap_info_header;
	alWAVEFORMATEX *wave_format_ex[AVI_MAX_TRACKS];
	alAVISTREAMHEADER stream_headers[AVI_MAX_TRACKS];

	void*		extradata;
	unsigned int extradata_size;

	// add a new riff chunk after this amount of bytes
	u64 new_riff_threshold;
} avi_t;

#define AVI_MODE_WRITE  0
#define AVI_MODE_READ   1

#define AVI_ERR_READ         3     /* Error reading from AVI File */
#define AVI_ERR_NOT_PERM     7     /* Operation not permitted:
                                      trying to read from a file open
                                      for writing or vice versa */
#define AVI_ERR_NO_IDX      13     /* The file has been opened with
                                      getIndex==0, but an operation has been
                                      performed that needs an index */

/* real global, avilib.c:48 */
int AVI_errno = 0;

/* Minimal faithful stub for gpac's generic file-I/O wrappers (their real bodies
 * first dispatch through a GF_FileIO virtualization layer we never construct
 * here; for a plain FILE*, as used exclusively by this harness, they reduce
 * exactly to fseeko64()/fread() -- see src/utils/os_file.c gf_fseek/gf_fread). */
static s32 gf_fseek(FILE *fp, s64 offset, s32 whence)
{
	if (!fp) return -1;
	return (s32) fseeko64(fp, (off64_t) offset, whence);
}
static size_t gf_fread(void *ptr, size_t nbytes, FILE *stream)
{
	return fread(ptr, 1, nbytes, stream);
}

/* Faithful no-op stub for the incidental error-logging macro (GF_LOG expands to
 * a conditional gf_log_lt()/gf_log() call in the real tree; it has no effect on
 * control flow or data, and on triggering inputs ASAN aborts inside avi_read's
 * fread before this line would ever run). */
#define GF_LOG_ERROR 1
#define GF_LOG_CONTAINER 1
#define GF_LOG(_ll, _lm, __args) do { } while (0)

/* ==== VERBATIM from src/media_tools/avilib.c:62 (avi_read is a direct callee
 * on AVI_read_audio's crash path) ==== */
static u32 avi_read(FILE *fd, char *buf, u32 len)
{
	u32 r = 0;

	while (r < len) {
		s32 n = (s32) gf_fread(buf + r, len - r, fd);
		if (n == 0) break;
		if (n < 0) return r;
		r += n;
	}

	return r;
}

/* ==== VERBATIM from data_cve/cve_0e6b472a/target/original_function.c ==== */
int AVI_read_audio(avi_t *AVI, u8 *audbuf, int bytes, int *continuous)
{
	int nr, todo;
	s64 pos;

	if(AVI->mode==AVI_MODE_WRITE) {
		AVI_errno = AVI_ERR_NOT_PERM;
		return -1;
	}
	if(!AVI->track[AVI->aptr].audio_index)         {
		AVI_errno = AVI_ERR_NO_IDX;
		return -1;
	}

	nr = 0; /* total number of bytes read */

	if (bytes==0) {
		AVI->track[AVI->aptr].audio_posc++;
		AVI->track[AVI->aptr].audio_posb = 0;
	}

	*continuous = 1;
	while(bytes>0)
	{
		s64 ret;
		int left = (int) (AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].len - AVI->track[AVI->aptr].audio_posb);
		if(left==0)
		{
			if(AVI->track[AVI->aptr].audio_posc>=AVI->track[AVI->aptr].audio_chunks-1) return nr;
			AVI->track[AVI->aptr].audio_posc++;
			AVI->track[AVI->aptr].audio_posb = 0;
			*continuous = 0;
			continue;
		}
		if(bytes<left)
			todo = bytes;
		else
			todo = left;
		pos = AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].pos + AVI->track[AVI->aptr].audio_posb;
		gf_fseek(AVI->fdes, pos, SEEK_SET);
		if ( (ret = avi_read(AVI->fdes,audbuf+nr,todo)) != todo)
		{
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[avilib] XXX pos = %"LLD", ret = %"LLD", todo = %ld\n", pos, ret, todo));
			AVI_errno = AVI_ERR_READ;
			return -1;
		}
		bytes -= todo;
		nr    += todo;
		AVI->track[AVI->aptr].audio_posb += todo;
	}

	return nr;
}
/* ==== end verbatim ==== */

/* AUDBUF_SIZE is the caller-side output buffer AVI_read_audio is asked to fill
 * with exactly `bytes` (== AUDBUF_SIZE) bytes -- ordinary, correctly-sized real
 * usage (see e.g. gpac's avi2rgb/mux code: audbuf is sized to `bytes`). */
#define AUDBUF_SIZE 16

int main(int argc, char **argv)
{
	if (argc < 2) return 0;
	FILE *cfg = fopen(argv[1], "rb");
	if (!cfg) return 0;
	unsigned char ctl = 0;
	if (fread(&ctl, 1, 1, cfg) != 1) ctl = 0;
	fclose(cfg);

	/* AVI->fdes reads real bytes from the SAME input file argv[1] -- attacker-
	 * controlled data, exactly as the real AVI parser would hand AVI_read_audio
	 * a FILE* positioned inside the caller's own AVI stream. */
	FILE *fdes = fopen(argv[1], "rb");
	if (!fdes) return 0;

	avi_t AVI;
	memset(&AVI, 0, sizeof(AVI));
	AVI.fdes = fdes;
	AVI.mode = AVI_MODE_READ;
	AVI.aptr = 0;

	audio_index_entry idx[1];
	memset(idx, 0, sizeof(idx));
	idx[0].pos = 0;

	AVI.track[0].audio_index = idx;
	AVI.track[0].audio_posc = 0;
	AVI.track[0].audio_chunks = 1;

	u8 *audbuf = (u8 *) malloc(AUDBUF_SIZE);
	if (!audbuf) { fclose(fdes); return 0; }
	int continuous = 0;

	if (ctl == 0) {
		/* SAFE: left==0 config -> AVI_read_audio takes the "advance chunk"
		 * branch; since audio_posc(0) >= audio_chunks-1(0) it returns
		 * immediately with nr=0. No I/O, no crash. */
		idx[0].len = 0;
		AVI.track[0].audio_posb = 0;
	} else if (ctl == 1) {
		/* SAFE: normal bounded read. len is fixed to exactly AUDBUF_SIZE
		 * (not derived from file size), so todo==AUDBUF_SIZE always -- the
		 * read can never write past audbuf regardless of how much real
		 * data the file actually has (a short file just yields a clean
		 * AVI_ERR_READ error return, still no OOB access). */
		idx[0].len = AUDBUF_SIZE;
		AVI.track[0].audio_posb = 0;
	} else {
		/* TRIGGERING: audio_posb (ctl, 2..255) > len (0) makes `left`
		 * wrap-then-truncate to a small negative int; `todo` inherits
		 * that negative value and becomes a ~4-billion-byte unsigned
		 * length inside avi_read()/gf_fread() -- ASAN's fread interceptor
		 * flags the destination range against the 16-byte audbuf heap
		 * allocation as an out-of-bounds WRITE before any real I/O runs. */
		idx[0].len = 0;
		AVI.track[0].audio_posb = (int) ctl;
	}

	int r = AVI_read_audio(&AVI, audbuf, AUDBUF_SIZE, &continuous);
	(void) r;

	free(audbuf);
	fclose(fdes);
	return 0;
}
