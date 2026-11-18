/* cve_barebone isolation harness for CVE-2023-50246 (jq)
 * Target: jvp_literal_number_literal (src/jv.c) -> heap-buffer-overflow WRITE (CWE-787)
 * The crash is the terminating NUL written 1 byte past jv_mem_alloc(digits+14)
 * inside decToString, reached via decNumberToString from the target function.
 * Real decToString / decNumberToString / jvp_*_ptr are pasted VERBATIM from
 * jq's src (the crash path); the target function is byte-for-byte from
 * target/original_function.c.  main() builds the decNumber literal directly. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

/* ---- decNumber local types / macros (verbatim from decNumberLocal.h) ---- */
#define Flag   uint8_t
#define Int    int32_t
#define uInt   uint32_t
#define uByte  uint8_t
#define DECDPUN 3                 /* DECimal Digits Per UNit */
#define decNumberUnit uint16_t    /* DECDPUN<=4 -> uint16_t */
#define Unit   decNumberUnit
#define DECNUMDIGITS 1
#define DECNUMUNITS ((DECNUMDIGITS+DECDPUN-1)/DECDPUN)

/* ---- decNumber.bits (verbatim from decNumber.h) ---- */
#define DECNEG    0x80
#define DECINF    0x40
#define DECNAN    0x20
#define DECSNAN   0x10
#define DECSPECIAL (DECINF|DECNAN|DECSNAN)

/* ---- decNumber data structure (verbatim from decNumber.h) ---- */
typedef struct {
  int32_t digits;
  int32_t exponent;
  uint8_t bits;
  decNumberUnit lsu[DECNUMUNITS];
} decNumber;

/* ---- decNumber test macros (verbatim from decNumber.h) ---- */
#define decNumberIsInfinite(dn)  (((dn)->bits&DECINF)!=0)
#define decNumberIsNaN(dn)       (((dn)->bits&(DECNAN|DECSNAN))!=0)
#define decNumberIsNegative(dn)  (((dn)->bits&DECNEG)!=0)
#define decNumberIsZero(dn)      (*(dn)->lsu==0 \
                                  && (dn)->digits==1 \
                                  && (((dn)->bits&DECSPECIAL)==0))

/* ---- shared data + D2U/MSUDIGITS/TODIGIT (verbatim from decContext.c /
 * decNumberLocal.h; DECDPUN==3 D2UTABLE) ---- */
const uInt DECPOWERS[10]={1, 10, 100, 1000, 10000, 100000, 1000000,
                          10000000, 100000000, 1000000000};
#define DECMAXD2U 49
const uByte d2utable[DECMAXD2U+1]={0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,
                      8,8,8,9,9,9,10,10,10,11,11,11,12,12,12,13,13,
                      13,14,14,14,15,15,15,16,16,16,17};
#define ISZERO(dn) decNumberIsZero(dn)
#define D2U(d) ((d)<=DECMAXD2U?d2utable[d]:((d)+DECDPUN-1)/DECDPUN)
#define MSUDIGITS(d) ((d)-(D2U(d)-1)*DECDPUN)
#define TODIGIT(u, cut, c, pow) {       \
    *(c)='0';                             \
    pow=DECPOWERS[cut]*2;                 \
    if ((u)>pow) {                        \
      pow*=4;                             \
      if ((u)>=pow) {(u)-=pow; *(c)+=8;}  \
      pow/=2;                             \
      if ((u)>=pow) {(u)-=pow; *(c)+=4;}  \
      pow/=2;                             \
      }                                   \
    if ((u)>=pow) {(u)-=pow; *(c)+=2;}    \
    pow/=2;                               \
    if ((u)>=pow) {(u)-=pow; *(c)+=1;}    \
    }

/* ---- jv value + number-literal internals (verbatim from jv.h / jv.c) ---- */
typedef enum {
  JV_KIND_INVALID,
  JV_KIND_NULL,
  JV_KIND_FALSE,
  JV_KIND_TRUE,
  JV_KIND_NUMBER,
  JV_KIND_STRING,
  JV_KIND_ARRAY,
  JV_KIND_OBJECT
} jv_kind;

typedef struct jv_refcnt {
  int count;
} jv_refcnt;

typedef struct {
  unsigned char kind_flags;
  unsigned char pad_;
  unsigned short offset;
  int size;
  union {
    struct jv_refcnt* ptr;
    double number;
  } u;
} jv;

