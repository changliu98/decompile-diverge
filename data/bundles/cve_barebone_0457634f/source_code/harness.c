/* cve_barebone direct-call harness for CVE-2022-0522 (radare2)
 * Target: vector64_dst_append  (libr/anal/p/anal_arm_cs.c)
 * Bug class: global-buffer-overflow READ (CWE-125).
 *
 * Fix commit d17a7bdf166108a29a27cd89bf454f9fa6c050d6 changes the macro
 *     #define VEC64_MASK(sh, sz) (bitmask_by_width[63]^(bitmask_by_width[sz-1]<<sh))
 * to
 *     #define VEC64_MASK(sh, sz) (bitmask_by_width[63]^(bitmask_by_width[sz>0?sz-1:0]<<sh))
 * i.e. it adds a `sz>0` guard before doing `sz-1`. The vulnerable macro body copied
 * below is missing that guard.
 *
 * vector64_dst_append's own body can drive `sz` to 0: `size = vector_size(&op)` returns
 * 64 whenever the ARM64 vector-arrangement-specifier operand is ARM64_VAS_2D or
 * ARM64_VAS_1D (`vas_size()`'s ARM64_VAS_2D/_1D case). When the instruction's per-lane
 * shift amount (`shift = i * size`) is NOT strictly inside (0, 64) -- which for size==64
 * is true for every possible `i`, since i*64 is always a multiple of 64 -- the function
 * takes the `else` branch and computes `dimsize = size % 64`. For size==64 that is
 * `dimsize = 0`, and `VEC64_MASK(shift, dimsize)` then evaluates
 * `bitmask_by_width[dimsize - 1]` = `bitmask_by_width[-1]`: an 8-byte READ immediately
 * BEFORE the start of the global array `bitmask_by_width` -- a global-buffer-overflow
 * (underflow) read, entirely inside vector64_dst_append's own inlined macro expansion
 * (the read happens while evaluating an argument to r_strbuf_appendf, before that call
 * even executes).
 *
 * This harness constructs the `cs_insn`/`cs_arm64_op` capstone-disassembly-result
 * structure directly from the input file's bytes (no real ARM64 disassembly needed --
 * vector64_dst_append only ever reads `op.vector_index`, `op.vas`, and `op.reg`) and
 * calls vector64_dst_append(&sb, &handle, &insn, 0, i) directly:
 *   byte[0] -> op.vas        (mod 14, i.e. one of ARM64_VAS_INVALID..ARM64_VAS_1D --
 *                              ARM64_VAS_1Q (size 128) is deliberately excluded: it
 *                              trips a DIFFERENT, still-unfixed OOB read on the "if"
 *                              branch that is not this CVE, so it would contaminate the
 *                              safe/triggering split)
 *   byte[1] -> i              (signed; the per-lane index -- any value with vas in
 *                              {ARM64_VAS_2D, ARM64_VAS_1D} and i!=-1 triggers)
 *   byte[2] -> op.vector_index (signed; -1 = "don't override i", else overrides i)
 *   byte[3] -> op.reg          (arbitrary; only fed to a stub cs_reg_name())
 * vas values 1..11 (ARM64_VAS_16B/8B/4B/1B/8H/4H/2H/1H/4S/2S/1S) all give size in
 * {8,16,32}, for which `dimsize` is never 0 and the corresponding bitmask_by_width
 * index is always in [7,31] -- safe for ANY i. vas==0 (ARM64_VAS_INVALID) takes the
 * function's `isvessas`-false branch entirely, never reaching vector_size() at all --
 * also safe.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <inttypes.h>

/* ==== real base-integer typedefs, verbatim macros from libr/include/r_types_base.h ==== */
#define ut64 uint64_t

/* ==== real format macro, verbatim non-Windows branch from libr/include/r_types.h ==== */
#define PFMT64x PRIx64

/* ==== real capstone API version this vendored tree ships, verbatim from
 *      shlr/capstone/include/capstone/capstone.h:50 (`#define CS_API_MAJOR 5`) --
 *      selects the `#else` (non-CS_API_MAJOR==4) arms of vector64_dst_append /
 *      vector_size / vas_size below, exactly as the real build does. ==== */
#define CS_API_MAJOR 5

