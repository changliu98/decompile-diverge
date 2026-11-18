/* cve_barebone direct-call harness for CVE-2019-20176 (pure-ftpd)
 * Target: listdir  (src/ls.c)
 * Bug class: stack exhaustion (CWE-674, "Uncontrolled Recursion" -- ASAN reports it as
 *   `stack-overflow`) caused by an `ALLOCA()` (== alloca(), the real Linux build config)
 *   call placed INSIDE the `while (opt_R && r != s)` loop body. Per gcc's own alloca(3)
 *   documentation: memory obtained via alloca() is not released until the ENCLOSING
 *   FUNCTION returns, not at the end of the loop body/block -- so every loop iteration
 *   that takes the `!chdir(FI_NAME(r))` branch piles ANOTHER `PATH_MAX+1` bytes onto
 *   listdir's own stack frame, on top of every earlier iteration's allocation, for the
 *   entire lifetime of THIS listdir() call. A directory containing many subdirectories
 *   (fully attacker-controlled via ordinary MKD + LIST -R) is enough to exhaust the
 *   stack and crash. The fix (jedisct1/pure-ftpd@aea56f4) hoists the alloca() call to
 *   run ONCE per listdir() invocation (before the loop) instead of once per entry.
 * Official NVD description: "In Pure-FTPd 1.0.49, a stack exhaustion issue was
 *   discovered in the listdir function in ls.c."
 *
 * listdir's own body drives the whole crash: sreaddir() (verbatim, real opendir/readdir
 * scan of the CURRENT directory -- no fake PureFileInfo array needed), listfile()
 * (verbatim; with the real `-F` classify flag it returns non-zero for directories so
 * they survive into the opt_R recursion loop), outputfiles()/addfile()/wrstr() (verbatim
 * bookkeeping/output plumbing), cmp() family + qsort (verbatim sort). addreply()/die()/
 * safe_write()/getname()/getgroup() are minimal faithful stand-ins for code paths that
 * are either never reached on this crash path (addreply: only on sreaddir() failure;
 * die: only the "someone rmdir()'d it" defensive branch) or genuinely incidental
 * (safe_write: a blocking write() loop, matching upstream's contract; getname/getgroup:
 * upstream itself ships a byte-identical trivial `#ifdef NO_FTP_USERS` variant of both,
 * used here verbatim since opt_l is off and neither is ever actually invoked).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#include <syslog.h>
#include <alloca.h>
#include <fcntl.h>

/* ---- real ftpd.h macros/types (verbatim) ---------------------------------- */

typedef struct PureFileInfo_ {
    char **names_pnt;
    size_t name_offset;
    off_t size;
    time_t mtime;
    mode_t mode;
    nlink_t nlink;
    uid_t uid;
    gid_t gid;
} PureFileInfo;

#define FI_NAME(X) (*((X)->names_pnt) + (X)->name_offset)

/* HAVE_ALLOCA branch -- the real, default Linux build config; this is the branch the
 * CVE actually lives in (the malloc/free fallback branch is self-balanced and safe). */
#define ALLOCA(X) alloca(X)
#define ALLOCA_FREE(X) do { } while (0)

/* CONF_SNPRINTF_TYPE == 8 (C99 snprintf) branch, verbatim. */
#define SNCHECK(CALL, SIZE) ((CALL) >= ((int) (SIZE)))

/* DISABLE_UNICODE_CONTROL_CHARS undefined branch, verbatim. */
#define ISCTRLCODE(X) ((X) == 0x7f || ((unsigned char) (X)) < 32U)

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

#ifndef DEFAULT_MAX_LS_FILES
# define DEFAULT_MAX_LS_FILES 10000U
#endif
#ifndef DEFAULT_MAX_LS_DEPTH
# define DEFAULT_MAX_LS_DEPTH 5U
#endif

#if CONF_TCP_SO_SNDBUF_UNUSED
#endif
#define CONF_TCP_SO_SNDBUF 65536

/* ---- real ls_p.h globals (verbatim; NO_FTP_USERS variant -- no userid/groupid) ---- */

static size_t page_size;
#define CHUNK_SIZE page_size

static unsigned int colwidth;
static unsigned int filenames;

struct filename {
    struct filename *down;
    struct filename *right;
    int top;
    char line[1];
};

static struct filename *head;
static struct filename *tail;
static unsigned int matches;

/* ls options (verbatim names) */
int opt_a, opt_C, opt_d, opt_F, opt_l, opt_R, opt_r, opt_t, opt_S;