#define KIND_MASK   0xF
#define PFLAGS_MASK 0xF0
#define PTYPE_MASK  0x70
enum { JVP_PAYLOAD_ALLOCATED = 0x80 };
#define JVP_MAKE_PFLAGS(ptype, allocated) ((((ptype) << 4) & PTYPE_MASK) | ((allocated) ? JVP_PAYLOAD_ALLOCATED : 0))
#define JVP_MAKE_FLAGS(kind, pflags) ((kind & KIND_MASK) | (pflags & PFLAGS_MASK))
#define JVP_FLAGS(j)  ((j).kind_flags)
#define JVP_HAS_FLAGS(j, flags) (JVP_FLAGS(j) == flags)
enum {
  JVP_NUMBER_NATIVE = 0,
  JVP_NUMBER_DECIMAL = 1
};
#define JVP_FLAGS_NUMBER_LITERAL  JVP_MAKE_FLAGS(JV_KIND_NUMBER, JVP_MAKE_PFLAGS(JVP_NUMBER_DECIMAL, 1))

typedef struct {
  jv_refcnt refcnt;
  double num_double;
  char * literal_data;
  decNumber num_decimal; // must be the last field in the structure for memory management
} jvp_literal_number;

/* jv_mem_alloc: faithful minimal stub (real one aborts on OOM) */
static void* jv_mem_alloc(size_t sz) {
  void* p = malloc(sz);
  if (!p) abort();
  return p;
}

/* ---- jvp_literal_number_ptr / jvp_dec_number_ptr (verbatim jv.c) ---- */
static jvp_literal_number* jvp_literal_number_ptr(jv j) {
  assert(JVP_HAS_FLAGS(j, JVP_FLAGS_NUMBER_LITERAL));
  return (jvp_literal_number*)j.u.ptr;
}

static decNumber* jvp_dec_number_ptr(jv j) {
  assert(JVP_HAS_FLAGS(j, JVP_FLAGS_NUMBER_LITERAL));
  return &(((jvp_literal_number*)j.u.ptr)->num_decimal);
}

/* forward declaration for the target */
static const char* jvp_literal_number_literal(jv n);

