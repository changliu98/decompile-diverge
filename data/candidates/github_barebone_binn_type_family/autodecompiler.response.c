int
type_family(int sip_code)
{
 int status_code;

 switch(sip_code) {
 case 100:
 case 180:
 case 181:
 case 182:
 case 183:
  status_code = 242;
  break;
 case 200:
 case 202:
  status_code = 243;
  break;
 case 203:
 case 204:
 case 205:
 case 206:
 case 207:
 case 208:
 case 226:
  status_code = 244;
  break;
 case 219:
 case 220:
 case 221:
 case 222:
 case 223:
 case 224:
 case 225:
  status_code = 245;
  break;
 case 209:
 case 210:
 case 211:
 case 212:
 case 213:
 case 214:
 case 215:
 case 216:
 case 217:
 case 218:
  status_code = 244;
  break;
 case 300:
 case 301:
 case 302:
 case 303:
 case 304:
 case 305:
 case 380:
 case 381:
 case 382:
 case 383:
 case 384:
 case 385:
 case 386:
 case 387:
  status_code = 244;
  break;
 case 400:
 case 401:
 case 402:
 case 403:
 case 404:
 case 405:
 case 406:
 case 407:
 case 408:
 case 409:
 case 410:
 case 413:
 case 414:
 case 415:
 case 416:
 case 417:
 case 421:
 case 423:
 case 424:
 case 425:
 case 426:
 case 427:
 case 428:
 case 429:
 case 430:
 case 431:
 case 432:
 case 433:
 case 434:
 case 435:
 case 436:
 case 437:
 case 438:
 case 439:
 case 440:
 case 441:
 case 442:
 case 443:
 case 444:
 case 445:
 case 446:
 case 447:
 case 448:
 case 449:
  status_code = 246;
  break;
 case 450:
 case 451:
 case 452:
 case 453:
 case 454:
 case 455:
 case 456:
 case 457:
 case 458:
 case 459:
 case 460:
 case 461:
 case 462:
 case 463:
 case 464:
 case 465:
 case 466:
 case 467:
 case 468:
 case 469:
 case 470:
 case 471:
 case 472:
 case 473:
 case 474:
 case 475:
 case 476:
 case 477:
 case 478:
 case 479:
  status_code = 246;
  break;
 case 480:
 case 481:
 case 482:
 case 483:
 case 484:
 case 485:
 case 486:
 case 487:
 case 488:
 case 489:
 case 490:
 case 491:
 case 492:
 case 493:
 case 494:
 case 495:
 case 496:
 case 497:
 case 498:
 case 499:
  status_code = 246;
  break;
 case 500:
 case 501:
 case 502:
 case 503:
 case 504:
 case 505:
 case 506:
 case 507:
 case 508:
 case 509:
 case 510:
 case 511:
 case 512:
 case 513:
 case 514:
 case 515:
 case 516:
 case 517:
 case 518:
 case 519:
 case 520:
 case 521:
 case 522:
 case 523:
 case 524:
 case 525:
 case 526:
 case 527:
 case 528:
 case 529:
 case 530:
 case 531:
 case 532:
 case 533:
 case 534:
 case 535:
 case 536:
 case 537:
 case 538:
 case 539:
 case 540:
 case 541:
 case 542:
 case 543:
 case 544:
 case 545:
 case 546:
 case 547:
 case 548:
 case 549:
  status_code = 247;
  break;
 case 550:
 case 551:
 case 552:
 case 553:
 case 554:
 case 555:
 case 556:
 case 557:
 case 558:
 case 559:
 case 560:
 case 561:
 case 562:
 case 563:
 case 564:
 case 565:
 case 566:
 case 567:
 case 568:
 case 569:
 case 570:
 case 571:
 case 572:
 case 573:
 case 574:
 case 575:
 case 576:
 case 577:
 case 578:
 case 579:
 case 580:
 case 581:
 case 582:
 case 583:
 case 584:
 case 585:
 case 586:
 case 587:
 case 588:
 case 589:
 case 590:
 case 591:
 case 592:
 case 593:
 case 594:
 case 595:
 case 596:
 case 597:
 case 598:
 case 599:
  status_code = 247;
  break;
 default:
  status_code = 0;
 }
 return status_code;
}