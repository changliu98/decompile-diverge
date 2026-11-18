#include <signal.h>

#include <stddef.h>

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

void testfunc16(int *p1, int *p2, int *const p3, const int *p4, int *p5) {
  if (*p1 > 100) {

  }

  if (*p5 > 100) {

  }

  p5++;
  p5 = p5 + 10;

  *p2++;
  *p2 = *p2 + 100;

  if (*p3 > 1000) {

  }

  if (*p4 < 100) {

  }

  asm("add %al, (%rax)");
}
