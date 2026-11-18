/*
 * cve_barebone direct-call harness for CVE-2022-1534 (libmobi)
 * target: mobi_reconstruct_infl  (src/parse_rawml.c)  CWE-125 heap OOB READ
 *
 * The real bug (fix commit fb1ab50e448ddbed746fd27ae07469bc506d838b): while
 * walking an inflection group's INDX_TAGARR_INFL_PARTS_V2 tag array
 * (`parts[]`), the function does
 *
 *     unsigned char *rule = (unsigned char *) infl->entries[parts[j]].label;
 *
 * using the attacker-controlled `parts[j]` value directly as an index into
 * the heap array `infl->entries[]` (size `infl->entries_count`) with NO
 * bounds check -- unlike the sibling loop variable `offset` a few lines
 * above, which IS checked against `infl->entries_count`. The fix adds
 * `if (parts[j] >= infl->entries_count) return MOBI_DATA_CORRUPT;`
 * immediately before the dereference.
 *
 * This harness embeds the REAL libmobi type vocabulary (struct/typedef/
 * #define names copied verbatim from src/mobi.h, src/index.h, src/buffer.c,
 * src/index.c) and the target function BYTE-FOR-BYTE from
 * data_cve/cve_12339d8e/target/original_function.c, then drives it in
 * isolation: it builds a minimal, hand-constructed MOBIIndx / MOBIIndexEntry
 * object graph (an "infl" index with N entries, and an "orth" entry pointing
 * at one inflection group inside it) directly in memory -- no MOBI file
 * parsing involved, matching how mobi_reconstruct_infl is actually called
 * from mobi_parse_rawml() after the INDX records have already been decoded.
 * FDP-style bytes from a HEAP input buffer decide: how many entries the
 * "infl" index has, and whether the crafted INFL_PARTS_V2 tag value for the
 * one inflection group is IN-BOUNDS (SAFE) or lands at/beyond
 * infl->entries_count (TRIGGER -> heap-buffer-overflow READ inside
 * mobi_reconstruct_infl's own body, on the `.label` field read).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ===================================================================== */
/* ==== real libmobi type vocabulary (verbatim names/fields) ==== */
/* ===================================================================== */

/* src/mobi.h:59-77 */
typedef enum {
    MOBI_SUCCESS = 0,
    MOBI_ERROR = 1,
    MOBI_PARAM_ERR = 2,
    MOBI_DATA_CORRUPT = 3,
    MOBI_FILE_NOT_FOUND = 4,
    MOBI_FILE_ENCRYPTED = 5,
    MOBI_FILE_UNSUPPORTED = 6,
    MOBI_MALLOC_FAILED = 7,
    MOBI_INIT_FAILED = 8,
    MOBI_BUFFER_END = 9,
    MOBI_XML_ERR = 10,
    MOBI_DRM_PIDINV = 11,
    MOBI_DRM_KEYNOTFOUND = 12,
    MOBI_DRM_UNSUPPORTED = 13,
    MOBI_WRITE_FAILED = 14,
    MOBI_DRM_EXPIRED = 15,
    MOBI_DRM_RANDOM_ERR = 16
} MOBI_RET;

/* src/mobi.h:215-219 */
typedef enum {
    MOBI_CP1252 = 1252,
    MOBI_UTF8 = 65001,
    MOBI_UTF16 = 65002,
} MOBIEncoding;

/* src/mobi.h:251-258 */
typedef struct MOBIPdbRecord {
    uint32_t offset;
    size_t size;
    uint8_t attributes;
    uint32_t uid;
    unsigned char *data;
    struct MOBIPdbRecord *next;
} MOBIPdbRecord;

/* src/mobi.h:416-420 */
typedef struct {
    size_t tagid;
    size_t tagvalues_count;
    uint32_t *tagvalues;
} MOBIIndexTag;

/* src/mobi.h:425-429 */
typedef struct {
    char *label;
    size_t tags_count;
    MOBIIndexTag *tags;
} MOBIIndexEntry;

/* src/mobi.h:434-446 */
typedef struct {
    size_t type;
    size_t entries_count;
    MOBIEncoding encoding;
    size_t total_entries_count;
    size_t ordt_offset;
    size_t ligt_offset;
    size_t ligt_entries_count;
    size_t cncx_records_count;
    MOBIPdbRecord *cncx_record;
    MOBIIndexEntry *entries;
    char *orth_index_name;
} MOBIIndx;

