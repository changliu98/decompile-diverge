/* cve_barebone direct-call harness for sdop check_supported() stack-buffer-overflow
 * https://github.com/philiphazel/sdop  fix_commit=ff83d851b4b39ff2fd37ab2ab14365649515b023
 *
 * ChangeLog (Version 1.11, 25-June-2024):
 *   "If a revisionflag attribute was given very long value, stack smashing could
 *    occur (the only valid value for revisionflag is "changed")."
 *
 * Target: check_supported  (src/read.c)
 * Bug class: stack-buffer-overflow WRITE (CWE-787) at
 *     (void)sprintf(CS buffer, "+%s=%s:%s", param->name, param->value, new->name);
 *   `buffer` is a fixed `uschar buffer[256]` local. The un-length-checked "%s" for
 *   param->value -- the DocBook "revisionflag" attribute's value, straight from
 *   document/user input -- lets an attacker-controlled long value overrun it. The
 *   fix (deliberately NOT applied here -- this file reproduces the PRE-fix body)
 *   truncates that copy with "%.*s".
 *
 * Everything but check_supported() itself is scaffolding, copied VERBATIM from
 * source_code/src/{mytypes.h,structs.h,sdop.h,datatables.c,tree.c} (real type
 * defs, real Ustrcmp/Ustrcpy/Ustrlen/CS/US macros, the real supported_elements[]
 * table check_supported()'s binary search walks, the real tree_search /
 * tree_insertnode). misc_malloc is a minimal faithful stub (allocate-or-die) for
 * the real one's memory-chain bookkeeping (main_memory_chain/memory_used/
 * memory_hwm), which is orthogonal to the bug and is never reached before the
 * crash on a triggering input.
 *
 * Build (dc_batch.py / dc_try.py, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==== from src/mytypes.h (verbatim) ==== */
#define FALSE         0
#define TRUE          1

typedef int BOOL;
typedef unsigned char uschar;

#define CS   (char *)
#define CCS  (const char *)
#define US   (unsigned char *)

#define Ustrcmp(s,t)       strcmp(CCS(s),CCS(t))
#define Ustrcpy(s,t)       strcpy(CS(s),CCS(t))
#define Ustrlen(s)         (int)strlen(CCS(s))

/* ==== from src/sdop.h (verbatim) ==== */
#define DBNAMESIZE           32
#define DBPARAMNAMESIZE      32

/* ==== from src/structs.h (verbatim) ==== */
typedef struct elliststr {
  uschar *name;
  uschar **attrs;
} elliststr;

typedef struct tree_node {
  struct tree_node *left;      /* pointer to left child */
  struct tree_node *right;     /* pointer to right child */
  union
    {
    void  *ptr;                /* pointer to data */
    int val[2];                /* or integer data (2 values) */
    } data;
  uschar  balance;             /* balancing factor */
  uschar  name[1];             /* node name - variable length */
} tree_node;

typedef struct paramstr {
  struct paramstr *next;
  uschar name[DBPARAMNAMESIZE];
  uschar seen;
  uschar value[1];
} paramstr;

typedef struct item {
  struct item *next;
  struct item *prev;
  struct item *partner;
  int linenumber;
  int flags;
  uschar name[DBNAMESIZE];
  union {
    paramstr *param;
    void *txtblk;
    void *prgrph;
    void *tdata;
    void *pdata;
    void *lngthstrng;
    void *ndxstr;
    uschar *string;
  } p;
} item;

/* ==== from src/datatables.c (verbatim: the real supported-elements table) ====
 * check_supported()'s binary search walks this exact sorted array; "para"
 * (used below) is one of its entries, with a NULL attrs list. */
uschar *nocheck_attrs[]       = { US"*",          NULL };

uschar *article_attrs[]       = { US"class",      US"id",       NULL };
uschar *chapter_attrs[]       = { US"id",         NULL };
uschar *colspec_attrs[]       = { US"align",      US"char",     US"charoff",
                                  US"colwidth",   US"colsep",   NULL };
uschar *emphasis_attrs[]      = { US"role",       NULL };
uschar *entry_attrs[]         = { US"align",      US"char",     US"charoff",
                                  NULL };
uschar *example_attrs[]       = { US"id",         NULL };
uschar *figure_attrs[]        = { US"id",         NULL };
uschar *footnote_attrs[]      = { US"id",         NULL };
uschar *footnoteref_attrs[]   = { US"linkend",    NULL };
uschar *imagedata_attrs[]     = { US"align",      US"depth",    US"fileref",
                                  US"format",     US"scale",    US"scalefit",
                                  US"width",      NULL };
uschar *imageobject_attrs[]   = { US"role",       NULL };
uschar *index_attrs[]         = { US"role",       NULL };
uschar *indexterm_attrs[]     = { US"class",      US"id",       US"role",
                                  US"startref",   NULL };
