/* cve_barebone direct-call harness for net-snmp access_parse_oid()
 * CVE fix commit 67ebb43e9038b2dae6e74ae8838b36fcc10fc937 adds a bounds
 * check before `contextPrefixL = oidIndex[groupNameL + 1];` in
 * agent/mibgroup/mibII/vacm_vars.c. Without it, an attacker-controlled
 * `oidIndex[0]` (the encoded groupName length) that is inconsistent with
 * the actual number of OID sub-identifiers (oidLen) makes the function
 * read oidIndex[groupNameL + 1] far past the end of the oidIndex array
 * -> heap-buffer-overflow READ (CWE-125).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- real type from include/net-snmp/library/oid.h (default, non-Cygwin,
 * !EIGHTBIT_SUBIDS build) --- */
typedef unsigned long oid;
#define MAX_SUBID   0xFFFFFFFFUL

/* --- access_parse_oid, copied byte-for-byte from
 * data_cve/cve_e41eb8a6/target/original_function.c --- */
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

/* --- driver: argv[1] is a file whose bytes are interpreted verbatim as a
 * heap-allocated array of `oid` (8-byte little-endian on x86_64) values,
 * i.e. exactly the wire-decoded index sub-identifiers access_parse_oid
 * expects. oidLen = number of complete 8-byte units present (minimum 1,
 * matching the function's own `oidLen <= 0` guard). The array is malloc'd
 * to EXACTLY oidLen elements so ASAN's heap redzone sits right where the
 * real net-snmp mibII table code's over-read would land. --- */
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long fsz = ftell(f);
    if (fsz < 0) fsz = 0;
    fseek(f, 0, SEEK_SET);

    size_t oidLen = (size_t) fsz / sizeof(oid);
    if (oidLen == 0)
        oidLen = 1;

    oid *oidIndex = (oid *) malloc(oidLen * sizeof(oid));
    if (!oidIndex) { fclose(f); return 0; }
    memset(oidIndex, 0, oidLen * sizeof(oid));

    size_t toread = oidLen * sizeof(oid);
    if ((size_t) fsz < toread)
        toread = (size_t) fsz;
    if (toread > 0) {
        size_t got = fread(oidIndex, 1, toread, f);
        (void) got;
    }
    fclose(f);

    unsigned char *groupName = NULL;
    size_t groupNameLen = 0;
    unsigned char *contextPrefix = NULL;
    size_t contextPrefixLen = 0;
    int model = 0, level = 0;

    int rc = access_parse_oid(oidIndex, oidLen, &groupName, &groupNameLen,
                               &contextPrefix, &contextPrefixLen,
                               &model, &level);

    if (rc == 0) {
        free(groupName);
        free(contextPrefix);
    }
    free(oidIndex);

    return 0;
}
