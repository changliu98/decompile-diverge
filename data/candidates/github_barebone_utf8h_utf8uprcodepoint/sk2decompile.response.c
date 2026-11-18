static lua_Unsigned utf8uprcodepoint(lua_Unsigned c) {
  lua_Unsigned r = c;
  if ((c >= 97 && c <= 122) || (c >= 224 && c <= 246) ||
      (c >= 248 && c <= 254) || (c >= 945 && c <= 961) ||
      (c >= 963 && c <= 971) || (c >= 1072 && c <= 1103)) {
    r = c - 32;
  } else if (c >= 1104 && c <= 1119) {
    r = c - 80;
  } else if ((c >= 256 && c <= 303) || (c >= 306 && c <= 311) ||
             (c >= 330 && c <= 375) || (c >= 386 && c <= 389) ||
             (c >= 416 && c <= 421) || (c >= 478 && c <= 495) ||
             (c >= 504 && c <= 543) || (c >= 546 && c <= 563) ||
             (c >= 582 && c <= 591) || (c >= 984 && c <= 1007) ||
             (c >= 1120 && c <= 1153) || (c >= 1162 && c <= 1279)) {
    r = c & 0xFFFFFFFE;
  } else if ((c >= 313 && c <= 328) || (c >= 377 && c <= 382) ||
             (c >= 431 && c <= 432) || (c >= 435 && c <= 438) ||
             (c >= 461 && c <= 476)) {
    r = (c - 1) | 1;
  } else if (c == 255) {
    r = 376;
  } else if (c == 384) {
    r = 579;
  } else if (c == 392) {
    r = 391;
  } else if (c == 396) {
    r = 395;
  } else if (c == 402) {
    r = 401;
  } else if (c == 409) {
    r = 408;
  } else if (c == 410) {
    r = 573;
  } else if (c == 414) {
    r = 544;
  } else if (c == 424) {
    r = 423;
  } else if (c == 429) {
    r = 428;
  } else if (c == 441) {
    r = 440;
  } else if (c == 445) {
    r = 444;
  } else if (c == 447) {
    r = 503;
  } else if (c == 454) {
    r = 452;
  } else if (c == 457) {
    r = 455;
  } else if (c == 460) {
    r = 458;
  } else if (c == 477) {
    r = 398;
  } else if (c == 499) {
    r = 497;
  } else if (c == 501) {
    r = 500;
  } else if (c == 572) {
    r = 571;
  } else if (c == 578) {
    r = 577;
  } else if (c == 658) {
    r = 439;
  } else if (c == 881) {
    r = 880;
  } else if (c == 883) {
    r = 882;
  } else if (c == 887) {
    r = 886;
  } else if (c == 891) {
    r = 1021;
  } else if (c == 892) {
    r = 1022;
  } else if (c == 893) {
    r = 1023;
  } else if (c == 940) {
    r = 902;
  } else if (c == 941) {
    r = 904;
  } else if (c == 942) {
    r = 905;
  } else if (c == 943) {
    r = 906;
  } else if (c == 972) {
    r = 908;
  } else if (c == 973) {
    r = 910;
  } else if (c == 974) {
    r = 911;
  } else if (c == 977) {
    r = 920;
  } else if (c == 983) {
    r = 975;
  } else if (c == 1010) {
    r = 1017;
  } else if (c == 1011) {
    r = 895;
  } else if (c == 1016) {
    r = 1015;
  } else if (c == 1019) {
    r = 1018;
  }
  return r;
}