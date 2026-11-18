/* cve_barebone harness -- Apache httpd CVE-2017-9798 "Optionsbleed" (CWE-416, heap
 * use-after-free) in ap_limit_section(). See module docstring in
 * scripts/gen_dc_cve_cba17423.py for the full root-cause writeup.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdarg.h>

/* ============================================================================
 * Minimal faithful APR stubs (apr is an external dependency, not vendored in this
 * checkout's srclib/).
 * ============================================================================ */
typedef int64_t apr_int64_t;
typedef long apr_ssize_t;
typedef unsigned long apr_size_t;

#define apr_isspace(c) (isspace(((unsigned char)(c))))

/* ---- pool: every sub-allocation is tracked individually, so "destroying" the pool
 * really free()s each one -- the concrete, ASAN-visible form of end-of-.htaccess-request
 * pool recycling this bug depends on. ---- */
typedef struct apr_pool_t {
    void **allocs;
    size_t n, cap;
} apr_pool_t;

static apr_pool_t *pool_create(void)
{
    apr_pool_t *p = (apr_pool_t *)malloc(sizeof(apr_pool_t));
    p->allocs = NULL; p->n = 0; p->cap = 0;
    return p;
}

static void *apr_palloc(apr_pool_t *p, apr_size_t size)
{
    void *mem = malloc(size ? size : 1);
    if (p->n == p->cap) {
        p->cap = p->cap ? p->cap * 2 : 8;
        p->allocs = (void **)realloc(p->allocs, p->cap * sizeof(void *));
    }
    p->allocs[p->n++] = mem;
    return mem;
}

static void *apr_pcalloc(apr_pool_t *p, apr_size_t size)
{
    void *mem = apr_palloc(p, size);
    memset(mem, 0, size);
    return mem;
}

static void pool_destroy(apr_pool_t *p)
{
    size_t i;
    for (i = 0; i < p->n; i++) free(p->allocs[i]);
    free(p->allocs);
    free(p);
}

static char *apr_pstrdup(apr_pool_t *p, const char *s)
{
    size_t len; char *res;
    if (s == NULL) return NULL;
    len = strlen(s) + 1;
    res = (char *)apr_palloc(p, len);
    memcpy(res, s, len);
    return res;
}

static char *apr_pstrmemdup(apr_pool_t *p, const char *s, apr_size_t n)
{
    char *res;
    if (s == NULL) return NULL;
    res = (char *)apr_palloc(p, n + 1);
    memcpy(res, s, n);
    res[n] = '\0';
    return res;
}

static char *apr_pstrcat(apr_pool_t *p, ...)
{
    va_list ap; const char *s; size_t len = 0; char *res, *cp;
    va_start(ap, p);
    while ((s = va_arg(ap, const char *)) != NULL) len += strlen(s);
    va_end(ap);
    res = (char *)apr_palloc(p, len + 1);
    cp = res;
    va_start(ap, p);
    while ((s = va_arg(ap, const char *)) != NULL) {
        size_t l = strlen(s);
        memcpy(cp, s, l);
        cp += l;
    }
    va_end(ap);
    *cp = '\0';
    return res;
}

/* ---- hash: real-APR contract -- apr_hash_set() stores the key/value POINTERS as given;
 * it does NOT copy the bytes they point to (documented APR behaviour, and the actual
 * mechanism this CVE exploits). Only the bookkeeping node itself comes from the hash
 * table's OWN (server-lifetime) pool, exactly like real apr_hash.c. ---- */
#define APR_HASH_KEY_STRING ((apr_ssize_t)-1)

typedef struct apr_hash_entry_t {
    struct apr_hash_entry_t *next;
    unsigned int hash;
    const void *key;
    apr_ssize_t klen;
    void *val;
} apr_hash_entry_t;

typedef struct apr_hash_t {
    apr_pool_t *pool;
    apr_hash_entry_t **array;
    unsigned int nbuckets;
} apr_hash_t;

