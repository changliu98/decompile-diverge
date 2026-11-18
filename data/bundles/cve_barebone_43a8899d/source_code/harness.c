/* cve_barebone harness -- cjson CVE-2019-1010239 / get_object_item NULL-deref (CWE-476)
 *
 * Isolated reproduction: get_object_item() is called directly on a hand-built cJSON node
 * chain shaped exactly like the state cJSON_Parse() leaves for an ARRAY (or any object
 * entry that lost its key): the first child has ->string == NULL. In the case_sensitive
 * branch, get_object_item's while-loop calls strcmp(name, current_element->string) BEFORE
 * checking that pointer for NULL -- with the first candidate's string == NULL, strcmp
 * reads through a NULL pointer -> SIGSEGV, caught by ASAN as "SEGV on unknown address
 * 0x000000000000" inside get_object_item itself (crash stack: strcmp interceptor --
 * get_object_item -- main).
 *
 * TRIGGER: child->string == NULL, case_sensitive == 1 (cJSON_GetObjectItemCaseSensitive).
 * SAFE:    child->string is a real (non-NULL) key -> strcmp compares two valid C strings,
 *          a normal miss/hit, no crash.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---- real cJSON node layout (cJSON.h, verbatim field names) ---- */
typedef struct cJSON
{
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;

    int type;

    char *valuestring;
    int valueint;
    double valuedouble;

    char *string;
} cJSON;

typedef int cJSON_bool;

/* ---- case_insensitive_strcmp: real callee referenced by get_object_item's else-branch
 * (source_code/cJSON.c, verbatim) -- needed for the file to compile standalone; it is not on
 * the crash path itself (it already NULL-checks both arguments). ---- */
static int case_insensitive_strcmp(const unsigned char *string1, const unsigned char *string2)
{
    if ((string1 == NULL) || (string2 == NULL))
    {
        return 1;
    }

    if (string1 == string2)
    {
        return 0;
    }

    for(; tolower(*string1) == tolower(*string2); (void)string1++, string2++)
    {
        if (*string1 == '\0')
        {
            return 0;
        }
    }

    return tolower(*string1) - tolower(*string2);
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the SEGV keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace). */
__attribute__((noinline))
static cJSON *get_object_item(const cJSON * const object, const char * const name, const cJSON_bool case_sensitive)
{
    cJSON *current_element = NULL;

    if ((object == NULL) || (name == NULL))
    {
        return NULL;
    }

    current_element = object->child;
    if (case_sensitive)
    {
        while ((current_element != NULL) && (strcmp(name, current_element->string) != 0))
        {
            current_element = current_element->next;
        }
    }
    else
    {
        while ((current_element != NULL) && (case_insensitive_strcmp((const unsigned char*)name, (const unsigned char*)(current_element->string)) != 0))
        {
            current_element = current_element->next;
        }
    }

    return current_element;
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

    unsigned char *data = (unsigned char *)malloc(n + 1);   /* HEAP input, ASAN-guarded */
    if (!data) { fclose(fp); return 2; }
    size_t got = fread(data, 1, n, fp);
    fclose(fp);
    data[got] = '\0';

    unsigned char mode = (got > 0) ? data[0] : 0;
    /* "name" = the rest of the input bytes, still inside the SAME heap allocation (NUL
     * terminated at data[got]) -- the attacker-controlled search key. */
    char *name = (got > 1) ? (char *)(data + 1) : (char *)data;

    /* Build the container get_object_item() is called on: a single-child chain whose FIRST
     * (and only) entry is shaped like an array element / keyless object entry. */
    cJSON *object = (cJSON *)malloc(sizeof(cJSON));
    memset(object, 0, sizeof(cJSON));
    cJSON *child = (cJSON *)malloc(sizeof(cJSON));
    memset(child, 0, sizeof(cJSON));
    object->child = child;
    child->next = NULL;
    child->prev = NULL;
    child->type = 0;   /* irrelevant to get_object_item, which reads only ->string / ->next */

    int trigger = ((mode & 1) == 0);   /* even mode byte -> TRIGGER */
    if (trigger)
    {
        child->string = NULL;                       /* <-- the exact pre-fix-reachable state */
    }
    else
    {
        child->string = strdup("safe_key_probe");    /* real, non-NULL key -> no crash */
    }

    /* volatile function pointer: forbid the compiler from proving the call away / folding
     * get_object_item into main's own frame despite __attribute__((noinline)). */
    cJSON *(* volatile fn)(const cJSON * const, const char * const, const cJSON_bool) = get_object_item;
    cJSON *found = fn(object, name, 1 /* case_sensitive -- the only branch with the bug */);
    (void)found;

    free(data);
    return 0;
}
