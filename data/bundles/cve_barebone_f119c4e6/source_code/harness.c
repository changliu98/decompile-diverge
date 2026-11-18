/*
 * cve_f119c4e6 direct-call crash harness for smartdns's _dns_encode_HTTPS()
 * (CVE-2023-31470 / CWE-787 heap-buffer-overflow WRITE).
 *
 * Root cause (src/dns.c, _dns_encode_HTTPS): while re-encoding a parsed HTTPS
 * answer RR's SvcParam list into the output buffer, the per-param loop only
 * checks `_dns_left_len(context) <= 0` (i.e. "is there ANY room left") before
 * doing `memcpy(context->ptr, param->value, param->len)` -- it never checks
 * that `param->len` (attacker-controlled, taken straight from the parsed
 * packet) actually FITS in the remaining output space. So a SvcParam whose
 * declared length exceeds the caller's output buffer overflows it by
 * (param->len - room_left) bytes. The upstream fix
 * (56d0332bf91104cfc877635f6c82e9348587df04) adds exactly that length check.
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the real smartdns
 *      types the function (and the real callees below) need: struct
 *      dns_context / dns_rrs / dns_packet / dns_packet_dict(_item) /
 *      dns_head / dns_https_param, and the dns_rr_type / dns_class /
 *      dns_type / dns_https_svcparam enums -- copied verbatim (field names,
 *      values, `packed`/flexible-array layout) from src/dns.h.
 *   2. VERBATIM real callees from src/dns.c that _dns_encode_HTTPS needs to
 *      actually run (the fault is inside _dns_encode_HTTPS itself, but it is
 *      unreachable without its own real helper chain): the wire-format
 *      read/write primitives (_dns_read_short/_dns_write_short/
 *      _dns_write_int/_dns_read_int/_dns_left_len), the SOURCE-side RR/
 *      SvcParam parse chain that produces the `struct dns_rrs *` +
 *      `struct dns_https_param *` the target function consumes
 *      (_dns_get_domain_from_packet, _dns_decode_domain, dict_hash,
 *      _dns_add_domain_dict, _dns_get_domain_offset, _dns_init_context_by_rrs,
 *      _dns_get_qr_head, _dns_get_rr_head, dns_get_rr_nested_start/next,
 *      dns_get_HTTPS_svcparm_start/next), and the OUTPUT-side encode chain
 *      _dns_encode_HTTPS calls before the vulnerable loop
 *      (_dns_encode_domain, _dns_encode_qr_head, _dns_encode_rr_head). All
 *      copied byte-for-byte from src/dns.c, unmodified.
 *   3. `tlog_ext` stubbed (src/dns.c calls it only via the `tlog()` macro for
 *      a diagnostic log line on the `param == NULL` early-return path -- no
 *      logging/threading subsystem needed) and `safe_strncpy` copied verbatim
 *      from src/include/stringutil.h (a `static inline` real callee of
 *      dns_get_HTTPS_svcparm_start).
 *   4. VERBATIM target function: dataset/cve_f119c4e6/target/original_function.c
 *      byte-for-byte (_dns_encode_HTTPS itself, UNCHANGED -- logic/names/
 *      signature untouched).
 *   5. main(): reads argv[1] into a HEAP buffer (required so ASAN
 *      instruments it), and from those raw bytes DIRECTLY builds the two
 *      real structures _dns_encode_HTTPS takes as arguments:
 *        - `struct dns_rrs *rrs` (the SOURCE / already-parsed answer RR):
 *          hand-assembled the same way the real dns_decode()/dns_get_rrs_start()
 *          would leave it -- embedded inside a `struct dns_packet`'s data
 *          area, root owner-name + DNS_T_HTTPS/DNS_C_IN/ttl/rdlen header,
 *          empty SVCB TargetName, then ONE attacker-controlled SvcParam TLV
 *          (key/len taken straight from argv[1] bytes, value bytes copied
 *          from the rest of argv[1] into a generously padded region so the
 *          SOURCE side never itself overflows -- this harness isolates the
 *          WRITE-side bug, matching the baseline's `access: WRITE`).
 *        - `struct dns_context context` (the OUTPUT / re-encode buffer): a
 *          SMALL heap buffer whose size is `18 + extra_room` where
 *          `extra_room` is itself taken from argv[1] -- 18 bytes is exactly
 *          what _dns_encode_HTTPS's own preamble (owner name + qtype/qclass +
 *          ttl/rdlen + priority + empty target + the SvcParam key/len fields)
 *          consumes before the vulnerable memcpy, so `extra_room` is exactly
 *          the room left for `param->value`: `extra_room < param->len` (with
 *          an allowed SvcParam key) reproduces the overflow; `extra_room >=
 *          param->len`, or a disallowed key (falls into the harmless
 *          `default: context->ptr -= 4;` branch), stays in-bounds.
 *      Calls `_dns_encode_HTTPS(&context, rrs)` directly, exactly once.
 *
 * Input format (argv[1], all fields little-endian, native host order --
 * `dns_get_HTTPS_svcparm_start`/`_next` read `param->key`/`param->len`
 * via a raw struct-cast on the parsed bytes, with NO ntohs() applied, so
 * this harness's SvcParam TLV bytes are written in that same native order):
 *   bytes[0..1]  extra_room (u16)  -- output-buffer slack beyond the 18-byte
 *                                     fixed preamble
 *   bytes[2..3]  key        (u16)  -- SvcParam key (DNS_HTTPS_T_* to hit the
 *                                     memcpy branch; anything >= 7 is safe)
 *   bytes[4..5]  len        (u16)  -- SvcParam declared length (attacker len)
 *   bytes[6..]   value bytes (optional, copied verbatim into param->value;
 *                                     the rest of the SOURCE-side value
 *                                     region is padding, never read as
 *                                     attacker-meaningful past `len`)
 * Fewer than 6 input bytes are zero-padded (a short/empty PoC is a safe,
 * cleanly-handled input: the parse chain runs out of data and
 * _dns_encode_HTTPS's own `param == NULL` check returns -1 without ever
 * reaching the loop).
 */
