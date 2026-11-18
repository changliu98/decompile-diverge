/* Direct-call ASAN harness for weborf CVE-2023-46586 (cgi_execute_child).
 *
 * Fix commit 49824204add55aab0568d90a6b1e7c822d32120d replaces
 *     executor = malloc(connection_prop->strfile_len + 1);
 *     strncpy(executor, connection_prop->strfile, connection_prop->strfile_len);
 * with a plain
 *     executor = connection_prop->strfile;
 * NVD's text: "cgi.c in weborf ... lacks '\0' termination of the path for CGI
 * scripts because strncpy is misused." The two removed lines are the entire
 * bug: strncpy's `n` argument both bounds the destination write AND controls
 * how far the source is scanned before a NUL is honoured. That `n` comes
 * from connection_prop->strfile_len, a plain struct field with no assertion
 * that it actually bounds connection_prop->strfile's real allocation.
 *
 * The described *consequence* (the resulting `executor` is later handed to
 * execl() unterminated) is not independently observable from a black-box
 * unit harness: execl()/execve() pass the pointer straight to the kernel,
 * which copies it in kernel space -- outside ASan's userspace
 * instrumentation. Verified empirically (see work notes): even a
 * maximally-poisoned 4-byte malloc with execl() called on it runs clean
 * under ASan, exit 0, no report.
 *
 * What IS directly, mechanically unsafe is the strncpy call itself: when
 * strfile_len does not honestly bound strfile's real allocation (both are
 * plain fields of the attacker-reachable connection_prop struct passed into
 * this function), the strncpy at the exact line the fix deletes reads past
 * the end of the heap `strfile` buffer -- a heap out-of-bounds READ
 * (CWE-125), asserted by ASan's strncpy interceptor right at the call site
 * the patch removes. This harness reproduces that.
 *
 * Modes, selected by input byte 0:
 *   'T' -- TRIGGER: strfile is a K-byte heap buffer with no NUL in it;
 *          strfile_len is set to K+64 (> the real allocation) and
 *          executor="" so cgi_execute_child takes the buggy
 *          malloc+strncpy branch -> strncpy over-reads strfile -> ASan
 *          heap-buffer-overflow READ, inside cgi_execute_child's own body.
 *   'D' -- DEEP-SAFE: same branch, but strfile_len correctly equals
 *          strlen(strfile) for a properly NUL-terminated, '/'-containing
 *          strfile -> strncpy stays in bounds -> falls through
 *          cgi_set_env_vars/cgi_child_chdir/execl and exits cleanly
 *          (execl's target does not exist -> exit(1)).
 *   else -- SAFE (early-exit): wpipe is deliberately invalid so dup() fails
 *          immediately and cgi_execute_child takes its own `error:` path
 *          and exit(1)s before ever touching connection_prop/executor.
 */
#include <ctype.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <unistd.h>

/* ---- options.h subset (verbatim values from source_code/options.h.in) ---- */
#define MAXINDEXCOUNT 10
#define SCRPT_TIMEOUT 30
#define SIGNATURE "weborf/1.0 (GNU/Linux)"
/* HIDE_CGI_ERRORS and SERVERDBG are intentionally NOT defined: HIDE_CGI_ERRORS
   would close(STDERR) before the buggy line runs, silently swallowing the
   ASan report we need to observe; SERVERDBG only gates diagnostic
   syslog()/perror() calls. Neither touches the vulnerable data flow. */

/* ---- types.h subset (verbatim; HAVE_LIBSSL/SEND_MIMETYPES/IPV6 undefined,
   matching the common non-SSL, non-libmagic, IPv4 build) ---- */
typedef int fd_t;

typedef struct {
    ssize_t len;                //length of the array
    char *data[MAXINDEXCOUNT];  //Array containing pointers
    int data_l[MAXINDEXCOUNT];  //Array containing len of strings
} array_ll;