uschar *itemizedlist_attrs[]  = { US"mark",       NULL };
uschar *literallayout_attrs[] = { US"class",      NULL };
uschar *orderedlist_attrs[]   = { US"numeration", NULL };
uschar *row_attrs[]           = { US"rowsep",     NULL };
uschar *table_attrs[]         = { US"colsep",     US"frame",    US"id",
                                  US"rowsep",     US"toc",      NULL };
uschar *tgroup_attrs[]        = { US"char",       US"charoff",  US"cols",
                                  US"colsep",     US"rowsep",   NULL };
uschar *ulink_attrs[]         = { US"url",        NULL };
uschar *xref_attrs[]          = { US"linkend",    NULL };

elliststr supported_elements[] = {
  { US"abbrev",            NULL },
  { US"abstract",          NULL },
  { US"acronym",           NULL },
  { US"address",           NULL },
  { US"affiliation",       NULL },
  { US"appendix",          chapter_attrs },
  { US"article",           article_attrs },
  { US"articleinfo",       NULL },
  { US"attribution",       NULL },
  { US"audiodata",         nocheck_attrs },
  { US"audioobject",       nocheck_attrs },
  { US"author",            NULL },
  { US"authorblurb",       nocheck_attrs },
  { US"authorinitials",    NULL },
  { US"blockquote",        NULL },
  { US"book",              NULL },
  { US"bookinfo",          NULL },
  { US"caption",           NULL },
  { US"chapter",           chapter_attrs },
  { US"citetitle",         emphasis_attrs },  /* sic */
  { US"colophon",          NULL },
  { US"colspec",           colspec_attrs },
  { US"command",           NULL },
  { US"computeroutput",    NULL },
  { US"copyright",         NULL },
  { US"corpauthor",        NULL },
  { US"date",              NULL },
  { US"edition",           NULL },
  { US"editor",            NULL },
  { US"email",             emphasis_attrs },  /* sic */
  { US"emphasis",          emphasis_attrs },
  { US"entry",             entry_attrs },
  { US"epigraph",          NULL },
  { US"example",           example_attrs },
  { US"figure",            figure_attrs },
  { US"filename",          NULL },
  { US"firstname",         NULL },
  { US"footnote",          footnote_attrs },
  { US"footnoteref",       footnoteref_attrs },
  { US"formalpara",        NULL },
  { US"function",          NULL },
  { US"holder",            NULL },
  { US"honorific",         NULL },
  { US"imagedata",         imagedata_attrs },
  { US"imageobject",       imageobject_attrs },
  { US"index",             index_attrs },
  { US"indexterm",         indexterm_attrs },
  { US"informalfigure",    figure_attrs },
  { US"informaltable",     table_attrs },
  { US"inlinemediaobject", NULL },
  { US"issuenum",          NULL },
  { US"itemizedlist",      itemizedlist_attrs },
  { US"jobtitle",          NULL },
  { US"keyword",           NULL },
  { US"keywordset",        NULL },
  { US"legalnotice",       NULL },
  { US"lineage",           NULL },
  { US"lineannotation",    NULL },
  { US"link",              nocheck_attrs },
  { US"listitem",          NULL },
  { US"literal",           NULL },
  { US"literallayout",     literallayout_attrs },
  { US"mediaobject",       NULL },
  { US"note",              NULL },
  { US"objectinfo",        NULL },
  { US"option",            NULL },
  { US"orderedlist",       orderedlist_attrs },
  { US"orgname",           NULL },
  { US"othercredit",       NULL },
  { US"othername",         NULL },
  { US"para",              NULL },
  { US"phrase",            NULL },
  { US"preface",           NULL },
  { US"primary",           NULL },
  { US"programlisting",    NULL },
  { US"pubdate",           NULL },
  { US"publishername",     NULL },
  { US"quote",             NULL },
  { US"releaseinfo",       NULL },
  { US"replaceable",       NULL },
  { US"revdescription",    NULL },
  { US"revhistory",        NULL },
  { US"revision",          NULL },
  { US"revnumber",         NULL },
  { US"revremark",         nocheck_attrs },
  { US"row",               row_attrs },
  { US"screen",            NULL },
  { US"secondary",         NULL },
  { US"sect1",             chapter_attrs },
  { US"sect2",             chapter_attrs },
  { US"sect3",             chapter_attrs },
  { US"sect4",             chapter_attrs },
  { US"sect5",             chapter_attrs },
  { US"section",           chapter_attrs },
  { US"sectioninfo",       NULL },
  { US"see",               NULL },
  { US"seealso",           NULL },
  { US"sidebar",           NULL },
  { US"simpara",           NULL },
  { US"subject",           nocheck_attrs },
  { US"subjectset",        nocheck_attrs },
  { US"subjectterm",       nocheck_attrs },
  { US"subscript",         NULL },
  { US"subtitle",          NULL },
  { US"superscript",       NULL },
  { US"surname",           NULL },
  { US"systemitem",        nocheck_attrs },
  { US"table",             table_attrs },
  { US"tbody",             NULL },
  { US"term",              NULL },
  { US"tertiary",          NULL },
  { US"textobject",        NULL },
  { US"tfoot",             NULL },
  { US"tgroup",            tgroup_attrs },
  { US"thead",             NULL },
  { US"title",             NULL },
  { US"titleabbrev",       NULL },
  { US"trademark",         nocheck_attrs },
  { US"ulink",             ulink_attrs },
  { US"userinput",         NULL },
  { US"variablelist",      NULL },
  { US"varlistentry",      NULL },
  { US"varname",           NULL },
  { US"videodata",         nocheck_attrs },
  { US"videoobject",       nocheck_attrs },
  { US"volumenum",         NULL },
  { US"xref",              xref_attrs },
  { US"year",              NULL }
};