#define APR_HASH_NBUCKETS 128

static unsigned int apr_hashfunc_default(const char *char_key, apr_ssize_t *klen)
{
    unsigned int hash = 0;
    const unsigned char *key = (const unsigned char *)char_key;
    const unsigned char *p;
    apr_ssize_t i;
    if (*klen == APR_HASH_KEY_STRING) {
        for (p = key; *p; p++) hash = hash * 33 + *p;
        *klen = (apr_ssize_t)(p - key);
    } else {
        for (p = key, i = *klen; i; i--, p++) hash = hash * 33 + *p;
    }
    return hash;
}

static apr_hash_t *apr_hash_make(apr_pool_t *pool)
{
    apr_hash_t *ht = (apr_hash_t *)apr_palloc(pool, sizeof(apr_hash_t));
    ht->pool = pool;
    ht->nbuckets = APR_HASH_NBUCKETS;
    ht->array = (apr_hash_entry_t **)apr_pcalloc(pool, ht->nbuckets * sizeof(apr_hash_entry_t *));
    return ht;
}

static apr_hash_entry_t **find_entry(apr_hash_t *ht, const void *key, apr_ssize_t klen, unsigned int hash)
{
    apr_hash_entry_t **hep;
    for (hep = &ht->array[hash % ht->nbuckets]; *hep; hep = &(*hep)->next) {
        if ((*hep)->hash == hash && (*hep)->klen == klen
            /* real key-content compare: dereferences (*hep)->key, the exact pointer
             * register_one_method() stored -- may be dangling. */
            && memcmp((*hep)->key, key, (size_t)klen) == 0) {
            break;
        }
    }
    return hep;
}

static void apr_hash_set(apr_hash_t *ht, const void *key, apr_ssize_t klen, const void *val)
{
    unsigned int hash;
    apr_hash_entry_t **hep;
    hash = apr_hashfunc_default((const char *)key, &klen);
    hep = find_entry(ht, key, klen, hash);
    if (*hep) {
        (*hep)->val = (void *)val;
        return;
    }
    {
        /* NEW entry: bookkeeping node from the hash table's OWN pool (server lifetime);
         * key/val pointers stored AS-IS from the caller (may be request-pool-scoped). */
        apr_hash_entry_t *e = (apr_hash_entry_t *)apr_palloc(ht->pool, sizeof(apr_hash_entry_t));
        e->hash = hash;
        e->key = key;
        e->klen = klen;
        e->val = (void *)val;
        e->next = NULL;
        *hep = e;
    }
}

static void *apr_hash_get(apr_hash_t *ht, const void *key, apr_ssize_t klen)
{
    unsigned int hash = apr_hashfunc_default((const char *)key, &klen);
    apr_hash_entry_t **hep = find_entry(ht, key, klen, hash);
    if (*hep) return (*hep)->val;
    return NULL;
}

/* ============================================================================
 * Real httpd struct layouts, verbatim field names/types (include/http_config.h,
 * include/util_cfgtree.h). Fields ap_limit_section never touches are kept as opaque
 * pointers (never dereferenced by the target); the fields it DOES access keep their
 * exact real names and types.
 * ============================================================================ */
typedef struct ap_directive_t ap_directive_t;
struct ap_directive_t {
    const char *directive;
    const char *args;
    struct ap_directive_t *next;
    struct ap_directive_t *first_child;
    struct ap_directive_t *parent;
    void *data;
};

struct apr_conf_vector_t;   /* opaque, unused by the target */

typedef const char *(*cmd_func) ();

typedef struct command_struct command_rec;
struct command_struct {
    const char *name;
    cmd_func func;
    void *cmd_data;
    int req_override;
    int args_how;
    const char *errmsg;
};

