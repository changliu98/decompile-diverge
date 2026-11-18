/*
 * Direct-call crash harness for CVE-2022-28550 (jhead, function DoCommand).
 *
 * DoCommand() (jhead.c) builds a shell command string (ExecString[PATH_MAX*3],
 * a STACK array local to DoCommand) by substituting "&i"/"&o" tokens found in
 * the global ApplyCommand (the -cmd argument in the real program) with a
 * shell-escaped path, via repeated calls to shellescape(). Neither the "&i"/
 * "&o" substitution path (e += shellescape(ExecString+e, ...)) nor the plain
 * literal-copy path (ExecString[e++] = ApplyCommand[a];) ever checks the
 * cumulative offset `e` against sizeof(ExecString) -- only shellescape's own
 * *local* counter `j` is bounded (against PATH_MAX, not against how much of
 * ExecString is already used). So an ApplyCommand containing enough "&i" (or
 * "&o") tokens makes `e` walk straight past the end of the ExecString stack
 * array; the next shellescape() call then performs an out-of-bounds WRITE at
 * `to[j++] = ...` -- an ASan stack-buffer-overflow with top frame
 * "shellescape", called from "DoCommand", matching the recorded baseline
 * (dedup "shellescape--DoCommand--ProcessFile", CWE-787 WRITE). This is
 * exactly the vector the upstream fix (64894dbc) targeted: it added
 * `if (e > PATH_MAX * 2) ErrFatal(...)` right before the &i/&o substitution
 * calls in DoCommand.
 *
 * This harness embeds DoCommand() VERBATIM (same body/signature/locals as
 * target/original_function.c) plus its two real, unmodified callee/global
 * dependencies from jhead.c (shellescape(), ErrFatal()) and the real macros
 * jhead.h defines for the non-_WIN32 build (TRUE/FALSE/SLASH, PATH_MAX via
 * the system <limits.h>, exactly as jhead.h does).
 *
 * main() reads the attacker-controlled PoC file (argv[1]) into a HEAP buffer
 * and uses it AS the ApplyCommand string (the thing that actually drives the
 * offset `e`) -- DoCommand does not take ApplyCommand as a parameter (it is
 * global state the real caller, main()/ProcessFile(), sets up before calling
 * DoCommand, exactly like the -cmd command-line flag does), so we set that
 * global from the heap buffer, then call DoCommand() once with a fixed,
 * heap-allocated FileName.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>
#include <limits.h>

/* ---- real jhead.h macros (non-_WIN32 branch) ---------------------------- */
#ifndef TRUE
    #define TRUE 1
    #define FALSE 0
#endif
/* jhead.h: #ifndef PATH_MAX #define PATH_MAX 1024 #endif -- on Linux
 * <limits.h> (included above) already defines PATH_MAX, so that fallback
 * never fires here either, exactly as in the real build. */
#define SLASH '/'

/* ---- real jhead.c globals DoCommand depends on --------------------------- */
static const char * CurrentFile = NULL;     /* jhead.c:41 */
static char * ApplyCommand = NULL;          /* jhead.c:60 -- the -cmd argument */

/*--------------------------------------------------------------------------
 * Error exit handler (verbatim, jhead.c:115)
 *--------------------------------------------------------------------------*/
void ErrFatal(const char * msg)
{
    fprintf(stderr,"\nError : %s\n", msg);
    if (CurrentFile) fprintf(stderr,"in file '%s'\n",CurrentFile);
    exit(EXIT_FAILURE);
}

/*--------------------------------------------------------------------------
 * Escape an argument such that it is interpreted literally by the shell
 * (returns the number of written characters)   (verbatim, jhead.c:334)
 *--------------------------------------------------------------------------*/
static int shellescape(char* to, const char* from)
{
    int i, j;
    i = j = 0;

    // Enclosing characters in double quotes preserves the literal value of
    // all characters within the quotes, with the exception of $, `, and \.
    to[j++] = '"';
    while(from[i])
    {
#ifdef _WIN32
        // Under WIN32, there isn't really anything dangerous you can do with
        // escape characters, plus windows users aren't as security paranoid.
        // Hence, no need to do fancy escaping.
        to[j++] = from[i++];
#else
        switch(from[i]) {
            case '"':
            case '$':
            case '`':
            case '\\':
                to[j++] = '\\';
                // Fallthru...
            default:
                to[j++] = from[i++];
        }
#endif
        if (j >= PATH_MAX) ErrFatal("max path exceeded");
    }
    to[j++] = '"';
    return j;
}