/* src/buffer.h:19-25 */
typedef struct {
    size_t offset;
    size_t maxlen;
    unsigned char *data;
    MOBI_RET error;
} MOBIBuffer;

/* src/index.h:47-56 */
#define INDX_TAGARR_ORTH_INFL 42
#define INDX_TAGARR_INFL_GROUPS 5
#define INDX_TAGARR_INFL_PARTS_V2 26
#define INDX_INFLTAG_SIZEMAX 25000
#define INDX_INFLBUF_SIZEMAX 500

/* src/debug.h (MOBI_DEBUG=0 default build -> no-op) */
#define debug_print(fmt, ...) ((void) 0)

/* ===================================================================== */
/* ==== real callees on/near the crash path, copied verbatim ==== */
/* ===================================================================== */

/* src/buffer.c:249-280 (static helper used by mobi_buffer_get_varlen) */
static uint32_t mobi_buffer_get_varlen_internal(MOBIBuffer *buf, size_t *len, const int direction) {
    uint32_t val = 0;
    uint8_t byte_count = 0;
    uint8_t byte;
    const uint8_t stop_flag = 0x80;
    const uint8_t mask = 0x7f;
    uint32_t shift = 0;
    do {
        if (direction == 1) {
            if (buf->offset + 1 > buf->maxlen) {
                debug_print("%s", "End of buffer\n");
                buf->error = MOBI_BUFFER_END;
                return val;
            }
            byte = buf->data[buf->offset++];
            val <<= 7;
            val |= (byte & mask);
        } else {
            if (buf->offset < 1) {
                debug_print("%s", "End of buffer\n");
                buf->error = MOBI_BUFFER_END;
                return val;
            }
            byte = buf->data[buf->offset--];
            val = val | (uint32_t)(byte & mask) << shift;
            shift += 7;
        }
        (*len)++;
        byte_count++;
    } while (!(byte & stop_flag) && (byte_count < 4));
    return val;
}

/* src/buffer.c:291-293 */
uint32_t mobi_buffer_get_varlen(MOBIBuffer *buf, size_t *len) {
    return mobi_buffer_get_varlen_internal(buf, len, 1);
}

/* src/buffer.c:315-329 */
void mobi_buffer_getstring(char *str, MOBIBuffer *buf, const size_t len) {
    if (!str) {
        buf->error = MOBI_PARAM_ERR;
        return;
    }
    if (buf->offset + len > buf->maxlen) {
        debug_print("%s", "End of buffer\n");
        buf->error = MOBI_BUFFER_END;
        str[0] = '\0';
        return;
    }
    memcpy(str, buf->data + buf->offset, len);
    str[len] = '\0';
    buf->offset += len;
}

/* src/buffer.c:50-61 */
MOBIBuffer * mobi_buffer_init_null(unsigned char *data, const size_t len) {
    MOBIBuffer *buf = malloc(sizeof(MOBIBuffer));
    if (buf == NULL) {
        debug_print("%s", "Buffer allocation failed\n");
        return NULL;
    }
    buf->data = data;
    buf->offset = 0;
    buf->maxlen = len;
    buf->error = MOBI_SUCCESS;
    return buf;
}

/* src/buffer.c:590-597 */
void mobi_buffer_setpos(MOBIBuffer *buf, const size_t pos) {
    if (pos <= buf->maxlen) {
        buf->offset = pos;
        return;
    }
    buf->error = MOBI_BUFFER_END;
    debug_print("%s", "End of buffer\n");
}

/* src/buffer.c:622-625 */
void mobi_buffer_free_null(MOBIBuffer *buf) {
    if (buf == NULL) { return; }
    free(buf);
}

/* src/index.c:860-876 (real callee: fetches group_name for name_attr) */
char * mobi_get_cncx_string(const MOBIPdbRecord *cncx_record, const uint32_t cncx_offset) {
    /* TODO: handle multiple cncx records */
    MOBIBuffer *buf = mobi_buffer_init_null(cncx_record->data, cncx_record->size);
    if (buf == NULL) {
        debug_print("%s\n", "Memory allocation failed");
        return NULL;
    }
    mobi_buffer_setpos(buf, cncx_offset);
    size_t len = 0;
    const uint32_t string_length = mobi_buffer_get_varlen(buf, &len);
    char *string = malloc(string_length + 1);
    if (string) {
        mobi_buffer_getstring(string, buf, string_length);
    }
    mobi_buffer_free_null(buf);
    return string;
}

