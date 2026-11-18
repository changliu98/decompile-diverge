/* cve_barebone harness -- gpac GF-2695 / gitn_box_del NULL-deref (CWE-476)
 *
 * Isolated reproduction: gitn_box_del() is called directly on a hand-built
 * GroupIdToNameBox shaped exactly like the state gitn_box_read() leaves behind when it
 * bails out after setting nb_entries but BEFORE allocating entries (a truncated/invalid
 * box). Real struct layout + real gf_free; everything off the destructor's own body
 * (box_new/box_read/the bitstream reader) is deliberately absent -- the harness builds
 * the post-partial-parse STATE directly rather than replaying the parser.
 *
 * TRIGGER: nb_entries > 0 && entries == NULL  -> ptr->entries[i].name dereferences a
 *          wild pointer a few bytes past NULL on iteration 0 -> SIGSEGV, caught by ASAN
 *          as "SEGV on unknown address" inside gitn_box_del itself.
 * SAFE:    entries allocated to match nb_entries (mirrors a box that finished
 *          gitn_box_read() successfully) -> gitn_box_del walks + frees it cleanly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- gpac base typedefs (real names, gpac/setup.h) ---- */
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef uint64_t        u64;

/* ---- GF_ISOM_BOX / GF_ISOM_FULL_BOX (real macros, isomedia_dev.h) ----
 * registry/child_boxes are never touched by gitn_box_del -- opaque/incomplete is enough,
 * kept as REAL type names for a faithful header layout. */
struct box_registry_entry;
typedef struct _tag_array GF_List;   /* real name, gpac/list.h; incomplete here (opaque) */

#define GF_ISOM_BOX			\
	u32 type;				\
	u64 size;				\
	const struct box_registry_entry *registry;\
	GF_List *child_boxes; 	\
	u16 internal_flags;		\
	u16 version;				\

#define GF_ISOM_FULL_BOX		\
	GF_ISOM_BOX			\
	u32 flags;			\

typedef struct
{
	GF_ISOM_BOX
} GF_Box;

/* ---- real struct (isomedia_dev.h, verbatim) ---- */
typedef struct
{
	u32 group_id;
	char *name;
} GroupIdNameEntry;

typedef struct
{
	GF_ISOM_FULL_BOX
	u16 nb_entries;
	GroupIdNameEntry *entries;
} GroupIdToNameBox;

/* ---- gf_free: real exported signature (gpac/setup.h: void gf_free(void *ptr);).
 * gf_mem_free's debug bookkeeping is incidental (not on the crash path -- the trigger
 * case SEGVs before any gf_free call is reached); free() is the faithful minimal stub. */
void gf_free(void *ptr) { free(ptr); }

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the SEGV keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace). */
__attribute__((noinline))
void gitn_box_del(GF_Box *s)
{
	u32 i;
	GroupIdToNameBox *ptr = (GroupIdToNameBox *)s;
	if (ptr == NULL) return;
	for (i=0; i<ptr->nb_entries; i++) {
		if (ptr->entries[i].name) gf_free(ptr->entries[i].name);
	}
	if (ptr->entries) gf_free(ptr->entries);
	gf_free(ptr);
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
   if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

   FILE *fp = fopen(argv[1], "rb");
   if (!fp) { perror("fopen"); return 2; }
   fseek(fp, 0, SEEK_END);
   long ln = ftell(fp);
   fseek(fp, 0, SEEK_SET);
   if (ln < 0) ln = 0;
   size_t n = (size_t)ln;
   unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
   size_t got = fread(data, 1, n, fp);
   fclose(fp);
   if (got < 2) { free(data); return 0; }                      /* too small -> clean exit */

   int trigger = data[0] & 1;                        /* 1 => entries==NULL (the CVE) */
   u32 nb_entries = 1u + (u32)(data[1] % 40);         /* 1..40, always > 0 */
   int name_parity = data[1] & 1;

   /* Build the box the way gitn_box_read() leaves it: allocate the box itself (mirrors
    * gitn_box_new()'s gf_malloc), set nb_entries, and either leave entries NULL (parser
    * bailed out before GF_SAFE_ALLOC_N) or allocate it to match (parser finished). */
   GroupIdToNameBox *box = (GroupIdToNameBox *)malloc(sizeof(GroupIdToNameBox));
   memset(box, 0, sizeof(*box));
   box->type = 0;               /* GF_ISOM_BOX_TYPE_GITN irrelevant to this function's body */
   box->nb_entries = (u16)nb_entries;

   if (trigger) {
      box->entries = NULL;      /* <-- the exact pre-fix-reachable state */
   } else {
      box->entries = (GroupIdNameEntry *)calloc(nb_entries, sizeof(GroupIdNameEntry));
      for (u32 i = 0; i < nb_entries; i++) {
         box->entries[i].group_id = i;
         if ((int)((i + name_parity) & 1)) {
            char buf[24];
            snprintf(buf, sizeof buf, "n%u", i);
            box->entries[i].name = strdup(buf);   /* heap alloc, freed by gitn_box_del */
         } else {
            box->entries[i].name = NULL;
         }
      }
   }
   free(data);

   /* volatile function pointer: forbid the compiler from inlining/proving-away the call. */
   void (*volatile fn)(GF_Box *) = gitn_box_del;
   fn((GF_Box *)box);   /* gitn_box_del frees `box` itself on the safe path -- don't touch it after */

   return 0;
}