typedef struct {
    fd_t sock;                 //File and ssl descriptor for the socket
    char ip_addr[INET_ADDRSTRLEN];              //ip address in string format

    bool keep_alive;            //True if we are using pipelining
    short int protocol_version; //See defines like HTTP_something
    int method_id;              //Index of the http method used (GET, POST)
    char *method;               //String version of the http method used
    char *http_param;           //Param string
    char *page;                 //Requested URI
    ssize_t page_len;           //Lengh of the page string
    char *get_params;           //Params in the URI, after the ? char
    char *strfile;              //File on filesystem
    ssize_t strfile_len;        //Length of string strfile
    struct stat strfile_stat;   //Stat of strfile
    int strfile_fd;             //File descriptor for strfile
    char *basedir;              //Basedir for the host
    unsigned int status_code;   //HTTP status code

} connection_t;

typedef struct {
    ssize_t len;                //length of the string
    char *data;                 //Pointer to string
} string_t;

typedef struct {
    char *basedir;
    char* authsock;             //Executable that will authenticate
    uid_t uid;                  //Uid to use after bind
    gid_t gid;                  //gid to use after bind
    bool is_inetd;              //True if it expects to be executed by inetd
    array_ll cgi_paths;         //Paths to cgi binaries
    bool virtual_host;          //True if must check for virtual hosts
    bool exec_script;           //Enable CGI if false
    bool tar_directory;         //Sends directories compressed into tar-files
    bool daemonize;             //Run daemon()
    char *ip;                   //IP addr with default value
    char *port;                 //port with default value

    char *indexes[MAXINDEXCOUNT];//List of pointers to index files
    int indexes_l;              //Count of the list
} weborf_configuration_t;

/* ---- myio.h subset (verbatim, non-SSL variant) ---- */
static inline int myio_getfd(fd_t fd) { return fd; }

/* ---- mystring.c helpers (verbatim), used by cgi_set_http_env_vars ---- */
void delChar(char *string, int pos, int n) {
    size_t l = strlen(string + pos);

    if (l < n)
        return;
    l -= n;
    memmove(string + pos, string + pos + n, l);
    string[l] = 0;

    return;
}

void strReplace(char *string, char *substr, char with) {
    char *pointer;
    int substrlen = strlen(substr);

    while ((pointer = strstr(string, substr)) != NULL) {
        delChar(pointer, 0, substrlen - 1);
        pointer[0] = with;
        string=pointer;
    }
}

void strToUpper(char *str) {
    int i = -1;
    while (str[++i]) {
        str[i] = toupper(str[i]);
    }
}

/* ---- cgi.c file-scope globals/macros (verbatim) ---- */
extern char ** environ;
weborf_configuration_t weborf_conf;

#define STDIN 0
#define STDOUT 1
#define STDERR 2

/* ---- cgi.c callees (verbatim from data_cve/cve_bba7ec1a/source_code/cgi.c) ---- */

static inline void cgi_set_http_env_vars(char *http_param) { //Sets Enviroment vars
    if (http_param == NULL)
        return;

    char *lasts;
    char *param;
    int i;
    int p_len;

    //Removes the 1st part with the protocol
    param = strtok_r(http_param, "\r\n", &lasts);
    setenv("SERVER_PROTOCOL", param, true);

    char hparam[200];
    hparam[0] = 'H';
    hparam[1] = 'T';
    hparam[2] = 'T';
    hparam[3] = 'P';
    hparam[4] = '_';

    //Cycles parameters
    while ((param = strtok_r(NULL, "\r\n", &lasts)) != NULL) {

        p_len = lasts-param-1;
        char *value = NULL;

        //Parses the parameter to split name from value
        for (i = 0; i < p_len; i++) {
            if (param[i] == ':' && param[i + 1] == ' ') {
                param[i] = '\0';
                value = &param[i + 2];

                strToUpper(param); //Converts to upper case
                strReplace(param, "-", '_');
                memccpy(hparam+5,param,'\0',195);
                setenv(hparam, value, true);

                break;
            }
        }

    }
}

