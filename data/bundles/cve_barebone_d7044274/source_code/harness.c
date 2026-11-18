/* cve_barebone isolation harness for CVE-2020-19491 (sam2p / giflib DGifSlurp)
 *
 * Crash: SEGV / NULL-pointer dereference (CWE-476) at cgif.c:470 inside
 * AddExtensionBlock(), reached from DGifSlurp().  In DGifSlurp the extension
 * "continuation" loop calls  AddExtensionBlock(sp, ...)  while `sp` is still
 * NULL (no IMAGE_DESC record has been read yet), so `New->ExtensionBlocks`
 * dereferences a NULL SavedImage*.
 *
 * Everything below the "TARGET FUNCTION" banner is DGifSlurp pasted BYTE-FOR-BYTE
 * from data_cve/cve_d7044274/target/original_function.c.  The types and the
 * GIF-reader callees on the crash path are copied VERBATIM (real names) from the
 * sam2p source tree (cgif.h / cgif.c / in_gif.cpp).  The image-decoding path
 * (DGifGetImageDesc / DGifGetLine + the LZW machinery) is NOT on the crash path
 * and is provided as a minimal faithful stub; no crafted input reaches it.
 */
#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/* cgif.c compiles as C++ inside `class CGIF { ... }`; the CGIFFF macro expands
 * to `CGIF::` there.  In this plain-C isolation it expands to nothing, so the
 * verbatim function bodies (including the target) compile unchanged. */
#define CGIFFF
#define PTS_const const

/* ---- constants / #defines (from cgif.h) ---- */
#define GIF_ERROR 0
#define GIF_OK    1
#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

#define D_GIF_ERR_OPEN_FAILED    101
#define D_GIF_ERR_READ_FAILED    102
#define D_GIF_ERR_NOT_GIF_FILE   103
#define D_GIF_ERR_NO_SCRN_DSCR   104
#define D_GIF_ERR_NO_IMAG_DSCR   105
#define D_GIF_ERR_NO_COLOR_MAP   106
#define D_GIF_ERR_WRONG_RECORD   107
#define D_GIF_ERR_DATA_TOO_BIG   108
#define D_GIF_ERR_NOT_ENOUGH_MEM 109
#define D_GIF_ERR_CLOSE_FAILED   110
#define D_GIF_ERR_NOT_READABLE   111
#define D_GIF_ERR_IMAGE_DEFECT   112
#define D_GIF_ERR_EOF_TOO_SOON   113
#define D_GIF_ERR_EXT_TOO_SHORT  114

#define COMMENT_EXT_FUNC_CODE     0xfe
#define GRAPHICS_EXT_FUNC_CODE    0xf9
#define PLAINTEXT_EXT_FUNC_CODE   0x01
#define APPLICATION_EXT_FUNC_CODE 0xff

/* ---- typedefs / structs (verbatim vocabulary from cgif.h) ---- */
typedef int             GifBooleanType;
typedef unsigned char   GifPixelType;
typedef unsigned char * GifRowType;
typedef unsigned char   GifByteType;

typedef struct GifColorType {
    GifByteType Red, Green, Blue;
} GifColorType;

typedef struct ColorMapObject {
    int ColorCount;
    int BitsPerPixel;
    GifColorType *Colors;               /* on malloc(3) heap */
} ColorMapObject;

typedef struct GifImageDesc {
    int Left, Top, Width, Height,       /* Current image dimensions. */
        Interlace;                      /* Sequential/Interlaced lines. */
    ColorMapObject *ColorMap;           /* The local color map */
} GifImageDesc;

struct SavedImage;
typedef struct GifFileType {
    int SWidth, SHeight,                /* Screen dimensions. */
        SColorResolution,
        SBackGroundColor;
    ColorMapObject *SColorMap;          /* NULL if not exists. */
    int ImageCount;                     /* Number of current image */
    struct SavedImage *SavedImages;     /* Use this to accumulate file state */
    void *Private;                      /* Don't mess with this! */
} GifFileType;

