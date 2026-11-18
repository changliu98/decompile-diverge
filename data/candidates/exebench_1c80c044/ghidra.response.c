/* WARNING: Removing unreachable block (ram,0x0010135d) */

void bn_mul_comba8(unsigned_long *r,unsigned_long *a,unsigned_long *b)

{
  ulong uVar1;
  ulong uVar2;
  ulong uVar3;
  ulong uVar4;
  ulong uVar5;
  unsigned_long ht_63;
  unsigned_long lt_63;
  unsigned_long m1_63;
  unsigned_long m_63;
  unsigned_long ht_62;
  unsigned_long lt_62;
  unsigned_long m1_62;
  unsigned_long m_62;
  unsigned_long ht_61;
  unsigned_long lt_61;
  unsigned_long m1_61;
  unsigned_long m_61;
  unsigned_long ht_60;
  unsigned_long lt_60;
  unsigned_long m1_60;
  unsigned_long m_60;
  unsigned_long ht_59;
  unsigned_long lt_59;
  unsigned_long m1_59;
  unsigned_long m_59;
  unsigned_long ht_58;
  unsigned_long lt_58;
  unsigned_long m1_58;
  unsigned_long m_58;
  unsigned_long ht_57;
  unsigned_long lt_57;
  unsigned_long m1_57;
  unsigned_long m_57;
  unsigned_long ht_56;
  unsigned_long lt_56;
  unsigned_long m1_56;
  unsigned_long m_56;
  unsigned_long ht_55;
  unsigned_long lt_55;
  unsigned_long m1_55;
  unsigned_long m_55;
  unsigned_long ht_54;
  unsigned_long lt_54;
  unsigned_long m1_54;
  unsigned_long m_54;
  unsigned_long ht_53;
  unsigned_long lt_53;
  unsigned_long m1_53;
  unsigned_long m_53;
  unsigned_long ht_52;
  unsigned_long lt_52;
  unsigned_long m1_52;
  unsigned_long m_52;
  unsigned_long ht_51;
  unsigned_long lt_51;
  unsigned_long m1_51;
  unsigned_long m_51;
  unsigned_long ht_50;
  unsigned_long lt_50;
  unsigned_long m1_50;
  unsigned_long m_50;
  unsigned_long ht_49;
  unsigned_long lt_49;
  unsigned_long m1_49;
  unsigned_long m_49;
  unsigned_long ht_48;
  unsigned_long lt_48;
  unsigned_long m1_48;
  unsigned_long m_48;
  unsigned_long ht_47;
  unsigned_long lt_47;
  unsigned_long m1_47;
  unsigned_long m_47;
  unsigned_long ht_46;
  unsigned_long lt_46;
  unsigned_long m1_46;
  unsigned_long m_46;
  unsigned_long ht_45;
  unsigned_long lt_45;
  unsigned_long m1_45;
  unsigned_long m_45;
  unsigned_long ht_44;
  unsigned_long lt_44;
  unsigned_long m1_44;
  unsigned_long m_44;
  unsigned_long ht_43;
  unsigned_long lt_43;
  unsigned_long m1_43;
  unsigned_long m_43;
  unsigned_long ht_42;
  unsigned_long lt_42;
  unsigned_long m1_42;
  unsigned_long m_42;
  unsigned_long ht_41;
  unsigned_long lt_41;
  unsigned_long m1_41;
  unsigned_long m_41;
  unsigned_long ht_40;
  unsigned_long lt_40;
  unsigned_long m1_40;
  unsigned_long m_40;
  unsigned_long ht_39;
  unsigned_long lt_39;
  unsigned_long m1_39;
  unsigned_long m_39;
  unsigned_long ht_38;
  unsigned_long lt_38;
  unsigned_long m1_38;
  unsigned_long m_38;
  unsigned_long ht_37;
  unsigned_long lt_37;
  unsigned_long m1_37;
  unsigned_long m_37;
  unsigned_long ht_36;
  unsigned_long lt_36;
  unsigned_long m1_36;
  unsigned_long m_36;
  unsigned_long ht_35;
  unsigned_long lt_35;
  unsigned_long m1_35;
  unsigned_long m_35;
  unsigned_long ht_34;
  unsigned_long lt_34;
  unsigned_long m1_34;
  unsigned_long m_34;
  unsigned_long ht_33;
  unsigned_long lt_33;
  unsigned_long m1_33;
  unsigned_long m_33;
  unsigned_long ht_32;
  unsigned_long lt_32;
  unsigned_long m1_32;
  unsigned_long m_32;
  unsigned_long ht_31;
  unsigned_long lt_31;
  unsigned_long m1_31;
  unsigned_long m_31;
  unsigned_long ht_30;
  unsigned_long lt_30;
  unsigned_long m1_30;
  unsigned_long m_30;
  unsigned_long ht_29;
  unsigned_long lt_29;
  unsigned_long m1_29;
  unsigned_long m_29;
  unsigned_long ht_28;
  unsigned_long lt_28;
  unsigned_long m1_28;
  unsigned_long m_28;
  unsigned_long ht_27;
  unsigned_long lt_27;
  unsigned_long m1_27;
  unsigned_long m_27;
  unsigned_long ht_26;
  unsigned_long lt_26;
  unsigned_long m1_26;
  unsigned_long m_26;
  unsigned_long ht_25;
  unsigned_long lt_25;
  unsigned_long m1_25;
  unsigned_long m_25;
  unsigned_long ht_24;
  unsigned_long lt_24;
  unsigned_long m1_24;
  unsigned_long m_24;
  unsigned_long ht_23;
  unsigned_long lt_23;
  unsigned_long m1_23;
  unsigned_long m_23;
  unsigned_long ht_22;
  unsigned_long lt_22;
  unsigned_long m1_22;
  unsigned_long m_22;
  unsigned_long ht_21;
  unsigned_long lt_21;
  unsigned_long m1_21;
  unsigned_long m_21;
  unsigned_long ht_20;
  unsigned_long lt_20;
  unsigned_long m1_20;
  unsigned_long m_20;
  unsigned_long ht_19;
  unsigned_long lt_19;
  unsigned_long m1_19;
  unsigned_long m_19;
  unsigned_long ht_18;
  unsigned_long lt_18;
  unsigned_long m1_18;
  unsigned_long m_18;
  unsigned_long ht_17;
  unsigned_long lt_17;
  unsigned_long m1_17;
  unsigned_long m_17;
  unsigned_long ht_16;
  unsigned_long lt_16;
  unsigned_long m1_16;
  unsigned_long m_16;
  unsigned_long ht_15;
  unsigned_long lt_15;
  unsigned_long m1_15;
  unsigned_long m_15;
  unsigned_long ht_14;
  unsigned_long lt_14;
  unsigned_long m1_14;
  unsigned_long m_14;
  unsigned_long ht_13;
  unsigned_long lt_13;
  unsigned_long m1_13;
  unsigned_long m_13;
  unsigned_long ht_12;
  unsigned_long lt_12;
  unsigned_long m1_12;
  unsigned_long m_12;
  unsigned_long ht_11;
  unsigned_long lt_11;
  unsigned_long m1_11;
  unsigned_long m_11;
  unsigned_long ht_10;
  unsigned_long lt_10;
  unsigned_long m1_10;
  unsigned_long m_10;
  unsigned_long ht_9;
  unsigned_long lt_9;
  unsigned_long m1_9;
  unsigned_long m_9;
  unsigned_long ht_8;
  unsigned_long lt_8;
  unsigned_long m1_8;
  unsigned_long m_8;
  unsigned_long ht_7;
  unsigned_long lt_7;
  unsigned_long m1_7;
  unsigned_long m_7;
  unsigned_long ht_6;
  unsigned_long lt_6;
  unsigned_long m1_6;
  unsigned_long m_6;
  unsigned_long ht_5;
  unsigned_long lt_5;
  unsigned_long m1_5;
  unsigned_long m_5;
  unsigned_long ht_4;
  unsigned_long lt_4;
  unsigned_long m1_4;
  unsigned_long m_4;
  unsigned_long ht_3;
  unsigned_long lt_3;
  unsigned_long m1_3;
  unsigned_long m_3;
  unsigned_long ht_2;
  unsigned_long lt_2;
  unsigned_long m1_2;
  unsigned_long m_2;
  unsigned_long ht_1;
  unsigned_long lt_1;
  unsigned_long m1_1;
  unsigned_long m_1;
  unsigned_long ht;
  unsigned_long lt;
  unsigned_long m1;
  unsigned_long m;
  unsigned_long c3;
  unsigned_long c2;
  unsigned_long c1;
  unsigned_long t2;
  unsigned_long t1;
  unsigned_long bh;
  unsigned_long bl;
  unsigned_long *b_local;
  unsigned_long *a_local;
  unsigned_long *r_local;
  
  uVar1 = *a >> 0x10 & 0xffff;
  uVar2 = *b >> 0x10 & 0xffff;
  uVar3 = (*b & 0xffff) * uVar1;
  ht = uVar2 * uVar1;
  uVar1 = uVar2 * (*a & 0xffff) + uVar3;
  uVar2 = uVar1 & 0xffffffff;
  if (uVar2 < uVar3) {
    ht = ht + 0x10000;
  }
  ht = (uVar2 >> 0x10) + ht;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar2 = (*b & 0xffff) * (*a & 0xffff) + uVar1 & 0xffffffff;
  if (uVar2 < uVar1) {
    ht = ht + 1;
  }
  c3 = (unsigned_long)((ht & 0xffffffff) < ht);
  *r = uVar2;
  uVar1 = *a >> 0x10 & 0xffff;
  uVar2 = b[1] >> 0x10 & 0xffff;
  uVar3 = (b[1] & 0xffff) * uVar1;
  ht_1 = uVar2 * uVar1;
  uVar1 = uVar2 * (*a & 0xffff) + uVar3;
  uVar2 = uVar1 & 0xffffffff;
  if (uVar2 < uVar3) {
    ht_1 = ht_1 + 0x10000;
  }
  ht_1 = (uVar2 >> 0x10) + ht_1;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar2 = (b[1] & 0xffff) * (*a & 0xffff) + uVar1 & 0xffffffff;
  if (uVar2 < uVar1) {
    ht_1 = ht_1 + 1;
  }
  t2 = ht_1;
  uVar1 = (ht & 0xffffffff) + uVar2 & 0xffffffff;
  if (uVar1 < uVar2) {
    t2 = ht_1 + 1;
  }
  uVar2 = c3 + t2 & 0xffffffff;
  c1 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = *b >> 0x10 & 0xffff;
  uVar5 = (*b & 0xffff) * uVar3;
  ht_2 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_2 = ht_2 + 0x10000;
  }
  ht_2 = (uVar4 >> 0x10) + ht_2;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (*b & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_2 = ht_2 + 1;
  }
  t2 = ht_2;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_2 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  r[1] = uVar1;
  uVar1 = a[2] >> 0x10 & 0xffff;
  uVar3 = *b >> 0x10 & 0xffff;
  uVar4 = (*b & 0xffff) * uVar1;
  ht_3 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[2] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_3 = ht_3 + 0x10000;
  }
  ht_3 = (uVar3 >> 0x10) + ht_3;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (*b & 0xffff) * (a[2] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_3 = ht_3 + 1;
  }
  t2 = ht_3;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_3 + 1;
  }
  uVar2 = c1 + t2 & 0xffffffff;
  c2 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = b[1] >> 0x10 & 0xffff;
  uVar5 = (b[1] & 0xffff) * uVar3;
  ht_4 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_4 = ht_4 + 0x10000;
  }
  ht_4 = (uVar4 >> 0x10) + ht_4;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[1] & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_4 = ht_4 + 1;
  }
  t2 = ht_4;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_4 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = *a >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_5 = uVar4 * uVar3;
  uVar3 = uVar4 * (*a & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_5 = ht_5 + 0x10000;
  }
  ht_5 = (uVar4 >> 0x10) + ht_5;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (*a & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_5 = ht_5 + 1;
  }
  t2 = ht_5;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_5 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  r[2] = uVar1;
  uVar1 = *a >> 0x10 & 0xffff;
  uVar3 = b[3] >> 0x10 & 0xffff;
  uVar4 = (b[3] & 0xffff) * uVar1;
  ht_6 = uVar3 * uVar1;
  uVar1 = uVar3 * (*a & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_6 = ht_6 + 0x10000;
  }
  ht_6 = (uVar3 >> 0x10) + ht_6;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[3] & 0xffff) * (*a & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_6 = ht_6 + 1;
  }
  t2 = ht_6;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_6 + 1;
  }
  uVar2 = c2 + t2 & 0xffffffff;
  c3 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_7 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_7 = ht_7 + 0x10000;
  }
  ht_7 = (uVar4 >> 0x10) + ht_7;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_7 = ht_7 + 1;
  }
  t2 = ht_7;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_7 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[2] >> 0x10 & 0xffff;
  uVar4 = b[1] >> 0x10 & 0xffff;
  uVar5 = (b[1] & 0xffff) * uVar3;
  ht_8 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[2] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_8 = ht_8 + 0x10000;
  }
  ht_8 = (uVar4 >> 0x10) + ht_8;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[1] & 0xffff) * (a[2] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_8 = ht_8 + 1;
  }
  t2 = ht_8;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_8 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = *b >> 0x10 & 0xffff;
  uVar5 = (*b & 0xffff) * uVar3;
  ht_9 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_9 = ht_9 + 0x10000;
  }
  ht_9 = (uVar4 >> 0x10) + ht_9;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (*b & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_9 = ht_9 + 1;
  }
  t2 = ht_9;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_9 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  r[3] = uVar1;
  uVar1 = a[4] >> 0x10 & 0xffff;
  uVar3 = *b >> 0x10 & 0xffff;
  uVar4 = (*b & 0xffff) * uVar1;
  ht_10 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[4] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_10 = ht_10 + 0x10000;
  }
  ht_10 = (uVar3 >> 0x10) + ht_10;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (*b & 0xffff) * (a[4] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_10 = ht_10 + 1;
  }
  t2 = ht_10;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_10 + 1;
  }
  uVar2 = c3 + t2 & 0xffffffff;
  c1 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = b[1] >> 0x10 & 0xffff;
  uVar5 = (b[1] & 0xffff) * uVar3;
  ht_11 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_11 = ht_11 + 0x10000;
  }
  ht_11 = (uVar4 >> 0x10) + ht_11;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[1] & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_11 = ht_11 + 1;
  }
  t2 = ht_11;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_11 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[2] >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_12 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[2] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_12 = ht_12 + 0x10000;
  }
  ht_12 = (uVar4 >> 0x10) + ht_12;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (a[2] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_12 = ht_12 + 1;
  }
  t2 = ht_12;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_12 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = b[3] >> 0x10 & 0xffff;
  uVar5 = (b[3] & 0xffff) * uVar3;
  ht_13 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_13 = ht_13 + 0x10000;
  }
  ht_13 = (uVar4 >> 0x10) + ht_13;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[3] & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_13 = ht_13 + 1;
  }
  t2 = ht_13;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_13 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = *a >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_14 = uVar4 * uVar3;
  uVar3 = uVar4 * (*a & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_14 = ht_14 + 0x10000;
  }
  ht_14 = (uVar4 >> 0x10) + ht_14;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (*a & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_14 = ht_14 + 1;
  }
  t2 = ht_14;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_14 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  r[4] = uVar1;
  uVar1 = *a >> 0x10 & 0xffff;
  uVar3 = b[5] >> 0x10 & 0xffff;
  uVar4 = (b[5] & 0xffff) * uVar1;
  ht_15 = uVar3 * uVar1;
  uVar1 = uVar3 * (*a & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_15 = ht_15 + 0x10000;
  }
  ht_15 = (uVar3 >> 0x10) + ht_15;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[5] & 0xffff) * (*a & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_15 = ht_15 + 1;
  }
  t2 = ht_15;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_15 + 1;
  }
  uVar2 = c1 + t2 & 0xffffffff;
  c2 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_16 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_16 = ht_16 + 0x10000;
  }
  ht_16 = (uVar4 >> 0x10) + ht_16;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_16 = ht_16 + 1;
  }
  t2 = ht_16;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_16 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[2] >> 0x10 & 0xffff;
  uVar4 = b[3] >> 0x10 & 0xffff;
  uVar5 = (b[3] & 0xffff) * uVar3;
  ht_17 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[2] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_17 = ht_17 + 0x10000;
  }
  ht_17 = (uVar4 >> 0x10) + ht_17;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[3] & 0xffff) * (a[2] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_17 = ht_17 + 1;
  }
  t2 = ht_17;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_17 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_18 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_18 = ht_18 + 0x10000;
  }
  ht_18 = (uVar4 >> 0x10) + ht_18;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_18 = ht_18 + 1;
  }
  t2 = ht_18;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_18 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[4] >> 0x10 & 0xffff;
  uVar4 = b[1] >> 0x10 & 0xffff;
  uVar5 = (b[1] & 0xffff) * uVar3;
  ht_19 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[4] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_19 = ht_19 + 0x10000;
  }
  ht_19 = (uVar4 >> 0x10) + ht_19;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[1] & 0xffff) * (a[4] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_19 = ht_19 + 1;
  }
  t2 = ht_19;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_19 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = *b >> 0x10 & 0xffff;
  uVar5 = (*b & 0xffff) * uVar3;
  ht_20 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_20 = ht_20 + 0x10000;
  }
  ht_20 = (uVar4 >> 0x10) + ht_20;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (*b & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_20 = ht_20 + 1;
  }
  t2 = ht_20;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_20 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  r[5] = uVar1;
  uVar1 = a[6] >> 0x10 & 0xffff;
  uVar3 = *b >> 0x10 & 0xffff;
  uVar4 = (*b & 0xffff) * uVar1;
  ht_21 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[6] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_21 = ht_21 + 0x10000;
  }
  ht_21 = (uVar3 >> 0x10) + ht_21;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (*b & 0xffff) * (a[6] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_21 = ht_21 + 1;
  }
  t2 = ht_21;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_21 + 1;
  }
  uVar2 = c2 + t2 & 0xffffffff;
  c3 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = b[1] >> 0x10 & 0xffff;
  uVar5 = (b[1] & 0xffff) * uVar3;
  ht_22 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_22 = ht_22 + 0x10000;
  }
  ht_22 = (uVar4 >> 0x10) + ht_22;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[1] & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_22 = ht_22 + 1;
  }
  t2 = ht_22;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_22 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[4] >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_23 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[4] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_23 = ht_23 + 0x10000;
  }
  ht_23 = (uVar4 >> 0x10) + ht_23;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (a[4] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_23 = ht_23 + 1;
  }
  t2 = ht_23;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_23 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = b[3] >> 0x10 & 0xffff;
  uVar5 = (b[3] & 0xffff) * uVar3;
  ht_24 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_24 = ht_24 + 0x10000;
  }
  ht_24 = (uVar4 >> 0x10) + ht_24;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[3] & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_24 = ht_24 + 1;
  }
  t2 = ht_24;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_24 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[2] >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_25 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[2] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_25 = ht_25 + 0x10000;
  }
  ht_25 = (uVar4 >> 0x10) + ht_25;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (a[2] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_25 = ht_25 + 1;
  }
  t2 = ht_25;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_25 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = b[5] >> 0x10 & 0xffff;
  uVar5 = (b[5] & 0xffff) * uVar3;
  ht_26 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_26 = ht_26 + 0x10000;
  }
  ht_26 = (uVar4 >> 0x10) + ht_26;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[5] & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_26 = ht_26 + 1;
  }
  t2 = ht_26;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_26 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = *a >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_27 = uVar4 * uVar3;
  uVar3 = uVar4 * (*a & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_27 = ht_27 + 0x10000;
  }
  ht_27 = (uVar4 >> 0x10) + ht_27;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (*a & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_27 = ht_27 + 1;
  }
  t2 = ht_27;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_27 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  r[6] = uVar1;
  uVar1 = *a >> 0x10 & 0xffff;
  uVar3 = b[7] >> 0x10 & 0xffff;
  uVar4 = (b[7] & 0xffff) * uVar1;
  ht_28 = uVar3 * uVar1;
  uVar1 = uVar3 * (*a & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_28 = ht_28 + 0x10000;
  }
  ht_28 = (uVar3 >> 0x10) + ht_28;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[7] & 0xffff) * (*a & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_28 = ht_28 + 1;
  }
  t2 = ht_28;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_28 + 1;
  }
  uVar2 = c3 + t2 & 0xffffffff;
  c1 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_29 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_29 = ht_29 + 0x10000;
  }
  ht_29 = (uVar4 >> 0x10) + ht_29;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_29 = ht_29 + 1;
  }
  t2 = ht_29;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_29 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[2] >> 0x10 & 0xffff;
  uVar4 = b[5] >> 0x10 & 0xffff;
  uVar5 = (b[5] & 0xffff) * uVar3;
  ht_30 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[2] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_30 = ht_30 + 0x10000;
  }
  ht_30 = (uVar4 >> 0x10) + ht_30;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[5] & 0xffff) * (a[2] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_30 = ht_30 + 1;
  }
  t2 = ht_30;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_30 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_31 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_31 = ht_31 + 0x10000;
  }
  ht_31 = (uVar4 >> 0x10) + ht_31;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_31 = ht_31 + 1;
  }
  t2 = ht_31;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_31 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[4] >> 0x10 & 0xffff;
  uVar4 = b[3] >> 0x10 & 0xffff;
  uVar5 = (b[3] & 0xffff) * uVar3;
  ht_32 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[4] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_32 = ht_32 + 0x10000;
  }
  ht_32 = (uVar4 >> 0x10) + ht_32;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[3] & 0xffff) * (a[4] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_32 = ht_32 + 1;
  }
  t2 = ht_32;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_32 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_33 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_33 = ht_33 + 0x10000;
  }
  ht_33 = (uVar4 >> 0x10) + ht_33;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_33 = ht_33 + 1;
  }
  t2 = ht_33;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_33 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[6] >> 0x10 & 0xffff;
  uVar4 = b[1] >> 0x10 & 0xffff;
  uVar5 = (b[1] & 0xffff) * uVar3;
  ht_34 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[6] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_34 = ht_34 + 0x10000;
  }
  ht_34 = (uVar4 >> 0x10) + ht_34;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[1] & 0xffff) * (a[6] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_34 = ht_34 + 1;
  }
  t2 = ht_34;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_34 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[7] >> 0x10 & 0xffff;
  uVar4 = *b >> 0x10 & 0xffff;
  uVar5 = (*b & 0xffff) * uVar3;
  ht_35 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[7] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_35 = ht_35 + 0x10000;
  }
  ht_35 = (uVar4 >> 0x10) + ht_35;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (*b & 0xffff) * (a[7] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_35 = ht_35 + 1;
  }
  t2 = ht_35;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_35 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  r[7] = uVar1;
  uVar1 = a[7] >> 0x10 & 0xffff;
  uVar3 = b[1] >> 0x10 & 0xffff;
  uVar4 = (b[1] & 0xffff) * uVar1;
  ht_36 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[7] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_36 = ht_36 + 0x10000;
  }
  ht_36 = (uVar3 >> 0x10) + ht_36;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[1] & 0xffff) * (a[7] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_36 = ht_36 + 1;
  }
  t2 = ht_36;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_36 + 1;
  }
  uVar2 = c1 + t2 & 0xffffffff;
  c2 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[6] >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_37 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[6] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_37 = ht_37 + 0x10000;
  }
  ht_37 = (uVar4 >> 0x10) + ht_37;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (a[6] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_37 = ht_37 + 1;
  }
  t2 = ht_37;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_37 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = b[3] >> 0x10 & 0xffff;
  uVar5 = (b[3] & 0xffff) * uVar3;
  ht_38 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_38 = ht_38 + 0x10000;
  }
  ht_38 = (uVar4 >> 0x10) + ht_38;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[3] & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_38 = ht_38 + 1;
  }
  t2 = ht_38;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_38 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[4] >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_39 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[4] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_39 = ht_39 + 0x10000;
  }
  ht_39 = (uVar4 >> 0x10) + ht_39;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (a[4] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_39 = ht_39 + 1;
  }
  t2 = ht_39;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_39 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = b[5] >> 0x10 & 0xffff;
  uVar5 = (b[5] & 0xffff) * uVar3;
  ht_40 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_40 = ht_40 + 0x10000;
  }
  ht_40 = (uVar4 >> 0x10) + ht_40;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[5] & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_40 = ht_40 + 1;
  }
  t2 = ht_40;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_40 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[2] >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_41 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[2] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_41 = ht_41 + 0x10000;
  }
  ht_41 = (uVar4 >> 0x10) + ht_41;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (a[2] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_41 = ht_41 + 1;
  }
  t2 = ht_41;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_41 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[1] >> 0x10 & 0xffff;
  uVar4 = b[7] >> 0x10 & 0xffff;
  uVar5 = (b[7] & 0xffff) * uVar3;
  ht_42 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[1] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_42 = ht_42 + 0x10000;
  }
  ht_42 = (uVar4 >> 0x10) + ht_42;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[7] & 0xffff) * (a[1] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_42 = ht_42 + 1;
  }
  t2 = ht_42;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_42 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  r[8] = uVar1;
  uVar1 = a[2] >> 0x10 & 0xffff;
  uVar3 = b[7] >> 0x10 & 0xffff;
  uVar4 = (b[7] & 0xffff) * uVar1;
  ht_43 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[2] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_43 = ht_43 + 0x10000;
  }
  ht_43 = (uVar3 >> 0x10) + ht_43;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[7] & 0xffff) * (a[2] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_43 = ht_43 + 1;
  }
  t2 = ht_43;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_43 + 1;
  }
  uVar2 = c2 + t2 & 0xffffffff;
  c3 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_44 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_44 = ht_44 + 0x10000;
  }
  ht_44 = (uVar4 >> 0x10) + ht_44;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_44 = ht_44 + 1;
  }
  t2 = ht_44;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_44 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[4] >> 0x10 & 0xffff;
  uVar4 = b[5] >> 0x10 & 0xffff;
  uVar5 = (b[5] & 0xffff) * uVar3;
  ht_45 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[4] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_45 = ht_45 + 0x10000;
  }
  ht_45 = (uVar4 >> 0x10) + ht_45;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[5] & 0xffff) * (a[4] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_45 = ht_45 + 1;
  }
  t2 = ht_45;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_45 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_46 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_46 = ht_46 + 0x10000;
  }
  ht_46 = (uVar4 >> 0x10) + ht_46;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_46 = ht_46 + 1;
  }
  t2 = ht_46;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_46 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[6] >> 0x10 & 0xffff;
  uVar4 = b[3] >> 0x10 & 0xffff;
  uVar5 = (b[3] & 0xffff) * uVar3;
  ht_47 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[6] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_47 = ht_47 + 0x10000;
  }
  ht_47 = (uVar4 >> 0x10) + ht_47;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[3] & 0xffff) * (a[6] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_47 = ht_47 + 1;
  }
  t2 = ht_47;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_47 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[7] >> 0x10 & 0xffff;
  uVar4 = b[2] >> 0x10 & 0xffff;
  uVar5 = (b[2] & 0xffff) * uVar3;
  ht_48 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[7] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_48 = ht_48 + 0x10000;
  }
  ht_48 = (uVar4 >> 0x10) + ht_48;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[2] & 0xffff) * (a[7] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_48 = ht_48 + 1;
  }
  t2 = ht_48;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_48 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  r[9] = uVar1;
  uVar1 = a[7] >> 0x10 & 0xffff;
  uVar3 = b[3] >> 0x10 & 0xffff;
  uVar4 = (b[3] & 0xffff) * uVar1;
  ht_49 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[7] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_49 = ht_49 + 0x10000;
  }
  ht_49 = (uVar3 >> 0x10) + ht_49;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[3] & 0xffff) * (a[7] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_49 = ht_49 + 1;
  }
  t2 = ht_49;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_49 + 1;
  }
  uVar2 = c3 + t2 & 0xffffffff;
  c1 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[6] >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_50 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[6] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_50 = ht_50 + 0x10000;
  }
  ht_50 = (uVar4 >> 0x10) + ht_50;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (a[6] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_50 = ht_50 + 1;
  }
  t2 = ht_50;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_50 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = b[5] >> 0x10 & 0xffff;
  uVar5 = (b[5] & 0xffff) * uVar3;
  ht_51 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_51 = ht_51 + 0x10000;
  }
  ht_51 = (uVar4 >> 0x10) + ht_51;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[5] & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_51 = ht_51 + 1;
  }
  t2 = ht_51;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_51 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[4] >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_52 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[4] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_52 = ht_52 + 0x10000;
  }
  ht_52 = (uVar4 >> 0x10) + ht_52;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (a[4] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_52 = ht_52 + 1;
  }
  t2 = ht_52;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_52 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  uVar3 = a[3] >> 0x10 & 0xffff;
  uVar4 = b[7] >> 0x10 & 0xffff;
  uVar5 = (b[7] & 0xffff) * uVar3;
  ht_53 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[3] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_53 = ht_53 + 0x10000;
  }
  ht_53 = (uVar4 >> 0x10) + ht_53;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[7] & 0xffff) * (a[3] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_53 = ht_53 + 1;
  }
  t2 = ht_53;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_53 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  r[10] = uVar1;
  uVar1 = a[4] >> 0x10 & 0xffff;
  uVar3 = b[7] >> 0x10 & 0xffff;
  uVar4 = (b[7] & 0xffff) * uVar1;
  ht_54 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[4] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_54 = ht_54 + 0x10000;
  }
  ht_54 = (uVar3 >> 0x10) + ht_54;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[7] & 0xffff) * (a[4] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_54 = ht_54 + 1;
  }
  t2 = ht_54;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_54 + 1;
  }
  uVar2 = c1 + t2 & 0xffffffff;
  c2 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_55 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_55 = ht_55 + 0x10000;
  }
  ht_55 = (uVar4 >> 0x10) + ht_55;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_55 = ht_55 + 1;
  }
  t2 = ht_55;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_55 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[6] >> 0x10 & 0xffff;
  uVar4 = b[5] >> 0x10 & 0xffff;
  uVar5 = (b[5] & 0xffff) * uVar3;
  ht_56 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[6] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_56 = ht_56 + 0x10000;
  }
  ht_56 = (uVar4 >> 0x10) + ht_56;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[5] & 0xffff) * (a[6] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_56 = ht_56 + 1;
  }
  t2 = ht_56;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_56 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  uVar3 = a[7] >> 0x10 & 0xffff;
  uVar4 = b[4] >> 0x10 & 0xffff;
  uVar5 = (b[4] & 0xffff) * uVar3;
  ht_57 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[7] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_57 = ht_57 + 0x10000;
  }
  ht_57 = (uVar4 >> 0x10) + ht_57;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[4] & 0xffff) * (a[7] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_57 = ht_57 + 1;
  }
  t2 = ht_57;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_57 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c2 = c2 + 1;
  }
  r[0xb] = uVar1;
  uVar1 = a[7] >> 0x10 & 0xffff;
  uVar3 = b[5] >> 0x10 & 0xffff;
  uVar4 = (b[5] & 0xffff) * uVar1;
  ht_58 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[7] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_58 = ht_58 + 0x10000;
  }
  ht_58 = (uVar3 >> 0x10) + ht_58;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[5] & 0xffff) * (a[7] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_58 = ht_58 + 1;
  }
  t2 = ht_58;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_58 + 1;
  }
  uVar2 = c2 + t2 & 0xffffffff;
  c3 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[6] >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_59 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[6] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_59 = ht_59 + 0x10000;
  }
  ht_59 = (uVar4 >> 0x10) + ht_59;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (a[6] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_59 = ht_59 + 1;
  }
  t2 = ht_59;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_59 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  uVar3 = a[5] >> 0x10 & 0xffff;
  uVar4 = b[7] >> 0x10 & 0xffff;
  uVar5 = (b[7] & 0xffff) * uVar3;
  ht_60 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[5] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_60 = ht_60 + 0x10000;
  }
  ht_60 = (uVar4 >> 0x10) + ht_60;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[7] & 0xffff) * (a[5] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_60 = ht_60 + 1;
  }
  t2 = ht_60;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_60 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c3 = c3 + 1;
  }
  r[0xc] = uVar1;
  uVar1 = a[6] >> 0x10 & 0xffff;
  uVar3 = b[7] >> 0x10 & 0xffff;
  uVar4 = (b[7] & 0xffff) * uVar1;
  ht_61 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[6] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_61 = ht_61 + 0x10000;
  }
  ht_61 = (uVar3 >> 0x10) + ht_61;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[7] & 0xffff) * (a[6] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_61 = ht_61 + 1;
  }
  t2 = ht_61;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_61 + 1;
  }
  uVar2 = c3 + t2 & 0xffffffff;
  c1 = (unsigned_long)(uVar2 < t2);
  uVar3 = a[7] >> 0x10 & 0xffff;
  uVar4 = b[6] >> 0x10 & 0xffff;
  uVar5 = (b[6] & 0xffff) * uVar3;
  ht_62 = uVar4 * uVar3;
  uVar3 = uVar4 * (a[7] & 0xffff) + uVar5;
  uVar4 = uVar3 & 0xffffffff;
  if (uVar4 < uVar5) {
    ht_62 = ht_62 + 0x10000;
  }
  ht_62 = (uVar4 >> 0x10) + ht_62;
  uVar3 = (uVar3 & 0xffff) * 0x10000;
  uVar4 = (b[6] & 0xffff) * (a[7] & 0xffff) + uVar3 & 0xffffffff;
  if (uVar4 < uVar3) {
    ht_62 = ht_62 + 1;
  }
  t2 = ht_62;
  uVar1 = uVar1 + uVar4 & 0xffffffff;
  if (uVar1 < uVar4) {
    t2 = ht_62 + 1;
  }
  uVar2 = uVar2 + t2 & 0xffffffff;
  if (uVar2 < t2) {
    c1 = c1 + 1;
  }
  r[0xd] = uVar1;
  uVar1 = a[7] >> 0x10 & 0xffff;
  uVar3 = b[7] >> 0x10 & 0xffff;
  uVar4 = (b[7] & 0xffff) * uVar1;
  ht_63 = uVar3 * uVar1;
  uVar1 = uVar3 * (a[7] & 0xffff) + uVar4;
  uVar3 = uVar1 & 0xffffffff;
  if (uVar3 < uVar4) {
    ht_63 = ht_63 + 0x10000;
  }
  ht_63 = (uVar3 >> 0x10) + ht_63;
  uVar1 = (uVar1 & 0xffff) * 0x10000;
  uVar3 = (b[7] & 0xffff) * (a[7] & 0xffff) + uVar1 & 0xffffffff;
  if (uVar3 < uVar1) {
    ht_63 = ht_63 + 1;
  }
  t2 = ht_63;
  uVar1 = uVar2 + uVar3 & 0xffffffff;
  if (uVar1 < uVar3) {
    t2 = ht_63 + 1;
  }
  r[0xe] = uVar1;
  r[0xf] = c1 + t2 & 0xffffffff;
  return;
}