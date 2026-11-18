#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- radare2 base integer types (libr/include/r_types_base.h), verbatim macros ---- */
#define ut64 unsigned long long
#define st64 long long
#define ut32 unsigned int
#define st32 int
#define ut16 unsigned short
#define st16 short
#define ut8 unsigned char
#define st8 signed char

#define UT32_MAX 0xFFFFFFFFU
#define UT8_MAX  0xFFU

/* ---- r_read_le32 (libr/include/r_endian.h), verbatim body ---- */
static inline ut32 r_read_le32(const void *src) {
	if (!src) {
		return UT32_MAX;
	}
	const ut8 *s = (const ut8*)src;
	return (((ut32)s[3]) << 24) | (((ut32)s[2]) << 16) |
		(((ut32)s[1]) << 8) | (((ut32)s[0]) << 0);
}

/* ---- RAnal: opaque; hexagon_v6_op never dereferences the `anal` param ---- */
typedef struct r_anal_t RAnal;

/* ---- RAnalOp (libr/include/r_anal.h): pruned to the two fields hexagon_v6_op
   actually touches (op->size, op->addr) -- real struct/field names & types,
   the rest of the real 30-field struct pulls in RList/RStrBuf/RAnalValue/etc
   that hexagon_v6_op's body never references ---- */
typedef struct r_anal_op_t {
	ut64 addr;
	int size;
} RAnalOp;

/* ---- RAnalOpMask (libr/include/r_anal.h), verbatim ---- */
typedef enum {
	R_ANAL_OP_MASK_BASIC = 0,
	R_ANAL_OP_MASK_ESIL  = 1,
	R_ANAL_OP_MASK_VAL   = 2,
	R_ANAL_OP_MASK_HINT  = 4,
	R_ANAL_OP_MASK_OPEX  = 8,
	R_ANAL_OP_MASK_DISASM = 16,
	R_ANAL_OP_MASK_ALL   = 1 | 2 | 4 | 8 | 16
} RAnalOpMask;

/* ---- HexInsn (libr/anal/arch/hexagon/hexagon_anal.h) and its two consumers:
   incidental to the crash. The OOB read happens at `r_read_le32(buf)`, which
   executes and traps BEFORE hexagon_v6_op ever touches `hi` or calls these two
   functions, so a minimal stand-in type + faithful no-op stubs are used (they
   only need to keep the "safe" (len>=4) path from crashing so it exits clean). ---- */
typedef struct { int _unused; } HexInsn;

static int hexagon_disasm_instruction(ut32 data, HexInsn *hi, ut32 addr) {
	(void)addr;
	/* genuinely propagate the decoded word so the optimizer cannot prove the
	   r_read_le32(buf) load inside hexagon_v6_op is dead and eliminate it;
	   always positive so the safe (len>=4) path below always reaches
	   hexagon_anal_instruction, matching a "valid packet decoded" outcome */
	hi->_unused = (int) data;
	return (int) (data % 251u) + 1;
}

static int hexagon_anal_instruction(HexInsn *hi, RAnalOp *op) {
	(void)op;
	return hi->_unused;
}

/* prevent -O1 from inlining the target out of the ASAN stack trace, without
   touching a single byte of its (verbatim, pasted below) definition */
static int hexagon_v6_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) __attribute__((noinline));

static int hexagon_v6_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	HexInsn hi = {0};;
	ut32 data = 0;
	data = r_read_le32 (buf);
	int size = hexagon_disasm_instruction (data, &hi, (ut32) addr);
	op->size = size;
	if (size <= 0) {
		return size;
	}

	op->addr = addr;
	return hexagon_anal_instruction (&hi, op);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	fseek(f, 0, SEEK_END);
	long fsz = ftell(f);
	if (fsz < 0) {
		fsz = 0;
	}
	fseek(f, 0, SEEK_SET);

	/* HEAP-allocate the input buffer, sized EXACTLY to the file length (never
	   0, to sidestep malloc(0) implementation ambiguity) -- this is the `buf`
	   that hexagon_v6_op reads. A file shorter than 4 bytes makes the
	   unconditional r_read_le32(buf) read past this allocation:
	   heap-buffer-overflow READ (CWE-125) -- exactly the bug the upstream fix
	   guards with "if (len < 4) { return 0; }" before the read. */
	size_t alloc_sz = (fsz > 0) ? (size_t) fsz : 1;
	ut8 *heapbuf = (ut8 *) malloc(alloc_sz);
	if (!heapbuf) {
		fclose(f);
		return 1;
	}
	memset(heapbuf, 0, alloc_sz);
	size_t got = (fsz > 0) ? fread(heapbuf, 1, (size_t) fsz, f) : 0;
	fclose(f);
	(void) got;

	RAnalOp op;
	memset(&op, 0, sizeof(op));

	int rc = hexagon_v6_op(NULL, &op, 0x1000, heapbuf, (int) fsz, R_ANAL_OP_MASK_BASIC);
	/* observe rc/op through an opaque external call so nothing upstream
	   (including the r_read_le32(buf) load) can be proven dead and dropped */
	fprintf(stderr, "rc=%d op.size=%d op.addr=%llu\n", rc, op.size, (unsigned long long) op.addr);

	free(heapbuf);
	return 0;
}