typedef enum {
    UNDEFINED_RECORD_TYPE,
    SCREEN_DESC_RECORD_TYPE,
    IMAGE_DESC_RECORD_TYPE,             /* Begin with ',' */
    EXTENSION_RECORD_TYPE,              /* Begin with '!' */
    TERMINATE_RECORD_TYPE               /* Begin with ';' */
} GifRecordType;

/* This is the in-core version of an extension record */
typedef struct {
    int         code;
    int         ByteCount;
    GifByteType *Bytes;                 /* on malloc(3) heap */
} ExtensionBlock;

/* This holds an image header, its unpacked raster bits, and extensions */
typedef struct SavedImage {
    GifImageDesc        ImageDesc;
    GifPixelType        *RasterBits;    /* on malloc(3) heap */
    int                 ExtensionBlockCount;
    ExtensionBlock      *ExtensionBlocks;   /* on malloc(3) heap */
    unsigned char       dispose;
    unsigned short      delay;
    signed short        transp;
    unsigned short      iter;
} SavedImage;

/* ---- private reader state (verbatim from cgif.c) ---- */
#define LZ_MAX_CODE 4095
#define FILE_STATE_READ 0x01
#define IS_READABLE(Private) (!(Private->FileState & FILE_STATE_READ))
#define GIF_STAMP     "GIFVER"
#define GIF_STAMP_LEN (sizeof(GIF_STAMP) - 1)
#define GIF_VERSION_POS 3

typedef struct GifFilePrivateType {
    int FileState,
        BitsPerPixel,
        ClearCode,
        EOFCode,
        RunningCode,
        RunningBits,
        MaxCode1,
        LastCode,
        CrntCode,
        StackPtr,
        CrntShiftState;
    unsigned long CrntShiftDWord;
    unsigned long PixelCount;
    FILE *File;
    CGIFFF GifByteType Buf[256];
    CGIFFF GifByteType Stack[LZ_MAX_CODE];
    CGIFFF GifByteType Suffix[LZ_MAX_CODE+1];
    unsigned int Prefix[LZ_MAX_CODE+1];
} GifFilePrivateType;

int CGIFFF _GifError = 0;

/* ---- forward declarations ---- */
static void *xmalloc(size_t size);
static void *xrealloc(void *ptr, size_t size);
static int BitSize(int n);
CGIFFF ColorMapObject *CGIFFF MakeMapObject(int ColorCount, GifColorType *ColorMap);
void CGIFFF FreeMapObject(CGIFFF ColorMapObject *Object);
static int DGifGetWord(FILE *File, int *Word);
int CGIFFF DGifGetScreenDesc(CGIFFF GifFileType *GifFile);
CGIFFF GifFileType *CGIFFF DGifOpenFILE(void/*FILE*/ *f);
int CGIFFF DGifGetRecordType(CGIFFF GifFileType *GifFile, CGIFFF GifRecordType *Type);
int CGIFFF DGifGetImageDesc(CGIFFF GifFileType *GifFile);
int CGIFFF DGifGetLine(CGIFFF GifFileType *GifFile, CGIFFF GifPixelType *Line, int LineLen);
int CGIFFF DGifGetExtension(CGIFFF GifFileType *GifFile, int *ExtCode, CGIFFF GifByteType **Extension);
int CGIFFF DGifGetExtensionNext(CGIFFF GifFileType *GifFile, CGIFFF GifByteType **Extension);
int CGIFFF AddExtensionBlock(CGIFFF SavedImage *New, int Len, CGIFFF GifByteType ExtData[]);
int CGIFFF DGifSlurp(CGIFFF GifFileType *GifFile);

/* ---- allocation helpers (verbatim from in_gif.cpp; the C++ Error::sev OOM
 *      path is off the crash path and becomes abort() in this plain-C port) ---- */
static void *xmalloc(size_t size) {
  void *result = malloc(size + (size == 0));
  if (!result) { fprintf(stderr, "GIF: out of memory\n"); abort(); }
  return result;
}

static void *xrealloc(void *ptr, size_t size) {
  void *result = realloc(ptr, size + (size == 0));
  if (!result) { fprintf(stderr, "GIF: out of memory\n"); abort(); }
  return result;
}