/* ==== real capstone handle typedef, verbatim from capstone.h:71 ==== */
typedef size_t csh;

/* ==== real capstone arm64 vector-arrangement-specifier enum, verbatim from
 *      shlr/capstone/include/capstone/arm64.h:818-834 ==== */
typedef enum arm64_vas {
	ARM64_VAS_INVALID = 0,
	ARM64_VAS_16B,
	ARM64_VAS_8B,
	ARM64_VAS_4B,
	ARM64_VAS_1B,
	ARM64_VAS_8H,
	ARM64_VAS_4H,
	ARM64_VAS_2H,
	ARM64_VAS_1H,
	ARM64_VAS_4S,
	ARM64_VAS_2S,
	ARM64_VAS_1S,
	ARM64_VAS_2D,
	ARM64_VAS_1D,
	ARM64_VAS_1Q,
} arm64_vas;

/* ==== capstone arm64 register + operand structs, reduced to the three fields
 *      vector64_dst_append actually dereferences (vector_index, vas, reg). The real
 *      cs_arm64_op (arm64.h:1348-1372) additionally carries `shift`/`ext`/`type`/`access`
 *      and a union of {imm, fp, mem, pstate, sys, prefetch, barrier} alongside `reg` --
 *      none of those are read anywhere in vector64_dst_append's body, so (as incidental,
 *      off-crash-path detail) they are omitted here rather than pulling in every
 *      supporting enum/struct (arm64_shifter, arm64_extender, arm64_op_mem, ...) that
 *      backs them. Field NAMES that ARE used keep their real names/real types. ==== */
typedef int arm64_reg;
typedef struct cs_arm64_op {
	int vector_index;	/* real field, arm64.h:1349 */
	arm64_vas vas;		/* real field, arm64.h:1350 */
	arm64_reg reg;		/* real field (union member), arm64.h:1358 */
} cs_arm64_op;

/* ==== real capstone arm64 instruction-detail struct, reduced to the `operands` array
 *      vector64_dst_append indexes (arm64.h:1375-1385 also carries `cc`/`update_flags`/
 *      `writeback`, none of which vector64_dst_append touches). ==== */
typedef struct cs_arm64 {
	uint8_t op_count;
	cs_arm64_op operands[8];
} cs_arm64;

/* ==== real capstone cs_detail, reduced: the real struct (capstone.h:312-341) is a union
 *      of 16 different architectures' detail structs (x86/arm/m68k/mips/ppc/sparc/sysz/
 *      xcore/tms320c64x/m680x/evm/mos65xx/wasm/bpf/riscv/arm64) plus regs_read/
 *      regs_write/groups arrays; vector64_dst_append only ever dereferences `->arm64`,
 *      so the other architectures (wholly incidental to this function) are omitted. ==== */
typedef struct cs_detail {
	cs_arm64 arm64;
} cs_detail;

/* ==== real capstone cs_insn, verbatim field list from capstone.h:344-381 except the
 *      last field (`detail`, the only one vector64_dst_append dereferences) keeps its
 *      real name/type; the others are kept for shape-fidelity though the function never
 *      reads them. ==== */
typedef struct cs_insn {
	unsigned int id;
	uint64_t address;
	uint16_t size;
	uint8_t bytes[24];
	char mnemonic[32];
	char op_str[160];
	cs_detail *detail;
} cs_insn;

/* ==== real radare2 RStrBuf, verbatim from libr/include/r_util/r_strbuf.h:8-14 ==== */
typedef struct {
	char buf[32];
	size_t len;
	char *ptr;
	size_t ptrlen;
	bool weakref;
} RStrBuf;

/* ==== incidental callee stubs -- NOT on the crash path in the sense that, on a
 *      triggering input, r_strbuf_appendf's caller (vector64_dst_append) evaluates its
 *      arguments -- including the OOB bitmask_by_width[-1] read -- BEFORE the call
 *      itself executes, so the process is already killed by ASAN before this body would
 *      ever run. IMPORTANT: the stub below genuinely consumes its varargs via
 *      vsnprintf(), mirroring the real r_strbuf_vappendf (libr/util/strbuf.c:277-286,
 *      `vsnprintf (string, sizeof (string), fmt, ap)`) rather than being a bare no-op --
 *      a no-op body (that never calls va_arg) lets the compiler prove the variadic
 *      argument EXPRESSIONS are dead and fold them away at -O1, which would silently
 *      optimize out the very read this harness exists to exercise. Going through libc's
 *      vsnprintf (opaque to the compiler) forces every argument, including the OOB
 *      read, to actually be materialized -- exactly as it is in the real build, where
 *      r_strbuf_vappendf's vsnprintf call plays the same role. cs_reg_name is likewise
 *      only used to build a string for that output. ==== */