/*--------------------------------------------------------------------------
 * Apply the specified command to the JPEG file.
 * TARGET FUNCTION -- verbatim from target/original_function.c
 *--------------------------------------------------------------------------*/
static void DoCommand(const char * FileName, int ShowIt)
{
    int a,e;
    char ExecString[PATH_MAX*3];
    char TempName[PATH_MAX+10];
    int TempUsed = FALSE;

    e = 0;

    // Generate an unused temporary file name in the destination directory
    // (a is the number of characters to copy from FileName)
    a = strlen(FileName)-1;
    while(a > 0 && FileName[a-1] != SLASH) a--;
    memcpy(TempName, FileName, a);
    strcpy(TempName+a, "XXXXXX");

    // Note: Compiler will warn about mkstemp.  but I need a filename, not a file.
    // I could just then get the file name from what mkstemp made, and pass that
    // to the executable, but that would make for the exact same vulnerability
    // as mktemp - that is, that between getting the random name, and making the file
    // some other program could snatch that exact same name!
    // also, not all platforms support mkstemp.
    mktemp(TempName);


    if(!TempName[0]) {
        ErrFatal("Cannot find available temporary file name");
    }


    // Build the exec string.  &i and &o in the exec string get replaced by input and output files.
    for (a=0;;a++){
        if (ApplyCommand[a] == '&'){
            if (ApplyCommand[a+1] == 'i'){
                // Input file.
                e += shellescape(ExecString+e, FileName);
                a += 1;
                continue;
            }
            if (ApplyCommand[a+1] == 'o'){
                // Needs an output file distinct from the input file.
                e += shellescape(ExecString+e, TempName);
                a += 1;
                TempUsed = TRUE;
                continue;
            }
        }
        ExecString[e++] = ApplyCommand[a];
        if (ApplyCommand[a] == 0) break;
    }

    if (ShowIt) printf("Cmd:%s\n",ExecString);

    errno = 0;
    a = system(ExecString);

    if (a || errno){
        // A command can however fail without errno getting set or system returning an error.
        if (errno) perror("system");
        ErrFatal("Problem executing specified command");
    }

    if (TempUsed){
        // Don't delete original file until we know a new one was created by the command.
        struct stat dummy;
        if (stat(TempName, &dummy) == 0){
            struct stat buf;
            int stat_result = stat(FileName, &buf);

            unlink(FileName);
            rename(TempName, FileName);
            if (stat_result == 0){
                // set Unix access rights and time to new file
                struct utimbuf mtime;
                chmod(FileName, buf.st_mode);

                mtime.actime = buf.st_atime;
                mtime.modtime = buf.st_mtime;

                utime(FileName, &mtime);
            }
        }else{
            ErrFatal("specified command did not produce expected output file");
        }
    }
}

/*--------------------------------------------------------------------------
 * main() -- reads argv[1] into a HEAP buffer (attacker-controlled), uses it
 * as ApplyCommand (DoCommand's global dependency), and calls DoCommand()
 * directly, exactly once.
 *--------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 1; }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    fseek(f, 0, SEEK_SET);

    /* Attacker-controlled ApplyCommand content, on the HEAP. */
    char *buf = (char *)malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return 1; }
    size_t rd = (sz > 0) ? fread(buf, 1, (size_t)sz, f) : 0;
    fclose(f);
    buf[rd] = '\0';

    ApplyCommand = buf;          /* what DoCommand actually reads/overflows on */
    CurrentFile = "vb_dc_input";

    /* Fixed, heap-allocated "image" path (its role is only to size TempName /
     * shellescape's per-call output -- the crash-driving data is ApplyCommand
     * above). */
    const char *fixed_name = "/tmp/x";
    char *FileName = (char *)malloc(strlen(fixed_name) + 1);
    if (!FileName) { free(buf); return 1; }
    strcpy(FileName, fixed_name);

    DoCommand(FileName, 0);

    free(FileName);
    free(buf);
    return 0;
}
