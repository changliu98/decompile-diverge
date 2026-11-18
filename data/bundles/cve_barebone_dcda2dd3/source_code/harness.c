/*
 * cve_barebone direct-call harness for CVE-2020-5208 (ipmitool read_fru_area).
 *
 * Bug: read_fru_area() (lib/ipmi_fru.c) trusts the length byte reported by the
 * IPMI device in the GET_FRU_DATA response (rsp->data[0]) and memcpy()s that
 * many bytes straight into the caller-supplied `frubuf` without ever checking
 * it against the remaining space in that buffer (or against rsp->data_len).
 * Real callers allocate frubuf as `malloc(fru.size)` (see ipmi_fru.c:3249-3253,
 * `read_fru_area(intf, &fru, fruId, 0, fru.size, pFruBuf)` right after
 * `pFruBuf = malloc(fru.size)`), so a malicious/misbehaving IPMI responder can
 * report a chunk length larger than fru.size and overflow that heap buffer --
 * a classic CWE-787 heap-based buffer overflow WRITE, fixed upstream in
 * e824c23316ae50beb7f7488f2055ac65e8b341f2 by clamping `tmp` against
 * `rsp->data_len` and a new `size_left_in_buffer` counter.
 *
 * This harness fakes the IPMI transport: `fake_sendrecv()` stands in for
 * `intf->sendrecv` and returns a GET_FRU_DATA response whose reported chunk
 * length (`data[0]`) is taken byte-by-byte from the fuzz input file, i.e. the
 * "device" is attacker-controlled. Everything else (struct layouts, macros,
 * `fru_cc_rq2big`, `val2str`/`completion_code_vals`, `lprintf`) is copied
 * verbatim (or a byte-faithful minimal re-declaration) from the real
 * ipmitool headers/sources so the target function's own body is untouched.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

/* ---- include/ipmitool/ipmi.h (real names/values) ---- */
#define IPMI_BUF_SIZE 1024
#define IPMI_NETFN_STORAGE 0xa

struct valstr {
	uint32_t val;
	const char *str;
};

const char *val2str(uint32_t val, const struct valstr *vs)
{
	static char un_str[32];
	int i;
	for (i = 0; vs[i].str != NULL; i++) {
		if (vs[i].val == val)
			return vs[i].str;
	}
	snprintf(un_str, sizeof(un_str), "Unknown (0x%02x)", val);
	return un_str;
}

/* ---- include/ipmitool/log.h ---- */
#define LOG_ERR      3
#define LOG_ERROR    3
#define LOG_NOTICE   5
#define LOG_INFO     6

void lprintf(int level, const char *format, ...)
{
	va_list ap;
	(void)level;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}

/* ---- include/ipmitool/ipmi_cc.h ---- */
#define IPMI_CC_REQ_DATA_INV_LENGTH    0xc7
#define IPMI_CC_REQ_DATA_FIELD_EXCEED  0xc8
#define IPMI_CC_CANT_RET_NUM_REQ_BYTES 0xca

/* ---- lib/ipmi_strings.c (trimmed, real entries) ---- */
const struct valstr completion_code_vals[] = {
	{ 0x00, "Command completed normally" },
	{ 0xc7, "Request data length invalid" },
	{ 0xc8, "Request data field length limit exceeded" },
	{ 0xca, "Cannot return number of requested data bytes" },
	{ 0xff, NULL }
};

/* ---- include/ipmitool/ipmi.h : struct ipmi_rq / struct ipmi_rs ---- */
struct ipmi_rq {
	struct {
		uint8_t netfn:6;
		uint8_t lun:2;
		uint8_t cmd;
		uint8_t target_cmd;
		uint16_t data_len;
		uint8_t *data;
	} msg;
};

struct ipmi_rs {
	uint8_t ccode;
	uint8_t data[IPMI_BUF_SIZE];
	int data_len;
	struct {
		uint8_t netfn;
		uint8_t cmd;
		uint8_t seq;
		uint8_t lun;
	} msg;
};