int supported_elements_count = sizeof(supported_elements)/sizeof(elliststr);

/* ==== from src/globals.c (verbatim declaration) ==== */
tree_node *unknown_element_tree = NULL;

/* ==== minimal faithful stub for src/misc.c's misc_malloc() ====
 * The real one wraps this same allocate-or-die contract in memory-chain
 * bookkeeping that is orthogonal to the bug under test, and (on a triggering
 * input) is never even reached -- the sprintf() overflow happens first. */
static void *
misc_malloc(int size)
{
void *yield = malloc((size_t)size);
if (yield == NULL) { fprintf(stderr, "sdop: failed to get memory\n"); exit(1); }
return yield;
}

/* ==== from src/tree.c (verbatim: tree_insertnode + tree_search) ==== */
#define tree_lbal      1         /* left subtree is longer */
#define tree_rbal      2         /* right subtree is longer */
#define tree_bmask     3         /* mask for flipping bits */

int
tree_insertnode(tree_node **treebase, tree_node *node)
{
tree_node *p = *treebase;
tree_node **q, *r, *s, **t;
int a;

node->left = node->right = NULL;
node->balance = 0;

/* Deal with an empty tree */

if (p == NULL)
  {
  *treebase = node;
  return TRUE;
  }

/* The tree is not empty. While finding the insertion point,
q points to the pointer to p, and t points to the pointer to
the potential re-balancing point. */

q = treebase;
t = q;

/* Loop to search tree for place to insert new node */

for (;;)
  {
  int c = Ustrcmp(node->name, p->name);
  if (c == 0) return FALSE;              /* Duplicate node encountered */

  /* Deal with climbing down the tree, exiting from the loop
  when we reach a leaf. */

  q = (c > 0)? &(p->right) : &(p->left);
  p = *q;
  if (p == NULL) break;

  /* Save the address of the pointer to the last node en route
  which has a non-zero balance factor. */

  if (p->balance != 0) t = q;
  }

/* When the above loop completes, q points to the pointer to NULL;
that is the place at which the new node must be inserted. */

*q = node;

/* Set up s as the potential re-balancing point, and r as the
next node after it along the route. */

s = *t;
r = (Ustrcmp(node->name, s->name) > 0)? s->right : s->left;

/* Adjust balance factors along the route from s to node. */

p = r;

while (p != node)
  {
  if (Ustrcmp(node->name, p->name) < 0)
    {
    p->balance = tree_lbal;
    p = p->left;
    }
  else
    {
    p->balance = tree_rbal;
    p = p->right;
    }
  }

/* Now the World-Famous Balancing Act */

a = (Ustrcmp(node->name, s->name) < 0)? tree_lbal : tree_rbal;

if (s->balance == 0) s->balance = (uschar)a;        /* The tree has grown higher */
  else if (s->balance != (uschar)a) s->balance = 0; /* It's become more balanced */
else                                                /* It's got out of balance */
  {
  /* Perform a single rotation */

  if (r->balance == (uschar)a)
    {
    p = r;
    if (a == tree_rbal)
      {
      s->right = r->left;
      r->left = s;
      }
    else
      {
      s->left = r->right;
      r->right = s;
      }
    s->balance = 0;
    r->balance = 0;
    }

  /* Perform a double rotation There was an occasion when the balancing
  factors were screwed up by a bug in the code that reads a tree from
  the spool. In case this ever happens again, check for changing p to NULL
  and don't do it. It is better to have an unbalanced tree than a crash. */

  else
    {
    if (a == tree_rbal)
      {
      if (r->left == NULL) return TRUE;   /* Bail out if tree corrupt */
      p = r->left;
      r->left = p->right;
      p->right = r;
      s->right = p->left;
      p->left = s;
      }
    else
      {
      if (r->right == NULL) return TRUE;  /* Bail out if tree corrupt */
      p = r->right;
      r->right = p->left;
      p->left = r;
      s->left = p->right;
      p->right = s;
      }

    s->balance = (p->balance == (uschar)a)? (uschar)(a^tree_bmask) : 0;
    r->balance = (p->balance == (uschar)(a^tree_bmask))? (uschar)a : 0;
    p->balance = 0;
    }

  /* Finishing touch */

  *t = p;
  }

return TRUE;     /* Successful insertion */
}