#define _GNU_SOURCE
#include <arpa/inet.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal real type/macro defs, verbatim from src/dns.h ---- */


#define DNS_MAX_CNAME_LEN 256

#define DNS_RR_END (0XFFFF)


typedef enum dns_rr_type {
	DNS_RRS_QD = 0,
	DNS_RRS_AN = 1,
	DNS_RRS_NS = 2,
	DNS_RRS_NR = 3,
	DNS_RRS_OPT = 4,
	DNS_RRS_END,
} dns_rr_type;

typedef enum dns_class {
	DNS_C_IN = 1, // DNS C IN
	DNS_C_ANY = 255
} dns_class_t;

typedef enum dns_type {
	DNS_T_A = 1,
	DNS_T_NS = 2,
	DNS_T_CNAME = 5,
	DNS_T_SOA = 6,
	DNS_T_PTR = 12,
	DNS_T_MX = 15,
	DNS_T_TXT = 16,
	DNS_T_AAAA = 28,
	DNS_T_SRV = 33,
	DNS_T_OPT = 41,
	DNS_T_SSHFP = 44,
	DNS_T_HTTPS = 65,
	DNS_T_SPF = 99,
	DNS_T_AXFR = 252,
	DNS_T_ALL = 255
} dns_type_t;

typedef enum dns_https_svcparam {
	DNS_HTTPS_T_MANDATORY = 0,
	DNS_HTTPS_T_ALPN = 1,
	DNS_HTTPS_T_NO_DEFAULT_ALPN = 2,
	DNS_HTTPS_T_PORT = 3,
	DNS_HTTPS_T_IPV4HINT = 4,
	DNS_HTTPS_T_ECH = 5,
	DNS_HTTPS_T_IPV6HINT = 6,
	DNS_HTTPS_T_ALL = 255
} dns_https_svcparam_t;

struct dns_head {
	unsigned short id;      /* identification number */
	unsigned short qr;      /* Query/Response Flag */
	unsigned short opcode;  /* Operation Code */
	unsigned char aa;       /* Authoritative Answer Flag */
	unsigned char tc;       /* Truncation Flag */
	unsigned char rd;       /* Recursion Desired */
	unsigned char ra;       /* Recursion Available */
	unsigned short rcode;   /* Response Code */
	unsigned short qdcount; /* number of question entries */
	unsigned short ancount; /* number of answer entries */
	unsigned short nscount; /* number of authority entries */
	unsigned short nrcount; /* number of additional resource entries */
} __attribute__((packed, aligned(2)));

#define DNS_PACKET_DICT_SIZE 16
struct dns_packet_dict_item {
	unsigned short pos;
	unsigned int hash;
};