/* ---- color-map + word helpers (verbatim from cgif.c) ---- */
static int BitSize(int n)
/* return smallest bitfield size n will fit in */
{
    register    int i;

    for (i = 1; i <= 8; i++)
        if ((1 << i) >= n)
            break;
    return(i);
}

CGIFFF ColorMapObject *CGIFFF MakeMapObject(int ColorCount, GifColorType *ColorMap)
{
    ColorMapObject *Object;

    if (ColorCount != (1 << BitSize(ColorCount)))
        return((ColorMapObject *)NULL);

    Object = (ColorMapObject *)xmalloc(sizeof(ColorMapObject));

    Object->Colors = (GifColorType *)xmalloc(ColorCount * sizeof(GifColorType));
    memset(Object->Colors, '\0', ColorCount * sizeof(GifColorType));

    Object->ColorCount = ColorCount;
    Object->BitsPerPixel = BitSize(ColorCount);

    if (ColorMap)
        memcpy((char *)Object->Colors,
               (char *)ColorMap, ColorCount * sizeof(GifColorType));

    return(Object);
}

void CGIFFF FreeMapObject(CGIFFF ColorMapObject *Object)
{
    free(Object->Colors);
    free(Object);
}

static int DGifGetWord(FILE *File, int *Word)
{
    unsigned char c[2];

    if (fread(c, 1, 2, File) != 2) {
        CGIFFF _GifError = D_GIF_ERR_READ_FAILED;
        return GIF_ERROR;
    }

    *Word = (((unsigned int) c[1]) << 8) + c[0];
    return GIF_OK;
}

/* ---- screen descriptor + open (verbatim from cgif.c) ---- */
int CGIFFF DGifGetScreenDesc(CGIFFF GifFileType *GifFile)
{
    int i, BitsPerPixel;
    GifByteType Buf[3];
    GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

    if (!IS_READABLE(Private)) {
        /* This file was NOT open for reading: */
        _GifError = D_GIF_ERR_NOT_READABLE;
        return GIF_ERROR;
    }

    /* Put the screen descriptor into the file: */
    if (DGifGetWord(Private->File, &GifFile->SWidth) == GIF_ERROR ||
        DGifGetWord(Private->File, &GifFile->SHeight) == GIF_ERROR)
        return GIF_ERROR;

    if (fread(Buf, 1, 3, Private->File) != 3) {
        _GifError = D_GIF_ERR_READ_FAILED;
        return GIF_ERROR;
    }
    GifFile->SColorResolution = (((Buf[0] & 0x70) + 1) >> 4) + 1;
    BitsPerPixel = (Buf[0] & 0x07) + 1;
    GifFile->SBackGroundColor = Buf[1];
    if (Buf[0] & 0x80) {                 /* Do we have global color map? */
        GifFile->SColorMap = MakeMapObject(1 << BitsPerPixel, NULL);

        /* Get the global color map: */
        for (i = 0; i < GifFile->SColorMap->ColorCount; i++) {
            if (fread(Buf, 1, 3, Private->File) != 3) {
                _GifError = D_GIF_ERR_READ_FAILED;
                return GIF_ERROR;
            }
            GifFile->SColorMap->Colors[i].Red = Buf[0];
            GifFile->SColorMap->Colors[i].Green = Buf[1];
            GifFile->SColorMap->Colors[i].Blue = Buf[2];
        }
    }

    return GIF_OK;
}

