/*
 * cve_dd8eedbb direct-call crash harness for mwifiex's
 * mwifiex_cmd_append_vsie_tlv() (CVE-2019-14897-class /
 * CWE-787 heap-buffer-overflow WRITE -- missing bound check on the
 * vendor-specific-IE TLV length before it is memcpy'd into the caller's
 * command buffer).
 *
 * Root cause (visible directly in target/original_function.c, unchanged):
 *   vs_param_set->header.len =
 *       cpu_to_le16((((u16) priv->vs_ie[id].ie[1]) & 0x00FF) + 2);
 *   memcpy(vs_param_set->ie, priv->vs_ie[id].ie,
 *          le16_to_cpu(vs_param_set->header.len));
 *
 *   `header.len` is derived directly from the attacker/firmware-influenced
 *   byte priv->vs_ie[id].ie[1] with NO upper bound: it ranges from 2 up to
 *   0xFF + 2 = 257. The function then memcpy()s that many bytes into
 *   vs_param_set->ie, which lives inside whatever command buffer the
 *   caller passed via **buffer -- there is no check that len fits the
 *   destination. The upstream fix (torvalds/linux commit
 *   b70261a288ea4d2f4ac7cd04be08a9f0f2de4f4d) adds exactly one guard:
 *       if (le16_to_cpu(vs_param_set->header.len) > MWIFIEX_MAX_VSIE_LEN)
 *               break;
 *   right before the memcpy. Without it, a large ie[1] value overflows
 *   whatever destination buffer the real command-building code allocated
 *   (in the driver: a fixed-size FW command buffer). This harness models
 *   that missing-bound-check scenario directly: **buffer points at a
 *   heap allocation sized for one well-formed TLV; an oversized ie[1]
 *   drives the memcpy straight past it.
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the real
 *      mwifiex types/macros the function needs -- u8/u16 scalar
 *      typedefs, __le16 + cpu_to_le16()/le16_to_cpu() (identity on a
 *      little-endian host, matching the real generic.h on LE arches),
 *      MWIFIEX_MAX_VSIE_NUM/MWIFIEX_MAX_VSIE_LEN, TLV_TYPE_PASSTHROUGH
 *      (PROPRIETARY_TLV_BASE_ID + 10), struct mwifiex_ie_types_header,
 *      struct mwifiex_ie_types_vendor_param_set, and
 *      struct mwifiex_vendor_spec_cfg_ie -- ALL copied verbatim (names,
 *      types, values) from source_code/drivers/net/wireless/marvell/
 *      mwifiex/{fw.h,ioctl.h,main.h}. struct mwifiex_private is reduced
 *      to the ONE field mwifiex_cmd_append_vsie_tlv() actually
 *      dereferences (vs_ie[MWIFIEX_MAX_VSIE_NUM], real name/type/size),
 *      the same "trim to the touched field" convention used for
 *      netdissect_options in the cve_01dcad96 harness.
 *   2. VERBATIM real mwifiex source: data_cve/cve_dd8eedbb/target/
 *      original_function.c byte-for-byte (the target function itself,
 *      UNCHANGED -- no logic/name/signature edits).
 *   3. main(): reads argv[1] into a HEAP buffer, uses its first byte as
 *      the attacker-controlled priv->vs_ie[0].ie[1] length byte (the
 *      rest fills ie[2..] for realism, though only ie[1] drives the
 *      bug), sets priv->vs_ie[0].mask == vsie_mask so the loop's single
 *      branch fires exactly once, and passes a heap **buffer sized for
 *      exactly one well-formed TLV (DEST_BUF_SIZE bytes) -- a small
 *      ie[1] fits inside it (SAFE); a large one overflows it (CRASH).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- real mwifiex scalar typedefs (normally from linux/types.h via
 * mwifiex's own headers) ---- */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef u16 __le16; /* __le16 is __u16 __bitwise; the __bitwise sparse
                      * annotation has no effect on a normal C compile */

/* ---- include/linux/byteorder/generic.h, verbatim behavior on a
 * little-endian host (cpu_to_le16/le16_to_cpu are identity on LE arches,
 * exactly as they are on the real ARM/x86 mwifiex targets) ---- */
#define cpu_to_le16(x) ((__le16)(x))
#define le16_to_cpu(x) ((u16)(x))

/* ---- fw.h, verbatim ---- */
#define PROPRIETARY_TLV_BASE_ID                 0x0100
#define TLV_TYPE_PASSTHROUGH        (PROPRIETARY_TLV_BASE_ID + 10)

struct mwifiex_ie_types_header {
	__le16 type;
	__le16 len;
} __attribute__((packed));

/* ---- ioctl.h, verbatim ---- */
#define MWIFIEX_MAX_VSIE_LEN       (256)
#define MWIFIEX_MAX_VSIE_NUM       (8)

/* ---- fw.h, verbatim ---- */
struct mwifiex_ie_types_vendor_param_set {
	struct mwifiex_ie_types_header header;
	u8 ie[MWIFIEX_MAX_VSIE_LEN];
};

/* ---- main.h, verbatim ---- */
struct mwifiex_vendor_spec_cfg_ie {
	u16 mask;
	u16 flag;
	u8 ie[MWIFIEX_MAX_VSIE_LEN];
};

