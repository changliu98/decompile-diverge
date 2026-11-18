{
  int bit ;
  int __cil_tmp3 ;
  int __cil_tmp4 ;
  int __cil_tmp5 ;
  int __cil_tmp6 ;
  int __cil_tmp7 ;
  int __cil_tmp8 ;
  int __cil_tmp9 ;
  int __cil_tmp10 ;
  int __cil_tmp11 ;
  int __cil_tmp12 ;
  int __cil_tmp13 ;
  int __cil_tmp14 ;
  int __cil_tmp15 ;
  int __cil_tmp16 ;
  int __cil_tmp17 ;
  int __cil_tmp18 ;
  int __cil_tmp19 ;
  int __cil_tmp20 ;
  int __cil_tmp21 ;
  int __cil_tmp22 ;
  int __cil_tmp23 ;
  int __cil_tmp24 ;
  int __cil_tmp25 ;
  int __cil_tmp26 ;
  int __cil_tmp27 ;
  int __cil_tmp28 ;
  int __cil_tmp29 ;
  int __cil_tmp30 ;
  int __cil_tmp31 ;
  int __cil_tmp32 ;
  int __cil_tmp33 ;
  int __cil_tmp34 ;
  int __cil_tmp35 ;
  int __cil_tmp36 ;
  int __cil_tmp37 ;
  int __cil_tmp38 ;
  int __cil_tmp39 ;
  int __cil_tmp40 ;
  int __cil_tmp41 ;
  int __cil_tmp42 ;
m_109 :
  if (bit < 64) {
    goto m_110;
  } else {
    {
      goto m_111;
    }
  }
  m_110:
  {
    __cil_tmp3 = nr & 63UL;
    bit = (int )__cil_tmp3;
    __cil_tmp4 = nr >> 6;
    __cil_tmp5 = (unsigned long )(addr) + __cil_tmp4 * 8UL;
    __cil_tmp6 = *((unsigned long *)__cil_tmp5);
    __cil_tmp7 = 1UL << bit;
    __cil_tmp8 = ~ __cil_tmp7;
    __cil_tmp9 = (unsigned long )__cil_tmp8;
    __cil_tmp10 = __cil_tmp9 & __cil_tmp6;
    __cil_tmp11 = (unsigned long )(addr) + __cil_tmp4 * 8UL;
    *((unsigned long *)__cil_tmp11) = __cil_tmp10;
  }
  return;

  m_111:
  {
    __cil_tmp12 = nr & 63UL;
    bit = (int )__cil_tmp12;
    __cil_tmp13 = nr >> 6;
    __cil_tmp14 = (unsigned long )(addr) + __cil_tmp13 * 8UL;
    __cil_tmp15 = *((unsigned long *)__cil_tmp14);
    __cil_tmp16 = 1UL << bit;
    __cil_tmp17 = ~ __cil_tmp16;
    __cil_tmp18 = (unsigned long )__cil_tmp17;
    __cil_tmp19 = __cil_tmp18 & __cil_tmp15;
    __cil_tmp20 = (unsigned long )(addr) + __cil_tmp13 * 8UL;
    *((unsigned long *)__cil_tmp20) = __cil_tmp19;
  }
  return;

  m_120:
  {
    __cil_tmp21 = nr & 63UL;
    bit = (int )__cil_tmp21;
    __cil_tmp22 = nr >> 6;
    __cil_tmp23 = (unsigned long )(addr) + __cil_tmp22 * 8UL;
    __cil_tmp24 = *((unsigned long *)__cil_tmp23);
    __cil_tmp25 = 1UL << bit;
    __cil_tmp26 = ~ __cil_tmp25;
    __cil_tmp27 = (unsigned long )__cil_tmp26;
    __cil_tmp28 = __cil_tmp27 & __cil_tmp24;
    __cil_tmp29 = (unsigned long )(addr) + __cil_tmp22 * 8UL;
    *((unsigned long *)__cil_tmp29) = __cil_tmp28;
  }
  return;

  m_130:
  {
    __cil_tmp30 = nr & 63UL;
    bit = (int )__cil_tmp30;
    __cil_tmp31 = nr >> 6;
    __cil_tmp32 = (unsigned long )(addr) + __cil_tmp31 * 8UL;
    __cil_tmp33 = *((unsigned long *)__cil_tmp32);
    __cil_tmp34 = 1UL << bit;
    __cil_tmp35 = ~ __cil_tmp34;
    __cil_tmp36 = (unsigned long )__cil_tmp35;
    __cil_tmp37 = __cil_tmp36 & __cil_tmp33;
    __cil_tmp38 = (unsigned long )(addr) + __cil_tmp31 * 8UL;
    *((unsigned long *)__cil_tmp38) = __cil_tmp37;
  }
  return;

  m_140:
  {
    __cil_tmp39 = nr & 63UL;
    bit = (int )__cil_tmp39;
    __cil_tmp40 = nr >> 6;
    __cil_tmp41 = (unsigned long )(addr) + __cil_tmp40 * 8UL;
    __cil_tmp42 = *((unsigned long *)__cil_tmp41);
    __cil_tmp43 = 1UL << bit;
    __cil_tmp44 = ~ __cil_tmp43;
    __cil_tmp45 = (unsigned long )__cil_tmp44;
    __cil_tmp46 = __cil_tmp45 & __cil_tmp42;
    __cil_tmp47 = (unsigned long )(addr) + __cil_tmp40 * 8UL;
    *((unsigned long *)__cil_tmp47) = __cil_tmp46;
  }
  return;

  m_150:
  {
    __cil_tmp48 = nr & 63UL;
    bit = (int )__cil_tmp48;
    __cil_tmp49 = nr >> 6;
    __cil_tmp50 = (unsigned long )(addr) + __cil_tmp49 * 8UL;
    __cil_tmp51 = *((unsigned long *)__cil_tmp50);
    __cil_tmp52 = 1UL << bit;
    __cil_tmp53 = ~ __cil_tmp52;
    __cil_tmp54 = (unsigned long )__cil_tmp53;
    __cil_tmp55 = __cil_tmp54 & __cil_tmp51;
    __cil_tmp56 = (unsigned long )(addr) + __cil_tmp49 * 8UL;
    *((unsigned long *)__cil_tmp56) = __cil_tmp55;
  }
  return;

  m_160:
  {
    __cil_tmp57 = nr & 63UL;
    bit = (int )__cil_tmp57;
    __cil_tmp58 = nr >> 6;
    __cil_tmp59 = (unsigned long )(addr) + __cil_tmp58 * 8UL;
    __cil_tmp60 = *((unsigned long *)__cil_tmp59);
    __cil_tmp61 = 1UL << bit;
    __cil_tmp62 = ~ __cil_tmp61;
    __cil_tmp63 = (unsigned long )__cil_tmp62;
    __cil_tmp64 = __cil_tmp63 & __cil_tmp60;
    __cil_tmp65 = (unsigned long )(addr) + __cil_tmp58 * 8UL;
    *((unsigned long *)__cil_tmp65) = __cil_tmp64;
  }
  return;

  m_170:
  {
    __cil_tmp66 = nr & 63UL;
    bit = (int )__cil_tmp66;
    __cil_tmp67 = nr >> 6;
    __cil_tmp68 = (unsigned long )(addr) + __cil_tmp67 * 8UL;
    __cil_tmp69 = *((unsigned long *)__cil_tmp68);
    __cil_tmp70 = 1UL << bit;
    __cil_tmp71 = ~ __cil_tmp70;
    __cil_tmp72 = (unsigned long )__cil_tmp71;
    __cil_tmp73 = __cil_tmp72 & __cil_tmp69;
    __cil_tmp74 = (unsigned long )(addr) + __cil_tmp67 * 8UL;
    *((unsigned long *)__cil_tmp74) = __cil_tmp73;
  }
  return;

  m_180:
  {
    __cil_tmp75 = nr & 63UL;
    bit = (int )__cil_tmp75;
    __cil_tmp76 = nr >> 6;
    __cil_tmp77 = (unsigned long )(addr) + __cil_tmp76 * 8UL;
    __cil_tmp78 = *((unsigned long *)__cil_tmp77);
    __cil_tmp79 = 1UL << bit;
    __cil_tmp80 = ~ __cil_tmp79;
    __cil_tmp81 = (unsigned long )__cil_tmp80;
    __cil_tmp82 = __cil_tmp81 & __cil_tmp78;
    __cil_tmp83 = (unsigned long )(addr) + __cil_tmp76 * 8UL;
    *((unsigned long *)__cil_tmp83) = __cil_tmp82;
  }
  return;

  m_190:
  {
    __cil_tmp84 = nr & 63UL;
    bit = (int )__cil_tmp84;
    __cil_tmp85 = nr >> 6;
    __cil_tmp86 = (unsigned long )(addr) + __cil_tmp85 * 8UL;
    __cil_tmp87 = *((unsigned long *)__cil_tmp86);
    __cil_tmp88 = 1UL << bit;
    __cil_tmp89 = ~ __cil_tmp88;
    __cil_tmp90 = (unsigned long )__cil_tmp89;
    __cil_tmp91 = __cil_tmp90 & __cil_tmp87;
    __cil_tmp92 = (unsigned long )(addr) + __cil_tmp85 * 8UL;
    *((unsigned long *)__cil_tmp92) = __cil_tmp91;
  }
  return;

  m_200:
  {
    __cil_tmp93 = nr & 63UL;
    bit = (int )__cil_tmp93;
    __cil_tmp94 = nr >> 6;
    __cil_tmp95 = (unsigned long )(addr) + __cil_tmp94 * 8UL;
    __cil_tmp96 = *((unsigned long *)__cil_tmp95);
    __cil_tmp97 = 1UL << bit;
    __cil_tmp98 = ~ __cil_tmp97;
    __cil_tmp99 = (unsigned long )__cil_tmp98;
    __cil_tmp100 = __cil_tmp99 & __cil_tmp96;
    __cil_tmp101 = (unsigned long )(addr) + __cil_tmp94 * 8UL;
    *((unsigned long *)__cil_tmp101) = __cil_tmp100;
  }
  return;

  m_210:
  {
    __cil_tmp102 = nr & 63UL;
    bit = (int )__cil_tmp102;
    __cil_tmp103 = nr >> 6;
    __cil_tmp104 = (unsigned long )(addr) + __cil_tmp103 * 8UL;
    __cil_tmp105 = *((unsigned long *)__cil_tmp104);
    __cil_tmp106 = 1UL << bit;
    __cil_tmp107 = ~ __cil_tmp106;
    __cil_tmp108 = (unsigned long )__cil_tmp107;
    __cil_tmp109 = __cil_tmp108 & __cil_tmp105;
    __cil_tmp110 = (unsigned long )(addr) + __cil_tmp103 * 8UL;
    *((unsigned long *)__cil_tmp110) = __cil_tmp109;
  }
  return;

  m_220:
  {
    __cil_tmp111 = nr & 63UL;
    bit = (int )__cil_tmp111;
    __cil_tmp112 = nr >> 6;
    __cil_tmp113 = (unsigned long )(addr) + __cil_tmp112 * 8UL;
    __cil_tmp114 = *((unsigned long *)__cil_tmp113);
    __cil_tmp115 = 1UL << bit;
    __cil_tmp116 = ~ __cil_tmp115;
    __cil_tmp117 = (unsigned long )__cil_tmp116;
    __cil_tmp118 = __cil_tmp117 & __cil_tmp114;
    __cil_tmp119 = (unsigned long )(addr) + __cil_tmp112 * 8UL;
    *((unsigned long *)__cil_tmp119) = __cil_tmp118;
  }
  return;

  m_230:
  {
    __cil_tmp120 = nr & 63UL;
    bit = (int )__cil_tmp120;
    __cil_tmp121 = nr >> 6;
    __cil_tmp122 = (unsigned long )(addr) + __cil_tmp121 * 8UL;
    __cil_tmp123 = *((unsigned long *)__cil_tmp122);
    __cil_tmp124 = 1UL << bit;
    __cil_tmp125 = ~ __cil_tmp124;
    __cil_tmp126 = (unsigned long )__cil_tmp125;
    __cil_tmp127 = __cil_tmp126 & __cil_tmp123;
    __cil_tmp128 = (unsigned long )(addr) + __cil_tmp121 * 8UL;
    *((unsigned long *)__cil_tmp128) = __cil_tmp127;
  }
  return;

  m_240:
  {
    __cil_tmp129 = nr & 63UL;
    bit = (int )__cil_tmp129;
    __cil_tmp130 = nr >> 6;
    __cil_tmp131 = (unsigned long )(addr) + __cil_tmp130 * 8UL;
    __cil_tmp132 = *((unsigned long *)__cil_tmp131);
    __cil_tmp133 = 1UL << bit;
    __cil_tmp134 = ~ __cil_tmp133;
    __cil_tmp135 = (unsigned long )__cil_tmp134;
    __cil_tmp136 = __cil_tmp135 & __cil_tmp132;
    __cil_tmp137 = (unsigned long )(addr) + __cil_tmp130 * 8UL;
    *((unsigned long *)__cil_tmp137) = __cil_tmp136;
  }
  return;

  m_250:
  {
    __cil_tmp138 = nr & 63UL;
    bit = (int )__cil_tmp138;
    __cil_tmp139 = nr >> 6;
    __cil_tmp140 = (unsigned long )(addr) + __cil_tmp139 * 8UL;
    __cil_tmp141 = *((unsigned long *)__cil_tmp140);
    __cil_tmp142 = 1UL << bit;
    __cil_tmp143 = ~ __cil_tmp142;
    __cil_tmp144 = (unsigned long )__cilmp_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000000_0000000000000