static inline void cgi_set_SERVER_ADDR_PORT(int sock) {

    char loc_addr[INET_ADDRSTRLEN];
    struct sockaddr_in addr;
    int addr_l=sizeof(struct sockaddr_in);

    getsockname(sock, (struct sockaddr *)&addr,(socklen_t *) &addr_l);
    inet_ntop(AF_INET, &addr.sin_addr,(char*)&loc_addr, INET_ADDRSTRLEN);

    setenv("SERVER_ADDR",(char*)&loc_addr,true);

    //TODO
    setenv("SERVER_PORT",weborf_conf.port,true);

}

static inline void cgi_set_env_vars(connection_t *connection_prop,char *real_basedir) {

    //Set CGI needed vars
    setenv("SERVER_SIGNATURE",SIGNATURE,true);
    setenv("SERVER_SOFTWARE",SIGNATURE,true);
    setenv("GATEWAY_INTERFACE","CGI/1.1",true);
    setenv("REQUEST_METHOD",connection_prop->method,true); //POST GET
    setenv("REDIRECT_STATUS","Ciao",true); // Mah.. i'll never understand php, this env var is needed
    setenv("SCRIPT_FILENAME",connection_prop->strfile,true); //This var is needed as well or php say no input file...
    setenv("DOCUMENT_ROOT",real_basedir,true);
    setenv("REMOTE_ADDR",connection_prop->ip_addr,true); //Client's address
    setenv("SCRIPT_NAME",connection_prop->page,true); //Name of the script without complete path

    char* http_host = getenv("HTTP_HOST");
    if (http_host)
        setenv("SERVER_NAME", http_host,true); //TODO for older http version this header might not exist

    //Request URI with or without a query
    if (connection_prop->get_params==NULL) {
        setenv("REQUEST_URI",connection_prop->page,true);
        setenv("QUERY_STRING","",true);//Query after ?
    } else {
        setenv("QUERY_STRING",connection_prop->get_params,true);//Query after ?

        //file and params were the same string.
        //Joining them again temporarily
        int delim=connection_prop->page_len;
        connection_prop->page[delim]='?';
        setenv("REQUEST_URI",connection_prop->page,true);
        connection_prop->page[delim]='\0';
    }

}

static inline void cgi_set_env_content_length() {
    //If Content-Length field exists
    char *content_l = getenv("HTTP_CONTENT_LENGTH");
    char *content_type = getenv("HTTP_CONTENT_TYPE");

    if (content_l != NULL && content_type != NULL) {
        setenv("CONTENT_LENGTH", content_l, true);
        setenv("CONTENT_TYPE", content_type, true);
    }
}

static inline char* cgi_child_chdir(connection_t *connection_prop) {
    //chdir to the directory
    char* last_slash = rindex(connection_prop->strfile, '/');
    last_slash[0] = 0;
    chdir(connection_prop->strfile);
    last_slash[0] = '/';
    return last_slash + 1;
}

/* ==== FUNCTION UNDER TEST -- byte-for-byte from
   data_cve/cve_bba7ec1a/target/original_function.c (verified identical) ==== */
static inline void cgi_execute_child(connection_t* connection_prop,string_t* post_param,char * executor,char* real_basedir,int *wpipe,int *ipipe) {
    char* errormsg = NULL;
    close(wpipe[0]); //Closes unused end of the pipe

    close(STDOUT);
    if (dup(wpipe[1]) == -1) { //Redirects the stdout
        errormsg = "dup() failed";
        goto error;
    }

#ifdef HIDE_CGI_ERRORS
    close(STDERR);
#endif
    //Redirecting standard input only if there is POST data
    if (post_param->data != NULL) {//Send post data to script's stdin
        close(STDIN);
        if (dup(ipipe[0]) == -1) {
            errormsg = "dup() failed";
            goto error;
        }
    }

    environ = NULL; //Clear env vars

    if (strlen(executor) == 0) {
        executor = malloc(connection_prop->strfile_len + 1);
        strncpy(executor, connection_prop->strfile, connection_prop->strfile_len);
    }

    cgi_set_http_env_vars(connection_prop->http_param);
    cgi_set_SERVER_ADDR_PORT(myio_getfd(connection_prop->sock));
    cgi_set_env_vars(connection_prop, real_basedir);
    cgi_set_env_content_length();
    char *filename = cgi_child_chdir(connection_prop);

    alarm(SCRPT_TIMEOUT); //Sets the timeout for the script
    execl(executor, executor, filename, (char *)0);
#ifdef SERVERDBG
    syslog(LOG_ERR,"Execution of %s failed", executor);
    perror("Execution of the page failed");
#endif
error:
#ifdef SERVERDBG
    if (errormsg)
        syslog(LOG_ERR, "%s", errormsg);
#endif
    exit(1);

}
/* ==== END FUNCTION UNDER TEST ==== */