/* ---- main.h struct mwifiex_private, reduced to the single field
 * mwifiex_cmd_append_vsie_tlv() dereferences (priv->vs_ie[id]); real
 * name and real type, unchanged, just without the ~150 unrelated driver
 * fields (list_head/spinlock_t/etc.) that would need extensive stubbing
 * for zero additional coverage of the bug. ---- */
struct mwifiex_private {
	struct mwifiex_vendor_spec_cfg_ie vs_ie[MWIFIEX_MAX_VSIE_NUM];
};

/* ==================================================================
 * verbatim target function -- data_cve/cve_dd8eedbb/target/original_function.c
 * ================================================================== */
int
mwifiex_cmd_append_vsie_tlv(struct mwifiex_private *priv,
			    u16 vsie_mask, u8 **buffer)
{
	int id, ret_len = 0;
	struct mwifiex_ie_types_vendor_param_set *vs_param_set;

	if (!buffer)
		return 0;
	if (!(*buffer))
		return 0;

	/*
	 * Traverse through the saved vendor specific IE array and append
	 * the selected(scan/assoc/adhoc) IE as TLV to the command
	 */
	for (id = 0; id < MWIFIEX_MAX_VSIE_NUM; id++) {
		if (priv->vs_ie[id].mask & vsie_mask) {
			vs_param_set =
				(struct mwifiex_ie_types_vendor_param_set *)
				*buffer;
			vs_param_set->header.type =
				cpu_to_le16(TLV_TYPE_PASSTHROUGH);
			vs_param_set->header.len =
				cpu_to_le16((((u16) priv->vs_ie[id].ie[1])
				& 0x00FF) + 2);
			memcpy(vs_param_set->ie, priv->vs_ie[id].ie,
			       le16_to_cpu(vs_param_set->header.len));
			*buffer += le16_to_cpu(vs_param_set->header.len) +
				   sizeof(struct mwifiex_ie_types_header);
			ret_len += le16_to_cpu(vs_param_set->header.len) +
				   sizeof(struct mwifiex_ie_types_header);
		}
	}
	return ret_len;
}
/* ==================================================================
 * end of verbatim target function
 * ================================================================== */

/* Compiler-escape barrier (harness-only helper, does NOT touch the target
 * function): force the compiler to assume `p` may be read/written by
 * unknown code so the memcpy/pointer-advance inside
 * mwifiex_cmd_append_vsie_tlv() cannot be proven dead and optimized away. */
static void
vb_escape(void *p)
{
	__asm__ __volatile__("" : : "g"(p) : "memory");
}

/* Destination command buffer sized for exactly one well-formed TLV:
 * 4-byte header + up to 60 bytes of IE payload. A small ie[1] (len <= 60)
 * fits; a large one (len > 60, up to the max 257) overflows it -- this is
 * precisely the class of destination the missing MWIFIEX_MAX_VSIE_LEN
 * check was added to protect. */
#define DEST_BUF_SIZE 64

int
main(int argc, char **argv)
{
	FILE *f;
	long fsz;
	size_t n;
	unsigned char *filebuf;
	struct mwifiex_private *priv;
	u8 *dest, *dest_orig, **pbuffer;
	u16 vsie_mask;
	size_t i;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* attacker data MUST live on the heap so ASAN instruments it */
	filebuf = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!filebuf) { fclose(f); return 1; }

	n = fsz > 0 ? fread(filebuf, 1, (size_t)fsz, f) : 0;
	fclose(f);

	priv = (struct mwifiex_private *)calloc(1, sizeof(*priv));
	if (!priv) { free(filebuf); return 1; }

	/* Only vs_ie[0] participates: mask matches vsie_mask so the loop's
	 * single branch fires exactly once, isolating the memcpy under test
	 * to one deterministic call -- mirrors the real per-entry TLV-append
	 * logic without needing to populate all 8 slots. */
	vsie_mask = 0x0001;
	priv->vs_ie[0].mask = 0x0001;
	priv->vs_ie[0].flag = 0;
	priv->vs_ie[0].ie[0] = 0xDD; /* vendor-specific element id, informational */
	priv->vs_ie[0].ie[1] = (n > 0) ? filebuf[0] : 0; /* THE bug: unbounded length byte */
	for (i = 2; i < MWIFIEX_MAX_VSIE_LEN; i++) {
		size_t src = i - 1; /* filebuf[1..] feeds ie[2..], zero-padded */
		priv->vs_ie[0].ie[i] = (src < n) ? filebuf[src] : 0;
	}

	/* undersized command buffer the real caller supplies via **buffer */
	dest = (u8 *)malloc(DEST_BUF_SIZE);
	if (!dest) { free(filebuf); free(priv); return 1; }
	memset(dest, 0, DEST_BUF_SIZE);
	dest_orig = dest;
	pbuffer = &dest;

	vb_escape(priv);
	vb_escape(dest);
	(void)mwifiex_cmd_append_vsie_tlv(priv, vsie_mask, pbuffer);
	vb_escape(dest);

	free(filebuf);
	free(priv);
	free(dest_orig);
	return 0;
}