static const char *r_str_getf(const char *str) {
	/* real body, verbatim from libr/util/str.c:844-846 */
	static const char *nullstr_c = "";
	return str ? str : nullstr_c;
}
static bool r_strbuf_appendf(RStrBuf *sb, const char *fmt, ...) {
	char string[1024];
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(string, sizeof(string), fmt, ap);
	va_end(ap);
	if (sb) {
		size_t l = strnlen(string, sizeof(string));
		if (sb->len + l + 1 <= sizeof(sb->buf)) {
			memcpy(sb->buf + sb->len, string, l);
			sb->buf[sb->len + l] = 0;
			sb->len += l;
		}
	}
	return true;
}
static const char *cs_reg_name(csh handle, arm64_reg reg) {
	(void)handle; (void)reg;
	return "x0";
}

/* ==== real callees, verbatim from libr/anal/p/anal_arm_cs.c:528-556, 887-897 ==== */
static int vas_size(arm64_vas vas) {
	switch (vas) {
	case ARM64_VAS_8B:
	case ARM64_VAS_16B:
		return 8;
	case ARM64_VAS_4H:
	case ARM64_VAS_8H:
		return 16;
	case ARM64_VAS_2S:
	case ARM64_VAS_4S:
		return 32;
	case ARM64_VAS_2D:
	case ARM64_VAS_1D:
		return 64;
	case ARM64_VAS_1Q:
		return 128;
#if CS_API_MAJOR > 4
	case ARM64_VAS_1B:
	case ARM64_VAS_4B:
		return 8;
	case ARM64_VAS_2H:
	case ARM64_VAS_1H:
		return 16;
	case ARM64_VAS_1S:
		return 32;
#endif
	default:
		return 64;
	}
}

static int vector_size(cs_arm64_op *op) {
#if CS_API_MAJOR == 4
	if (op->vess) {
		return vess_size(op->vess);
	}
#endif
	if (op->vas) {
		return vas_size(op->vas);
	} else {
		return 64;
	}
}

/* ==== TARGET FUNCTION -- byte-for-byte from
 *      data_cve/cve_0457634f/target/original_function.c
 *      (radare2 libr/anal/p/anal_arm_cs.c:1057-1094, vul_commit 8525ad0b) ==== */
#define BITMASK_BY_WIDTH_COUNT 64
static const ut64 bitmask_by_width[BITMASK_BY_WIDTH_COUNT] = {
	0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x1ff, 0x3ff, 0x7ff,
	0xfff, 0x1fff, 0x3fff, 0x7fff, 0xffff, 0x1ffff, 0x3ffff, 0x7ffff,
	0xfffff, 0x1fffff, 0x3fffff, 0x7fffff, 0xffffff, 0x1ffffffLL, 0x3ffffffLL,
	0x7ffffffLL, 0xfffffffLL, 0x1fffffffLL, 0x3fffffffLL, 0x7fffffffLL, 0xffffffffLL,
	0x1ffffffffLL, 0x3ffffffffLL, 0x7ffffffffLL, 0xfffffffffLL, 0x1fffffffffLL,
	0x3fffffffffLL, 0x7fffffffffLL, 0xffffffffffLL, 0x1ffffffffffLL, 0x3ffffffffffLL,
	0x7ffffffffffLL, 0xfffffffffffLL, 0x1fffffffffffLL, 0x3fffffffffffLL, 0x7fffffffffffLL,
	0xffffffffffffLL, 0x1ffffffffffffLL, 0x3ffffffffffffLL, 0x7ffffffffffffLL,
	0xfffffffffffffLL, 0x1fffffffffffffLL, 0x3fffffffffffffLL, 0x7fffffffffffffLL,
	0xffffffffffffffLL, 0x1ffffffffffffffLL, 0x3ffffffffffffffLL, 0x7ffffffffffffffLL,
	0xfffffffffffffffLL, 0x1fffffffffffffffLL, 0x3fffffffffffffffLL, 0x7fffffffffffffffLL, 0xffffffffffffffffLL
};