struct dns_packet_dict {
	short dict_count;
	struct dns_packet_dict_item names[DNS_PACKET_DICT_SIZE];
};

/* packet head */
struct dns_packet {
	struct dns_head head;
	unsigned short questions;
	unsigned short answers;
	unsigned short nameservers;
	unsigned short additional;
	unsigned short optcount;
	unsigned short optional;
	unsigned short payloadsize;
	struct dns_packet_dict namedict;
	int size;
	int len;
	unsigned char data[0];
};

struct dns_rrs {
	struct dns_packet *packet;
	unsigned short next;
	unsigned short len;
	int type;
	unsigned char data[0];
};

/* packet encode/decode context */
struct dns_context {
	struct dns_packet *packet;
	struct dns_packet_dict *namedict;
	unsigned char *data;
	int maxsize;
	unsigned char *ptr;
};

struct dns_https_param {
	unsigned short key;
	unsigned short len;
	unsigned char value[0];
};


/* ---- tlog: stub out smartdns logging (dns.c references it via the tlog()
 * macro on the `param == NULL` diagnostic path only) ---- */
typedef int tlog_level;
#define TLOG_DEBUG 0
#define TLOG_ERROR 4

static int tlog_ext(tlog_level level, const char *file, int line, const char *func, void *userptr,
					 const char *format, ...)
{
	(void)level; (void)file; (void)line; (void)func; (void)userptr; (void)format;
	return 0;
}

#define tlog(level, format, ...) tlog_ext(level, __FILE__, __LINE__, __func__, NULL, format, ##__VA_ARGS__)

/* ---- safe_strncpy, verbatim from src/include/stringutil.h (real callee of
 * dns_get_HTTPS_svcparm_start) ---- */
static inline char *safe_strncpy(char *dest, const char *src, size_t n)
{
	if (src == NULL) {
		dest[0] = '\0';
		return dest;
	}

	if (n <= 0) {
		return NULL;
	}

#if __GNUC__  > 7
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#endif
	char *ret = strncpy(dest, src, n - 1);
    if (n > 0) {
	    dest[n - 1] = '\0';
    }
#if __GNUC__  > 7
#pragma GCC diagnostic pop
#endif
	return ret;
}

/* ---- VERBATIM real callees from src/dns.c (unmodified; the ones
 * _dns_encode_HTTPS's own real call chain needs to actually run) ---- */


static unsigned short _dns_read_short(unsigned char **buffer)
{
	unsigned short value = 0;

	value = ntohs(*((unsigned short *)(*buffer)));
	*buffer += 2;
	return value;
}

static void _dns_write_short(unsigned char **buffer, unsigned short value)
{
	value = htons(value);
	*((unsigned short *)(*buffer)) = value;
	*buffer += 2;
}

static void _dns_write_int(unsigned char **buffer, unsigned int value)
{
	value = htonl(value);
	*((unsigned int *)(*buffer)) = value;
	*buffer += 4;
}

static unsigned int _dns_read_int(unsigned char **buffer)
{
	unsigned int value = 0;

	value = ntohl(*((unsigned int *)(*buffer)));
	*buffer += 4;

	return value;
}

static inline int _dns_left_len(struct dns_context *context)
{
	return context->maxsize - (context->ptr - context->data);
}

