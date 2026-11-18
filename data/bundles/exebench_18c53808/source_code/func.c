#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>

#include <math.h>

static void gui_combine_scissor(int dst[4], int src[4])
{
 if (!src)
  return;

 int dp[4] = {dst[0], dst[1], dst[0] + dst[2], dst[1] + dst[3]};
 int sp[4] = {src[0], src[1], src[0] + src[2], src[1] + src[3]};

 do { int c = 0; { dp[c] = ((dp[c] > sp[c]) ? (dp[c]) : (sp[c])); } c = 1; { dp[c] = ((dp[c] > sp[c]) ? (dp[c]) : (sp[c])); } } while(0);
 do { int c = 0; { dp[c + 2] = ((dp[c + 2] < sp[c + 2]) ? (dp[c + 2]) : (sp[c + 2])); } c = 1; { dp[c + 2] = ((dp[c + 2] < sp[c + 2]) ? (dp[c + 2]) : (sp[c + 2])); } } while(0);

 dst[0] = dp[0];
 dst[1] = dp[1];
 dst[2] = dp[2] - dp[0];
 dst[3] = dp[3] - dp[1];
}