/* ---- decToString / decNumberToString (verbatim decNumber.c, crash path) ---- */
static void decToString(const decNumber *dn, char *string, Flag eng) {
  Int exp=dn->exponent;       // local copy
  Int e;                      // E-part value
  Int pre;                    // digits before the '.'
  Int cut;                    // for counting digits in a Unit
  char *c=string;             // work [output pointer]
  const Unit *up=dn->lsu+D2U(dn->digits)-1; // -> msu [input pointer]
  uInt u, pow;                // work

  #if DECCHECK
  if (decCheckOperands(DECUNRESU, dn, DECUNUSED, DECUNCONT)) {
    strcpy(string, "?");
    return;}
  #endif

  if (decNumberIsNegative(dn)) {   // Negatives get a minus
    *c='-';
    c++;
    }
  if (dn->bits&DECSPECIAL) {       // Is a special value
    if (decNumberIsInfinite(dn)) {
      strcpy(c,   "Inf");
      strcpy(c+3, "inity");
      return;}
    // a NaN
    if (dn->bits&DECSNAN) {        // signalling NaN
      *c='s';
      c++;
      }
    strcpy(c, "NaN");
    c+=3;                          // step past
    // if not a clean non-zero coefficient, that's all there is in a
    // NaN string
    if (exp!=0 || (*dn->lsu==0 && dn->digits==1)) return;
    // [drop through to add integer]
    }

  // calculate how many digits in msu, and hence first cut
  cut=MSUDIGITS(dn->digits);       // [faster than remainder]
  cut--;                           // power of ten for digit

  if (exp==0) {                    // simple integer [common fastpath]
    for (;up>=dn->lsu; up--) {     // each Unit from msu
      u=*up;                       // contains DECDPUN digits to lay out
      for (; cut>=0; c++, cut--) TODIGIT(u, cut, c, pow);
      cut=DECDPUN-1;               // next Unit has all digits
      }
    *c='\0';                       // terminate the string
    return;}

  /* non-0 exponent -- assume plain form */
  pre=dn->digits+exp;              // digits before '.'
  e=0;                             // no E
  if ((exp>0) || (pre<-5)) {       // need exponential form
    e=exp+dn->digits-1;            // calculate E value
    pre=1;                         // assume one digit before '.'
    if (eng && (e!=0)) {           // engineering: may need to adjust
      Int adj;                     // adjustment
      // The C remainder operator is undefined for negative numbers, so
      // a positive remainder calculation must be used here
      if (e<0) {
        adj=(-e)%3;
        if (adj!=0) adj=3-adj;
        }
       else { // e>0
        adj=e%3;
        }
      e=e-adj;
      // if dealing with zero still produce an exponent which is a
      // multiple of three, as expected, but there will only be the
      // one zero before the E, still.  Otherwise note the padding.
      if (!ISZERO(dn)) pre+=adj;
       else {  // is zero
        if (adj!=0) {              // 0.00Esnn needed
          e=e+3;
          pre=-(2-adj);
          }
        } // zero
      } // eng
    } // need exponent

  /* lay out the digits of the coefficient, adding 0s and . as needed */
  u=*up;
  if (pre>0) {                     // xxx.xxx or xx00 (engineering) form
    Int n=pre;
    for (; pre>0; pre--, c++, cut--) {
      if (cut<0) {                 // need new Unit
        if (up==dn->lsu) break;    // out of input digits (pre>digits)
        up--;
        cut=DECDPUN-1;
        u=*up;
        }
      TODIGIT(u, cut, c, pow);
      }
    if (n<dn->digits) {            // more to come, after '.'
      *c='.'; c++;
      for (;; c++, cut--) {
        if (cut<0) {               // need new Unit
          if (up==dn->lsu) break;  // out of input digits
          up--;
          cut=DECDPUN-1;
          u=*up;
          }
        TODIGIT(u, cut, c, pow);
        }
      }
     else for (; pre>0; pre--, c++) *c='0'; // 0 padding (for engineering) needed
    }
   else {                          // 0.xxx or 0.000xxx form
    *c='0'; c++;
    *c='.'; c++;
    for (; pre<0; pre++, c++) *c='0';   // add any 0's after '.'
    for (; ; c++, cut--) {
      if (cut<0) {                 // need new Unit
        if (up==dn->lsu) break;    // out of input digits
        up--;
        cut=DECDPUN-1;
        u=*up;
        }
      TODIGIT(u, cut, c, pow);
      }
    }

  /* Finally add the E-part, if needed.  It will never be 0, has a
     base maximum and minimum of +999999999 through -999999999, but
     could range down to -1999999998 for anormal numbers */
  if (e!=0) {
    Flag had=0;               // 1=had non-zero
    *c='E'; c++;
    *c='+'; c++;              // assume positive
    u=e;                      // ..
    if (e<0) {
      *(c-1)='-';             // oops, need -
      u=-e;                   // uInt, please
      }
    // lay out the exponent [_itoa or equivalent is not ANSI C]
    for (cut=9; cut>=0; cut--) {
      TODIGIT(u, cut, c, pow);
      if (*c=='0' && !had) continue;    // skip leading zeros
      had=1;                            // had non-0
      c++;                              // step for next
      } // cut
    }
  *c='\0';          // terminate the string (all paths)
  return;
  } // decToString

char * decNumberToString(const decNumber *dn, char *string){
  decToString(dn, string, 0);
  return string;
  } // DecNumberToString

/* ==== TARGET: jvp_literal_number_literal (verbatim target/original_function.c) ==== */
static const char* jvp_literal_number_literal(jv n) {
  assert(JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL));
  decNumber *pdec = jvp_dec_number_ptr(n);
  jvp_literal_number* plit = jvp_literal_number_ptr(n);

  if (decNumberIsNaN(pdec)) {
    return "null";
  }

  if (decNumberIsInfinite(pdec)) {
    // We cannot preserve the literal data of numbers outside the limited
    // range of exponent. Since `decNumberToString` returns "Infinity"
    // (or "-Infinity"), and to reduce stack allocations as possible, we
    // normalize infinities in the callers instead of printing the maximum
    // (or minimum) double here.
    return NULL;
  }

  if (plit->literal_data == NULL) {
    int len = jvp_dec_number_ptr(n)->digits + 14;
    plit->literal_data = jv_mem_alloc(len);

    // Preserve the actual precision as we have parsed it
    // don't do decNumberTrim(pdec);

    decNumberToString(pdec, plit->literal_data);
  }

  return plit->literal_data;
}