static int _dns_get_domain_from_packet(unsigned char *packet, int packet_size, unsigned char **domain_ptr, char *output,
									   int size)
{
	int output_len = 0;
	int copy_len = 0;
	int len = 0;
	unsigned char *ptr = *domain_ptr;
	int is_compressed = 0;
	int ptr_jump = 0;

	/*[len]string[len]string...[0]0 */
	while (1) {
		if (ptr >= packet + packet_size || ptr < packet || output_len >= size - 1 || ptr_jump > 32) {
			return -1;
		}

		len = *ptr;
		if (len == 0) {
			*output = 0;
			ptr++;
			break;
		}

		/* compressed domain */
		if (len >= 0xC0) {
			if ((ptr + 2) > (packet + packet_size)) {
				return -1;
			}
			/*
			0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
			+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
			| 1  1|                OFFSET                   |
			+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
			*/
			/* read offset */
			len = _dns_read_short(&ptr) & 0x3FFF;
			if (is_compressed == 0) {
				*domain_ptr = ptr;
			}

			ptr = packet + len;
			if (ptr > packet + packet_size) {
				tlog(TLOG_DEBUG, "length is not enough %u:%ld, %p, %p", packet_size, (long)(ptr - packet), *domain_ptr,
					 packet);
				return -1;
			}
			is_compressed = 1;
			ptr_jump++;
			continue;
		}

		ptr_jump = 0;

		/* change [len] to '.' */
		if (output_len > 0) {
			*output = '.';
			output++;
			output_len += 1;
		}

		if (ptr > packet + packet_size) {
			tlog(TLOG_DEBUG, "length is not enough %u:%ld, %p, %p", packet_size, (long)(ptr - packet), *domain_ptr,
				 packet);
			return -1;
		}

		ptr++;
		if (output_len < size - 1) {
			/* copy sub string */
			copy_len = (len < size - output_len) ? len : size - 1 - output_len;
			if ((ptr + copy_len) > (packet + packet_size)) {
				tlog(TLOG_DEBUG, "length is not enough %u:%ld, %p, %p", packet_size, (long)(ptr - packet), *domain_ptr,
					 packet);
				return -1;
			}
			memcpy(output, ptr, copy_len);
		}

		ptr += len;
		output += len;
		output_len += len;
	}

	if (is_compressed == 0) {
		*domain_ptr = ptr;
	}

	return 0;
}

static int _dns_decode_domain(struct dns_context *context, char *output, int size)
{
	return _dns_get_domain_from_packet(context->data, context->maxsize, &(context->ptr), output, size);
}

static unsigned int dict_hash(const char *s)
{
	unsigned int hashval = 0;
	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval;
}

static int _dns_add_domain_dict(struct dns_context *context, unsigned int hash, int pos)
{
	struct dns_packet_dict *dict = context->namedict;

	if (dict->dict_count >= DNS_PACKET_DICT_SIZE) {
		return -1;
	}

	if (hash == 0) {
		return -1;
	}

	if (pos >= context->maxsize) {
		return -1;
	}

	int index = dict->dict_count;
	dict->names[index].hash = hash;
	dict->names[index].pos = pos;
	dict->dict_count++;

	return 0;
}

static int _dns_get_domain_offset(struct dns_context *context, const char *domain)
{
	int i = 0;

	char domain_check[DNS_MAX_CNAME_LEN];
	struct dns_packet_dict *dict = context->namedict;

	if (*domain == '\0') {
		return -1;
	}

	unsigned int hash = dict_hash(domain);
	for (i = 0; i < dict->dict_count; i++) {
		if (dict->names[i].hash != hash) {
			continue;
		}

		unsigned char *domain_check_ptr = dict->names[i].pos + context->data;
		if (_dns_get_domain_from_packet(context->data, context->maxsize, &domain_check_ptr, domain_check,
										DNS_MAX_CNAME_LEN) != 0) {
			return -1;
		}

		return dict->names[i].pos;
	}

	_dns_add_domain_dict(context, hash, context->ptr - 1 - context->data);
	return -1;
}

static int _dns_encode_domain(struct dns_context *context, const char *domain)
{
	int num = 0;
	int total_len = 0;
	unsigned char *ptr_num = context->ptr++;
	int dict_offset = 0;

	dict_offset = _dns_get_domain_offset(context, domain);
	total_len++;

	/*[len]string[len]string...[0]0 */
	while (_dns_left_len(context) > 1 && *domain != 0) {
		total_len++;
		if (dict_offset >= 0) {
			int offset = 0xc000 | dict_offset;
			_dns_write_short(&ptr_num, offset);
			context->ptr++;
			ptr_num = NULL;
			return total_len;
		}

		if (*domain == '.') {
			*ptr_num = num;
			num = 0;
			ptr_num = context->ptr;
			domain++;
			context->ptr++;
			dict_offset = _dns_get_domain_offset(context, domain);
			continue;
		}
		*context->ptr = *domain;
		num++;
		context->ptr++;
		domain++;
	}

	*ptr_num = num;

	if (total_len > 1) {
		/* if domain is '\0', [domain] is '\0' */
		*(context->ptr) = 0;
		total_len++;
		context->ptr++;
	}

	if (_dns_left_len(context) <= 0) {
		return -1;
	}

	return total_len;
}

static void _dns_init_context_by_rrs(struct dns_rrs *rrs, struct dns_context *context)
{
	context->packet = rrs->packet;
	context->data = rrs->packet->data;
	context->ptr = rrs->data;
	context->namedict = &rrs->packet->namedict;
	context->maxsize = rrs->data - rrs->packet->data + rrs->len;
}

