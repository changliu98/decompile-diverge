int pgetarg(char *pattern, int ppos, int *len, int *from, int *to, int *reverse)
{
  int type;
  int c;
  int i;
  int j;
  int k;
  int l;
  int m;
  int n;
  int o;
  int p;
  int q;
  int r;
  int s;
  int t;
  int u;
  int v;
  int w;
  int x;
  int y;
  int z;
  int aa;
  int ab;
  int ac;
  int ad;
  int ae;
  int af;
  int ag;
  int ah;
  int ai;
  int aj;
  int ak;
  int al;
  int am;
  int an;
  int ao;
  int ap;
  int aq;
  int ar;
  int as;
  int at;
  int au;
  int av;
  int aw;
  int ax;
  int ay;
  int az;
  int ba;
  int bb;
  int bc;
  int bd;
  int be;
  int bf;
  int bg;
  int bh;
  int bi;
  int bj;
  int bk;
  int bl;
  int bm;
  int bn;
  int bo;
  int bp;
  int bq;
  int br;
  int bs;
  int bt;
  int bu;
  int bv;
  int bw;
  int bx;
  int by;
  int bz;
  int ca;
  int cb;
  int cc;
  int cd;
  int ce;
  int cf;
  int cg;
  int ch;
  int ci;
  int cj;
  int ck;
  int cl;
  int cm;
  int cn;
  int co;
  int cp;
  int cq;
  int cr;
  int cs;
  int ct;
  int cu;
  int cv;
  int cw;
  int cx;
  int cy;
  int cz;
  int da;
  int db;
  int dc;
  int dd;
  int de;
  int df;
  int dg;
  int dh;
  int di;
  int dj;
  int dk;
  int dl;
  int dm;
  int dn;
  int do_;
  int dp;
  int dq;
  int dr;
  int ds;
  int dt;
  int du;
  int dv;
  int dw;
  int dx;
  int dy;
  int dz;
  int ea;
  int eb;
  int ec;
  int ed;
  int ee;
  int ef;
  int eg;
  int eh;
  int ei;
  int ej;
  int ek;
  int el;
  int em;
  int en;
  int eo;
  int ep;
  int eq;
  int er;
  int es;
  int et;
  int eu;
  int ev;
  int ew;
  int ex;
  int ey;
  int ez;
  int fa;
  int fb;
  int fc;
  int fd;
  int fe;
  int ff;
  int fg;
  int fh;
  int fi;
  int fj;
  int fk;
  int fl;
  int fm;
  int fn;
  int fo;
  int fp;
  int fq;
  int fr;
  int fs;
  int ft;
  int fu;
  int fv;
  int fw;
  int fx;
  int fy;
  int fz;
  int ga;
  int gb;
  int gc;
  int gd;
  int ge;
  int gf;
  int gg;
  int gh;
  int gi;
  int gj;
  int gk;
  int gl;
  int gm;
  int gn;
  int go;
  int gp;
  int gq;
  int gr;
  int gs;
  int gt;
  int gu;
  int gv;
  int gw;
  int gx;
  int gy;
  int gz;
  int ha;
  int hb;
  int hc;
  int hd;
  int he;
  int hf;
  int hg;
  int hh;
  int hi;
  int hj;
  int hk;
  int hl;
  int hm;
  int hn;
  int ho;
  int hp;
  int hq;
  int hr;
  int hs;
  int ht;
  int hu;
  int hv;
  int hw;
  int hx;
  int hy;
  int hz;
  int ia;
  int ib;
  int ic;
  int id;
  int ie;
  int if_;
  int ig;
  int ih;
  int ii;
  int ij;
  int ik;
  int il;
  int im;
  int in_;
  int io;
  int ip;
  int iq;
  int ir;
  int is_;
  int it;
  int iu;
  int iv;
  int iw;
  int ix;
  int iy;
  int iz;
  int ja;
  int jb;
  int jc;
  int jd;
  int je;
  int jf;
  int jg;
  int jh;
  int ji;
  int jj;
  int jk;
  int jl;
  int jm;
  int jn;
  int jo;
  int jp;
  int jq;
  int jr;
  int js;
  int jt;
  int ju;
  int jv;
  int jw;
  ka = kb = kc = kd = ke = kf = kg = kh = ki = kj = kk = kl = km = kn = ko = kp =
  kq = kr = ks = kt = ku = kv = kw = kx = ky = kz =
  la = lb = lc = ld = le = lf = lg = lh = li = lj = lk =
  ll = lm = ln = lo = lp = lq = lr = ls = lt = lu = lv =
  lw = lx = ly = lz =
  ma = mb = mc = md = me = mf = mg = mh = mi = mj = mk =
  ml = mm = mn = mo = mp = mq = mr = ms = mt = mu = mv =
  mw = mx = my = mz =
  na = nb = nc = nd = ne = nf = ng = nh = ni = nj = nk =
  nl = nm = nn = no = np = nq = nr = ns = nt = nu = nv =
  nw = nx = ny = nz =
  oa = ob = oc = od = oe = of = og = oh = oi = oj = ok =
  ol = om = on = oo = op = oq = or = os = ot = ou = ov =
  ow = ox = oy = oz =
  pa = pb = pc = pd = pe = pf = pg = ph = pi = pj = pk =
  pl = pm = pn = po = pp = pq = pr = ps = pt = pu = pv =
  pw = px = py = pz =
  qa = qb = qc = qd = qe = qf = qg = qh = qi = qj = qk =
  ql = qm = qn = qo = qp = qq = qr = qs = qt = qu = qv =
  qw = qx = qy = qz =
  ra = rb = rc = rd = re = rf = rg = rh = ri = rj = rk =
  rl = rm = rn = ro = rp = rq = rr = rs = rt = ru = rv =
  rw = rx = ry = rz =
  sa = sb = sc = sd = se = sf = sg = sh = si = sj = sk =
  sl = sm = sn = so = sp = sq = sr = ss = st = su = sv =
  sw = sx = sy = sz =
  ta = tb = tc = td = te = tf = tg = th = ti = tj = tk =
  tl = tm = tn = to = tp = tq = tr = ts = tt = tu = tv =
  tw = tx = ty = tz =
  ua = ub = uc = ud = ue = uf = ug = uh = ui = uj = uk =
  ul = um = un = uo = up =