tree_node *
tree_search(tree_node *p, uschar *name)
{
while (p != NULL)
  {
  int c = Ustrcmp(name, p->name);
  if (c == 0) return p;
  p = (c < 0)? p->left : p->right;
  }
return NULL;
}

/* ==== VERBATIM from data_cve/cve_ebfa56f7/target/original_function.c ==== */
static void
check_supported(item *new)
{
int c = -1;
int bot = 0;
int top = supported_elements_count;
int mid;
tree_node *tn;
paramstr *param;

while (top > bot)
  {
  mid = (top + bot)/2;
  c = Ustrcmp(new->name, supported_elements[mid].name);
  if (c == 0) break;
  if (c < 0) top = mid; else bot = mid + 1;
  }

/* Element is not recognized; insert in tree if not already there. */

if (c != 0)
  {
  tn = tree_search(unknown_element_tree, new->name);
  if (tn == NULL)
    {
    tn = misc_malloc(sizeof(tree_node) + Ustrlen(new->name));
    Ustrcpy(tn->name, new->name);
    (void)tree_insertnode(&unknown_element_tree, tn);
    }
  return;
  }

/* Element is recognized, check its attributes. Those that start with "#" are
invented internal ones. */

for (param = new->p.param; param != NULL; param = param->next)
  {
  uschar buffer[256];
  uschar **aptr;
  if (param->name[0] == '#') continue;

  /* Check common attributes - check their values */

  if (Ustrcmp(param->name, "revisionflag") == 0)
    {
    if (Ustrcmp(param->value, "changed") == 0) continue;
    (void)sprintf(CS buffer, "+%s=%s:%s", param->name, param->value,
      new->name);
    }

  /* See if this attribute is listed as supported unless the first item
  in the list is "*", which means the element itself is ignored. */

  else
    {
    aptr = supported_elements[mid].attrs;
    if (aptr != NULL)
      {
      if (Ustrcmp(*aptr, "*") == 0) continue;
      for (; *aptr != NULL; aptr++)
        if (Ustrcmp(*aptr, param->name) == 0) break;
      if (*aptr != NULL) continue;
      }
    (void)sprintf(CS buffer, "+%s:%s", param->name, new->name);
    }

  /* Add to unknown tree */

  tn = tree_search(unknown_element_tree, buffer);
  if (tn == NULL)
    {
    tn = misc_malloc(sizeof(tree_node) + Ustrlen(buffer));
    Ustrcpy(tn->name, buffer);
    (void)tree_insertnode(&unknown_element_tree, tn);
    }
  }
}
/* ==== end verbatim ==== */

int
main(int argc, char **argv)
{
if (argc < 2) return 0;

FILE *f = fopen(argv[1], "rb");
if (f == NULL) return 0;
if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
long sz = ftell(f);
if (sz < 0) { fclose(f); return 0; }
if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

/* HEAP-allocate the whole PoC file, ASAN-guarded; +1 byte for our own NUL
   terminator so the copy below never reads past what we just wrote. */
unsigned char *filebuf = (unsigned char *)malloc((size_t)sz + 1);
if (filebuf == NULL) { fclose(f); return 0; }
size_t nread = fread(filebuf, 1, (size_t)sz, f);
fclose(f);
filebuf[nread] = '\0';

/* Build the item/paramstr chain check_supported() expects: a recognized
   element ("para", whose supported_elements[] entry has a NULL attrs list)
   carrying one "revisionflag" attribute whose value is the raw file
   content -- exactly the CVE's trigger vector (a DocBook revisionflag
   attribute value is document/attacker-controlled text). paramstr is the
   real flexible-array-member idiom the codebase uses everywhere else
   (c.f. misc_malloc(sizeof(tree_node)+Ustrlen(...)) in check_supported
   itself): allocate sizeof(paramstr)+nread bytes so value[] has room for
   the nread content bytes plus our NUL. */
item it;
memset(&it, 0, sizeof(it));
strcpy((char *)it.name, "para");

paramstr *p = (paramstr *)malloc(sizeof(paramstr) + nread);
if (p == NULL) { free(filebuf); return 0; }
p->next = NULL;
p->seen = 0;
strcpy((char *)p->name, "revisionflag");
memcpy(p->value, filebuf, nread + 1);   /* copies our NUL terminator too */

it.p.param = p;

check_supported(&it);

free(p);
free(filebuf);
return 0;
}
