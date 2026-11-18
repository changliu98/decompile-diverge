void __cdecl MD5Transform(unsigned int *buf, const unsigned int *in)
{
  unsigned int d; // [rsp+0h] [rbp-20h]
  unsigned int da; // [rsp+0h] [rbp-20h]
  unsigned int db; // [rsp+0h] [rbp-20h]
  unsigned int dc; // [rsp+0h] [rbp-20h]
  unsigned int dd; // [rsp+0h] [rbp-20h]
  unsigned int de; // [rsp+0h] [rbp-20h]
  unsigned int df; // [rsp+0h] [rbp-20h]
  unsigned int dg; // [rsp+0h] [rbp-20h]
  unsigned int dh; // [rsp+0h] [rbp-20h]
  unsigned int di; // [rsp+0h] [rbp-20h]
  unsigned int dj; // [rsp+0h] [rbp-20h]
  unsigned int dk; // [rsp+0h] [rbp-20h]
  unsigned int dl; // [rsp+0h] [rbp-20h]
  unsigned int dm; // [rsp+0h] [rbp-20h]
  unsigned int dn; // [rsp+0h] [rbp-20h]
  unsigned int dp; // [rsp+0h] [rbp-20h]
  unsigned int dq; // [rsp+0h] [rbp-20h]
  unsigned int dr; // [rsp+0h] [rbp-20h]
  unsigned int ds; // [rsp+0h] [rbp-20h]
  unsigned int dt; // [rsp+0h] [rbp-20h]
  unsigned int du; // [rsp+0h] [rbp-20h]
  unsigned int dv; // [rsp+0h] [rbp-20h]
  unsigned int dw; // [rsp+0h] [rbp-20h]
  unsigned int dx; // [rsp+0h] [rbp-20h]
  unsigned int dy; // [rsp+0h] [rbp-20h]
  unsigned int dz; // [rsp+0h] [rbp-20h]
  unsigned int dba; // [rsp+0h] [rbp-20h]
  unsigned int dbb; // [rsp+0h] [rbp-20h]
  unsigned int dbc; // [rsp+0h] [rbp-20h]
  unsigned int dbd; // [rsp+0h] [rbp-20h]
  unsigned int dbe; // [rsp+0h] [rbp-20h]
  unsigned int dbf; // [rsp+0h] [rbp-20h]
  unsigned int dbg; // [rsp+0h] [rbp-20h]
  unsigned int c; // [rsp+4h] [rbp-1Ch]
  unsigned int ca; // [rsp+4h] [rbp-1Ch]
  unsigned int cb; // [rsp+4h] [rbp-1Ch]
  unsigned int cc; // [rsp+4h] [rbp-1Ch]
  unsigned int cd; // [rsp+4h] [rbp-1Ch]
  unsigned int ce; // [rsp+4h] [rbp-1Ch]
  unsigned int cf; // [rsp+4h] [rbp-1Ch]
  unsigned int cg; // [rsp+4h] [rbp-1Ch]
  unsigned int ch; // [rsp+4h] [rbp-1Ch]
  unsigned int ci; // [rsp+4h] [rbp-1Ch]
  unsigned int cj; // [rsp+4h] [rbp-1Ch]
  unsigned int ck; // [rsp+4h] [rbp-1Ch]
  unsigned int cl; // [rsp+4h] [rbp-1Ch]
  unsigned int cm; // [rsp+4h] [rbp-1Ch]
  unsigned int cn; // [rsp+4h] [rbp-1Ch]
  unsigned int co; // [rsp+4h] [rbp-1Ch]
  unsigned int cp; // [rsp+4h] [rbp-1Ch]
  unsigned int cq; // [rsp+4h] [rbp-1Ch]
  unsigned int cr; // [rsp+4h] [rbp-1Ch]
  unsigned int cs; // [rsp+4h] [rbp-1Ch]
  unsigned int ct; // [rsp+4h] [rbp-1Ch]
  unsigned int cu; // [rsp+4h] [rbp-1Ch]
  unsigned int cv; // [rsp+4h] [rbp-1Ch]
  unsigned int cw; // [rsp+4h] [rbp-1Ch]
  unsigned int cx; // [rsp+4h] [rbp-1Ch]
  unsigned int cy; // [rsp+4h] [rbp-1Ch]
  unsigned int cz; // [rsp+4h] [rbp-1Ch]
  unsigned int cba; // [rsp+4h] [rbp-1Ch]
  unsigned int cbb; // [rsp+4h] [rbp-1Ch]
  unsigned int cbc; // [rsp+4h] [rbp-1Ch]
  unsigned int cbd; // [rsp+4h] [rbp-1Ch]
  unsigned int cbe; // [rsp+4h] [rbp-1Ch]
  unsigned int cbf; // [rsp+4h] [rbp-1Ch]
  unsigned int b; // [rsp+8h] [rbp-18h]
  unsigned int ba; // [rsp+8h] [rbp-18h]
  unsigned int bb; // [rsp+8h] [rbp-18h]
  unsigned int bc; // [rsp+8h] [rbp-18h]
  unsigned int bd; // [rsp+8h] [rbp-18h]
  unsigned int be; // [rsp+8h] [rbp-18h]
  unsigned int bf; // [rsp+8h] [rbp-18h]
  unsigned int bg; // [rsp+8h] [rbp-18h]
  unsigned int bh; // [rsp+8h] [rbp-18h]
  unsigned int bi; // [rsp+8h] [rbp-18h]
  unsigned int bj; // [rsp+8h] [rbp-18h]
  unsigned int bk; // [rsp+8h] [rbp-18h]
  unsigned int bl; // [rsp+8h] [rbp-18h]
  unsigned int bm; // [rsp+8h] [rbp-18h]
  unsigned int bn; // [rsp+8h] [rbp-18h]
  unsigned int bo; // [rsp+8h] [rbp-18h]
  unsigned int bp; // [rsp+8h] [rbp-18h]
  unsigned int bq; // [rsp+8h] [rbp-18h]
  unsigned int br; // [rsp+8h] [rbp-18h]
  unsigned int bs; // [rsp+8h] [rbp-18h]
  unsigned int bt; // [rsp+8h] [rbp-18h]
  unsigned int bu; // [rsp+8h] [rbp-18h]
  unsigned int bv; // [rsp+8h] [rbp-18h]
  unsigned int bw; // [rsp+8h] [rbp-18h]
  unsigned int bx; // [rsp+8h] [rbp-18h]
  unsigned int by; // [rsp+8h] [rbp-18h]
  unsigned int bz; // [rsp+8h] [rbp-18h]
  unsigned int bba; // [rsp+8h] [rbp-18h]
  unsigned int bbb; // [rsp+8h] [rbp-18h]
  unsigned int bbc; // [rsp+8h] [rbp-18h]
  unsigned int bbd; // [rsp+8h] [rbp-18h]
  unsigned int bbe; // [rsp+8h] [rbp-18h]
  unsigned int a; // [rsp+Ch] [rbp-14h]
  unsigned int aa; // [rsp+Ch] [rbp-14h]
  unsigned int ab; // [rsp+Ch] [rbp-14h]
  unsigned int ac; // [rsp+Ch] [rbp-14h]
  unsigned int ad; // [rsp+Ch] [rbp-14h]
  unsigned int ae; // [rsp+Ch] [rbp-14h]
  unsigned int af; // [rsp+Ch] [rbp-14h]
  unsigned int ag; // [rsp+Ch] [rbp-14h]
  unsigned int ah; // [rsp+Ch] [rbp-14h]
  unsigned int ai; // [rsp+Ch] [rbp-14h]
  unsigned int aj; // [rsp+Ch] [rbp-14h]
  unsigned int ak; // [rsp+Ch] [rbp-14h]
  unsigned int al; // [rsp+Ch] [rbp-14h]
  unsigned int am; // [rsp+Ch] [rbp-14h]
  unsigned int an; // [rsp+Ch] [rbp-14h]
  unsigned int ao; // [rsp+Ch] [rbp-14h]
  unsigned int ap; // [rsp+Ch] [rbp-14h]
  unsigned int aq; // [rsp+Ch] [rbp-14h]
  unsigned int ar; // [rsp+Ch] [rbp-14h]
  unsigned int as; // [rsp+Ch] [rbp-14h]
  unsigned int at; // [rsp+Ch] [rbp-14h]
  unsigned int au; // [rsp+Ch] [rbp-14h]
  unsigned int av; // [rsp+Ch] [rbp-14h]
  unsigned int aw; // [rsp+Ch] [rbp-14h]
  unsigned int ax; // [rsp+Ch] [rbp-14h]
  unsigned int ay; // [rsp+Ch] [rbp-14h]
  unsigned int az; // [rsp+Ch] [rbp-14h]
  unsigned int aba; // [rsp+Ch] [rbp-14h]
  unsigned int abb; // [rsp+Ch] [rbp-14h]
  unsigned int abc; // [rsp+Ch] [rbp-14h]
  unsigned int abd; // [rsp+Ch] [rbp-14h]
  unsigned int abe; // [rsp+Ch] [rbp-14h]

  b = buf[1];
  c = buf[2];
  d = buf[3];
  a = *buf + *in + ((d ^ c) & b ^ d) - 680876936;
  aa = b + ((a >> 25) | (a << 7));
  da = d + in[1] + ((c ^ b) & aa ^ c) - 389564586;
  db = aa + ((da >> 20) | (da << 12));
  ca = c + in[2] + ((b ^ aa) & db ^ b) + 606105819;
  cb = db + ((ca >> 15) | (ca << 17));
  ba = b + in[3] + ((aa ^ db) & cb ^ aa) - 1044525330;
  bb = cb + ((ba >> 10) | (ba << 22));
  ab = aa + in[4] + ((db ^ cb) & bb ^ db) - 176418897;
  ac = bb + ((ab >> 25) | (ab << 7));
  dc = db + in[5] + ((cb ^ bb) & ac ^ cb) + 1200080426;
  dd = ac + ((dc >> 20) | (dc << 12));
  cc = cb + in[6] + ((bb ^ ac) & dd ^ bb) - 1473231341;
  cd = dd + ((cc >> 15) | (cc << 17));
  bc = bb + in[7] + ((ac ^ dd) & cd ^ ac) - 45705983;
  bd = cd + ((bc >> 10) | (bc << 22));
  ad = ac + in[8] + ((dd ^ cd) & bd ^ dd) + 1770035416;
  ae = bd + ((ad >> 25) | (ad << 7));
  de = dd + in[9] + ((cd ^ bd) & ae ^ cd) - 1958414417;
  df = ae + ((de >> 20) | (de << 12));
  ce = cd + in[10] + ((bd ^ ae) & df ^ bd) - 42063;
  cf = df + ((ce >> 15) | (ce << 17));
  be = bd + in[11] + ((ae ^ df) & cf ^ ae) - 1990404162;
  bf = cf + ((be >> 10) | (be << 22));
  af = ae + in[12] + ((df ^ cf) & bf ^ df) + 1804603682;
  ag = bf + ((af >> 25) | (af << 7));
  dg = df + in[13] + ((cf ^ bf) & ag ^ cf) - 40341101;
  dh = ag + ((dg >> 20) | (dg << 12));
  cg = cf + in[14] + ((bf ^ ag) & dh ^ bf) - 1502002290;
  ch = dh + ((cg >> 15) | (cg << 17));
  bg = bf + in[15] + ((ag ^ dh) & ch ^ ag) + 1236535329;
  bh = ch + ((bg >> 10) | (bg << 22));
  ah = ag + in[1] + ((ch ^ bh) & dh ^ ch) - 165796510;
  ai = bh + ((ah >> 27) | (32 * ah));
  di = dh + in[6] + ((bh ^ ai) & ch ^ bh) - 1069501632;
  dj = ai + ((di >> 23) | (di << 9));
  ci = ch + in[11] + ((ai ^ dj) & bh ^ ai) + 643717713;
  cj = dj + ((ci >> 18) | (ci << 14));
  bi = bh + *in + ((dj ^ cj) & ai ^ dj) - 373897302;
  bj = cj + ((bi >> 12) | (bi << 20));
  aj = ai + in[5] + ((cj ^ bj) & dj ^ cj) - 701558691;
  ak = bj + ((aj >> 27) | (32 * aj));
  dk = dj + in[10] + ((bj ^ ak) & cj ^ bj) + 38016083;
  dl = ak + ((dk >> 23) | (dk << 9));
  ck = cj + in[15] + ((ak ^ dl) & bj ^ ak) - 660478335;
  cl = dl + ((ck >> 18) | (ck << 14));
  bk = bj + in[4] + ((dl ^ cl) & ak ^ dl) - 405537848;
  bl = cl + ((bk >> 12) | (bk << 20));
  al = ak + in[9] + ((cl ^ bl) & dl ^ cl) + 568446438;
  am = bl + ((al >> 27) | (32 * al));
  dm = dl + in[14] + ((bl ^ am) & cl ^ bl) - 1019803690;
  dn = am + ((dm >> 23) | (dm << 9));
  cm = cl + in[3] + ((am ^ dn) & bl ^ am) - 187363961;
  cn = dn + ((cm >> 18) | (cm << 14));
  bm = bl + in[8] + ((dn ^ cn) & am ^ dn) + 1163531501;
  bn = cn + ((bm >> 12) | (bm << 20));
  an = am + in[13] + ((cn ^ bn) & dn ^ cn) - 1444681467;
  ao = bn + ((an >> 27) | (32 * an));
  dp = dn + in[2] + ((bn ^ ao) & cn ^ bn) - 51403784;
  dq = ao + ((dp >> 23) | (dp << 9));
  co = cn + in[7] + ((ao ^ dq) & bn ^ ao) + 1735328473;
  cp = dq + ((co >> 18) | (co << 14));
  bo = bn + in[12] + ((dq ^ cp) & ao ^ dq) - 1926607734;
  bp = cp + ((bo >> 12) | (bo << 20));
  ap = ao + in[5] + (dq ^ cp ^ bp) - 378558;
  aq = bp + ((ap >> 28) | (16 * ap));
  dr = dq + in[8] + (cp ^ bp ^ aq) - 2022574463;
  ds = aq + ((dr >> 21) | (dr << 11));
  cq = cp + in[11] + (bp ^ aq ^ ds) + 1839030562;
  cr = ds + (HIWORD(cq) | (cq << 16));
  bq = bp + in[14] + (aq ^ ds ^ cr) - 35309556;
  br = cr + ((bq >> 9) | (bq << 23));
  ar = aq + in[1] + (ds ^ cr ^ br) - 1530992060;
  as = br + ((ar >> 28) | (16 * ar));
  dt = ds + in[4] + (cr ^ br ^ as) + 1272893353;
  du = as + ((dt >> 21) | (dt << 11));
  cs = cr + in[7] + (br ^ as ^ du) - 155497632;
  ct = du + (HIWORD(cs) | (cs << 16));
  bs = br + in[10] + (as ^ du ^ ct) - 1094730640;
  bt = ct + ((bs >> 9) | (bs << 23));
  at = as + in[13] + (du ^ ct ^ bt) + 681279174;
  au = bt + ((at >> 28) | (16 * at));
  dv = du + *in + (ct ^ bt ^ au) - 358537222;
  dw = au + ((dv >> 21) | (dv << 11));
  cu = ct + in[3] + (bt ^ au ^ dw) - 722521979;
  cv = dw + (HIWORD(cu) | (cu << 16));
  bu = bt + in[6] + (au ^ dw ^ cv) + 76029189;
  bv = cv + ((bu >> 9) | (bu << 23));
  av = au + in[9] + (dw ^ cv ^ bv) - 640364487;
  aw = bv + ((av >> 28) | (16 * av));
  dx = dw + in[12] + (cv ^ bv ^ aw) - 421815835;
  dy = aw + ((dx >> 21) | (dx << 11));
  cw = cv + in[15] + (bv ^ aw ^ dy) + 530742520;
  cx = dy + (HIWORD(cw) | (cw << 16));
  bw = bv + in[2] + (aw ^ dy ^ cx) - 995338651;
  bx = cx + ((bw >> 9) | (bw << 23));
  ax = aw + *in + ((~dy | bx) ^ cx) - 198630844;
  ay = bx + ((ax >> 26) | (ax << 6));
  dz = dy + in[7] + ((~cx | ay) ^ bx) + 1126891415;
  dba = ay + ((dz >> 22) | (dz << 10));
  cy = cx + in[14] + ((~bx | dba) ^ ay) - 1416354905;
  cz = dba + ((cy >> 17) | (cy << 15));
  by = bx + in[5] + ((~ay | cz) ^ dba) - 57434055;
  bz = cz + ((by >> 11) | (by << 21));
  az = ay + in[12] + ((~dba | bz) ^ cz) + 1700485571;
  aba = bz + ((az >> 26) | (az << 6));
  dbb = dba + in[3] + ((~cz | aba) ^ bz) - 1894986606;
  dbc = aba + ((dbb >> 22) | (dbb << 10));
  cba = cz + in[10] + ((~bz | dbc) ^ aba) - 1051523;
  cbb = dbc + ((cba >> 17) | (cba << 15));
  bba = bz + in[1] + ((~aba | cbb) ^ dbc) - 2054922799;
  bbb = cbb + ((bba >> 11) | (bba << 21));
  abb = aba + in[8] + ((~dbc | bbb) ^ cbb) + 1873313359;
  abc = bbb + ((abb >> 26) | (abb << 6));
  dbd = dbc + in[15] + ((~cbb | abc) ^ bbb) - 30611744;
  dbe = abc + ((dbd >> 22) | (dbd << 10));
  cbc = cbb + in[6] + ((~bbb | dbe) ^ abc) - 1560198380;
  cbd = dbe + ((cbc >> 17) | (cbc << 15));
  bbc = bbb + in[13] + ((~abc | cbd) ^ dbe) + 1309151649;
  bbd = cbd + ((bbc >> 11) | (bbc << 21));
  abd = abc + in[4] + ((~dbe | bbd) ^ cbd) - 145523070;
  abe = bbd + ((abd >> 26) | (abd << 6));
  dbf = dbe + in[11] + ((~cbd | abe) ^ bbd) - 1120210379;
  dbg = abe + ((dbf >> 22) | (dbf << 10));
  cbe = cbd + in[2] + ((~bbd | dbg) ^ abe) + 718787259;
  cbf = dbg + ((cbe >> 17) | (cbe << 15));
  bbe = bbd + in[9] + ((~abe | cbf) ^ dbg) - 343485551;
  *buf += abe;
  buf[1] += cbf + ((bbe >> 11) | (bbe << 21));
  buf[2] += cbf;
  buf[3] += dbg;
}