static int _dns_get_qr_head(struct dns_context *context, char *domain, int maxsize, int *qtype, int *qclass)
{
	int ret = 0;

	if (domain == NULL || context == NULL) {
		return -1;
	}

	ret = _dns_decode_domain(context, domain, maxsize);
	if (ret < 0) {
		return -1;
	}

	if (_dns_left_len(context) < 4) {
		return -1;
	}

	*qtype = _dns_read_short(&context->ptr);
	*qclass = _dns_read_short(&context->ptr);

	return 0;
}

static int _dns_get_rr_head(struct dns_context *context, char *domain, int maxsize, int *qtype, int *qclass, int *ttl,
							int *rr_len)
{
	int len = 0;

	/* resource record head */
	/* |domain          |
	 * |qtype  | qclass |
	 * |       ttl      |
	 * | rrlen | rrdata |
	 */
	len = _dns_get_qr_head(context, domain, maxsize, qtype, qclass);

	if (_dns_left_len(context) < 6) {
		return -1;
	}

	*ttl = _dns_read_int(&context->ptr);
	*rr_len = _dns_read_short(&context->ptr);

	return len;
}

void *dns_get_rr_nested_start(struct dns_rrs *rrs, char *domain, int maxsize, int *qtype, int *ttl, int *rr_len)
{
	struct dns_context data_context;
	int qclass = 0;
	int ret = 0;

	_dns_init_context_by_rrs(rrs, &data_context);
	ret = _dns_get_rr_head(&data_context, domain, DNS_MAX_CNAME_LEN, qtype, &qclass, ttl, rr_len);
	if (ret < 0) {
		return NULL;
	}

	if (qclass != DNS_C_IN) {
		return NULL;
	}

	if (*rr_len < 2) {
		return NULL;
	}

	return data_context.ptr;
}

void *dns_get_rr_nested_next(struct dns_rrs *rrs, void *rr_nested, int rr_nested_len)
{
	void *end = rrs->data + rrs->len;
	void *p = rr_nested + rr_nested_len;
	if (p == end) {
		return NULL;
	} else if (p > end) {
		return NULL;
	}

	return p;
}

struct dns_https_param *dns_get_HTTPS_svcparm_start(struct dns_rrs *rrs, char *domain, int maxsize, int *ttl,
													int *priority, char *target, int target_size)
{
	int qtype = 0;
	unsigned char *data = NULL;
	int rr_len = 0;

	data = dns_get_rr_nested_start(rrs, domain, maxsize, &qtype, ttl, &rr_len);
	if (data == NULL) {
		return NULL;
	}

	if (qtype != DNS_T_HTTPS) {
		return NULL;
	}

	if (rr_len < 2) {
		return NULL;
	}

	*priority = _dns_read_short(&data);
	rr_len -= 2;
	if (rr_len <= 0) {
		return NULL;
	}

	int len = strnlen((char *)data, rr_len);
	safe_strncpy(target, (char *)data, target_size);
	data += len + 1;
	rr_len -= len + 1;
	if (rr_len <= 0) {
		return NULL;
	}

	return (struct dns_https_param *)data;
}

struct dns_https_param *dns_get_HTTPS_svcparm_next(struct dns_rrs *rrs, struct dns_https_param *param)
{
	return dns_get_rr_nested_next(rrs, param, sizeof(struct dns_https_param) + param->len);
}

static int _dns_encode_qr_head(struct dns_context *context, char *domain, int qtype, int qclass)
{
	int ret = 0;
	ret = _dns_encode_domain(context, domain);
	if (ret < 0) {
		return -1;
	}

	if (_dns_left_len(context) < 4) {
		return -1;
	}

	_dns_write_short(&context->ptr, qtype);
	_dns_write_short(&context->ptr, qclass);

	return 0;
}

static int _dns_encode_rr_head(struct dns_context *context, char *domain, int qtype, int qclass, int ttl, int rr_len,
							   unsigned char **rr_len_ptr)
{
	int ret = 0;
	ret = _dns_encode_qr_head(context, domain, qtype, qclass);
	if (ret < 0) {
		return -1;
	}

	if (_dns_left_len(context) < 6) {
		return -1;
	}

	_dns_write_int(&context->ptr, ttl);
	if (rr_len_ptr) {
		*rr_len_ptr = context->ptr;
	}
	_dns_write_short(&context->ptr, rr_len);

	return 0;
}