CGIFFF GifFileType *CGIFFF DGifOpenFILE(void/*FILE*/ *f) {
    char Buf[GIF_STAMP_LEN+1];
    GifFileType *GifFile;
    GifFilePrivateType *Private;
    GifFile = (GifFileType *) xmalloc(sizeof(GifFileType));

    memset(GifFile, '\0', sizeof(GifFileType));

    Private = (GifFilePrivateType *) xmalloc(sizeof(GifFilePrivateType));
    GifFile->Private = (void *) Private;
    Private->File = (FILE*)f;
    Private->FileState = 0;   /* Make sure bit 0 = 0 (File open for read). */

    /* Let's see if this is a GIF file: */
    if (fread(Buf, 1, GIF_STAMP_LEN, Private->File) != GIF_STAMP_LEN) {
        _GifError = D_GIF_ERR_READ_FAILED;
        free((char *) Private);
        free((char *) GifFile);
        return NULL;
    }

    Buf[GIF_STAMP_LEN] = 0;
    if (strncmp(GIF_STAMP, Buf, GIF_VERSION_POS) != 0) {
        _GifError = D_GIF_ERR_NOT_GIF_FILE;
        free((char *) Private);
        free((char *) GifFile);
        return NULL;
    }

    if (DGifGetScreenDesc(GifFile) == GIF_ERROR) {
        free((char *) Private);
        free((char *) GifFile);
        return NULL;
    }

    _GifError = 0;

    return GifFile;
}

/* ---- record + extension readers on the crash path (verbatim from cgif.c) ---- */
int CGIFFF DGifGetRecordType(CGIFFF GifFileType *GifFile, CGIFFF GifRecordType *Type)
{
    GifByteType Buf;
    GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

    if (!IS_READABLE(Private)) {
        /* This file was NOT open for reading: */
        _GifError = D_GIF_ERR_NOT_READABLE;
        return GIF_ERROR;
    }

    if (fread(&Buf, 1, 1, Private->File) != 1) {
        _GifError = D_GIF_ERR_READ_FAILED;
        return GIF_ERROR;
    }

    switch (Buf) {
        case ',': *Type = IMAGE_DESC_RECORD_TYPE; break;
        case '!': *Type = EXTENSION_RECORD_TYPE;  break;
        case ';': *Type = TERMINATE_RECORD_TYPE;  break;
        default:  *Type = UNDEFINED_RECORD_TYPE;
            _GifError = D_GIF_ERR_WRONG_RECORD;
            return GIF_ERROR;
    }

    return GIF_OK;
}

int CGIFFF DGifGetExtension(CGIFFF GifFileType *GifFile, int *ExtCode,
                                            CGIFFF GifByteType **Extension)
{
    GifByteType Buf;
    GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;


    if (!IS_READABLE(Private)) {
        /* This file was NOT open for reading: */
        _GifError = D_GIF_ERR_NOT_READABLE;
        return GIF_ERROR;
    }

    if (fread(&Buf, 1, 1, Private->File) != 1) {
        _GifError = D_GIF_ERR_READ_FAILED;
        return GIF_ERROR;
    }
    *ExtCode = Buf;

    return DGifGetExtensionNext(GifFile, Extension);
}

int CGIFFF DGifGetExtensionNext(CGIFFF GifFileType *GifFile, CGIFFF GifByteType **Extension)
{
    GifByteType Buf;
    GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

    if (fread(&Buf, 1, 1, Private->File) != 1) {
        _GifError = D_GIF_ERR_READ_FAILED;
        return GIF_ERROR;
    }
    if (Buf > 0) {
        *Extension = Private->Buf;           /* Use private unused buffer. */
        (*Extension)[0] = Buf;  /* Pascal strings notation (pos. 0 is len.). */
        if (fread(&((*Extension)[1]), 1, Buf, Private->File) != Buf) {
            _GifError = D_GIF_ERR_READ_FAILED;
            return GIF_ERROR;
        }
    }
    else
        *Extension = NULL;

    return GIF_OK;
}

/* ---- crash site: verbatim from cgif.c:466 (line 470 derefs New==NULL) ---- */
int CGIFFF AddExtensionBlock(CGIFFF SavedImage *New, int Len, CGIFFF GifByteType ExtData[])
{
    ExtensionBlock      *ep;

    if (New->ExtensionBlocks == NULL)
        New->ExtensionBlocks = (ExtensionBlock *)xmalloc(sizeof(ExtensionBlock));
    else
        New->ExtensionBlocks =
            (ExtensionBlock *)xrealloc(New->ExtensionBlocks,
                      sizeof(ExtensionBlock) * (New->ExtensionBlockCount + 1));

    if (New->ExtensionBlocks == NULL)
        return(GIF_ERROR);

    ep = &New->ExtensionBlocks[New->ExtensionBlockCount++];

    ep->Bytes = (GifByteType *)xmalloc(ep->ByteCount = Len);

    if (ExtData)
        memcpy(ep->Bytes, ExtData, Len);

    return(GIF_OK);
}