int main(int argc, char **argv) {
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    if (fsz < 0) fsz = 0;
    fseek(f, 0, SEEK_SET);
    unsigned char *buf = (unsigned char*)malloc((size_t)fsz + 1);  // heap, ASAN-guarded
    size_t n = 0;
    if (fsz > 0) n = fread(buf, 1, (size_t)fsz, f);
    fclose(f);
    buf[n] = 0;

    unsigned char mode = (n > 0) ? buf[0] : 'S';

    weborf_conf.port = "80";

    connection_t conn;
    memset(&conn, 0, sizeof(conn));
    string_t post_param;
    post_param.len = 0;
    post_param.data = NULL;    // skip the ipipe/STDIN-redirect branch entirely
    int wpipe[2];
    int ipipe[2] = { -1, -1 }; // never touched (post_param.data is always NULL)

    if (mode == 'T') {
        /* strncpy over-reads connection_prop->strfile because strfile_len
           does not honestly bound strfile's real allocation -- the exact
           line the fix (49824204) deletes. */
        size_t payload = (n > 1) ? (n - 1) : 0;
        size_t K = (payload > 0) ? payload : 1;
        char *strfile = (char*)malloc(K);
        for (size_t i = 0; i < K; i++) {
            unsigned char b = (payload > 0) ? buf[1 + i] : 'A';
            strfile[i] = b ? (char)b : 'A';   // never embed a NUL: that would
                                               // let strncpy stop early and
                                               // hide the over-read
        }
        conn.strfile = strfile;
        conn.strfile_len = (ssize_t)(K + 64);  // > strfile's real K-byte allocation

        if (pipe(wpipe) != 0) return 0;
        char executor[1] = { 0 };              // strlen(executor)==0 -> buggy branch
        cgi_execute_child(&conn, &post_param, executor, (char*)"/tmp", wpipe, ipipe);
    } else if (mode == 'D') {
        /* Same branch, but strfile_len correctly equals strlen(strfile) for
           a properly NUL-terminated, '/'-containing strfile -> in bounds. */
        size_t payload = (n > 1) ? (n - 1) : 0;
        size_t K = (payload > 0) ? payload : 4;
        char *strfile = (char*)malloc(5 + K + 1);   // "/tmp/" + K bytes + NUL
        memcpy(strfile, "/tmp/", 5);
        for (size_t i = 0; i < K; i++) {
            unsigned char b = (payload > 0) ? buf[1 + i] : 'x';
            if (b == 0 || b == '/') b = 'x';
            strfile[5 + i] = (char)b;
        }
        strfile[5 + K] = 0;
        conn.strfile = strfile;
        conn.strfile_len = (ssize_t)strlen(strfile);
        conn.method = (char*)"GET";
        conn.http_param = NULL;
        conn.page = (char*)"/index";
        conn.get_params = NULL;
        conn.sock = -1;
        strncpy(conn.ip_addr, "127.0.0.1", sizeof(conn.ip_addr) - 1);

        if (pipe(wpipe) != 0) return 0;
        char executor[1] = { 0 };
        cgi_execute_child(&conn, &post_param, executor, (char*)"/tmp", wpipe, ipipe);
    } else {
        /* SAFE: dup() on a deliberately-invalid fd fails immediately, so
           cgi_execute_child takes its own `error:` path and exit(1)s before
           ever touching connection_prop/executor/strfile. */
        wpipe[0] = -1;
        wpipe[1] = -1;
        char executor[] = "/bin/true";
        cgi_execute_child(&conn, &post_param, executor, (char*)"/tmp", wpipe, ipipe);
    }
    return 0;
}
