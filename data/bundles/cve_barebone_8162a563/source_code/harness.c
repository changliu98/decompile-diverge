/* cve_barebone direct-call harness for cve_8162a563 (net-snmp, CVE-2022-24805)
 * Target: access_parse_oid  (agent/mibgroup/mibII/vacm_vars.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * fix_commit 67ebb43e9038b2dae6e74ae8838b36fcc10fc937 adds exactly:
 *     groupNameL = oidIndex[0];
 *   + if ((groupNameL + 1) > (int) oidLen) {
 *   +     return 1;
 *   + }
 *     contextPrefixL = oidIndex[groupNameL + 1];  // the initial name length
 * access_parse_oid trusts oidIndex[0] (attacker-controlled) as a length "groupNameL" and
 * immediately reads oidIndex[groupNameL + 1] -- before checking groupNameL against the
 * actual array length oidLen. Handing it a short oidIndex array whose first element is a
 * large groupNameL makes that second read walk straight past the end of the allocation:
 * an OOB READ entirely inside access_parse_oid's own body, exactly at the line the patch
 * guards.
 *
 * oid == unsigned long (include/net-snmp/library/oid.h, default !EIGHTBIT_SUBIDS branch,
 * the real net-snmp build config on this project's normal Linux/x86-64 target). No other
 * project type/macro/callee is needed: access_parse_oid's body only touches oid/malloc/
 * free/size_t, all from the standard headers vacm_vars.c already includes.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* ---- real net-snmp typedef (include/net-snmp/library/oid.h, default branch) ---- */
typedef unsigned long oid;

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline (+ called through a volatile function pointer below) purely so the OOB read keeps
 * its own stack frame in the ASAN backtrace -- does not touch the function's own bytes. */
__attribute__((noinline))
int
access_parse_oid(oid * oidIndex, size_t oidLen,
                 unsigned char **groupName, size_t * groupNameLen,
                 unsigned char **contextPrefix, size_t * contextPrefixLen,
                 int *model, int *level)
{
    int             groupNameL, contextPrefixL;
    int             i;

    /*
     * first check the validity of the oid 
     */
    if ((oidLen <= 0) || (!oidIndex)) {
        return 1;
    }
    groupNameL = oidIndex[0];
    contextPrefixL = oidIndex[groupNameL + 1];  /* the initial name length */
    if ((int) oidLen != groupNameL + contextPrefixL + 4) {
        return 1;
    }

    /*
     * its valid, malloc the space and store the results 
     */
    if (contextPrefix == NULL || groupName == NULL) {
        return 1;
    }

    *groupName = (unsigned char *) malloc(groupNameL + 1);
    if (*groupName == NULL) {
        return 1;
    }

    *contextPrefix = (unsigned char *) malloc(contextPrefixL + 1);
    if (*contextPrefix == NULL) {
        free(*groupName);
        return 1;
    }

    *contextPrefixLen = contextPrefixL;
    *groupNameLen = groupNameL;

    for (i = 0; i < groupNameL; i++) {
        if (oidIndex[i + 1] > 255) {
            free(*groupName);
            free(*contextPrefix);
            return 1;
        }
        groupName[0][i] = (unsigned char) oidIndex[i + 1];
    }
    groupName[0][groupNameL] = 0;


    for (i = 0; i < contextPrefixL; i++) {
        if (oidIndex[i + groupNameL + 2] > 255) {
            free(*groupName);
            free(*contextPrefix);
            return 1;
        }
        contextPrefix[0][i] = (unsigned char) oidIndex[i + groupNameL + 2];
    }
    contextPrefix[0][contextPrefixL] = 0;

    *model = oidIndex[groupNameL + contextPrefixL + 2];
    *level = oidIndex[groupNameL + contextPrefixL + 3];

    return 0;

}
/* ==== end verbatim target function ==== */

/* ---- driver ------------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded), reinterpreted as a tightly-sized
 * array of `oid` (8-byte) elements -- exactly `floor(filesize / sizeof(oid))` of them, so the
 * ASAN redzone sits immediately after the LAST real element the file supplies. This directly
 * mirrors the real attack surface: access_parse_oid's caller (sec2group_parse_oid-family
 * VACM index parsing) hands it an OID array taken straight off the wire, whose length is
 * exactly `oidLen` -- there is no slack padding to "absorb" a bad groupNameL. */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 64; }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 64; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

    size_t n = (size_t)fsz / sizeof(oid);            /* whole oid elements present in the file */
    size_t alloc_n = n ? n : 1;                        /* still a valid heap alloc when n==0 */
    oid *oidIndex = (oid *)malloc(alloc_n * sizeof(oid));
    if (!oidIndex) { fclose(fp); return 64; }
    size_t got = n ? fread(oidIndex, sizeof(oid), n, fp) : 0;
    fclose(fp);
    if (got != n) { free(oidIndex); return 64; }

    unsigned char *groupName = NULL, *contextPrefix = NULL;
    size_t groupNameLen = 0, contextPrefixLen = 0;
    int model = 0, level = 0;

    /* volatile function pointer: forbids inlining access_parse_oid into main() so it keeps
     * its own frame in the ASAN backtrace. Same arguments/semantics as a direct call. */
    int (*volatile vb_call_access_parse_oid)(oid *, size_t, unsigned char **, size_t *,
                                              unsigned char **, size_t *, int *, int *)
        = access_parse_oid;

    int rc = vb_call_access_parse_oid(oidIndex, n, &groupName, &groupNameLen,
                                       &contextPrefix, &contextPrefixLen, &model, &level);
    (void)rc; (void)model; (void)level; (void)groupNameLen; (void)contextPrefixLen;

    /* Only reached on a SAFE run (a triggering run aborts inside the call above). */
    if (groupName) free(groupName);
    if (contextPrefix) free(contextPrefix);
    free(oidIndex);
    return 0;
}