typedef struct cmd_parms_struct cmd_parms;
struct cmd_parms_struct {
    void *info;
    int override;
    int override_opts;
    void *override_list;              /* opaque apr_table_t*, unused by target */
    apr_int64_t limited;
    void *limited_xmethods;           /* opaque apr_array_header_t*, unused by target */
    void *xlimited;                   /* opaque ap_method_list_t*, unused by target */
    void *config_file;                /* opaque ap_configfile_t*, unused by target */
    ap_directive_t *directive;
    apr_pool_t *pool;
    apr_pool_t *temp_pool;
    void *server;                     /* opaque server_rec*, unused by target */
    char *path;
    const command_rec *cmd;
    struct apr_conf_vector_t *context;
    const ap_directive_t *err_directive;
    ap_directive_t *parent;
};

#define RAW_ARGS 0
#define AP_CORE_DECLARE_NONSTD(type) type   /* real macro expands to plain `type` on non-Windows */

/* ============================================================================
 * Real httpd config-word parser (server/util.c, verbatim) -- ap_limit_section's own
 * tokenizer for the method list.
 * ============================================================================ */
static char *substring_conf(apr_pool_t *p, const char *start, int len, char quote)
{
    char *result = apr_palloc(p, len + 1);
    char *resp = result;
    int i;

    for (i = 0; i < len; ++i) {
        if (start[i] == '\\' && (start[i + 1] == '\\'
                                 || (quote && start[i + 1] == quote)))
            *resp++ = start[++i];
        else
            *resp++ = start[i];
    }

    *resp++ = '\0';
    return result;
}

static char *ap_getword_conf(apr_pool_t *p, const char **line)
{
    const char *str = *line, *strend;
    char *res;
    char quote;

    while (apr_isspace(*str))
        ++str;

    if (!*str) {
        *line = str;
        return "";
    }

    if ((quote = *str) == '"' || quote == '\'') {
        strend = str + 1;
        while (*strend && *strend != quote) {
            if (*strend == '\\' && strend[1] &&
                (strend[1] == quote || strend[1] == '\\')) {
                strend += 2;
            }
            else {
                ++strend;
            }
        }
        res = substring_conf(p, str + 1, strend - str - 1, quote);

        if (*strend == quote)
            ++strend;
    }
    else {
        strend = str;
        while (*strend && !apr_isspace(*strend))
            ++strend;

        res = substring_conf(p, str, strend - str, 0);
    }

    while (apr_isspace(*strend))
        ++strend;
    *line = strend;
    return res;
}

#define ap_strrchr_c(s, c) strrchr(s, c)

/* ============================================================================
 * Real httpd dynamic-method registry (modules/http/http_protocol.c, verbatim). THIS is
 * the crash path: register_one_method()/ap_method_register() (the WRITE side, called
 * from ap_limit_section on an unrecognized method) and ap_method_number_of() (the READ
 * side, called from ap_limit_section at the top of its method-parsing loop) are copied
 * byte-for-byte.
 * ============================================================================ */
#define M_GET                   0
#define M_PUT                   1
#define M_POST                  2
#define M_DELETE                3
#define M_CONNECT               4
#define M_OPTIONS               5
#define M_TRACE                 6
#define M_INVALID               26
#define AP_METHOD_BIT ((apr_int64_t)1)

#define METHOD_NUMBER_FIRST (M_INVALID + 1)
#define METHOD_NUMBER_LAST  62

static apr_hash_t *methods_registry = NULL;
static int cur_method_number = METHOD_NUMBER_FIRST;

/* internal function to register one method/number pair */
static void register_one_method(apr_pool_t *p, const char *methname,
                                int methnum)
{
    int *pnum = apr_palloc(p, sizeof(*pnum));

    *pnum = methnum;
    apr_hash_set(methods_registry, methname, APR_HASH_KEY_STRING, pnum);
}

