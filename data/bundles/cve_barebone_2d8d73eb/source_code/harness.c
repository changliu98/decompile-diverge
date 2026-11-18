/* cve_barebone direct-call harness for cve_2d8d73eb (suricata, CVE-2025-64330)
 * Target: EveAddVerdict  (src/output-json-alert.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * See the module docstring of scripts/gen_dc_cve_2d8d73eb.py for the full mechanism. In
 * short: EveAddVerdict unconditionally reads p->alerts.alerts[p->alerts.cnt] once the
 * packet's action excludes reject/accept. p->alerts.alerts is allocated with exactly
 * packet_alert_max entries (valid indices 0..cnt-1); when cnt reaches the array's capacity
 * (all alert slots filled), reading index cnt lands one PacketAlert struct past the end of
 * the heap allocation.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <netinet/in.h> /* not strictly needed (IPPROTO_* used only on the unreached reject
                          * branch below) but harmless/real -- EveAddVerdict's own TU pulls
                          * these in transitively via decode.h. */

/* ---- real macros (util-optimize.h, verbatim) ---- */
#define likely(expr) __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)

/* ---- real macro (suricata-common.h:332, verbatim: `#define SigIntId uint32_t`) ---- */
#define SigIntId uint32_t

/* ---- real action flag bits (action-globals.h, verbatim) ---- */
#define ACTION_ALERT       0x01
#define ACTION_DROP        0x02
#define ACTION_REJECT      0x04
#define ACTION_REJECT_DST  0x08
#define ACTION_REJECT_BOTH 0x10
#define ACTION_PASS        0x20
#define ACTION_CONFIG      0x40
#define ACTION_ACCEPT      0x80
#define ACTION_REJECT_ANY  (ACTION_REJECT | ACTION_REJECT_DST | ACTION_REJECT_BOTH)

/* ---- incidental types EveAddVerdict/PacketCheckAction reference only through pointers that
 * are never dereferenced on this call path -- kept opaque/forward-declared, exactly as real
 * (decode.h itself only forward-declares `struct Signature_`; PacketContextData is a real
 * struct but PacketAlert only ever holds a pointer to it, never walked here). ---- */
struct Signature_;
struct PacketContextData;

/* ---- real PacketAlert / PacketAlerts layout (decode.h:248-294, verbatim field names). ---- */
typedef struct PacketAlert_ {
    SigIntId iid; /* Internal ID, used for sorting */
    uint8_t action; /* Internal num, used for thresholding */
    uint8_t flags;
    const struct Signature_ *s;
    uint64_t tx_id; /* Used for sorting */
    int64_t frame_id;
    struct PacketContextData *json_info;
} PacketAlert;

typedef struct PacketAlerts_ {
    uint16_t cnt;
    uint16_t discarded;
    uint16_t suppressed;
    PacketAlert *alerts;
    /* single pa used when we're dropping, so we can log it out in the drop log. */
    PacketAlert drop;
} PacketAlerts;

/* ---- Packet_: REDUCED to exactly the real-named fields EveAddVerdict / PacketCheckAction
 * dereference (decode.h's real Packet_, decode.h:500-686, carries ~60 more fields --
 * addresses, flow, vlan, capture-method unions, l2/l3/l4 header views, timestamps, tunnel
 * bookkeeping, etc -- none of which either function reads). Field types/names match
 * decode.h:523 (proto), :609 (action), :620 (alerts), :653 (root) exactly. ---- */
typedef struct Packet_ {
    uint8_t proto;
    uint8_t action; /* IPS action to take */
    PacketAlerts alerts;
    struct Packet_ *root; /* tunnel: ptr to the 'real' packet, NULL if not tunneled */
} Packet;

/* ---- real PacketCheckAction (source_code/src/packet.c:49-58, verbatim). ---- */
bool PacketCheckAction(const Packet *p, const uint8_t a)
{
    if (likely(p->root == NULL)) {
        return (p->action & a) != 0;
    } else {
        /* check against both */
        const uint8_t actions = p->action | p->root->action;
        return (actions & a) != 0;
    }
}

/* ---- EngineModeIsIPS: incidental to the OOB read (source_code/src/suricata.c:242-246, real
 * body `DEBUG_VALIDATE_BUG_ON(...); return g_engine_mode >= ENGINE_MODE_IPS;`, gated on a
 * global the CLI sets once at startup). It only selects which action string an
 * already-DROP-flagged packet is logged with -- it never touches alerts/cnt and cannot
 * affect whether the OOB read at the bottom of EveAddVerdict fires (that read is reached
 * regardless of this function's answer, as long as the packet isn't reject/accept-flagged).
 * Minimal faithful stub returning a real, reachable value of the real function (IDS mode,
 * the common non-inline default). ---- */
int EngineModeIsIPS(void)
{
    return 0;
}