/* src/index.c:781-796 (real callee: called 3x inside mobi_reconstruct_infl) */
size_t mobi_get_indxentry_tagarray(uint32_t **tagarr, const MOBIIndexEntry *entry, const size_t tagid) {
    if (entry == NULL) {
        debug_print("%s", "INDX entry not initialized\n");
        return 0;
    }
    size_t i = 0;
    while (i < entry->tags_count) {
        if (entry->tags[i].tagid == tagid) {
            *tagarr = entry->tags[i].tagvalues;
            return entry->tags[i].tagvalues_count;
        }
        i++;
    }
    //debug_print("tag[%zu] not found in entry: %s\n", tagid, entry->label);
    return 0;
}

/* src/index.c:943-1001 (real callee: called on `rule` derived from the
 * (possibly OOB) infl->entries[parts[j]].label) */
MOBI_RET mobi_decode_infl(unsigned char *decoded, int *decoded_size, const unsigned char *rule) {
    int pos = *decoded_size;
    char mod = 'i';
    char dir = '<';
    char olddir;
    unsigned char c;
    while ((c = *rule++)) {
        if (c <= 4) {
            mod = (c <= 2) ? 'i' : 'd'; /* insert, delete */
            olddir = dir;
            dir = (c & 2) ? '<' : '>'; /* left, right */
            if (olddir != dir && olddir) {
                pos = (c & 2) ? *decoded_size : 0;
            }
        }
        else if (c > 10 && c < 20) {
            if (dir == '>') {
                pos = *decoded_size;
            }
            pos -= c - 10;
            dir = 0;
            if (pos < 0 || pos > *decoded_size) {
                debug_print("Position setting failed (%s)\n", decoded);
                return MOBI_DATA_CORRUPT;
            }
        }
        else {
            if (mod == 'i') {
                const unsigned char *s = decoded + pos;
                unsigned char *d = decoded + pos + 1;
                const int l = *decoded_size - pos;
                if (l < 0 || d + l > decoded + INDX_INFLBUF_SIZEMAX) {
                    debug_print("Out of buffer in %s at pos: %i\n", decoded, pos);
                    return MOBI_DATA_CORRUPT;
                }
                memmove(d, s, (size_t) l);
                decoded[pos] = c;
                (*decoded_size)++;
                if (dir == '>') { pos++; }
            } else {
                if (dir == '<') { pos--; }
                const unsigned char *s = decoded + pos + 1;
                unsigned char *d = decoded + pos;
                const int l = *decoded_size - pos;
                if (l < 0 || d + l > decoded + INDX_INFLBUF_SIZEMAX) {
                    debug_print("Out of buffer in %s at pos: %i\n", decoded, pos);
                    return MOBI_DATA_CORRUPT;
                }
                if (decoded[pos] != c) {
                    debug_print("Character mismatch in %s at pos: %i (%c != %c)\n", decoded, pos, decoded[pos], c);
                    return MOBI_DATA_CORRUPT;
                }
                memmove(d, s, (size_t) l);
                (*decoded_size)--;
            }
        }
    }
    return MOBI_SUCCESS;
}

/* ===================================================================== */
/* ==== TARGET FUNCTION (byte-for-byte from                          ==== */
/* ==== data_cve/cve_12339d8e/target/original_function.c)            ==== */
/* ===================================================================== */

