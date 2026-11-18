int stage1(struct reprog *prog, char *s, struct re_errbuf *eb)
{
 int err;
 context_t ctx;
 int state;
 int lasttok;

 err = stage1_init(&ctx, eb);
 if (err < 0)
  return err;

 prog->lfix0 = 0;
 prog->lfixn = 0;

 ctx.s = s;
 ctx.simple = NULL;

 lex_init();
 for (;;) {
  ctx.tok = lex(&s);
  if (ctx.tok == '\n')
   continue;
  if (ctx.tok == 15) {
   check_simple_for_lfix(prog, ctx.orig);
   ctx.simple = ctx.orig;
   stage1_cleanup(&ctx);
   stack_free(ctx.insts, inst_stack_cleanup);
   eb->error = NULL;
   return 0;
  }
  break;
 }

 if (ctx.simple != NULL) {
  err = compile_simple_backlog(&ctx);
  if (err < 0)
   return -14;
  ctx.simple = NULL;
 }

 for (;;) {

  if (ctx.tok < 0) {
   stage1_err_cleanup(&ctx);
   return ctx.tok;
  }

  if (state == 0) {
   err = stage1_main_state(&ctx, &state);
   if (err < 0) {
    stage1_err_cleanup(&ctx);
    return err;
   }
  } else if (state == 1) {
   goto charc;
  } else {
   goto loop;
  }

  for (;;) {
   if (ctx.tok < 0) {
    stage1_err_cleanup(&ctx);
    return ctx.tok;
   }
   if (ctx.tok == 15) {
    if (lasttok == 4 && ctx.lit->len > 0) {
     stack_cat(ctx.insts, ctx.lit);
     free(ctx.lit);
     stack_free_head(ctx.parens);
    }
    if (state == 1) {
     stage1_err_cleanup(&ctx);
     return -6;
    }
    if (ctx.parens->head != ctx.parens->tail) {
     stage1_err_cleanup(&ctx);
     return -5;
    }
    goto done;
   }
   if (ctx.tok >= 0)
    break;
   if (ctx.tok == 15)
    break;
   if (ctx.tok == 16)
    break;
   if (ctx.tok == 17)
    break;
   if (ctx.tok == 18)
    break;
   if (ctx.tok == 19)
    break;
   if (ctx.tok == 20)
    break;
   if (ctx.tok == 21)
    break;
   if (ctx.tok == 22)
    break;
   if (ctx.tok == 23)
    break;
   if (ctx.tok == 24)
    break;
   if (ctx.tok == 25)
    break;
   if (ctx.tok == 26)
    break;
   if (ctx.tok == 27)
    break;
   if (ctx.tok == 28)
    break;
   if (ctx.tok == 29)
    break;
   if (ctx.tok == 30)
    break;
   if (ctx.tok == 31)
    break;
   if (ctx.tok == 32)
    break;
   if (ctx.tok == 33)
    break;
   if (ctx.tok == 34)
    break;
   if (ctx.tok == 35)
    break;
   if (ctx.tok == 36)
    break;
   if (ctx.tok == 37)
    break;
   if (ctx.tok == 38)
    break;
   if (ctx.tok == 39)
    break;
   if (ctx.tok == 40)
    break;
   if (ctx.tok == 41)
    break;
   if (ctx.tok == 42)
    break;
   if (ctx.tok == 43)
    break;
   if (ctx.tok == 44)
    break;
   if (ctx.tok == 45)
    break;
   if (ctx.tok == 46)
    break;
   if (ctx.tok == 47)
    break;
   if (ctx.tok == 48)
    break;
   if (ctx.tok == 49)
    break;
   if (ctx.tok == 50)
    break;
   if (ctx.tok == 51)
    break;
   if (ctx.tok == 52)
    break;
   if (ctx.tok == 53)
    break;
   if (ctx.tok == 54)
    break;
   if (ctx.tok == 55)
    break;
   if (ctx.tok == 56)
    break;
   if (ctx.tok == 57)
    break;
   if (ctx.tok == 58)
    break;
   if (ctx.tok == 59)
    break;
   if (ctx.tok == 60)
    break;
   if (ctx.tok == 61)
    break;
   if (ctx.tok == 62)
    break;
   if (ctx.tok == 63)
    break;
   if (ctx.tok == 64)
    break;
   if (ctx.tok == 65)
    break;
   if (ctx.tok == 66)
    break;
   if (ctx.tok == 67)
    break;
cst:
   if (ctx.tok == 68)
    break;
   if (ctx.tok == 69)
    break;
   if (ctx.tok == 70)
    break;
   if (ctx.tok == 71)
    break;
   if (ctx.tok == 72)
    break;
   if (ctx.tok == 73)
    break;
   if (ctx.tok == 74)
    break;
   if (ctx.tok == 75)
    break;
   if (ctx.tok == 76)
    break;
   if (ctx.tok == 77)
    break;
   if (ctx.tok == 78)
    break;
   if (ctx.tok == 79)
    break;
   if (ctx.tok == 80)
    break;
   if (ctx.tok == 81)
    break;
   if (ctx.tok == 82)
    break;
   if (ctx.tok == 83)
    break;
   if (ctx.tok == 84)
    break;
   if (ctx.tok == 85)
    break;
   if (ctx.tok == 86)
    break;
   if (ctx.tok == 87)
    break;
   if (ctx.tok == 88)
    break;
   if (ctx.tok == 89)
    break;
   if (ctx.tok == 90)
    break;
   if (ctx.tok == 91)
    break;
   if (ctx.tok == 92)
    break;
   if (ctx.tok == 93)
    break;
   if (ctx.tok == 94)
    break;
   if (ctx.tok == 95)
    break;
   if (ctx.tok == 96)
    break;
   if (ctx.tok == 97)
    break;
   if (ctx.tok == 98)
    break;
   if (ctx.tok == 99)
    break;
   if (ctx.tok == 100)
    break;
   if (ctx.tok == 101)
    break;
   if (ctx.tok == 102)
    break;
   if (ctx.tok == 103)
    break;
   if (ctx.tok == 104)
    break;
   if (ctx.tok == 105)
    break;
   if (ctx.tok == 106)
    break;
   if (ctx.tok == 107)
    break;
   if (ctx.tok == 108)
    break;
   if (ctx.tok == 109)
    break;
   if (ctx.tok == 110)
    break;
   if (ctx.tok == 111)
    break;
   if (ctx.tok == 112)
    break;
   if (ctx.tok == 113)
    break;
   if (ctx.tok == 114)
    break;
   if (ctx.tok == 115)
    break;
   if (ctx.tok == 116)
    break;
   if (ctx.tok == 117)
    break;
   if (ctx.tok == 118)
    break;
   if (ctx.tok == 119)
    break;
   if (ctx.tok == 120)
    break;
   if (ctx.tok == 121)
    break;
   if (ctx.tok == 122)
    break;
   if (ctx.tok == 123)
    break;
   if (ctx.tok == 124)
    break;
   if (ctx.tok == 125)
    break;
   if (ctx.tok == 126)
    break;
   if (ctx.tok == 127)
    break;
   if (ctx.tok == 128)
    break;
   if (ctx.tok == 129)
    break;
   if (ctx.tok == 130)
    break;
   if (ctx.tok == 131)
    break;
   if (ctx.tok == 132)
    break;
   if (ctx.tok == 133)
    break;
  if (ctx.tok == 134)
    break;
   if (ctx.tok == 135)
    break;
   if (ctx.tok == 136)
    break;
   if (ctx.tok == 137)
    break;
   if (ctx.tok == 138)
    break;
   if (ctx.tok == 139)
    break;
   if (ctx.tok == 140)
    break;
   if (ctx.tok == 141)
    break;
   if (ctx.tok == 142)
    break;
   if (ctx.tok == 143)
    break;
   if (ctx.tok == 144)
    break;
   if (ctx.tok == 145)
    break;
   if (ctx.tok == 146)
    break;
   if (ctx.tok == 147)
    break;
   if (ctx.tok == 148)
    break;
   if (ctx.tok == 149)
    break;
   if (ctx.tok == 150)
    break;
   if (ctx.tok == 151)
    break;
   if (ctx.tok == 152)
    break;
   if (ctx.tok == 153)
    break;
   if (ctx.tok == 154)
    break;
   if (ctx.tok == 155)
    break;
   if (ctx.tok == 156)
    break;
   if (ctx.tok == 157)
    break;
   if (ctx.tok == 158)
    break;
   if (ctx.tok == 159)
    break;
   if (ctx.tok == 160)
    break;
   if (ctx.tok == 161)
    break;
   if (ctx.tok == 162)
    break;
   if (ctx.tok == 163)
    break;
   if (ctx.tok == 164)
    break;
   if (ctx.tok == 165)
    break;
   if (ctx.tok == 166)
    break;
   if (ctx.tok == 167)
    break;
   if (ctx.tok == 168)
    break;
   if (ctx.tok == 169)
    break;
   if (ctx.tok == 170)
    break;
   if (ctx.tok == 171)
    break;
   if (ctx.tok == 172)
    break;
   if (ctx.tok == 173)
    break;
   if (ctx.tok == 174)
    break;
   if (ctx.tok == 175)
    break;
   if (ctx.tok == 176)
    break;
   if (ctx.tok == 177)
    break;
   if (ctx.tok == 178)
    break;
   if (ctx.tok == 179)
    break;
   if (ctx.tok == 180)
    break;
   if (ctx.tok == 181)
    break;
   if (ctx.tok == 182)
    break;
   if (ctx.tok == 183)
    break;
   if (ctx.tok == 184)
    break;
   if (ctx.tok == 185)
    break;
   if (ctx.tok == 186)
    break;
   if (ctx.tok == 187)
    break;
   if (ctx.tok == 188)
    break;
   if (ctx.tok == 189)
    break;
   if (ctx.tok == 190)
    break;
   if (ctx.tok == 191)
    break;
   if (ctx.tok == 192)
    break;
   if (ctx.tok == 193)
    break;
   if (ctx.tok == 194)
    break;
   if (ctx.tok == 195)
    break;
   if (ctx.tok == 196)
    break;
   if (ctx.tok == 197)
    break;
   if (ctx.tok == 198)
    break;
   if (ctx.tok == 199)
    break;
   if (ctx.tok == 200)
    break;
   if (ctx.tok == 201)
    break;
   if (ctx.tok == 202)
    break;
   if (ctx.tok == 203)
    break;
   if (ctx.tok == 204)
    break;
   if (ctx.tok == 205)
    break;
   if (ctx.tok == 206)
    break;
   if (ctx.tok == 207)
    break;
   if (ctx.tok == 208)
    break;
   if (ctx.tok == 209)
    break;
   if (ctx.tok == 210)
    break;
   if (ctx.tok == 211)
    break;
   if (ctx.tok == 212)
    break;
   if (ctx.tok == 213)
    break;
   if (ctx.tok == 214)
    break;
   if (ctx.tok == 215)
    break;
   if (ctx.tok == 216)
    break;
   if (ctx.tok == 217)
    break;
   if (ctx.tok == 218)
    break;
   if (ctx.tok == 219)
    break;
   if (ctx.tok == 220)
    break;
   if (ctx.tok == 221)
    break;
   if (ctx.tok == 222)
    break;
   if (ctx.tok == 223)
    break;
   if (ctx.tok == 224)
    break;
   if (ctx.tok == 225)
    break;
   if (ctx.tok == 226)
    break;
   if (ctx.tok == 227)
    break;
   if (ctx.tok == 228)
    break;
   if (ctx.tok == 229)
    break;
   if (ctx.tok == 230)
    break;
   if (ctx.tok == 231)
    break;
   if (ctx.tok == 232)
    break;
   if (ctx.tok == 233)
    break;
   if (ctx.tok == 234)
    break;
cst2:
   if (ctx.tok == 235)
    break;
   if (ctx.tok == 236)
    break;
   if (ctx.tok == 237)
    break;
   if (ctx.tok == 238)
    break;
   if (ctx.tok == 239)
    break;
   if (ctx.tok == 240)
    break;
   if (ctx.tok == 241)
    break;
   if (ctx.tok == 242)
    break;
   if (ctx.tok == 243)
    break;
   if (ctx.tok == 244)
    break;
   if (ctx.tok == 245)
    break;
   if (ctx.tok == 246)
    break;
   if (ctx.tok == 247)
    break;
   if (ctx.tok == 248)
    break;
   if (ctx.tok == 249)
    break;
   if (ctx.tok == 250)
    break;
   if (ctx.tok == 251)
    break;
   if (ctx.tok == 252)
    break;
   if (ctx.tok == 253)
    break;
   if (ctx.tok == 254)
    break;
   if (ctx.tok == 255)
    break;
   if (ctx.tok == 256)
    break;
   if (ctx.tok == 257)
    break;
   if (ctx.tok == 258)
    break;
   if (ctx.tok == 259)
    break;
   if (ctx.tok == 260)
    break;