/* ---- SCJsonBuilder: opaque Rust type (rust/src/jsonbuilder.rs; rust/cbindgen.toml renames
 * "JsonBuilder" -> "SCJsonBuilder" in the generated rust-bindings.h) -- C code only ever
 * holds pointers to it, never sees real fields. SCJbOpenObject/SCJbOpenArray/
 * SCJbSetFormatted/SCJbAppendString/SCJbClose are real `#[no_mangle] pub extern "C"`
 * exports (same file, verified exact signatures) with these exact C signatures; bodies are
 * minimal faithful stubs -- incidental JSON-formatting machinery that none of
 * EveAddVerdict's five calls into this API use to touch Packet/alerts state.
 *
 * In the REAL build these are cross-language calls into a separate Rust crate, so LLVM's C
 * optimizer can never see through them -- they are opaque, and every call (with whatever
 * string argument) is unconditionally preserved. Reducing them to plain same-TU C functions
 * with a visible, side-effect-free body (`return true;`) would hand the optimizer visibility
 * it never has in the real build: at -O1, seeing that BOTH the "pass" and "alert"
 * JB_SET_STRING calls (and every other branch's calls) are equivalent no-ops, the compiler
 * proves the entire if/else-if chain -- INCLUDING the vulnerable
 * `p->alerts.alerts[p->alerts.cnt].action` read that selects between them -- is dead and
 * deletes it, silently curing the CVE instead of reproducing it (confirmed by objdump: with a
 * plain body the whole SCJb call tree and the OOB read vanish from EveAddVerdict's
 * disassembly, and dc_batch reports 0/25 triggering). `weak, noinline` restores the real,
 * faithful "opaque external symbol" semantics without adding any actual behavior: a weak
 * symbol may be interposed by a different definition at link time, so LLVM's interprocedural
 * purity/function-attribute inference (which would otherwise see straight through a same-TU
 * `noinline`-only body) cannot assume anything about it, cannot merge calls across different
 * string arguments, and cannot prove any branch reaching one is dead -- exactly the guarantee
 * the real cross-language (Rust) link boundary already provides for free. Verified by
 * objdump: EveAddVerdict now contains real `call SCJb*` instructions and the OOB read/ASAN
 * shadow-check sequence for `alerts[cnt].action` survives intact. ---- */
typedef struct SCJsonBuilder {
    int _unused;
} SCJsonBuilder;

#define VB_OPAQUE __attribute__((noinline, weak))

VB_OPAQUE bool SCJbOpenObject(SCJsonBuilder *js, const char *key)
{
    (void)js;
    (void)key;
    return true;
}

VB_OPAQUE bool SCJbOpenArray(SCJsonBuilder *js, const char *key)
{
    (void)js;
    (void)key;
    return true;
}

VB_OPAQUE bool SCJbSetFormatted(SCJsonBuilder *js, const char *formatted)
{
    (void)js;
    (void)formatted;
    return true;
}

VB_OPAQUE bool SCJbAppendString(SCJsonBuilder *js, const char *val)
{
    (void)js;
    (void)val;
    return true;
}

VB_OPAQUE bool SCJbClose(SCJsonBuilder *js)
{
    (void)js;
    return true;
}

/* ---- real macro (source_code/src/rust.h:26, verbatim). ---- */
#define JB_SET_STRING(jb, key, val) SCJbSetFormatted((jb), "\"" key "\":\"" val "\"")

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline purely so the OOB read keeps its own named stack frame in the ASAN report --
 * does not touch the function's own bytes. */