/* ---- include/ipmitool/ipmi_intf.h : struct ipmi_intf (trimmed to the
 * fields read_fru_area actually touches) + the max-response-size helper ---- */
struct ipmi_intf {
	struct ipmi_rs *(*sendrecv)(struct ipmi_intf *intf, struct ipmi_rq *req);
	uint16_t max_response_data_size;
};

uint16_t ipmi_intf_get_max_response_data_size(struct ipmi_intf *intf)
{
	return intf->max_response_data_size;
}

/* ---- include/ipmitool/ipmi_fru.h ---- */
struct fru_info {
	uint16_t size;
	uint8_t access:1;
	uint8_t max_read_size;
	uint8_t max_write_size;
};

#define GET_FRU_DATA 0x11
#define FRU_BLOCK_SZ 8
#define FRU_AREA_MAXIMUM_BLOCK_SZ 32

/* ---- lib/ipmi_fru.c:104 (verbatim, static helper read_fru_area calls) ---- */
static inline bool fru_cc_rq2big(int code) {
	return (code == IPMI_CC_REQ_DATA_INV_LENGTH
		|| code == IPMI_CC_REQ_DATA_FIELD_EXCEED
		|| code == IPMI_CC_CANT_RET_NUM_REQ_BYTES);
}

/* ==== target/original_function.c verbatim below ==== */
int
read_fru_area(struct ipmi_intf * intf, struct fru_info *fru, uint8_t id,
			uint32_t offset, uint32_t length, uint8_t *frubuf)
{
	uint32_t off = offset, tmp, finish;
	struct ipmi_rs * rsp;
	struct ipmi_rq req;
	uint8_t msg_data[4];

	if (offset > fru->size) {
		lprintf(LOG_ERR, "Read FRU Area offset incorrect: %d > %d",
			offset, fru->size);
		return -1;
	}

	finish = offset + length;
	if (finish > fru->size) {
		finish = fru->size;
		lprintf(LOG_NOTICE, "Read FRU Area length %d too large, "
			"Adjusting to %d",
			offset + length, finish - offset);
	}

	memset(&req, 0, sizeof(req));
	req.msg.netfn = IPMI_NETFN_STORAGE;
	req.msg.cmd = GET_FRU_DATA;
	req.msg.data = msg_data;
	req.msg.data_len = 4;

	if (fru->max_read_size == 0) {
		uint16_t max_rs_size = ipmi_intf_get_max_response_data_size(intf) - 1;

		/* validate lower bound of the maximum response data size */
		if (max_rs_size <= 1) {
			lprintf(LOG_ERROR, "Maximum response size is too small to send "
					"a read request");
			return -1;
		}

		/*
		 * Read FRU Info command may read up to 255 bytes of data.
		 */
		if (max_rs_size - 1 > 255) {
			/*  Limit the max read size with 255 bytes. */
			fru->max_read_size = 255;
		} else {
			/* subtract 1 byte for bytes count */
			fru->max_read_size = max_rs_size - 1;
		}

		/* check word access */
		if (fru->access) {
			fru->max_read_size &= ~1;
		}
	}

	do {
		tmp = fru->access ? off >> 1 : off;
		msg_data[0] = id;
		msg_data[1] = (uint8_t)(tmp & 0xff);
		msg_data[2] = (uint8_t)(tmp >> 8);
		tmp = finish - off;
		if (tmp > fru->max_read_size)
			msg_data[3] = (uint8_t)fru->max_read_size;
		else
			msg_data[3] = (uint8_t)tmp;

		rsp = intf->sendrecv(intf, &req);
		if (!rsp) {
			lprintf(LOG_NOTICE, "FRU Read failed");
			break;
		}
		if (rsp->ccode) {
			/* if we get C7h or C8h or CAh return code then we requested too
			* many bytes at once so try again with smaller size */
			if (fru_cc_rq2big(rsp->ccode)
			    && fru->max_read_size > FRU_BLOCK_SZ)
			{
				if (fru->max_read_size > FRU_AREA_MAXIMUM_BLOCK_SZ) {
					/* subtract read length more aggressively */
					fru->max_read_size -= FRU_BLOCK_SZ;
				} else {
					/* subtract length less aggressively */
					fru->max_read_size--;
				}

				lprintf(LOG_INFO, "Retrying FRU read with request size %d",
						fru->max_read_size);
				continue;
			}

			lprintf(LOG_NOTICE, "FRU Read failed: %s",
				val2str(rsp->ccode, completion_code_vals));
			break;
		}

		tmp = fru->access ? rsp->data[0] << 1 : rsp->data[0];
		memcpy(frubuf, rsp->data + 1, tmp);
		off += tmp;
		frubuf += tmp;
		/* sometimes the size returned in the Info command
		* is too large.  return 0 so higher level function
		* still attempts to parse what was returned */
		if (tmp == 0 && off < finish) {
			return 0;
		}
	} while (off < finish);

	if (off < finish) {
		return -1;
	}

	return 0;
}/* ==== end target/original_function.c ==== */