static int ap_method_register(apr_pool_t *p, const char *methname)
{
    int *methnum;

    if (methname == NULL) {
        return M_INVALID;
    }

    /* Check if the method was previously registered.  If it was
     * return the associated method number.
     */
    methnum = (int *)apr_hash_get(methods_registry, methname,
                                  APR_HASH_KEY_STRING);
    if (methnum != NULL)
        return *methnum;

    if (cur_method_number > METHOD_NUMBER_LAST) {
        return M_INVALID;
    }

    register_one_method(p, methname, cur_method_number);
    return cur_method_number++;
}

static int ap_method_number_of(const char *method)
{
    int len = strlen(method);

    /* check if the method has been dynamically registered */
    int *methnum = apr_hash_get(methods_registry, method, len);

    if (methnum != NULL) {
        return *methnum;
    }

    return M_INVALID;
}

/* ============================================================================
 * Real httpd error-string helpers, same file (server/core.c) as the target, verbatim.
 * ============================================================================ */
static char *unclosed_directive(cmd_parms *cmd)
{
    return apr_pstrcat(cmd->pool, cmd->cmd->name,
                       "> directive missing closing '>'", NULL);
}

static char *missing_container_arg(cmd_parms *cmd)
{
    return apr_pstrcat(cmd->pool, cmd->cmd->name,
                       "> directive requires additional arguments", NULL);
}

/* ============================================================================
 * ap_walk_config -- directive-tree recursion, orthogonal to the registry bug and never
 * reached on the crash path (the crash, when it happens, happens earlier, inside the
 * method-parsing loop). Stubbed as a no-op: real config-tree walking needs a whole
 * module/hook system this isolated harness has no use for.
 * ============================================================================ */
static const char *ap_walk_config(ap_directive_t *current, cmd_parms *cmd, struct apr_conf_vector_t *context)
{
    (void)current; (void)cmd; (void)context;
    return NULL;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the UAF report keeps its own stack frame (dc_batch requires the target
 * function's name in the ASAN backtrace). */
__attribute__((noinline))
AP_CORE_DECLARE_NONSTD(const char *) ap_limit_section(cmd_parms *cmd,
                                                      void *dummy,
                                                      const char *arg)
{
    const char *endp = ap_strrchr_c(arg, '>');
    const char *limited_methods;
    void *tog = cmd->cmd->cmd_data;
    apr_int64_t limited = 0;
    apr_int64_t old_limited = cmd->limited;
    const char *errmsg;

    if (endp == NULL) {
        return unclosed_directive(cmd);
    }

    limited_methods = apr_pstrmemdup(cmd->temp_pool, arg, endp - arg);

    if (!limited_methods[0]) {
        return missing_container_arg(cmd);
    }

    while (limited_methods[0]) {
        char *method = ap_getword_conf(cmd->temp_pool, &limited_methods);
        int methnum;

        /* check for builtin or module registered method number */
        methnum = ap_method_number_of(method);

        if (methnum == M_TRACE && !tog) {
            return "TRACE cannot be controlled by <Limit>, see TraceEnable";
        }
        else if (methnum == M_INVALID) {
            /* method has not been registered yet, but resource restriction
             * is always checked before method handling, so register it.
             */
            methnum = ap_method_register(cmd->pool,
                                         apr_pstrdup(cmd->pool, method));
        }

        limited |= (AP_METHOD_BIT << methnum);
    }

    /* Killing two features with one function,
     * if (tog == NULL) <Limit>, else <LimitExcept>
     */
    limited = tog ? ~limited : limited;

    if (!(old_limited & limited)) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive excludes all methods", NULL);
    }
    else if ((old_limited & limited) == old_limited) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           "> directive specifies methods already excluded",
                           NULL);
    }

    cmd->limited &= limited;

    errmsg = ap_walk_config(cmd->directive->first_child, cmd, cmd->context);

    cmd->limited = old_limited;

    return errmsg;
}