static int _dns_encode_HTTPS(struct dns_context *context, struct dns_rrs *rrs)
{
	int ret = 0;
	int qtype = 0;
	int qclass = 0;
	char domain[DNS_MAX_CNAME_LEN];
	char target[DNS_MAX_CNAME_LEN] = {0};
	unsigned char *rr_len_ptr = NULL;
	unsigned char *start = NULL;
	unsigned char *rr_start = NULL;
	int ttl = 0;
	int priority = 0;
	struct dns_https_param *param = NULL;

	param = dns_get_HTTPS_svcparm_start(rrs, domain, DNS_MAX_CNAME_LEN, &ttl, &priority, target, DNS_MAX_CNAME_LEN);
	if (param == NULL) {
		tlog(TLOG_ERROR, "get https param failed.");
		return -1;
	}

	ret = _dns_encode_rr_head(context, domain, qtype, qclass, ttl, 0, &rr_len_ptr);
	if (ret < 0) {
		return -1;
	}

	rr_start = context->ptr;
	if (_dns_left_len(context) < 2) {
		tlog(TLOG_ERROR, "left len is invalid.");
		return -1;
	}

	_dns_write_short(&context->ptr, priority);
	ret = _dns_encode_domain(context, target);
	if (ret < 0) {
		return -1;
	}

	start = context->ptr;
	for (; param != NULL; param = dns_get_HTTPS_svcparm_next(rrs, param)) {
		if (context->ptr - start > rrs->len || _dns_left_len(context) <= 0) {
			return -1;
		}

		_dns_write_short(&context->ptr, param->key);
		_dns_write_short(&context->ptr, param->len);
		switch (param->key) {
		case DNS_HTTPS_T_MANDATORY:
		case DNS_HTTPS_T_NO_DEFAULT_ALPN:
		case DNS_HTTPS_T_ALPN:
		case DNS_HTTPS_T_PORT:
		case DNS_HTTPS_T_IPV4HINT:
		case DNS_HTTPS_T_ECH:
		case DNS_HTTPS_T_IPV6HINT: {
			memcpy(context->ptr, param->value, param->len);
			context->ptr += param->len;
		} break;
		default:
			/* skip unknown key */
			context->ptr -= 4;
			break;
		}
	}

	_dns_write_short(&rr_len_ptr, context->ptr - rr_start);

	return 0;
}


/* ---- direct-call driver ---- */

/* little-endian u16 read from the raw input bytes, zero-padded past `n` */
static unsigned short rd16(const unsigned char *buf, size_t n, size_t off)
{
	unsigned short v = 0;
	if (off < n) {
		v = (unsigned short)buf[off];
	}
	if (off + 1 < n) {
		v = (unsigned short)(v | ((unsigned short)buf[off + 1] << 8));
	}
	return v;
}

#define DC_HDR_LEN 18u          /* bytes _dns_encode_HTTPS's preamble consumes
                                  * before the vulnerable memcpy: 1(owner) +
                                  * 2(qtype) + 2(qclass) + 4(ttl) + 2(rdlen) +
                                  * 2(priority) + 1(target) + 2(key) + 2(len) */
