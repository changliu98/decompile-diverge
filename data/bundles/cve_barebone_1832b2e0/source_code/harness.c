/* cve_barebone direct-call harness for cve_1832b2e0 (CVE-2025-68670, xrdp)
 * Target: xrdp_wm_parse_domain_information  (xrdp/xrdp_login_wnd.c)
 * Bug class: heap-buffer-overflow WRITE (CWE-787).
 *
 * fix_commit 488c8c7d4d189514a366cd8301b6e816c5218ffa added a `resultSize` parameter and
 * switched the unbounded `g_strncpy(resultBuffer, &originalDomainInfo[1], pos)` copy (`pos` =
 * the unbounded position of "__" inside the attacker-controlled domain string) to a
 * size-checked `strlcpy(..., resultSize)`, plus a new `(unsigned int)pos < resultSize` guard.
 * g_strncpy (common/string_calls.c) is:
 *     rv = strncpy(dest, src, len);
 *     dest[len] = 0;
 * so any `originalDomainInfo` whose "__" marker sits at/past byte 256 makes this function
 * overflow its own 256-byte resultBuffer contract (the function's own comment: "resultBuffer
 * assumed to be 256 chars"; every real caller -- xrdp_wm_show_edits()/xrdp_login_wnd_create(),
 * both in this same file -- passes exactly `char resultIP[256]`) purely via its own internal,
 * attacker-influenced copy length. Entirely inside this one function's body.
 *
 * g_pos/g_strncpy (real callees on the crash path) and g_htoi (compiled into the `if(decode)`
 * branch -- the symbol must exist to link even though this harness always calls with decode=0,
 * which isolates the resultBuffer WRITE overflow from the separate, unrelated
 * originalDomainInfo[pos+3] OOB READ that decode=1 can trigger) are copied VERBATIM (exact line
 * slices) from source_code/common/string_calls.c. g_memset is os_calls.h's own
 * `#define g_memset memset` (a pure alias). LOG(...) drives xrdp's real logging subsystem,
 * wholly incidental to the bug, so it is stubbed as a no-op with the same variadic call shape.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* os_calls.h: #define g_memset memset -- a pure macro alias, no wrapper logic. */
#define g_memset memset

/* log.h's LOG(log_level, args...) macro drives the real logging subsystem (log_message() -> a
 * configured logging destination) -- entirely incidental to the bug (xrdp_wm_parse_domain_
 * information never inspects what LOG does with its arguments), so it is stubbed out as a
 * no-op here; the variadic call shape is preserved so every real LOG(...) call site in the
 * pasted target function still compiles unchanged. */
#define LOG_LEVEL_DEBUG 0
#define LOG(log_level, ...) ((void)0)

/* ==== common/string_calls.c -- real callees on the crash path, copied VERBATIM ==== */
char *
g_strncpy(char *dest, const char *src, int len)
{
    char *rv;

    if (src == 0 && dest != 0)
    {
        dest[0] = 0;
        return dest;
    }

    if (dest == 0 || src == 0)
    {
        return 0;
    }

    rv = strncpy(dest, src, len);
    dest[len] = 0;
    return rv;
}

int
g_pos(const char *str, const char *to_find)
{
    const char *pp;

    pp = strstr(str, to_find);

    if (pp == 0)
    {
        return -1;
    }

    return (pp - str);
}

/* g_htoi is only reached when decode!=0 (this harness always calls with decode=0); the call is
 * still compiled into the function body (decode is a runtime int, not a compile-time constant),
 * so the symbol must exist to link -- copied verbatim like the others. */
unsigned int
g_htoi(const char *str)
{
    unsigned int rv = 0;
    while (*str != '\0')
    {
        char c = *str;
        unsigned int val;
        if (c >= '0' && c <= '9')
        {
            val = c - '0';
        }
        else if (c >= 'A' && c <= 'F')
        {
            val = (c - 'A' + 10);
        }
        else if (c >= 'a' && c <= 'f')
        {
            val = (c - 'a' + 10);
        }
        else
        {
            break; // Unrecognised character
        }
        rv = (rv << 4) | val;
        ++str;
    }

    return rv;
}

