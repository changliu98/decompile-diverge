/* WARNING: Removing unreachable block (ram,0x001012ef) */
/* WARNING: Removing unreachable block (ram,0x001012c2) */
/* WARNING: Removing unreachable block (ram,0x001014ec) */

void bn_sqr_comba8(uint *r,uint *a)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint m_35;
  uint h_7;
  uint l_7;
  uint ht_27;
  uint lt_27;
  uint m1_27;
  uint m_34;
  uint ht_26;
  uint lt_26;
  uint m1_26;
  uint m_33;
  uint m_32;
  uint h_6;
  uint l_6;
  uint ht_25;
  uint lt_25;
  uint m1_25;
  uint m_31;
  uint ht_24;
  uint lt_24;
  uint m1_24;
  uint m_30;
  uint ht_23;
  uint lt_23;
  uint m1_23;
  uint m_29;
  uint ht_22;
  uint lt_22;
  uint m1_22;
  uint m_28;
  uint m_27;
  uint h_5;
  uint l_5;
  uint ht_21;
  uint lt_21;
  uint m1_21;
  uint m_26;
  uint ht_20;
  uint lt_20;
  uint m1_20;
  uint m_25;
  uint ht_19;
  uint lt_19;
  uint m1_19;
  uint m_24;
  uint ht_18;
  uint lt_18;
  uint m1_18;
  uint m_23;
  uint ht_17;
  uint lt_17;
  uint m1_17;
  uint m_22;
  uint ht_16;
  uint lt_16;
  uint m1_16;
  uint m_21;
  uint m_20;
  uint h_4;
  uint l_4;
  uint ht_15;
  uint lt_15;
  uint m1_15;
  uint m_19;
  uint ht_14;
  uint lt_14;
  uint m1_14;
  uint m_18;
  uint ht_13;
  uint lt_13;
  uint m1_13;
  uint m_17;
  uint ht_12;
  uint lt_12;
  uint m1_12;
  uint m_16;
  uint ht_11;
  uint lt_11;
  uint m1_11;
  uint m_15;
  uint ht_10;
  uint lt_10;
  uint m1_10;
  uint m_14;
  uint ht_9;
  uint lt_9;
  uint m1_9;
  uint m_13;
  uint m_12;
  uint h_3;
  uint l_3;
  uint ht_8;
  uint lt_8;
  uint m1_8;
  uint m_11;
  uint ht_7;
  uint lt_7;
  uint m1_7;
  uint m_10;
  uint ht_6;
  uint lt_6;
  uint m1_6;
  uint m_9;
  uint ht_5;
  uint lt_5;
  uint m1_5;
  uint m_8;
  uint ht_4;
  uint lt_4;
  uint m1_4;
  uint m_7;
  uint m_6;
  uint h_2;
  uint l_2;
  uint ht_3;
  uint lt_3;
  uint m1_3;
  uint m_5;
  uint ht_2;
  uint lt_2;
  uint m1_2;
  uint m_4;
  uint ht_1;
  uint lt_1;
  uint m1_1;
  uint m_3;
  uint m_2;
  uint h_1;
  uint l_1;
  uint ht;
  uint lt;
  uint m1;
  uint m_1;
  uint m;
  uint h;
  uint l;
  uint c3;
  uint c2;
  uint c1;
  uint t2;
  uint t1;
  uint bh;
  uint bl;
  uint *a_local;
  uint *r_local;
  
  uVar1 = *a & 0xffff;
  uVar2 = *a >> 0x10;
  h = uVar2 * uVar2 + (int)((long)((ulong)(uVar1 * uVar2) & 0xffff8000) >> 0xf);
  uVar2 = uVar1 * uVar2 * 0x20000;
  uVar1 = uVar1 * uVar1 + uVar2;
  if (uVar1 < uVar2) {
    h = h + 1;
  }
  *r = uVar1;
  uVar1 = (*a & 0xffff) * (a[1] >> 0x10);
  ht = (*a >> 0x10) * (a[1] >> 0x10);
  uVar2 = (*a >> 0x10) * (a[1] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht = ht + 0x10000;
  }
  ht = (uVar2 >> 0x10) + ht;
  uVar1 = (*a & 0xffff) * (a[1] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht = ht + 1;
  }
  c1 = (uint)((ht & 0x80000000) != 0);
  t2 = ht * 2;
  if ((uVar1 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar2 = h + uVar1 * 2;
  if ((uVar2 < uVar1 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar1 = t2;
  r[1] = uVar2;
  uVar2 = a[1] & 0xffff;
  uVar3 = a[1] >> 0x10;
  h_1 = uVar3 * uVar3 + (int)((long)((ulong)(uVar2 * uVar3) & 0xffff8000) >> 0xf);
  uVar3 = uVar2 * uVar3 * 0x20000;
  uVar2 = uVar2 * uVar2 + uVar3;
  if (uVar2 < uVar3) {
    h_1 = h_1 + 1;
  }
  t2 = h_1;
  if (uVar1 + uVar2 < uVar2) {
    t2 = h_1 + 1;
  }
  uVar4 = c1 + t2;
  c2 = (uint)(uVar4 < t2);
  uVar3 = (*a & 0xffff) * (a[2] >> 0x10);
  ht_1 = (*a >> 0x10) * (a[2] >> 0x10);
  uVar5 = (*a >> 0x10) * (a[2] & 0xffff) + uVar3;
  if (uVar5 < uVar3) {
    ht_1 = ht_1 + 0x10000;
  }
  ht_1 = (uVar5 >> 0x10) + ht_1;
  uVar3 = (*a & 0xffff) * (a[2] & 0xffff) + uVar5 * 0x10000;
  if (uVar3 < uVar5 * 0x10000) {
    ht_1 = ht_1 + 1;
  }
  if ((ht_1 & 0x80000000) != 0) {
    c2 = c2 + 1;
  }
  t2 = ht_1 * 2;
  if ((uVar3 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 + uVar3 * 2;
  if ((uVar1 < uVar3 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar4 = uVar4 + t2;
  if (uVar4 < t2) {
    c2 = c2 + 1;
  }
  r[2] = uVar1;
  uVar1 = (*a & 0xffff) * (a[3] >> 0x10);
  ht_2 = (*a >> 0x10) * (a[3] >> 0x10);
  uVar2 = (*a >> 0x10) * (a[3] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_2 = ht_2 + 0x10000;
  }
  ht_2 = (uVar2 >> 0x10) + ht_2;
  uVar1 = (*a & 0xffff) * (a[3] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_2 = ht_2 + 1;
  }
  c3 = (uint)((ht_2 & 0x80000000) != 0);
  t2 = ht_2 * 2;
  if ((uVar1 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar4 = uVar4 + uVar1 * 2;
  if ((uVar4 < uVar1 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar1 = c2 + t2;
  if (uVar1 < t2) {
    c3 = c3 + 1;
  }
  uVar2 = (a[1] & 0xffff) * (a[2] >> 0x10);
  ht_3 = (a[1] >> 0x10) * (a[2] >> 0x10);
  uVar3 = (a[1] >> 0x10) * (a[2] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_3 = ht_3 + 0x10000;
  }
  ht_3 = (uVar3 >> 0x10) + ht_3;
  uVar2 = (a[1] & 0xffff) * (a[2] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_3 = ht_3 + 1;
  }
  if ((ht_3 & 0x80000000) != 0) {
    c3 = c3 + 1;
  }
  t2 = ht_3 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar4 = uVar4 + uVar2 * 2;
  if ((uVar4 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c3 = c3 + 1;
  }
  r[3] = uVar4;
  uVar2 = a[2] & 0xffff;
  uVar3 = a[2] >> 0x10;
  h_2 = uVar3 * uVar3 + (int)((long)((ulong)(uVar2 * uVar3) & 0xffff8000) >> 0xf);
  uVar3 = uVar2 * uVar3 * 0x20000;
  uVar2 = uVar2 * uVar2 + uVar3;
  if (uVar2 < uVar3) {
    h_2 = h_2 + 1;
  }
  t2 = h_2;
  uVar1 = uVar1 + uVar2;
  if (uVar1 < uVar2) {
    t2 = h_2 + 1;
  }
  uVar5 = c3 + t2;
  c1 = (uint)(uVar5 < t2);
  uVar2 = (a[1] & 0xffff) * (a[3] >> 0x10);
  ht_4 = (a[1] >> 0x10) * (a[3] >> 0x10);
  uVar3 = (a[1] >> 0x10) * (a[3] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_4 = ht_4 + 0x10000;
  }
  ht_4 = (uVar3 >> 0x10) + ht_4;
  uVar2 = (a[1] & 0xffff) * (a[3] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_4 = ht_4 + 1;
  }
  if ((ht_4 & 0x80000000) != 0) {
    c1 = c1 + 1;
  }
  t2 = ht_4 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c1 = c1 + 1;
  }
  uVar2 = (*a & 0xffff) * (a[4] >> 0x10);
  ht_5 = (*a >> 0x10) * (a[4] >> 0x10);
  uVar3 = (*a >> 0x10) * (a[4] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_5 = ht_5 + 0x10000;
  }
  ht_5 = (uVar3 >> 0x10) + ht_5;
  uVar2 = (*a & 0xffff) * (a[4] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_5 = ht_5 + 1;
  }
  if ((ht_5 & 0x80000000) != 0) {
    c1 = c1 + 1;
  }
  t2 = ht_5 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c1 = c1 + 1;
  }
  r[4] = uVar1;
  uVar1 = (*a & 0xffff) * (a[5] >> 0x10);
  ht_6 = (*a >> 0x10) * (a[5] >> 0x10);
  uVar2 = (*a >> 0x10) * (a[5] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_6 = ht_6 + 0x10000;
  }
  ht_6 = (uVar2 >> 0x10) + ht_6;
  uVar1 = (*a & 0xffff) * (a[5] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_6 = ht_6 + 1;
  }
  c2 = (uint)((ht_6 & 0x80000000) != 0);
  t2 = ht_6 * 2;
  if ((uVar1 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar1 * 2;
  if ((uVar5 < uVar1 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar1 = c1 + t2;
  if (uVar1 < t2) {
    c2 = c2 + 1;
  }
  uVar2 = (a[1] & 0xffff) * (a[4] >> 0x10);
  ht_7 = (a[1] >> 0x10) * (a[4] >> 0x10);
  uVar3 = (a[1] >> 0x10) * (a[4] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_7 = ht_7 + 0x10000;
  }
  ht_7 = (uVar3 >> 0x10) + ht_7;
  uVar2 = (a[1] & 0xffff) * (a[4] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_7 = ht_7 + 1;
  }
  if ((ht_7 & 0x80000000) != 0) {
    c2 = c2 + 1;
  }
  t2 = ht_7 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c2 = c2 + 1;
  }
  uVar2 = (a[2] & 0xffff) * (a[3] >> 0x10);
  ht_8 = (a[2] >> 0x10) * (a[3] >> 0x10);
  uVar3 = (a[2] >> 0x10) * (a[3] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_8 = ht_8 + 0x10000;
  }
  ht_8 = (uVar3 >> 0x10) + ht_8;
  uVar2 = (a[2] & 0xffff) * (a[3] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_8 = ht_8 + 1;
  }
  if ((ht_8 & 0x80000000) != 0) {
    c2 = c2 + 1;
  }
  t2 = ht_8 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c2 = c2 + 1;
  }
  r[5] = uVar5;
  uVar2 = a[3] & 0xffff;
  uVar3 = a[3] >> 0x10;
  h_3 = uVar3 * uVar3 + (int)((long)((ulong)(uVar2 * uVar3) & 0xffff8000) >> 0xf);
  uVar3 = uVar2 * uVar3 * 0x20000;
  uVar2 = uVar2 * uVar2 + uVar3;
  if (uVar2 < uVar3) {
    h_3 = h_3 + 1;
  }
  t2 = h_3;
  uVar1 = uVar1 + uVar2;
  if (uVar1 < uVar2) {
    t2 = h_3 + 1;
  }
  uVar5 = c2 + t2;
  c3 = (uint)(uVar5 < t2);
  uVar2 = (a[2] & 0xffff) * (a[4] >> 0x10);
  ht_9 = (a[2] >> 0x10) * (a[4] >> 0x10);
  uVar3 = (a[2] >> 0x10) * (a[4] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_9 = ht_9 + 0x10000;
  }
  ht_9 = (uVar3 >> 0x10) + ht_9;
  uVar2 = (a[2] & 0xffff) * (a[4] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_9 = ht_9 + 1;
  }
  if ((ht_9 & 0x80000000) != 0) {
    c3 = c3 + 1;
  }
  t2 = ht_9 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c3 = c3 + 1;
  }
  uVar2 = (a[1] & 0xffff) * (a[5] >> 0x10);
  ht_10 = (a[1] >> 0x10) * (a[5] >> 0x10);
  uVar3 = (a[1] >> 0x10) * (a[5] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_10 = ht_10 + 0x10000;
  }
  ht_10 = (uVar3 >> 0x10) + ht_10;
  uVar2 = (a[1] & 0xffff) * (a[5] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_10 = ht_10 + 1;
  }
  if ((ht_10 & 0x80000000) != 0) {
    c3 = c3 + 1;
  }
  t2 = ht_10 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c3 = c3 + 1;
  }
  uVar2 = (*a & 0xffff) * (a[6] >> 0x10);
  ht_11 = (*a >> 0x10) * (a[6] >> 0x10);
  uVar3 = (*a >> 0x10) * (a[6] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_11 = ht_11 + 0x10000;
  }
  ht_11 = (uVar3 >> 0x10) + ht_11;
  uVar2 = (*a & 0xffff) * (a[6] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_11 = ht_11 + 1;
  }
  if ((ht_11 & 0x80000000) != 0) {
    c3 = c3 + 1;
  }
  t2 = ht_11 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c3 = c3 + 1;
  }
  r[6] = uVar1;
  uVar1 = (*a & 0xffff) * (a[7] >> 0x10);
  ht_12 = (*a >> 0x10) * (a[7] >> 0x10);
  uVar2 = (*a >> 0x10) * (a[7] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_12 = ht_12 + 0x10000;
  }
  ht_12 = (uVar2 >> 0x10) + ht_12;
  uVar1 = (*a & 0xffff) * (a[7] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_12 = ht_12 + 1;
  }
  c1 = (uint)((ht_12 & 0x80000000) != 0);
  t2 = ht_12 * 2;
  if ((uVar1 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar1 * 2;
  if ((uVar5 < uVar1 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar1 = c3 + t2;
  if (uVar1 < t2) {
    c1 = c1 + 1;
  }
  uVar2 = (a[1] & 0xffff) * (a[6] >> 0x10);
  ht_13 = (a[1] >> 0x10) * (a[6] >> 0x10);
  uVar3 = (a[1] >> 0x10) * (a[6] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_13 = ht_13 + 0x10000;
  }
  ht_13 = (uVar3 >> 0x10) + ht_13;
  uVar2 = (a[1] & 0xffff) * (a[6] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_13 = ht_13 + 1;
  }
  if ((ht_13 & 0x80000000) != 0) {
    c1 = c1 + 1;
  }
  t2 = ht_13 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c1 = c1 + 1;
  }
  uVar2 = (a[2] & 0xffff) * (a[5] >> 0x10);
  ht_14 = (a[2] >> 0x10) * (a[5] >> 0x10);
  uVar3 = (a[2] >> 0x10) * (a[5] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_14 = ht_14 + 0x10000;
  }
  ht_14 = (uVar3 >> 0x10) + ht_14;
  uVar2 = (a[2] & 0xffff) * (a[5] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_14 = ht_14 + 1;
  }
  if ((ht_14 & 0x80000000) != 0) {
    c1 = c1 + 1;
  }
  t2 = ht_14 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c1 = c1 + 1;
  }
  uVar2 = (a[3] & 0xffff) * (a[4] >> 0x10);
  ht_15 = (a[3] >> 0x10) * (a[4] >> 0x10);
  uVar3 = (a[3] >> 0x10) * (a[4] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_15 = ht_15 + 0x10000;
  }
  ht_15 = (uVar3 >> 0x10) + ht_15;
  uVar2 = (a[3] & 0xffff) * (a[4] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_15 = ht_15 + 1;
  }
  if ((ht_15 & 0x80000000) != 0) {
    c1 = c1 + 1;
  }
  t2 = ht_15 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c1 = c1 + 1;
  }
  r[7] = uVar5;
  uVar2 = a[4] & 0xffff;
  uVar3 = a[4] >> 0x10;
  h_4 = uVar3 * uVar3 + (int)((long)((ulong)(uVar2 * uVar3) & 0xffff8000) >> 0xf);
  uVar3 = uVar2 * uVar3 * 0x20000;
  uVar2 = uVar2 * uVar2 + uVar3;
  if (uVar2 < uVar3) {
    h_4 = h_4 + 1;
  }
  t2 = h_4;
  uVar1 = uVar1 + uVar2;
  if (uVar1 < uVar2) {
    t2 = h_4 + 1;
  }
  uVar5 = c1 + t2;
  c2 = (uint)(uVar5 < t2);
  uVar2 = (a[3] & 0xffff) * (a[5] >> 0x10);
  ht_16 = (a[3] >> 0x10) * (a[5] >> 0x10);
  uVar3 = (a[3] >> 0x10) * (a[5] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_16 = ht_16 + 0x10000;
  }
  ht_16 = (uVar3 >> 0x10) + ht_16;
  uVar2 = (a[3] & 0xffff) * (a[5] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_16 = ht_16 + 1;
  }
  if ((ht_16 & 0x80000000) != 0) {
    c2 = c2 + 1;
  }
  t2 = ht_16 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c2 = c2 + 1;
  }
  uVar2 = (a[2] & 0xffff) * (a[6] >> 0x10);
  ht_17 = (a[2] >> 0x10) * (a[6] >> 0x10);
  uVar3 = (a[2] >> 0x10) * (a[6] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_17 = ht_17 + 0x10000;
  }
  ht_17 = (uVar3 >> 0x10) + ht_17;
  uVar2 = (a[2] & 0xffff) * (a[6] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_17 = ht_17 + 1;
  }
  if ((ht_17 & 0x80000000) != 0) {
    c2 = c2 + 1;
  }
  t2 = ht_17 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c2 = c2 + 1;
  }
  uVar2 = (a[1] & 0xffff) * (a[7] >> 0x10);
  ht_18 = (a[1] >> 0x10) * (a[7] >> 0x10);
  uVar3 = (a[1] >> 0x10) * (a[7] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_18 = ht_18 + 0x10000;
  }
  ht_18 = (uVar3 >> 0x10) + ht_18;
  uVar2 = (a[1] & 0xffff) * (a[7] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_18 = ht_18 + 1;
  }
  if ((ht_18 & 0x80000000) != 0) {
    c2 = c2 + 1;
  }
  t2 = ht_18 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c2 = c2 + 1;
  }
  r[8] = uVar1;
  uVar1 = (a[2] & 0xffff) * (a[7] >> 0x10);
  ht_19 = (a[2] >> 0x10) * (a[7] >> 0x10);
  uVar2 = (a[2] >> 0x10) * (a[7] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_19 = ht_19 + 0x10000;
  }
  ht_19 = (uVar2 >> 0x10) + ht_19;
  uVar1 = (a[2] & 0xffff) * (a[7] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_19 = ht_19 + 1;
  }
  c3 = (uint)((ht_19 & 0x80000000) != 0);
  t2 = ht_19 * 2;
  if ((uVar1 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar1 * 2;
  if ((uVar5 < uVar1 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar1 = c2 + t2;
  if (uVar1 < t2) {
    c3 = c3 + 1;
  }
  uVar2 = (a[3] & 0xffff) * (a[6] >> 0x10);
  ht_20 = (a[3] >> 0x10) * (a[6] >> 0x10);
  uVar3 = (a[3] >> 0x10) * (a[6] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_20 = ht_20 + 0x10000;
  }
  ht_20 = (uVar3 >> 0x10) + ht_20;
  uVar2 = (a[3] & 0xffff) * (a[6] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_20 = ht_20 + 1;
  }
  if ((ht_20 & 0x80000000) != 0) {
    c3 = c3 + 1;
  }
  t2 = ht_20 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c3 = c3 + 1;
  }
  uVar2 = (a[4] & 0xffff) * (a[5] >> 0x10);
  ht_21 = (a[4] >> 0x10) * (a[5] >> 0x10);
  uVar3 = (a[4] >> 0x10) * (a[5] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_21 = ht_21 + 0x10000;
  }
  ht_21 = (uVar3 >> 0x10) + ht_21;
  uVar2 = (a[4] & 0xffff) * (a[5] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_21 = ht_21 + 1;
  }
  if ((ht_21 & 0x80000000) != 0) {
    c3 = c3 + 1;
  }
  t2 = ht_21 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c3 = c3 + 1;
  }
  r[9] = uVar5;
  uVar2 = a[5] & 0xffff;
  uVar3 = a[5] >> 0x10;
  h_5 = uVar3 * uVar3 + (int)((long)((ulong)(uVar2 * uVar3) & 0xffff8000) >> 0xf);
  uVar3 = uVar2 * uVar3 * 0x20000;
  uVar2 = uVar2 * uVar2 + uVar3;
  if (uVar2 < uVar3) {
    h_5 = h_5 + 1;
  }
  t2 = h_5;
  uVar1 = uVar1 + uVar2;
  if (uVar1 < uVar2) {
    t2 = h_5 + 1;
  }
  uVar5 = c3 + t2;
  c1 = (uint)(uVar5 < t2);
  uVar2 = (a[4] & 0xffff) * (a[6] >> 0x10);
  ht_22 = (a[4] >> 0x10) * (a[6] >> 0x10);
  uVar3 = (a[4] >> 0x10) * (a[6] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_22 = ht_22 + 0x10000;
  }
  ht_22 = (uVar3 >> 0x10) + ht_22;
  uVar2 = (a[4] & 0xffff) * (a[6] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_22 = ht_22 + 1;
  }
  if ((ht_22 & 0x80000000) != 0) {
    c1 = c1 + 1;
  }
  t2 = ht_22 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c1 = c1 + 1;
  }
  uVar2 = (a[3] & 0xffff) * (a[7] >> 0x10);
  ht_23 = (a[3] >> 0x10) * (a[7] >> 0x10);
  uVar3 = (a[3] >> 0x10) * (a[7] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_23 = ht_23 + 0x10000;
  }
  ht_23 = (uVar3 >> 0x10) + ht_23;
  uVar2 = (a[3] & 0xffff) * (a[7] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_23 = ht_23 + 1;
  }
  if ((ht_23 & 0x80000000) != 0) {
    c1 = c1 + 1;
  }
  t2 = ht_23 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c1 = c1 + 1;
  }
  r[10] = uVar1;
  uVar1 = (a[4] & 0xffff) * (a[7] >> 0x10);
  ht_24 = (a[4] >> 0x10) * (a[7] >> 0x10);
  uVar2 = (a[4] >> 0x10) * (a[7] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_24 = ht_24 + 0x10000;
  }
  ht_24 = (uVar2 >> 0x10) + ht_24;
  uVar1 = (a[4] & 0xffff) * (a[7] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_24 = ht_24 + 1;
  }
  c2 = (uint)((ht_24 & 0x80000000) != 0);
  t2 = ht_24 * 2;
  if ((uVar1 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar1 * 2;
  if ((uVar5 < uVar1 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar1 = c1 + t2;
  if (uVar1 < t2) {
    c2 = c2 + 1;
  }
  uVar2 = (a[5] & 0xffff) * (a[6] >> 0x10);
  ht_25 = (a[5] >> 0x10) * (a[6] >> 0x10);
  uVar3 = (a[5] >> 0x10) * (a[6] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_25 = ht_25 + 0x10000;
  }
  ht_25 = (uVar3 >> 0x10) + ht_25;
  uVar2 = (a[5] & 0xffff) * (a[6] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_25 = ht_25 + 1;
  }
  if ((ht_25 & 0x80000000) != 0) {
    c2 = c2 + 1;
  }
  t2 = ht_25 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar2 * 2;
  if ((uVar5 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c2 = c2 + 1;
  }
  uVar1 = uVar1 + t2;
  if (uVar1 < t2) {
    c2 = c2 + 1;
  }
  r[0xb] = uVar5;
  uVar2 = a[6] & 0xffff;
  uVar3 = a[6] >> 0x10;
  h_6 = uVar3 * uVar3 + (int)((long)((ulong)(uVar2 * uVar3) & 0xffff8000) >> 0xf);
  uVar3 = uVar2 * uVar3 * 0x20000;
  uVar2 = uVar2 * uVar2 + uVar3;
  if (uVar2 < uVar3) {
    h_6 = h_6 + 1;
  }
  t2 = h_6;
  uVar1 = uVar1 + uVar2;
  if (uVar1 < uVar2) {
    t2 = h_6 + 1;
  }
  uVar5 = c2 + t2;
  c3 = (uint)(uVar5 < t2);
  uVar2 = (a[5] & 0xffff) * (a[7] >> 0x10);
  ht_26 = (a[5] >> 0x10) * (a[7] >> 0x10);
  uVar3 = (a[5] >> 0x10) * (a[7] & 0xffff) + uVar2;
  if (uVar3 < uVar2) {
    ht_26 = ht_26 + 0x10000;
  }
  ht_26 = (uVar3 >> 0x10) + ht_26;
  uVar2 = (a[5] & 0xffff) * (a[7] & 0xffff) + uVar3 * 0x10000;
  if (uVar2 < uVar3 * 0x10000) {
    ht_26 = ht_26 + 1;
  }
  if ((ht_26 & 0x80000000) != 0) {
    c3 = c3 + 1;
  }
  t2 = ht_26 * 2;
  if ((uVar2 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar1 = uVar1 + uVar2 * 2;
  if ((uVar1 < uVar2 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c3 = c3 + 1;
  }
  uVar5 = uVar5 + t2;
  if (uVar5 < t2) {
    c3 = c3 + 1;
  }
  r[0xc] = uVar1;
  uVar1 = (a[6] & 0xffff) * (a[7] >> 0x10);
  ht_27 = (a[6] >> 0x10) * (a[7] >> 0x10);
  uVar2 = (a[6] >> 0x10) * (a[7] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_27 = ht_27 + 0x10000;
  }
  ht_27 = (uVar2 >> 0x10) + ht_27;
  uVar1 = (a[6] & 0xffff) * (a[7] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_27 = ht_27 + 1;
  }
  c1 = (uint)((ht_27 & 0x80000000) != 0);
  t2 = ht_27 * 2;
  if ((uVar1 & 0x80000000) != 0) {
    t2 = t2 + 1;
  }
  uVar5 = uVar5 + uVar1 * 2;
  if ((uVar5 < uVar1 * 2) && (t2 = t2 + 1, t2 == 0)) {
    c1 = c1 + 1;
  }
  uVar1 = c3 + t2;
  if (uVar1 < t2) {
    c1 = c1 + 1;
  }
  r[0xd] = uVar5;
  uVar2 = a[7] & 0xffff;
  uVar3 = a[7] >> 0x10;
  h_7 = uVar3 * uVar3 + (int)((long)((ulong)(uVar2 * uVar3) & 0xffff8000) >> 0xf);
  uVar3 = uVar2 * uVar3 * 0x20000;
  uVar2 = uVar2 * uVar2 + uVar3;
  if (uVar2 < uVar3) {
    h_7 = h_7 + 1;
  }
  t2 = h_7;
  uVar1 = uVar1 + uVar2;
  if (uVar1 < uVar2) {
    t2 = h_7 + 1;
  }
  r[0xe] = uVar1;
  r[0xf] = c1 + t2;
  return;
}