#define INSOP64(x) insn->detail->arm64.operands[x]
#define REG64(x) r_str_getf (cs_reg_name (*handle, insn->detail->arm64.operands[x].reg))
#define VEC64_MASK(sh, sz) (bitmask_by_width[63]^(bitmask_by_width[sz-1]<<sh))

static void vector64_dst_append(RStrBuf *sb, csh *handle, cs_insn *insn, int n, int i) {
	cs_arm64_op op = INSOP64 (n);

	if (op.vector_index != -1) {
		i = op.vector_index;
	}
#if CS_API_MAJOR == 4
	const bool isvessas = (op.vess || op.vas);
#else
	const bool isvessas = op.vas;
#endif
	if (isvessas && i != -1) {
		int size = vector_size (&op);
		int shift = i * size;
		char *regc = "l";
		size_t s = sizeof (bitmask_by_width) / sizeof (*bitmask_by_width);
		size_t index = size > 0? (size - 1) % s: 0;
		if (index >= BITMASK_BY_WIDTH_COUNT) {
			index = 0;
		}
		ut64 mask = bitmask_by_width[index];
		if (shift >= 64) {
			shift -= 64;
			regc = "h";
		}

		if (shift > 0 && shift < 64) {
			r_strbuf_appendf (sb, "%d,SWAP,0x%"PFMT64x",&,<<,%s%s,0x%"PFMT64x",&,|,%s%s",
				shift, mask, REG64 (n), regc, VEC64_MASK (shift, size), REG64 (n), regc);
		} else {
			int dimsize = size % 64;
			r_strbuf_appendf (sb, "0x%"PFMT64x",&,%s%s,0x%"PFMT64x",&,|,%s%s",
				mask, REG64 (n), regc, VEC64_MASK (shift, dimsize), REG64 (n), regc);
		}
	} else {
		r_strbuf_appendf (sb, "%s", REG64 (n));
	}
}
/* ==== END TARGET FUNCTION ==== */

int main(int argc, char **argv) {
	if (argc < 2) {
		return 0;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		return 0;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz_l = ftell(f);
	if (sz_l < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }
	size_t sz = (size_t)sz_l;

	/* Heap-allocate the raw input (ASAN-guarded). */
	uint8_t *buf = (uint8_t *)malloc(sz > 0 ? sz : 1);
	if (!buf) { fclose(f); return 0; }
	size_t nread = sz > 0 ? fread(buf, 1, sz, f) : 0;
	fclose(f);
	if (nread != sz) { free(buf); return 0; }

	uint8_t b_vas = sz > 0 ? buf[0] : 0;
	int8_t  b_i   = sz > 1 ? (int8_t)buf[1] : 0;
	int8_t  b_vix = sz > 2 ? (int8_t)buf[2] : -1;
	uint8_t b_reg = sz > 3 ? buf[3] : 0;
	free(buf);

	/* mod 14 -> {ARM64_VAS_INVALID..ARM64_VAS_1D}, deliberately excluding
	 * ARM64_VAS_1Q (see file header comment). */
	arm64_vas vas = (arm64_vas)((int)(b_vas % 14));

	cs_arm64_op op0;
	memset(&op0, 0, sizeof(op0));
	op0.vector_index = (int)b_vix;
	op0.vas = vas;
	op0.reg = (arm64_reg)((b_reg % 28) + 1);

	cs_detail detail;
	memset(&detail, 0, sizeof(detail));
	detail.arm64.op_count = 1;
	detail.arm64.operands[0] = op0;

	cs_insn insn;
	memset(&insn, 0, sizeof(insn));
	insn.detail = &detail;

	csh handle = 1;
	RStrBuf sb;
	memset(&sb, 0, sizeof(sb));

	vector64_dst_append(&sb, &handle, &insn, 0, (int)b_i);

	return 0;
}