__attribute__((noinline))
void EveAddVerdict(SCJsonBuilder *jb, const Packet *p)
{
    SCJbOpenObject(jb, "verdict");

    /* add verdict info */
    if (PacketCheckAction(p, ACTION_REJECT_ANY)) {
        // check rule to define type of reject packet sent
        if (EngineModeIsIPS()) {
            JB_SET_STRING(jb, "action", "drop");
        } else {
            JB_SET_STRING(jb, "action", "alert");
        }
        if (PacketCheckAction(p, ACTION_REJECT)) {
            JB_SET_STRING(jb, "reject-target", "to_client");
        } else if (PacketCheckAction(p, ACTION_REJECT_DST)) {
            JB_SET_STRING(jb, "reject-target", "to_server");
        } else if (PacketCheckAction(p, ACTION_REJECT_BOTH)) {
            JB_SET_STRING(jb, "reject-target", "both");
        }
        SCJbOpenArray(jb, "reject");
        switch (p->proto) {
            case IPPROTO_UDP:
            case IPPROTO_ICMP:
            case IPPROTO_ICMPV6:
                SCJbAppendString(jb, "icmp-prohib");
                break;
            case IPPROTO_TCP:
                SCJbAppendString(jb, "tcp-reset");
                break;
        }
        SCJbClose(jb);

    } else if (PacketCheckAction(p, ACTION_DROP) && EngineModeIsIPS()) {
        JB_SET_STRING(jb, "action", "drop");
    } else if (PacketCheckAction(p, ACTION_ACCEPT)) {
        JB_SET_STRING(jb, "action", "accept");
    } else if (p->alerts.alerts[p->alerts.cnt].action & ACTION_PASS) {
        JB_SET_STRING(jb, "action", "pass");
    } else {
        // TODO make sure we don't have a situation where this wouldn't work
        JB_SET_STRING(jb, "action", "alert");
    }

    /* Close verdict */
    SCJbClose(jb);
}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Input format (attacker-controlled file, read into a HEAP buffer, exactly 4 bytes):
 *   byte0 = proto        -> p->proto (inert here: only read on the reject branch, which this
 *                            harness's action byte always steers around)
 *   byte1 = action_raw    -> p->action = action_raw & (ALERT|DROP|PASS|CONFIG), i.e. with the
 *                            REJECT_ANY/ACCEPT bits masked off -- this models "the packet's
 *                            matched signatures were plain alert/drop/pass/config rules, no
 *                            reject or accept rule fired", the real-world precondition the fix
 *                            commit's cnt<=packet_alert_max / cnt<packet_alert_max guards
 *                            defend against. (byte1's REJECT/ACCEPT bits, when present in the
 *                            raw byte, are deliberately exercised on some corpus files below to
 *                            demonstrate the mask -- EveAddVerdict still never reaches the OOB
 *                            read for those bits' *real* semantics, only via the harness's own
 *                            masked p->action.)
 *   byte2 = len_b         -> array_len = (len_b % 16) + 1, in [1,16] (mirrors the real default
 *                            packet_alert_max == PACKET_ALERT_MAX == 15). p->alerts.alerts is
 *                            HEAP-allocated with exactly array_len PacketAlert entries --
 *                            exactly what real PacketAlertCreate()'s
 *                            SCCalloc(packet_alert_max, sizeof(PacketAlert)) does.
 *   byte3 = cnt_b          -> p->alerts.cnt = cnt_b (attacker/detection-engine-influenced
 *                            count of alerts already stored for this packet).
 *
 * TRIGGER: cnt_b == array_len (the array is exactly full -- cnt has reached capacity, matching
 * the fix commit's guarded boundary exactly). EveAddVerdict's read of
 * alerts[cnt].action lands one PacketAlert struct past the end of the array ->
 * heap-buffer-overflow READ.
 * SAFE: cnt_b < array_len (a valid index, 0..array_len-1) -> in-bounds read, EveAddVerdict
 * returns normally.
 */
int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 64;
    }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("fopen");
        return 64;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return 64;
    }
    long fsz = ftell(fp);
    if (fsz < 0) {
        fclose(fp);
        return 64;
    }
    if (fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        return 64;
    }

    size_t n = (size_t)fsz;
    uint8_t *data = (uint8_t *)malloc(n ? n : 1); /* HEAP input, ASAN-guarded */
    if (!data) {
        fclose(fp);
        return 64;
    }
    size_t got = n ? fread(data, 1, n, fp) : 0;
    fclose(fp);
    if (got != n || n < 4) {
        free(data);
        return 64;
    }

    uint8_t proto_b = data[0];
    uint8_t action_raw = data[1];
    uint8_t len_b = data[2];
    uint8_t cnt_b = data[3];

    uint16_t array_len = (uint16_t)(len_b % 16) + 1; /* [1,16], mirrors packet_alert_max */
    uint16_t cnt = cnt_b;

    /* p->alerts.alerts: HEAP-allocated, exactly array_len entries -- the real buffer under
     * test (matches real PacketAlertCreate's SCCalloc(packet_alert_max, sizeof(PacketAlert))
     * sizing exactly). */
    PacketAlert *alerts = (PacketAlert *)malloc(sizeof(PacketAlert) * array_len);
    if (!alerts) {
        free(data);
        return 64;
    }
    memset(alerts, 0, sizeof(PacketAlert) * array_len);

    Packet pkt;
    memset(&pkt, 0, sizeof(pkt));
    pkt.proto = proto_b;
    pkt.action = (uint8_t)(action_raw & (ACTION_ALERT | ACTION_DROP | ACTION_PASS | ACTION_CONFIG));
    pkt.root = NULL;
    pkt.alerts.cnt = cnt;
    pkt.alerts.discarded = 0;
    pkt.alerts.suppressed = 0;
    pkt.alerts.alerts = alerts;

    SCJsonBuilder jb_obj;
    memset(&jb_obj, 0, sizeof(jb_obj));

    EveAddVerdict(&jb_obj, &pkt);

    /* Only reached on a SAFE run (a triggering run aborts inside the read above). */
    free(alerts);
    free(data);
    return 0;
}