/* ---- direct-call driver ---- */
/* Parse argv[1] (a decimal number string) into a decNumber literal exactly as
 * jq would represent it (coefficient significant digits + base-10 exponent),
 * then call jvp_literal_number_literal on it.  Triggering inputs (negative
 * number, a decimal point, and a 10-digit exponent magnitude) drive
 * decNumberToString/decToString to write the terminating NUL one byte past the
 * digits+14 heap buffer -> heap-buffer-overflow WRITE. */
int main(int argc, char** argv) {
  if (argc < 2) return 0;
  FILE* f = fopen(argv[1], "rb");
  if (!f) return 0;
  fseek(f, 0, SEEK_END);
  long fsz = ftell(f);
  fseek(f, 0, SEEK_SET);
  if (fsz < 0) fsz = 0;
  /* HEAP-allocate the raw input so ASAN guards it */
  char* raw = (char*)malloc((size_t)fsz + 1);
  size_t got = fread(raw, 1, (size_t)fsz, f);
  fclose(f);
  raw[got] = '\0';
  while (got > 0 && (raw[got-1]=='\n' || raw[got-1]=='\r' ||
                     raw[got-1]==' '  || raw[got-1]=='\t')) raw[--got] = '\0';

  size_t i = 0;
  int neg = 0;
  if (i < got && (raw[i]=='-' || raw[i]=='+')) { if (raw[i]=='-') neg = 1; i++; }

  char* coef = (char*)malloc(got + 2);
  int clen = 0, frac = 0, seen_dot = 0;
  for (; i < got; i++) {
    char ch = raw[i];
    if (ch >= '0' && ch <= '9') {
      if (clen < 60) { coef[clen++] = ch; if (seen_dot) frac++; }
    } else if (ch == '.' && !seen_dot) {
      seen_dot = 1;
    } else {
      break;
    }
  }
  long pexp = 0; int eneg = 0;
  if (i < got && (raw[i]=='e' || raw[i]=='E')) {
    i++;
    if (i < got && (raw[i]=='-' || raw[i]=='+')) { if (raw[i]=='-') eneg = 1; i++; }
    for (; i < got && raw[i] >= '0' && raw[i] <= '9'; i++) {
      pexp = pexp * 10 + (raw[i] - '0');
      if (pexp > 2000000000L) pexp = 2000000000L;
    }
    if (eneg) pexp = -pexp;
  }
  coef[clen] = '\0';

  /* strip leading zeros of the coefficient (keep >=1 significant digit) */
  int start = 0;
  while (start < clen - 1 && coef[start] == '0') start++;
  char* sig = coef + start;
  int digits = clen - start;
  if (digits < 1) { sig = (char*)"0"; digits = 1; }

  long expo = pexp - (long)frac;
  if (expo >  999999999L)  expo =  999999999L;
  if (expo < -1999999997L) expo = -1999999997L;

  int nunits = (digits + DECDPUN - 1) / DECDPUN;
  jvp_literal_number* plit = (jvp_literal_number*)jv_mem_alloc(
      sizeof(jvp_literal_number) + sizeof(Unit) * (size_t)(nunits + 1));
  plit->refcnt.count = 1;
  plit->num_double = 0.0;
  plit->literal_data = NULL;
  decNumber* dn = &plit->num_decimal;
  dn->digits = digits;
  dn->exponent = (int32_t)expo;
  dn->bits = neg ? DECNEG : 0;
  for (int u = 0; u < nunits + 1; u++) dn->lsu[u] = 0;
  for (int k = 0; k < digits; k++) {
    int dv = sig[digits - 1 - k] - '0';
    int unit = k / DECDPUN;
    int pos  = k % DECDPUN;
    unsigned mult = 1;
    for (int m = 0; m < pos; m++) mult *= 10;
    dn->lsu[unit] = (Unit)(dn->lsu[unit] + dv * mult);
  }

  jv n;
  n.kind_flags = JVP_FLAGS_NUMBER_LITERAL;
  n.pad_ = 0;
  n.offset = 0;
  n.size = 0;
  n.u.ptr = (struct jv_refcnt*)plit;

  /* indirect call keeps jvp_literal_number_literal a real (un-inlined) frame */
  const char* (*volatile fn)(jv) = jvp_literal_number_literal;
  const char* r = fn(n);
  if (r) { volatile size_t L = strlen(r); (void)L; }
  return 0;
}
