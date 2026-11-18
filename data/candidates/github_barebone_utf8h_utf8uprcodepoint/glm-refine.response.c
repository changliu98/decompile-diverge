utf8_int32_t __cdecl utf8uprcodepoint(utf8_int32_t cp)
{
  // Ranges where lowercase to uppercase is a simple subtraction of 32
  // (e.g., ASCII 'a'-'z', Latin-1 'à'-'ö', Greek 'α'-'ω', Cyrillic 'а'-'я')
  if ( (cp >= 97 && cp <= 122)   ||
       (cp >= 224 && cp <= 246)  ||
       (cp >= 248 && cp <= 254)  ||
       (cp >= 945 && cp <= 961)  ||
       (cp >= 963 && cp <= 971)  ||
       (cp >= 1072 && cp <= 1103) )
  {
    return cp - 32;
  }

  // Special subtraction for specific Cyrillic characters
  if (cp >= 1104 && cp <= 1119)
    return cp - 80;

  // Ranges where lowercase characters are odd and uppercase are even.
  // (cp & 0xFFFFFFFE) is equivalent to (cp - 1), clearing the lowest bit.
  if ( (cp >= 256 && cp <= 303)  ||
       (cp >= 306 && cp <= 311)  ||
       (cp >= 330 && cp <= 375)  ||
       (cp >= 386 && cp <= 389)  ||
       (cp >= 416 && cp <= 421)  ||
       (cp >= 478 && cp <= 495)  ||
       (cp >= 504 && cp <= 543)  ||
       (cp >= 546 && cp <= 563)  ||
       (cp >= 582 && cp <= 591)  ||
       (cp >= 984 && cp <= 1007) ||
       (cp >= 1120 && cp <= 1153)||
       (cp >= 1162 && cp <= 1279) )
  {
    return cp & 0xFFFFFFFE;
  }

  // Ranges where lowercase characters are even and uppercase are odd.
  // (cp - 1) | 1 sets the lowest bit to 1, effectively subtracting 1 from an even number.
  if ( (cp >= 313 && cp <= 328)  ||
       (cp >= 377 && cp <= 382)  ||
       (cp >= 431 && cp <= 432)  ||
       (cp >= 435 && cp <= 438)  ||
       (cp >= 461 && cp <= 476) )
  {
    return (cp - 1) | 1;
  }

  // Special 1-to-1 mappings for irregular lowercase characters
  switch (cp)
  {
    case 255:   return 376;
    case 384:   return 579;
    case 392:   return 391;
    case 396:   return 395;
    case 402:   return 401;
    case 409:   return 408;
    case 410:   return 573;
    case 414:   return 544;
    case 424:   return 423;
    case 429:   return 428;
    case 441:   return 440;
    case 445:   return 444;
    case 447:   return 503;
    case 454:   return 452;
    case 457:   return 455;
    case 460:   return 458;
    case 477:   return 398;
    case 499:   return 497;
    case 501:   return 500;
    case 572:   return 571;
    case 578:   return 577;
    case 658:   return 439;
    case 881:   return 880;
    case 883:   return 882;
    case 887:   return 886;
    case 891:   return 1021;
    case 892:   return 1022;
    case 893:   return 1023;
    case 940:   return 902;
    case 941:   return 904;
    case 942:   return 905;
    case 943:   return 906;
    case 972:   return 908;
    case 973:   return 910;
    case 974:   return 911;
    case 977:   return 920;
    case 983:   return 975;
    case 1010:  return 1017;
    case 1011:  return 895;
    case 1016:  return 1015;
    case 1019:  return 1018;
  }

  // If it doesn't match any lowercase mapping, return the original codepoint
  return cp;
}