/* ==== end common/string_calls.c ==== */

/* ============================================================================
 * TARGET FUNCTION -- copied BYTE-FOR-BYTE from
 * data_cve/cve_1832b2e0/target/original_function.c
 * ============================================================================ */
static int
xrdp_wm_parse_domain_information(char *originalDomainInfo, int comboMax,
                                 int decode, char *resultBuffer)
{
    int ret;
    int pos;
    int comboxindex;
    char index[2];

    /* If the first char in the domain name is '_' we use the domain
       name as IP*/
    ret = 0; /* default return value */
    /* resultBuffer assumed to be 256 chars */
    g_memset(resultBuffer, 0, 256);
    if (originalDomainInfo[0] == '_')
    {
        /* we try to locate a number indicating what combobox index the user
         * prefer the information is loaded from domain field, from the client
         * We must use valid chars in the domain name.
         * Underscore is a valid name in the domain.
         * Invalid chars are ignored in microsoft client therefore we use '_'
         * again. this sec '__' contains the split for index.*/
        pos = g_pos(&originalDomainInfo[1], "__");
        if (pos > 0)
        {
            /* an index is found we try to use it */
            LOG(LOG_LEVEL_DEBUG, "domain contains index char __");
            if (decode)
            {
                g_memset(index, 0, 2);
                /* we just accept values 0-9  (one figure) */
                g_strncpy(index, &originalDomainInfo[pos + 3], 1);
                comboxindex = g_htoi(index);
                LOG(LOG_LEVEL_DEBUG,
                    "index value as string: %s, as int: %d, max: %d",
                    index, comboxindex, comboMax - 1);
                /* limit to max number of items in combo box */
                if ((comboxindex > 0) && (comboxindex < comboMax))
                {
                    LOG(LOG_LEVEL_DEBUG, "domain contains a valid "
                        "index number");
                    ret = comboxindex; /* preferred index for combo box. */
                }
            }
            /* pos limit the String to only contain the IP */
            g_strncpy(resultBuffer, &originalDomainInfo[1], pos);
        }
        else
        {
            LOG(LOG_LEVEL_DEBUG, "domain does not contain _");
            g_strncpy(resultBuffer, &originalDomainInfo[1], 255);
        }
    }
    return ret;
}
/* ==== end verbatim target function ==== */

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the raw input as the attacker-controlled "domain" string (ASAN-guarded).
     * This directly mirrors the real caller chain:
     *   xrdp_wm_show_edits() / xrdp_login_wnd_create()
     *     -> xrdp_wm_parse_domain_information(self->session->client_info->domain, ...)
     * client_info->domain is filled from an RDP client's connection-time domain field with no
     * length cap before this function ever runs -- exactly what the raw file bytes stand in
     * for here. */
    char *originalDomainInfo = (char *)malloc((size_t)sz + 1);
    if (!originalDomainInfo) { fclose(f); return 0; }
    size_t n = sz > 0 ? fread(originalDomainInfo, 1, (size_t)sz, f) : 0;
    fclose(f);
    originalDomainInfo[n] = '\0';

    /* resultBuffer: HEAP-allocated at exactly 256 bytes -- the function's own comment
     * ("resultBuffer assumed to be 256 chars") and every real call site (both pass
     * `char resultIP[256]`) agree this is the contract. Any write past it below is
     * xrdp_wm_parse_domain_information's OWN bug (an unbounded copy length derived from
     * attacker-controlled originalDomainInfo), not an under-sized harness buffer. */
    char *resultBuffer = (char *)malloc(256);
    if (!resultBuffer) { free(originalDomainInfo); return 0; }

    int comboMax = 10;  /* plausible combo-box item count; only read when decode!=0 */
    int decode = 0;     /* isolates the resultBuffer WRITE overflow (this harness's target bug)
                            from the separate originalDomainInfo[pos+3] READ gated behind
                            decode -- keeps every triggering/safe input unambiguous */

    xrdp_wm_parse_domain_information(originalDomainInfo, comboMax, decode, resultBuffer);

    free(resultBuffer);
    free(originalDomainInfo);
    return 0;
}