/* ================= driver ================= */
static cmd_parms *make_cmd(apr_pool_t *pool, const command_rec *cmdrec)
{
    cmd_parms *cmd = (cmd_parms *)malloc(sizeof(cmd_parms));
    memset(cmd, 0, sizeof(*cmd));
    cmd->cmd = cmdrec;
    cmd->pool = pool;
    cmd->temp_pool = pool;      /* .htaccess processing: pool == temp_pool (the exact
                                  * condition the official fix's new guard checks for). */
    cmd->limited = -1;          /* apr_int64_t -1: nothing excluded yet (real init value) */
    {
        ap_directive_t *dir = (ap_directive_t *)apr_palloc(pool, sizeof(ap_directive_t));
        memset(dir, 0, sizeof(*dir));
        cmd->directive = dir;   /* first_child == NULL -> ap_walk_config stub, no-op */
    }
    cmd->context = NULL;
    return cmd;
}

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

    /* HEAP-allocated, ASAN-guarded attacker input -- this file's raw bytes ARE the `arg`
     * ap_limit_section() would receive for a "<Limit ARG" directive (the config parser
     * strips the "<Limit"/"<LimitExcept" keyword before invoking the section handler
     * with the remainder). */
    char *arg = (char *)malloc(n + 1);
    if (!arg) { fclose(fp); return 2; }
    size_t got = fread(arg, 1, n, fp);
    fclose(fp);
    arg[got] = '\0';

    static const command_rec limit_cmd = {
        "Limit", NULL, NULL /* cmd_data==NULL -> <Limit>, not <LimitExcept> */,
        0, RAW_ARGS, "..."
    };

    /* Server-lifetime pool + registry: mirrors ap_method_registry_init() being called
     * once at startup, pre-registering the standard methods exactly like the real init
     * does, so they never take the dynamic-registration path. */
    apr_pool_t *global_pool = pool_create();
    methods_registry = apr_hash_make(global_pool);
    cur_method_number = METHOD_NUMBER_FIRST;
    register_one_method(global_pool, "GET", M_GET);
    register_one_method(global_pool, "HEAD", M_GET);
    register_one_method(global_pool, "PUT", M_PUT);
    register_one_method(global_pool, "POST", M_POST);
    register_one_method(global_pool, "DELETE", M_DELETE);
    register_one_method(global_pool, "CONNECT", M_CONNECT);
    register_one_method(global_pool, "OPTIONS", M_OPTIONS);
    register_one_method(global_pool, "TRACE", M_TRACE);

    /* volatile function pointer: forbid the compiler from proving away or folding either
     * call to ap_limit_section (it already can't, since it mutates the global registry
     * and calls through cmd->cmd->func-shaped indirection, but keep the established
     * pattern used across this CVE wave). */
    const char *(* volatile fn)(cmd_parms *, void *, const char *) = ap_limit_section;

    /* ---- call 1: "request" #1 parses the attacker's <Limit ARG> from .htaccess context
     * (cmd->pool == cmd->temp_pool). If ARG names an unrecognized method, it gets
     * registered into the server-lifetime methods_registry with its key/value memory
     * backed by THIS pool. ---- */
    apr_pool_t *req1 = pool_create();
    cmd_parms *cmd1 = make_cmd(req1, &limit_cmd);
    fn(cmd1, NULL, arg);

    /* end of request #1: httpd recycles/clears the per-request pool. */
    free(cmd1);
    pool_destroy(req1);

    /* ---- call 2: a LATER, independent request re-parses the exact same directive text
     * (e.g. the next hit under the same .htaccess-guarded directory). ap_limit_section's
     * own ap_method_number_of() call, at the top of its method-parsing loop, looks the
     * same method name up again -- finds the entry request #1 planted, and dereferences
     * its now-freed key to verify the match. ---- */
    apr_pool_t *req2 = pool_create();
    cmd_parms *cmd2 = make_cmd(req2, &limit_cmd);
    fn(cmd2, NULL, arg);

    free(cmd2);
    pool_destroy(req2);

    free(arg);
    return 0;
}