/* ---- image-decode path: NOT on the crash path.  Minimal faithful stubs so the
 *      TU links; no crafted input contains a ',' IMAGE_DESC record, so these are
 *      never executed. ---- */
int CGIFFF DGifGetImageDesc(CGIFFF GifFileType *GifFile)
{
    (void)GifFile;
    _GifError = D_GIF_ERR_NO_IMAG_DSCR;
    return GIF_ERROR;
}

int CGIFFF DGifGetLine(CGIFFF GifFileType *GifFile, CGIFFF GifPixelType *Line, int LineLen)
{
    (void)GifFile; (void)Line; (void)LineLen;
    _GifError = D_GIF_ERR_READ_FAILED;
    return GIF_ERROR;
}

/* ============================ TARGET FUNCTION ============================ */
/* The following DGifSlurp is pasted BYTE-FOR-BYTE from
 * data_cve/cve_d7044274/target/original_function.c -- do not edit. */
int CGIFFF DGifSlurp(CGIFFF GifFileType *GifFile)
{
    static unsigned InterlacedOffset[] = { 0, 4, 2, 1 }, /* The way Interlaced image should. */
                    InterlacedJumps[] = { 8, 8, 4, 2 };  /* be read - offsets and jumps... */
    /**** pts: unused vars ****/
    /* int i, j, Error, ImageSize; */
    int ext_code;

    GifRecordType RecordType;
    /**** pts ****/
    SavedImage *sp=0; /**** pts: avoid gcc warning */
    /** Extension info of next SavedImage */
    SavedImage ext;
    /** No-extension info */
    SavedImage noext;

    GifByteType *ExtData;

    /**** pts ****/
    memset(&noext, 0, sizeof(noext));
    noext.delay=0;
    noext.dispose=0;
    noext.iter=1;
    noext.transp=(-1);
    noext.ExtensionBlocks=NULL;
    noext.ExtensionBlockCount=0;
    ext=noext;

    /**** pts ****/
    GifFile->SavedImages=0;

    do {
	if (DGifGetRecordType(GifFile, &RecordType) == GIF_ERROR)
	    return(GIF_ERROR);

	switch (RecordType) {
	    case IMAGE_DESC_RECORD_TYPE:
		if (DGifGetImageDesc(GifFile) == GIF_ERROR)
		    return(GIF_ERROR);

                /**** pts: DGifGetImageDesc has already allocated the mem ****/
		sp = &GifFile->SavedImages[GifFile->ImageCount-1];
		/**** pts: apply extensions to the image just read */
		ext.RasterBits=sp->RasterBits;
		ext.ImageDesc=sp->ImageDesc;
		*sp=ext;
		ext=noext;

		/**** pts ****/
		sp->RasterBits = (GifPixelType*) xmalloc((0L+sp->ImageDesc.Width) * sp->ImageDesc.Height * sizeof(GifPixelType));
		if (sp->ImageDesc.Interlace) {
		  unsigned i, j, Height=sp->ImageDesc.Height, Width=sp->ImageDesc.Width;
		  /* Need to perform 4 passes on the images: */
 		  for (i = 0; i < 4; i++)
		    for (j = InterlacedOffset[i]; j < Height; j += InterlacedJumps[i])
		      if (DGifGetLine(GifFile, sp->RasterBits+Width*j, Width) != GIF_OK) return GIF_ERROR;
		} else {
		  if (DGifGetLine(GifFile, sp->RasterBits, (0L+sp->ImageDesc.Width) * sp->ImageDesc.Height)
		      == GIF_ERROR)
		      return(GIF_ERROR);
		}
		break;

	    case EXTENSION_RECORD_TYPE:

		if (DGifGetExtension(GifFile,&ext_code,&ExtData)==GIF_ERROR)
		    return(GIF_ERROR);
		if (ExtData!=NULL) {
		    #if 0 /**** pts ****/
		      ep = &ext.ExtensionBlocks[ext.ExtensionBlockCount++];
		      ep->ByteCount = ExtData[0];
		      ep->Bytes = (GifByteType *)xmalloc(ep->ByteCount * sizeof(GifByteType));
		      memcpy(ep->Bytes, ExtData, ep->ByteCount * sizeof(char));
		    #else
                      /**** pts ****/
                      if (0xf9==(unsigned char)(ext_code)) {
                        if (ExtData[0] < 4) { ext_too_short:
                          _GifError = D_GIF_ERR_EXT_TOO_SHORT;
                          return GIF_ERROR;
                        }
                        ext.dispose=ExtData[1]>>2;
                        ext.delay=(ExtData[3] << 8) | ExtData[2];
                        if ((ExtData[1] & 0x01) == 1) {
                          if (ExtData[0] < 5) goto ext_too_short;
                          ext.transp=ExtData[4];
                        }
                      } else if (0xff==(unsigned char)(ext_code)) {
                        if (ExtData[0] < 4) goto ext_too_short;
                        ext.iter=(ExtData[3] << 8) | ExtData[2];
                      } else {
                        AddExtensionBlock(&ext, ExtData[0], ExtData+1);
                        ext.ExtensionBlocks[ext.ExtensionBlockCount-1].code=ext_code;
                      }
		    #endif
		    while (1) {
		        if (DGifGetExtensionNext(GifFile, &ExtData) == GIF_ERROR)
			  return(GIF_ERROR);
		        #if 0 /**** pts ****/
  			  ep = &ext.ExtensionBlocks[ext.ExtensionBlockCount++];
  			  ep->ByteCount = ExtData[0];
			  ep->Bytes = (GifByteType *)xmalloc(ep->ByteCount * sizeof(GifByteType));
  			  memcpy(ep->Bytes,ExtData,ep->ByteCount * sizeof(char));
  			#else
  			  if (ExtData==NULL) break;
  			  AddExtensionBlock(sp, ExtData[0], ExtData+1);
  			#endif
		    }
		}
		break;

	    case TERMINATE_RECORD_TYPE:
		break;

	    default:	/* Should be trapped by DGifGetRecordType */
		break;
	}
    }
    while
	(RecordType != TERMINATE_RECORD_TYPE);

    return(GIF_OK);
}
/* ============================ DRIVER ============================ */
/* Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded), wraps it in a real
 * FILE* via fmemopen, then drives the genuine reader exactly as sam2p's
 * in_gif_reader does: DGifOpenFILE (reads the "GIF8xa" stamp + screen
 * descriptor) followed by DGifSlurp.  A GIF whose first record is an extension
 * with a continuation sub-block (before any image descriptor) drives DGifSlurp
 * into AddExtensionBlock(sp=NULL) -> NULL deref (CWE-476). */
int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 2;
    }

    FILE *inf = fopen(argv[1], "rb");
    if (!inf) { perror("fopen"); return 2; }
    if (fseek(inf, 0, SEEK_END) != 0) { fclose(inf); return 2; }
    long sz = ftell(inf);
    if (sz < 0) { fclose(inf); return 2; }
    if (fseek(inf, 0, SEEK_SET) != 0) { fclose(inf); return 2; }

    /* HEAP-allocate the input so any over-read/over-write is ASAN-visible. */
    unsigned char *buf = (unsigned char *)malloc((size_t)sz + 1);
    if (!buf) { fclose(inf); return 2; }
    size_t got = fread(buf, 1, (size_t)sz, inf);
    fclose(inf);

    /* A real stdio stream backed by the heap buffer -> the reader's fread()s
     * consume it exactly like a file on disk. */
    FILE *mf = fmemopen(buf, got, "rb");
    if (!mf) { free(buf); return 2; }

    GifFileType *giff = DGifOpenFILE((void *)mf);
    if (giff != NULL) {
        DGifSlurp(giff);            /* <-- crash lands here for triggering inputs */
    }

    fclose(mf);
    free(buf);
    return 0;
}