/* ---- real globals.h globals (verbatim defaults) ---------------------------- */

static char wd[PATH_MAX + 1U];              /* current working directory */
static signed char broken_client_compat;    /* don't enable workarounds by default */
static unsigned int max_ls_files = DEFAULT_MAX_LS_FILES;
static unsigned int max_ls_depth = DEFAULT_MAX_LS_DEPTH;
static const char *months[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/* ---- minimal faithful stand-ins for callees off the crash path ------------- */

/* Only invoked if sreaddir() fails (never happens: we always chdir into a real,
 * readable directory before calling listdir). */
void addreply(const int code, const char * const line, ...)
{
    (void) code; (void) line;
}

/* Only invoked on the defensive "someone rmdir()'d it while we were listing"
 * double-chdir-failure path -- unreachable here since our chdir("..") always
 * succeeds. Faithful shape: report + terminate. */
void die(const int err, const int priority, const char * const format, ...)
{
    va_list ap;
    (void) priority;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    _exit(err);
}

/* Real upstream contract (safe_rw.h): a short-write-safe wrapper around write(2).
 * The real implementation additionally does select()-based timeout handling; timeout
 * is unused here (we never actually block -- `f` is opened on /dev/null). */
ssize_t safe_write(const int fd, const void * const buf_, size_t count, const int timeout)
{
    const char *buf = (const char *) buf_;
    size_t written = 0;
    ssize_t n;
    (void) timeout;
    while (written < count) {
        n = write(fd, buf + written, count - written);
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        if (n == 0) {
            break;
        }
        written += (size_t) n;
    }
    return (ssize_t) written;
}

/* Upstream's own `#ifdef NO_FTP_USERS` variant, verbatim -- byte-identical to the
 * normal variant's semantics when there's no passwd/group lookup available. Never
 * actually called on this crash path (only reached from listfile()'s opt_l branch,
 * and this harness runs with opt_l == 0). */
const char *getname(const uid_t uid)
{
    static char number[11];
    snprintf(number, sizeof number, "%-10d", uid);
    return number;
}

const char *getgroup(const gid_t gid)
{
    static char number[11];
    snprintf(number, sizeof number, "%-10d", gid);
    return number;
}

int checkprintable(const char *s)
{
    int ret = 0;
    unsigned char c;

    while ((c = (unsigned char) *s) != 0U) {
        if (ISCTRLCODE(c)) {
            ret--;
            break;
        }
        s++;
    }

    return ret;
}

/* ==== VERBATIM from data_cve/cve_953b134c/source_code/src/ls.c (real callees on the
 * crash path) ================================================================= */

static void wrstr(const int f, void * const tls_fd, const char *s)
{
    static char outbuf[CONF_TCP_SO_SNDBUF];
    static size_t outcnt;
    size_t l;

    if (s == NULL) {
        if (outcnt > (size_t) 0U) {
            {
                (void) tls_fd;
                if (safe_write(f, outbuf, outcnt, -1) != (ssize_t) outcnt) {
                    return;
                }
            }
        }
        outcnt = (size_t) 0U;
        return;
    }
    if ((l = strlen(s)) <= (size_t) 0U) {
        return;
    }
    if (l <= (sizeof outbuf - outcnt)) {
        memcpy(outbuf + outcnt, s, l); /* secure, see above */
        outcnt += l;
        return;
    }
    if (outcnt < sizeof outbuf) {
        const size_t rest = sizeof outbuf - outcnt;

        memcpy(outbuf + outcnt, s, rest);   /* secure, see above */
        s += rest;
        l -= rest;
    }
    {
        if (safe_write(f, outbuf, sizeof outbuf, -1) !=
            (ssize_t) sizeof outbuf) {
            return;
        }
    }
    {
        while (l > sizeof outbuf) {
            if (safe_write(f, s, sizeof outbuf, -1) !=
                (ssize_t) sizeof outbuf) {
                return;
            }
            s += sizeof outbuf;
            l -= sizeof outbuf;
        }
    }
    if (l > (size_t) 0U) {
        memcpy(outbuf, s, l);          /* safe, l <= sizeof outbuf */
        outcnt = l;
    }
}

static void addfile(const char *name, const char *suffix)
{
    struct filename *p;
    unsigned int l;

    if (!name || !suffix) {
        return;
    }
    if (matches >= max_ls_files) {
        return;
    }
    matches++;
    l = (unsigned int) (strlen(name) + strlen(suffix));
    if (l > colwidth) {
        colwidth = l;
    }
    if ((p = malloc(offsetof(struct filename, line) + l + 1U)) == NULL) {
        return;
    }
    if (SNCHECK(snprintf(p->line, l + 1U, "%s%s", name, suffix), l + 1U)) {
        _exit(EXIT_FAILURE);
    }
    if (tail != NULL) {
        tail->down = p;
    } else {
        head = p;
    }
    tail = p;
    filenames++;
}

/* listfile returns non-zero if the file is a directory */
static int listfile(const PureFileInfo * const fi, const char *name)
{
    int rval = 0;
    struct stat st;
    struct tm *t;
    char suffix[2] = { 0, 0 };

    if (fi == NULL) {
        if (lstat(name, &st) < 0) {
            return 0;
        }
    } else {
        st.st_size = fi->size;
        st.st_mtime = fi->mtime;
        st.st_mode = fi->mode;
        st.st_nlink = fi->nlink;
        st.st_uid = fi->uid;
        st.st_gid = fi->gid;
        name = FI_NAME(fi);
    }
    if (
        broken_client_compat != 0 &&
        S_ISLNK(st.st_mode)) {
        struct stat sts;

        if (stat(name, &sts) == 0 && !S_ISLNK(sts.st_mode)) {
            st = sts;
        }
    } /* Show non-dangling symlinks as files/directories */
    t = localtime((time_t *) &st.st_mtime);
    if (t == NULL) {
        return 0;
    }
    if (opt_F) {
        if (S_ISLNK(st.st_mode))
            suffix[0] = '@';
        else if (S_ISDIR(st.st_mode)) {
            suffix[0] = '/';
            rval = 1;
        } else if (st.st_mode & 010101) {
            suffix[0] = '*';
        }
    }
    if (opt_l) {
        char *alloca_nameline;
        const size_t sizeof_nameline = PATH_MAX + PATH_MAX + 128U;
        char timeline[6U];
        char m[PATH_MAX + 1U];
        const char *format;

        strncpy(m, " ---------", (sizeof m) - (size_t) 1U);
        m[(sizeof m) - (size_t) 1U] = 0;
        switch (st.st_mode & S_IFMT) {
        case S_IFREG:
            m[0] = '-';
            break;
        case S_IFLNK:
            m[0] = 'l';
            break;            /* readlink() here? */
        case S_IFDIR:
            m[0] = 'd';
            rval = 1;
            break;
        }
        if (m[0] != ' ') {
            if (st.st_mode & 0400) {
                m[1] = 'r';
            }
            if (st.st_mode & 0200) {
                m[2] = 'w';
            }
            if (st.st_mode & 0100) {
                m[3] = (char) (st.st_mode & 04000 ? 's' : 'x');
            } else if (st.st_mode & 04000) {
                m[3] = 'S';
            }
            if (st.st_mode & 040) {
                m[4] = 'r';
            }
            if (st.st_mode & 020) {
                m[5] = 'w';
            }
            if (st.st_mode & 010) {
                m[6] = (char) (st.st_mode & 02000 ? 's' : 'x');
            } else if (st.st_mode & 02000) {
                m[6] = 'S';
            }
            if (st.st_mode & 04) {
                m[7] = 'r';
            }
            if (st.st_mode & 02) {
                m[8] = 'w';
            }
            if (st.st_mode & 01) {
                m[9] = (char) (st.st_mode & 01000 ? 't' : 'x');
            } else if (st.st_mode & 01000) {
                m[9] = 'T';
            }
            if (time(NULL) - st.st_mtime > 180 * 24 * 60 * 60) {
                if (SNCHECK(snprintf(timeline, sizeof timeline, "%5d",
                                     t->tm_year + 1900), sizeof timeline)) {
                    _exit(EXIT_FAILURE);
                }
            } else {
                if (SNCHECK(snprintf(timeline, sizeof timeline, "%02d:%02d",
                                     t->tm_hour, t->tm_min), sizeof timeline)) {
                    _exit(EXIT_FAILURE);
                }
            }
            if ((alloca_nameline = ALLOCA(sizeof_nameline)) == NULL) {
                return 0;
            }
            if (st.st_size < 10000000000U) {
                format = "%s %4u %s %s %10llu %s %2d %s %s";
            } else {
                format = "%s %4u %s %s %18llu %s %2d %s %s";
            }
            if (SNCHECK(snprintf(alloca_nameline, sizeof_nameline,
                                 format,
                                 m, (unsigned int) st.st_nlink,
                                 getname(st.st_uid),
                                 getgroup(st.st_gid),
                                 (unsigned long long) st.st_size,
                                 months[t->tm_mon],
                                 t->tm_mday, timeline, name),
                        sizeof_nameline)) {
                ALLOCA_FREE(alloca_nameline);
                _exit(EXIT_FAILURE);
            }
            if (S_ISLNK(st.st_mode)) {
                char *p = alloca_nameline + strlen(alloca_nameline);
                {
                    ssize_t sx;

                    if ((sx = readlink(name, m, sizeof m - 1U)) > 0) {
                        m[sx] = 0;
                    } else {
                        m[0] = m[1] = '.';
                        m[2] = 0;
                    }
                }
                suffix[0] = 0;
                if (opt_F && stat(name, &st) == 0) {
                    if (S_ISLNK(st.st_mode)) {
                        suffix[0] = '@';
                    } else if (S_ISDIR(st.st_mode)) {
                        suffix[0] = '/';
                    } else if (st.st_mode & 010101) {
                        suffix[0] = '*';
                    }
                }
                if (SNCHECK
                    (snprintf(p, (sizeof_nameline) - strlen(alloca_nameline),
                              " -> %s", m),
                     (sizeof_nameline) - strlen(alloca_nameline))) {
                    ALLOCA_FREE(alloca_nameline);
                    _exit(EXIT_FAILURE);
                }
            }
            addfile(alloca_nameline, suffix);
            ALLOCA_FREE(alloca_nameline);
        }                    /* hide non-downloadable files */
    } else {
        if (S_ISREG(st.st_mode) ||
            S_ISDIR(st.st_mode) || S_ISLNK(st.st_mode)) {
            addfile(name, suffix);
        }
    }
    return rval;
}

static void outputfiles(int f, void * const tls_fd)
{
    unsigned int n;
    struct filename *p;
    struct filename *q;

    if (!head) {
        return;
    }
    tail->down = NULL;
    tail = NULL;
    colwidth = (colwidth | 7U) + 1U;
    if (opt_l != 0 || opt_C == 0) {
        colwidth = 75U;
    }
    /* set up first column */
    p = head;
    p->top = 1;
    if (colwidth > 75U) {
        n = filenames;
    } else {
        n = (filenames + (75U / colwidth) - 1U) / (75U / colwidth);
    }
    while (n && p) {
        p = p->down;
        if (p != NULL) {
            p->top = 0;
        }
        n--;
    }

    /* while there's a neighbour to the right, point at it */
    q = head;
    while (p) {
        p->top = q->top;
        q->right = p;
        q = q->down;
        p = p->down;
    }

    /* some are at the right end */
    while (q) {
        q->right = NULL;
        q = q->down;
    }

    /* don't want wraparound, do we? */
    p = head;
    while (p && p->down && !p->down->top) {
        p = p->down;
    }
    if (p && p->down) {
        p->down = NULL;
    }

    /* print each line, which consists of each column */
    p = head;
    while (p) {
        q = p;
        p = p->down;
        while (q) {
            char pad[6];
            char *tmp = (char *) q;

            if (q->right) {
                memset(pad, '\t', sizeof pad - 1U);
                pad[(sizeof pad) - 1] = 0;
                pad[(colwidth + 7U - strlen(q->line)) / 8] = 0;
            } else {
                pad[0] = '\r';
                pad[1] = '\n';
                pad[2] = 0;
            }
            wrstr(f, tls_fd, q->line);
            wrstr(f, tls_fd, pad);
            q = q->right;
            free(tmp);
            tmp = NULL;
        }
    }

    /* reset variables for next time */
    head = tail = NULL;
    colwidth = 0U;
    filenames = 0U;
}

/* functions to to sort for qsort() */
static int cmp(const void * const a, const void * const b)
{
    return strcmp(FI_NAME((const PureFileInfo *) a),
                  FI_NAME((const PureFileInfo *) b));
}

static int cmp_r(const void * const a, const void * const b)
{
    return strcmp(FI_NAME((const PureFileInfo *) b),
                  FI_NAME((const PureFileInfo *) a));
}

static int cmp_t(const void * const a, const void * const b)
{
    if (((const PureFileInfo *) a)->mtime < ((const PureFileInfo *) b)->mtime) {
        return 1;
    }
    if (((const PureFileInfo *) a)->mtime > ((const PureFileInfo *) b)->mtime) {
        return -1;
    }
    return 0;
}

static int cmp_rt(const void * const a, const void * const b)
{
    return cmp_t(b, a);
}

static int cmp_S(const void * const a, const void * const b)
{
    if (((const PureFileInfo *) a)->size < ((const PureFileInfo *) b)->size) {
        return 1;
    }
    if (((const PureFileInfo *) a)->size > ((const PureFileInfo *) b)->size) {
        return -1;
    }
    return 0;
}

static int cmp_rS(const void * const a, const void * const b)
{
    return cmp_S(b, a);
}

static PureFileInfo *sreaddir(char **names_pnt)
{
    struct stat st;
    DIR *d;
    struct dirent *de;
    PureFileInfo *files_info;
    PureFileInfo *file_info;
    size_t files_info_size;
    size_t files_info_counter = (size_t) 0U;
    char *names;
    size_t names_size;
    size_t names_counter = (size_t) 0U;
    size_t name_len;
    int (*cmp_func)(const void * const, const void * const);

    if ((d = opendir(".")) == NULL) {
        return NULL;
    }
    names_size = CHUNK_SIZE;
    if ((names = malloc(names_size)) == NULL) {
        closedir(d);
        return NULL;
    }
    files_info_size = CHUNK_SIZE / sizeof *files_info;
    if ((files_info = malloc(files_info_size * sizeof *files_info)) == NULL) {
        closedir(d);
        free(names);
        return NULL;
    }
    while ((de = readdir(d)) != NULL) {
        if (checkprintable(de->d_name) != 0 || lstat(de->d_name, &st) < 0) {
            continue;
        }
        name_len = strlen(de->d_name) + (size_t) 1U;
        while (names_counter + name_len >= names_size) {
            char *new_names;

            if (name_len >= CHUNK_SIZE) {
                names_size += name_len + CHUNK_SIZE;
            } else {
                names_size += CHUNK_SIZE;
            }
            if ((new_names = realloc(names, names_size)) == NULL) {
                nomem:
                closedir(d);
                free(names);
                free(files_info);
                return NULL;
            }
            names = new_names;
        }
        while ((files_info_counter + (size_t) 1U) >= files_info_size) {
            PureFileInfo *new_files_info;

            files_info_size += (CHUNK_SIZE / sizeof *files_info);
            if ((new_files_info = realloc(files_info,
                                          files_info_size * sizeof *files_info)) == NULL) {
                goto nomem;
            }
            files_info = new_files_info;
        }
        memcpy(&names[names_counter], de->d_name, name_len);   /* safe */
        names[names_counter + name_len - 1] = 0;
        file_info = &files_info[files_info_counter];
        file_info->names_pnt = names_pnt;
        file_info->name_offset = names_counter;
        file_info->size = st.st_size;
        file_info->mtime = st.st_mtime;
        file_info->mode = st.st_mode;
        file_info->nlink = st.st_nlink;
        file_info->uid = st.st_uid;
        file_info->gid = st.st_gid;
        names_counter += name_len;
        files_info_counter++;
    }
    closedir(d);
    files_info[files_info_counter].name_offset = (size_t) -1;
    *names_pnt = names;

    if (opt_t) {
        if (opt_r) {
            cmp_func = cmp_rt;
        } else {
            cmp_func = cmp_t;
        }
    } else if (opt_S) {
        if (opt_r) {
            cmp_func = cmp_rS;
        } else {
            cmp_func = cmp_S;
        }
    } else if (opt_r) {
        cmp_func = cmp_r;
    } else {
        cmp_func = cmp;
    }
    qsort(files_info, files_info_counter, sizeof files_info[0], cmp_func);

    return files_info;
}

/* ==== VERBATIM from data_cve/cve_953b134c/target/original_function.c (byte-for-byte,
 * this is the CVE-2019-20176 target function) ================================= */

#define MSG_CANT_READ_FILE "Sorry, we were unable to read [%s]"

/* have to change to the directory first (speed hack for -R) */
static void listdir(unsigned int depth, int f, void * const tls_fd,
                    const char *name)
{
    PureFileInfo *dir;
    char *names;
    PureFileInfo *s;
    PureFileInfo *r;
    int d;

    if (depth >= max_ls_depth || matches >= max_ls_files) {
        return;
    }
    if ((dir = sreaddir(&names)) == NULL) {
        addreply(226, MSG_CANT_READ_FILE, name);
        return;
    }
    s = dir;
    while (s->name_offset != (size_t) -1) {
        d = 0;
        if (FI_NAME(s)[0] != '.') {
            d = listfile(s, NULL);
        } else if (opt_a) {
            if (FI_NAME(s)[1] == 0 ||
                (FI_NAME(s)[1] == '.' && FI_NAME(s)[2] == 0)) {
                listfile(s, NULL);
            } else {
                d = listfile(s, NULL);
            }
        }
        if (!d) {
            s->name_offset = (size_t) -1;
        }
        s++;
    }
    outputfiles(f, tls_fd);
    r = dir;
    while (opt_R && r != s) {
        if (r->name_offset != (size_t) -1 && !chdir(FI_NAME(r))) {
            char *alloca_subdir;
            const size_t sizeof_subdir = PATH_MAX + 1U;

            if ((alloca_subdir = ALLOCA(sizeof_subdir)) == NULL) {
                goto toomany;
            }
            if (SNCHECK(snprintf(alloca_subdir, sizeof_subdir, "%s/%s",
                                 name, FI_NAME(r)), sizeof_subdir)) {
                goto nolist;
            }
            wrstr(f, tls_fd, "\r\n\r\n");
            wrstr(f, tls_fd, alloca_subdir);
            wrstr(f, tls_fd, ":\r\n\r\n");
            listdir(depth + 1U, f, tls_fd, alloca_subdir);
            nolist:
            ALLOCA_FREE(alloca_subdir);
            if (matches >= max_ls_files) {
                goto toomany;
            }
            if (chdir("..")) {    /* defensive in the extreme... */
                if (chdir(wd) || chdir(name)) {    /* someone rmdir()'d it? */
                    die(421, LOG_ERR, "chdir: %s", strerror(errno));
                }
            }
        }
        r++;
    }
    toomany:
    free(names);
    free(dir);
    names = NULL;
}
/* ==== end verbatim ==== */

/* ---- driver ----------------------------------------------------------------- */

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 0;
    }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        return 0;
    }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 0; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 0; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 0; }

    /* HEAP-allocate the raw input so ASAN guards it. */
    unsigned char *ibuf = (unsigned char *) malloc((size_t) fsz > 0 ? (size_t) fsz : 1);
    if (!ibuf) { fclose(fp); return 0; }
    size_t irn = fsz > 0 ? fread(ibuf, 1, (size_t) fsz, fp) : 0;
    fclose(fp);

    /* FDP-style argument construction: the input's first 4 bytes (little-endian),
     * or its single byte if shorter, choose N -- the number of subdirectories the
     * attacker has created (via ordinary MKD) inside the directory they then LIST -R.
     * That subdirectory count is exactly the attacker-controlled quantity this bug is
     * sensitive to: each one that pure-ftpd descends into during the recursive listing
     * piles another ALLOCA(PATH_MAX+1) onto listdir()'s stack frame. */
    uint32_t n = 0;
    if (irn >= 4) {
        n = (uint32_t) ibuf[0] | ((uint32_t) ibuf[1] << 8) |
            ((uint32_t) ibuf[2] << 16) | ((uint32_t) ibuf[3] << 24);
    } else if (irn > 0) {
        n = ibuf[0];
    }
    free(ibuf);
    if (n > 9500U) {
        n = 9500U;   /* sanity clamp only -- stay under max_ls_files (10000) so every
                       * entry survives to the alloca loop instead of an early cutoff */
    }

    char scratch[] = "/tmp/pfd_dc_XXXXXX";
    char *root = mkdtemp(scratch);
    if (!root) {
        return 0;
    }
    if (chdir(root) != 0) {
        return 0;
    }
    for (uint32_t i = 0; i < n; i++) {
        char name[32];
        snprintf(name, sizeof name, "d%u", i);
        if (mkdir(name, 0700) != 0) {
            break;
        }
    }

#if defined(_SC_PAGESIZE)
    page_size = (size_t) sysconf(_SC_PAGESIZE);
#else
    page_size = (size_t) 4096U;
#endif
    if (page_size == 0) {
        page_size = 4096U;
    }
    strncpy(wd, root, sizeof(wd) - 1U);
    wd[sizeof(wd) - 1U] = 0;

    /* LIST -R -F: recursive, classify-directories-with-'/' -- a real, ordinary FTP
     * client listing mode; no other opt_* flags set (matches upstream's zero-init). */
    opt_R = 1;
    opt_F = 1;

    int devnull = open("/dev/null", O_WRONLY);
    if (devnull < 0) {
        devnull = 1;
    }

    listdir(0U, devnull, NULL, ".");

    if (devnull > 2) {
        close(devnull);
    }
    return 0;
}
