/* WARNING: Removing unreachable block (ram,0x00101346) */
/* WARNING: Removing unreachable block (ram,0x00101319) */
/* WARNING: Removing unreachable block (ram,0x001014ab) */

void bn_mul_comba4(uint *r,uint *a,uint *b)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint ht_15;
  uint lt_15;
  uint m1_15;
  uint m_15;
  uint ht_14;
  uint lt_14;
  uint m1_14;
  uint m_14;
  uint ht_13;
  uint lt_13;
  uint m1_13;
  uint m_13;
  uint ht_12;
  uint lt_12;
  uint m1_12;
  uint m_12;
  uint ht_11;
  uint lt_11;
  uint m1_11;
  uint m_11;
  uint ht_10;
  uint lt_10;
  uint m1_10;
  uint m_10;
  uint ht_9;
  uint lt_9;
  uint m1_9;
  uint m_9;
  uint ht_8;
  uint lt_8;
  uint m1_8;
  uint m_8;
  uint ht_7;
  uint lt_7;
  uint m1_7;
  uint m_7;
  uint ht_6;
  uint lt_6;
  uint m1_6;
  uint m_6;
  uint ht_5;
  uint lt_5;
  uint m1_5;
  uint m_5;
  uint ht_4;
  uint lt_4;
  uint m1_4;
  uint m_4;
  uint ht_3;
  uint lt_3;
  uint m1_3;
  uint m_3;
  uint ht_2;
  uint lt_2;
  uint m1_2;
  uint m_2;
  uint ht_1;
  uint lt_1;
  uint m1_1;
  uint m_1;
  uint ht;
  uint lt;
  uint m1;
  uint m;
  uint c3;
  uint c2;
  uint c1;
  uint t2;
  uint t1;
  uint bh;
  uint bl;
  uint *b_local;
  uint *a_local;
  uint *r_local;
  
  uVar1 = (*b & 0xffff) * (*a >> 0x10);
  ht = (*b >> 0x10) * (*a >> 0x10);
  uVar2 = (*b >> 0x10) * (*a & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht = ht + 0x10000;
  }
  ht = (uVar2 >> 0x10) + ht;
  uVar1 = (*b & 0xffff) * (*a & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht = ht + 1;
  }
  *r = uVar1;
  uVar1 = (b[1] & 0xffff) * (*a >> 0x10);
  ht_1 = (b[1] >> 0x10) * (*a >> 0x10);
  uVar2 = (b[1] >> 0x10) * (*a & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_1 = ht_1 + 0x10000;
  }
  ht_1 = (uVar2 >> 0x10) + ht_1;
  uVar1 = (b[1] & 0xffff) * (*a & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_1 = ht_1 + 1;
  }
  t2 = ht_1;
  if (ht + uVar1 < uVar1) {
    t2 = ht_1 + 1;
  }
  uVar2 = t2;
  uVar3 = (*b & 0xffff) * (a[1] >> 0x10);
  ht_2 = (*b >> 0x10) * (a[1] >> 0x10);
  uVar4 = (*b >> 0x10) * (a[1] & 0xffff) + uVar3;
  if (uVar4 < uVar3) {
    ht_2 = ht_2 + 0x10000;
  }
  ht_2 = (uVar4 >> 0x10) + ht_2;
  uVar3 = (*b & 0xffff) * (a[1] & 0xffff) + uVar4 * 0x10000;
  if (uVar3 < uVar4 * 0x10000) {
    ht_2 = ht_2 + 1;
  }
  t2 = ht_2;
  uVar1 = ht + uVar1 + uVar3;
  if (uVar1 < uVar3) {
    t2 = ht_2 + 1;
  }
  uVar2 = uVar2 + t2;
  c1 = (uint)(uVar2 < t2);
  r[1] = uVar1;
  uVar1 = (*b & 0xffff) * (a[2] >> 0x10);
  ht_3 = (*b >> 0x10) * (a[2] >> 0x10);
  uVar3 = (*b >> 0x10) * (a[2] & 0xffff) + uVar1;
  if (uVar3 < uVar1) {
    ht_3 = ht_3 + 0x10000;
  }
  ht_3 = (uVar3 >> 0x10) + ht_3;
  uVar1 = (*b & 0xffff) * (a[2] & 0xffff) + uVar3 * 0x10000;
  if (uVar1 < uVar3 * 0x10000) {
    ht_3 = ht_3 + 1;
  }
  t2 = ht_3;
  uVar2 = uVar2 + uVar1;
  if (uVar2 < uVar1) {
    t2 = ht_3 + 1;
  }
  uVar4 = c1 + t2;
  c2 = (uint)(uVar4 < t2);
  uVar1 = (b[1] & 0xffff) * (a[1] >> 0x10);
  ht_4 = (b[1] >> 0x10) * (a[1] >> 0x10);
  uVar3 = (b[1] >> 0x10) * (a[1] & 0xffff) + uVar1;
  if (uVar3 < uVar1) {
    ht_4 = ht_4 + 0x10000;
  }
  ht_4 = (uVar3 >> 0x10) + ht_4;
  uVar1 = (b[1] & 0xffff) * (a[1] & 0xffff) + uVar3 * 0x10000;
  if (uVar1 < uVar3 * 0x10000) {
    ht_4 = ht_4 + 1;
  }
  t2 = ht_4;
  uVar2 = uVar2 + uVar1;
  if (uVar2 < uVar1) {
    t2 = ht_4 + 1;
  }
  uVar4 = uVar4 + t2;
  if (uVar4 < t2) {
    c2 = c2 + 1;
  }
  uVar1 = (b[2] & 0xffff) * (*a >> 0x10);
  ht_5 = (b[2] >> 0x10) * (*a >> 0x10);
  uVar3 = (b[2] >> 0x10) * (*a & 0xffff) + uVar1;
  if (uVar3 < uVar1) {
    ht_5 = ht_5 + 0x10000;
  }
  ht_5 = (uVar3 >> 0x10) + ht_5;
  uVar1 = (b[2] & 0xffff) * (*a & 0xffff) + uVar3 * 0x10000;
  if (uVar1 < uVar3 * 0x10000) {
    ht_5 = ht_5 + 1;
  }
  t2 = ht_5;
  uVar2 = uVar2 + uVar1;
  if (uVar2 < uVar1) {
    t2 = ht_5 + 1;
  }
  uVar4 = uVar4 + t2;
  if (uVar4 < t2) {
    c2 = c2 + 1;
  }
  r[2] = uVar2;
  uVar1 = (b[3] & 0xffff) * (*a >> 0x10);
  ht_6 = (b[3] >> 0x10) * (*a >> 0x10);
  uVar2 = (b[3] >> 0x10) * (*a & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_6 = ht_6 + 0x10000;
  }
  ht_6 = (uVar2 >> 0x10) + ht_6;
  uVar1 = (b[3] & 0xffff) * (*a & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_6 = ht_6 + 1;
  }
  t2 = ht_6;
  uVar4 = uVar4 + uVar1;
  if (uVar4 < uVar1) {
    t2 = ht_6 + 1;
  }
  uVar3 = c2 + t2;
  c3 = (uint)(uVar3 < t2);
  uVar1 = (b[2] & 0xffff) * (a[1] >> 0x10);
  ht_7 = (b[2] >> 0x10) * (a[1] >> 0x10);
  uVar2 = (b[2] >> 0x10) * (a[1] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_7 = ht_7 + 0x10000;
  }
  ht_7 = (uVar2 >> 0x10) + ht_7;
  uVar1 = (b[2] & 0xffff) * (a[1] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_7 = ht_7 + 1;
  }
  t2 = ht_7;
  uVar4 = uVar4 + uVar1;
  if (uVar4 < uVar1) {
    t2 = ht_7 + 1;
  }
  uVar3 = uVar3 + t2;
  if (uVar3 < t2) {
    c3 = c3 + 1;
  }
  uVar1 = (b[1] & 0xffff) * (a[2] >> 0x10);
  ht_8 = (b[1] >> 0x10) * (a[2] >> 0x10);
  uVar2 = (b[1] >> 0x10) * (a[2] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_8 = ht_8 + 0x10000;
  }
  ht_8 = (uVar2 >> 0x10) + ht_8;
  uVar1 = (b[1] & 0xffff) * (a[2] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_8 = ht_8 + 1;
  }
  t2 = ht_8;
  uVar4 = uVar4 + uVar1;
  if (uVar4 < uVar1) {
    t2 = ht_8 + 1;
  }
  uVar3 = uVar3 + t2;
  if (uVar3 < t2) {
    c3 = c3 + 1;
  }
  uVar1 = (*b & 0xffff) * (a[3] >> 0x10);
  ht_9 = (*b >> 0x10) * (a[3] >> 0x10);
  uVar2 = (*b >> 0x10) * (a[3] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_9 = ht_9 + 0x10000;
  }
  ht_9 = (uVar2 >> 0x10) + ht_9;
  uVar1 = (*b & 0xffff) * (a[3] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_9 = ht_9 + 1;
  }
  t2 = ht_9;
  uVar4 = uVar4 + uVar1;
  if (uVar4 < uVar1) {
    t2 = ht_9 + 1;
  }
  uVar3 = uVar3 + t2;
  if (uVar3 < t2) {
    c3 = c3 + 1;
  }
  r[3] = uVar4;
  uVar1 = (b[1] & 0xffff) * (a[3] >> 0x10);
  ht_10 = (b[1] >> 0x10) * (a[3] >> 0x10);
  uVar2 = (b[1] >> 0x10) * (a[3] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_10 = ht_10 + 0x10000;
  }
  ht_10 = (uVar2 >> 0x10) + ht_10;
  uVar1 = (b[1] & 0xffff) * (a[3] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_10 = ht_10 + 1;
  }
  t2 = ht_10;
  uVar3 = uVar3 + uVar1;
  if (uVar3 < uVar1) {
    t2 = ht_10 + 1;
  }
  uVar4 = c3 + t2;
  c1 = (uint)(uVar4 < t2);
  uVar1 = (b[2] & 0xffff) * (a[2] >> 0x10);
  ht_11 = (b[2] >> 0x10) * (a[2] >> 0x10);
  uVar2 = (b[2] >> 0x10) * (a[2] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_11 = ht_11 + 0x10000;
  }
  ht_11 = (uVar2 >> 0x10) + ht_11;
  uVar1 = (b[2] & 0xffff) * (a[2] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_11 = ht_11 + 1;
  }
  t2 = ht_11;
  uVar3 = uVar3 + uVar1;
  if (uVar3 < uVar1) {
    t2 = ht_11 + 1;
  }
  uVar4 = uVar4 + t2;
  if (uVar4 < t2) {
    c1 = c1 + 1;
  }
  uVar1 = (b[3] & 0xffff) * (a[1] >> 0x10);
  ht_12 = (b[3] >> 0x10) * (a[1] >> 0x10);
  uVar2 = (b[3] >> 0x10) * (a[1] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_12 = ht_12 + 0x10000;
  }
  ht_12 = (uVar2 >> 0x10) + ht_12;
  uVar1 = (b[3] & 0xffff) * (a[1] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_12 = ht_12 + 1;
  }
  t2 = ht_12;
  uVar3 = uVar3 + uVar1;
  if (uVar3 < uVar1) {
    t2 = ht_12 + 1;
  }
  uVar4 = uVar4 + t2;
  if (uVar4 < t2) {
    c1 = c1 + 1;
  }
  r[4] = uVar3;
  uVar1 = (b[3] & 0xffff) * (a[2] >> 0x10);
  ht_13 = (b[3] >> 0x10) * (a[2] >> 0x10);
  uVar2 = (b[3] >> 0x10) * (a[2] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_13 = ht_13 + 0x10000;
  }
  ht_13 = (uVar2 >> 0x10) + ht_13;
  uVar1 = (b[3] & 0xffff) * (a[2] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_13 = ht_13 + 1;
  }
  t2 = ht_13;
  uVar4 = uVar4 + uVar1;
  if (uVar4 < uVar1) {
    t2 = ht_13 + 1;
  }
  uVar3 = c1 + t2;
  c2 = (uint)(uVar3 < t2);
  uVar1 = (b[2] & 0xffff) * (a[3] >> 0x10);
  ht_14 = (b[2] >> 0x10) * (a[3] >> 0x10);
  uVar2 = (b[2] >> 0x10) * (a[3] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_14 = ht_14 + 0x10000;
  }
  ht_14 = (uVar2 >> 0x10) + ht_14;
  uVar1 = (b[2] & 0xffff) * (a[3] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_14 = ht_14 + 1;
  }
  t2 = ht_14;
  uVar4 = uVar4 + uVar1;
  if (uVar4 < uVar1) {
    t2 = ht_14 + 1;
  }
  uVar3 = uVar3 + t2;
  if (uVar3 < t2) {
    c2 = c2 + 1;
  }
  r[5] = uVar4;
  uVar1 = (b[3] & 0xffff) * (a[3] >> 0x10);
  ht_15 = (b[3] >> 0x10) * (a[3] >> 0x10);
  uVar2 = (b[3] >> 0x10) * (a[3] & 0xffff) + uVar1;
  if (uVar2 < uVar1) {
    ht_15 = ht_15 + 0x10000;
  }
  ht_15 = (uVar2 >> 0x10) + ht_15;
  uVar1 = (b[3] & 0xffff) * (a[3] & 0xffff) + uVar2 * 0x10000;
  if (uVar1 < uVar2 * 0x10000) {
    ht_15 = ht_15 + 1;
  }
  t2 = ht_15;
  uVar3 = uVar3 + uVar1;
  if (uVar3 < uVar1) {
    t2 = ht_15 + 1;
  }
  r[6] = uVar3;
  r[7] = c2 + t2;
  return;
}