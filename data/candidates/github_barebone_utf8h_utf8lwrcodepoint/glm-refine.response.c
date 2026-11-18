utf8_int32_t __cdecl utf8lwrcodepoint(utf8_int32_t cp)
{
    if ((cp >= 65   && cp <= 90)  ||
        (cp >= 192  && cp <= 214) ||
        (cp >= 216  && cp <= 222) ||
        (cp >= 913  && cp <= 929) ||
        (cp >= 931  && cp <= 939) ||
        (cp >= 1040 && cp <= 1071))
    {
        return cp + 32;
    }

    if (cp >= 1024 && cp <= 1039)
        return cp + 80;

    if ((cp >= 256  && cp <= 303) ||
        (cp >= 306  && cp <= 311) ||
        (cp >= 330  && cp <= 375) ||
        (cp >= 386  && cp <= 389) ||
        (cp >= 416  && cp <= 421) ||
        (cp >= 478  && cp <= 495) ||
        (cp >= 504  && cp <= 543) ||
        (cp >= 546  && cp <= 563) ||
        (cp >= 582  && cp <= 591) ||
        (cp >= 984  && cp <= 1007)||
        (cp >= 1120 && cp <= 1153)||
        (cp >= 1162 && cp <= 1279))
    {
        return cp | 1;
    }

    if ((cp >= 313 && cp <= 328) ||
        (cp >= 377 && cp <= 382) ||
        (cp >= 431 && cp <= 432) ||
        (cp >= 435 && cp <= 438) ||
        (cp >= 461 && cp <= 476))
    {
        return (cp + 1) & 0xFFFFFFFE;
    }

    switch (cp)
    {
        case 376:  return 255;
        case 391:  return 392;
        case 395:  return 396;
        case 398:  return 477;
        case 401:  return 402;
        case 408:  return 409;
        case 423:  return 424;
        case 428:  return 429;
        case 439:  return 658;
        case 440:  return 441;
        case 444:  return 445;
        case 452:  return 454;
        case 455:  return 457;
        case 458:  return 460;
        case 497:  return 499;
        case 500:  return 501;
        case 503:  return 447;
        case 544:  return 414;
        case 571:  return 572;
        case 573:  return 410;
        case 577:  return 578;
        case 579:  return 384;
        case 880:  return 881;
        case 882:  return 883;
        case 886:  return 887;
        case 895:  return 1011;
        case 902:  return 940;
        case 904:  return 941;
        case 905:  return 942;
        case 906:  return 943;
        case 908:  return 972;
        case 910:  return 973;
        case 911:  return 974;
        case 975:  return 983;
        case 1012: return 952;
        case 1015: return 1016;
        case 1017: return 1010;
        case 1018: return 1019;
        case 1021: return 891;
        case 1022: return 892;
        case 1023: return 893;
    }

    return cp;
}