#define DC_VALUE_PAD 70000u      /* SOURCE-side padding: comfortably more than
                                  * the max u16 `len` (65535) so the READ side
                                  * of the memcpy never itself overflows --
                                  * this harness isolates the WRITE-side bug */

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 64;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 64;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 64; }
	long fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 64; }

	/* attacker data MUST live on the heap so ASAN instruments it */
	unsigned char *raw = (unsigned char *)malloc((size_t)(fsz > 0 ? fsz : 1));
	if (!raw) { fclose(f); return 70; }
	size_t n = fsz > 0 ? fread(raw, 1, (size_t)fsz, f) : 0;
	fclose(f);

	unsigned short extra_room = rd16(raw, n, 0);
	unsigned short key = rd16(raw, n, 2);
	unsigned short plen = rd16(raw, n, 4);
	const unsigned char *value_bytes = (n > 6) ? (raw + 6) : NULL;
	size_t n_value_bytes = (n > 6) ? (n - 6) : 0;

	/* ---- SOURCE side: a real struct dns_packet with a real struct dns_rrs
	 * embedded in its data area (exactly how dns_get_rrs_start() would leave
	 * it), carrying one hand-assembled HTTPS answer RR: root owner name,
	 * DNS_T_HTTPS/DNS_C_IN/ttl=0/rdlen=7, priority=0, empty SVCB
	 * TargetName, then the attacker-controlled SvcParam TLV. ---- */
	size_t content_size = (size_t)DC_HDR_LEN + DC_VALUE_PAD;
	size_t packet_alloc_size = sizeof(struct dns_packet) + sizeof(struct dns_rrs) + content_size;
	unsigned char *packet_mem = (unsigned char *)malloc(packet_alloc_size);
	if (!packet_mem) { free(raw); return 70; }
	memset(packet_mem, 0, sizeof(struct dns_packet) + sizeof(struct dns_rrs));

	struct dns_packet *fake_packet = (struct dns_packet *)packet_mem;
	struct dns_rrs *rrs = (struct dns_rrs *)fake_packet->data;
	unsigned char *content = rrs->data;
	size_t content_capacity = (size_t)((packet_mem + packet_alloc_size) - content);
	memset(content, 0x41, content_capacity); /* padding: 'A' fill */

	size_t off = 0;
	content[off++] = 0x00; /* owner name: root */
	{
		unsigned short v = htons(65); /* qtype = DNS_T_HTTPS */
		memcpy(content + off, &v, 2); off += 2;
	}
	{
		unsigned short v = htons(1); /* qclass = DNS_C_IN */
		memcpy(content + off, &v, 2); off += 2;
	}
	{
		unsigned int v = htonl(0); /* ttl */
		memcpy(content + off, &v, 4); off += 4;
	}
	{
		unsigned short v = htons(7); /* rdlen: priority(2)+target(1)+SvcParam hdr(4) */
		memcpy(content + off, &v, 2); off += 2;
	}
	{
		unsigned short v = htons(0); /* priority */
		memcpy(content + off, &v, 2); off += 2;
	}
	content[off++] = 0x00; /* SVCB TargetName: root */

	/* SvcParam TLV: key/len in NATIVE host order -- dns_get_HTTPS_svcparm_start
	 * reads param->key/param->len via a raw struct cast, no ntohs() (see the
	 * file header comment) */
	memcpy(content + off, &key, 2); off += 2;
	memcpy(content + off, &plen, 2); off += 2;
	size_t value_off = off; /* == DC_HDR_LEN */
	if (value_bytes && n_value_bytes > 0) {
		size_t value_room = content_capacity - value_off;
		size_t copy_n = n_value_bytes < value_room ? n_value_bytes : value_room;
		memcpy(content + value_off, value_bytes, copy_n);
	}

	rrs->packet = fake_packet;
	rrs->next = 0xFFFF; /* DNS_RR_END */
	rrs->len = (unsigned short)off; /* == DC_HDR_LEN: span of the header + SvcParam TLV header */
	rrs->type = 1; /* DNS_RRS_AN */

	/* ---- OUTPUT side: the SMALL re-encode buffer. Its size is exactly
	 * DC_HDR_LEN + extra_room, so `extra_room` is exactly the room left for
	 * param->value when the vulnerable memcpy runs: extra_room < plen (with
	 * an allowed SvcParam key) reproduces the heap-buffer-overflow WRITE. ---- */
	size_t out_cap = (size_t)DC_HDR_LEN + extra_room;
	unsigned char *out_buf = (unsigned char *)malloc(out_cap);
	if (!out_buf) { free(packet_mem); free(raw); return 70; }

	struct dns_context context;
	memset(&context, 0, sizeof(context));
	context.packet = NULL;   /* _dns_encode_HTTPS's own call chain never dereferences this */
	context.namedict = NULL; /* only touched for a non-empty domain string; both domains here are root */
	context.data = out_buf;
	context.maxsize = (int)out_cap;
	context.ptr = out_buf;

	int ret = _dns_encode_HTTPS(&context, rrs); /* <-- direct call to the target function */

	/* keep the result observable so the optimizer can't elide the call */
	volatile int sink = ret;
	if (sink == 0) {
		ptrdiff_t written = context.ptr - out_buf;
		for (ptrdiff_t i = 0; i < written && i < (ptrdiff_t)out_cap; i++) {
			putchar(out_buf[i]);
		}
	}

	free(out_buf);
	free(packet_mem);
	free(raw);
	return 0;
}