/*
 * Attacker-controlled "IPMI transport": every call reads one byte from the
 * fuzz input and reports it as the GET_FRU_DATA response's chunk length
 * (rsp->data[0]) -- exactly the value read_fru_area's vulnerable memcpy()
 * trusts blindly. ccode is always 0 (success) so we go straight down the
 * memcpy path every time; data_len is generously large (real firmware would
 * set it to whatever it wants, and the pre-fix code never checks it).
 */
static const uint8_t *g_input;
static size_t g_input_len;
static size_t g_input_pos;

static uint8_t next_byte(void)
{
	if (g_input_pos < g_input_len)
		return g_input[g_input_pos++];
	return 0;
}

static struct ipmi_rs g_rsp;

static struct ipmi_rs *fake_sendrecv(struct ipmi_intf *intf, struct ipmi_rq *req)
{
	size_t i;
	(void)intf;
	(void)req;
	memset(&g_rsp, 0, sizeof(g_rsp));
	g_rsp.ccode = 0x00;
	g_rsp.data[0] = next_byte();
	for (i = 1; i < sizeof(g_rsp.data); i++)
		g_rsp.data[i] = (uint8_t)(i & 0xff);
	g_rsp.data_len = (int)sizeof(g_rsp.data);
	return &g_rsp;
}

int main(int argc, char **argv)
{
	FILE *f;
	long sz;
	uint8_t *filebuf;
	uint8_t *frubuf;
	struct ipmi_intf intf;
	struct fru_info fru;
	int rc;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}
	f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 0)
		sz = 0;
	filebuf = malloc(sz > 0 ? (size_t)sz : 1);
	if (!filebuf) {
		fclose(f);
		return 1;
	}
	if (sz > 0 && fread(filebuf, 1, (size_t)sz, f) != (size_t)sz) {
		fclose(f);
		free(filebuf);
		return 1;
	}
	fclose(f);

	g_input = filebuf;
	g_input_len = (size_t)sz;
	g_input_pos = 0;

	memset(&intf, 0, sizeof(intf));
	intf.sendrecv = fake_sendrecv;
	intf.max_response_data_size = 64;

	memset(&fru, 0, sizeof(fru));
	fru.size = 16;          /* declared FRU area size (device-reported, real ipmitool) */
	fru.access = 0;
	fru.max_read_size = 0;  /* forces the auto-compute branch, as on a real first call */

	/* Faithful to the real call site (lib/ipmi_fru.c:3249-3253):
	 *   pFruBuf = malloc(fru.size);
	 *   read_fru_area(intf, &fru, fruId, 0, fru.size, pFruBuf);
	 * -- the output buffer is heap-allocated to exactly fru.size bytes. */
	frubuf = malloc(fru.size);
	if (!frubuf) {
		free(filebuf);
		return 1;
	}

	rc = read_fru_area(&intf, &fru, 0, 0, fru.size, frubuf);
	printf("read_fru_area rc=%d\n", rc);

	free(frubuf);
	free(filebuf);
	return 0;
}