MOBI_RET mobi_reconstruct_infl(char *outstring, const MOBIIndx *infl, const MOBIIndexEntry *orth_entry) {
    const char *label = orth_entry->label;
    uint32_t *infl_groups = NULL;
    size_t infl_count = mobi_get_indxentry_tagarray(&infl_groups, orth_entry, INDX_TAGARR_ORTH_INFL);
    
    if (infl_count == 0 || !infl_groups) {
        return MOBI_SUCCESS;
    }    
    const char *start_tag = "<idx:infl>";
    const char *end_tag = "</idx:infl>";
    const char *iform_tag = "<idx:iform%s value=\"%s\"/>";
    char name_attr[INDX_INFLBUF_SIZEMAX + 1];
    char infl_tag[INDX_INFLBUF_SIZEMAX + 1];
    strcpy(outstring, start_tag);
    size_t initlen = strlen(start_tag) + strlen(end_tag);
    size_t outlen = initlen;
    size_t label_length = strlen(label);
    if (label_length > INDX_INFLBUF_SIZEMAX) {
        debug_print("Entry label too long (%s)\n", label);
        return MOBI_DATA_CORRUPT;
    }
    if (infl->cncx_record == NULL) {
        debug_print("%s\n", "Missing cncx record");
        return MOBI_DATA_CORRUPT;
    }
    for (size_t i = 0; i < infl_count; i++) {
        size_t offset = infl_groups[i];
        if (offset >= infl->entries_count) {
            debug_print("%s\n", "Invalid entry offset");
            return MOBI_DATA_CORRUPT;
        }
        uint32_t *groups;
        size_t group_cnt = mobi_get_indxentry_tagarray(&groups, &infl->entries[offset], INDX_TAGARR_INFL_GROUPS);
        uint32_t *parts;
        size_t part_cnt = mobi_get_indxentry_tagarray(&parts, &infl->entries[offset], INDX_TAGARR_INFL_PARTS_V2);
        if (group_cnt != part_cnt) {
            return MOBI_DATA_CORRUPT;
        }
        for (size_t j = 0; j < part_cnt; j++) {
            name_attr[0] = '\0';
            char *group_name = mobi_get_cncx_string(infl->cncx_record, groups[j]);
            if (group_name == NULL) {
                debug_print("%s\n", "Memory allocation failed");
                return MOBI_MALLOC_FAILED;
            }
            if (strlen(group_name)) {
                snprintf(name_attr, INDX_INFLBUF_SIZEMAX, " name=\"%s\"", group_name);
            }
            free(group_name);
            
            unsigned char decoded[INDX_INFLBUF_SIZEMAX + 1];
            memset(decoded, 0, INDX_INFLBUF_SIZEMAX + 1);
            unsigned char *rule = (unsigned char *) infl->entries[parts[j]].label;
            memcpy(decoded, label, label_length);
            int decoded_length = (int) label_length;
            MOBI_RET ret = mobi_decode_infl(decoded, &decoded_length, rule);
            if (ret != MOBI_SUCCESS) {
                return ret;
            }
            if (decoded_length == 0) {
                continue;
            }
            int n = snprintf(infl_tag, INDX_INFLBUF_SIZEMAX, iform_tag, name_attr, decoded);
            if (n > INDX_INFLBUF_SIZEMAX) {
                debug_print("Skipping truncated tag: %s\n", infl_tag);
                continue;
            }
            outlen += strlen(infl_tag);
            if (outlen > INDX_INFLTAG_SIZEMAX) {
                debug_print("Inflections text in %s too long (%zu)\n", label, outlen);
                return MOBI_ERROR;
            }
            strcat(outstring, infl_tag);
        }
    }
    if (outlen == initlen) {
        outstring[0] = '\0';
    } else {
        strcat(outstring, end_tag);
    }
    return MOBI_SUCCESS;
}
/* ===================================================================== */
/* ==== END TARGET FUNCTION ==== */
/* ===================================================================== */

/* -------------------------- driver -------------------------- */

/* fixed 4-byte cncx blob: varlen-encoded length=3 ("grp") at offset 0
 * (0x83 = stop-flag(0x80) | 3) -- used by mobi_get_cncx_string(). */
static unsigned char CNCX_BLOB[4] = { 0x83, 'g', 'r', 'p' };

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

    /* HEAP-allocated input buffer so any over-read is ASAN-visible */
    unsigned char *raw = (unsigned char *) malloc(sz ? (size_t) sz : 1);
    size_t n = fread(raw, 1, (size_t) sz, f);
    fclose(f);

    /* FDP-style byte consumption */
    unsigned char b0 = (n > 0) ? raw[0] : 0;   /* -> entries_count       */
    unsigned char b1 = (n > 1) ? raw[1] : 0;   /* bit0: trigger vs safe; upper bits: overflow delta / good index */
    unsigned char b2 = (n > 2) ? raw[2] : 0;   /* -> label length        */

    int trigger = b1 & 1;

    /* size of infl->entries[] : [2, 10] */
    size_t entries_count = 2 + (size_t) (b0 % 9);

    /* build the "infl" index entries array on the heap, EXACTLY
     * entries_count elements -- so indexing past it is ASAN-visible. */
    MOBIIndexEntry *entries = (MOBIIndexEntry *) malloc(entries_count * sizeof(MOBIIndexEntry));
    for (size_t i = 0; i < entries_count; i++) {
        entries[i].label = (char *) calloc(1, 1);   /* "" -- benign, empty decode rule */
        entries[i].tags_count = 0;
        entries[i].tags = NULL;
    }

    /* entries[0] is the "inflection group" entry: it carries the
     * INFL_GROUPS (5) and INFL_PARTS_V2 (26) tag arrays that
     * mobi_reconstruct_infl reads via mobi_get_indxentry_tagarray(). */
    uint32_t *group_vals = (uint32_t *) malloc(sizeof(uint32_t));
    group_vals[0] = 0; /* cncx offset 0 -> CNCX_BLOB "grp" */

    uint32_t part_idx;
    if (trigger) {
        /* OOB: entries_count + delta, same class the fix commit guards
         * against ("if (parts[j] >= infl->entries_count) return
         * MOBI_DATA_CORRUPT;") -- unpatched code has no such check. Delta is
         * kept well past entries_count (empirically, ASAN's small-allocation
         * size-class slack can hide a +1..+5 element overrun of this 24-byte-
         * stride array; +50..+250 elements reliably lands the read of the
         * `.label` field in the poisoned redzone). */
        unsigned delta = 50 + 50 * ((b1 >> 1) % 5);
        part_idx = (uint32_t) (entries_count + delta);
    } else {
        /* in-bounds: a real, initialized entries[] slot with an empty
         * (benign) label so mobi_decode_infl() runs cleanly. */
        part_idx = (uint32_t) (b2 % entries_count);
    }
    uint32_t *part_vals = (uint32_t *) malloc(sizeof(uint32_t));
    part_vals[0] = part_idx;

    MOBIIndexTag *tags0 = (MOBIIndexTag *) malloc(2 * sizeof(MOBIIndexTag));
    tags0[0].tagid = INDX_TAGARR_INFL_GROUPS;
    tags0[0].tagvalues_count = 1;
    tags0[0].tagvalues = group_vals;
    tags0[1].tagid = INDX_TAGARR_INFL_PARTS_V2;
    tags0[1].tagvalues_count = 1;
    tags0[1].tagvalues = part_vals;
    entries[0].tags_count = 2;
    entries[0].tags = tags0;

    /* cncx record backing mobi_get_cncx_string() */
    MOBIPdbRecord *cncx_rec = (MOBIPdbRecord *) calloc(1, sizeof(MOBIPdbRecord));
    unsigned char *cncx_data = (unsigned char *) malloc(sizeof(CNCX_BLOB));
    memcpy(cncx_data, CNCX_BLOB, sizeof(CNCX_BLOB));
    cncx_rec->data = cncx_data;
    cncx_rec->size = sizeof(CNCX_BLOB);

    MOBIIndx infl;
    infl.type = 2;
    infl.entries_count = entries_count;
    infl.encoding = MOBI_UTF8;
    infl.total_entries_count = entries_count;
    infl.ordt_offset = 0;
    infl.ligt_offset = 0;
    infl.ligt_entries_count = 0;
    infl.cncx_records_count = 1;
    infl.cncx_record = cncx_rec;
    infl.entries = entries;
    infl.orth_index_name = NULL;

    /* the "orth" dictionary entry, pointing at inflection group 0 */
    size_t label_len = 1 + (size_t) (b2 % 20);
    char *orth_label = (char *) malloc(label_len + 1);
    for (size_t i = 0; i < label_len; i++) {
        orth_label[i] = (char) ('a' + (int) ((i + b2) % 26));
    }
    orth_label[label_len] = '\0';

    uint32_t *orth_infl_vals = (uint32_t *) malloc(sizeof(uint32_t));
    orth_infl_vals[0] = 0; /* -> infl->entries[0], the group entry above */
    MOBIIndexTag *orth_tags = (MOBIIndexTag *) malloc(sizeof(MOBIIndexTag));
    orth_tags[0].tagid = INDX_TAGARR_ORTH_INFL;
    orth_tags[0].tagvalues_count = 1;
    orth_tags[0].tagvalues = orth_infl_vals;

    MOBIIndexEntry orth_entry;
    orth_entry.label = orth_label;
    orth_entry.tags_count = 1;
    orth_entry.tags = orth_tags;

    /* outstring: generously heap-sized so the (checked, bounded) XML
     * accumulation never itself overflows -- we're isolating the
     * parts[j]-index READ bug, not the length-checked WRITE path. */
    char *outstring = (char *) malloc(4096);
    outstring[0] = '\0';

    MOBI_RET ret = mobi_reconstruct_infl(outstring, &infl, &orth_entry);
    fprintf(stderr, "mobi_reconstruct_infl ret=%d outstring=\"%s\"\n", (int) ret, outstring);

    free(raw);
    return 0;
}
