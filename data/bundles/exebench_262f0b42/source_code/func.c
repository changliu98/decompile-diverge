#include <string.h>

#include <stdlib.h>

#include <stdio.h>

void breakup(short int fcs_bit[], unsigned short usps_crc)
{
 int i;

 for(i = 0; i < 13; i++) {
  fcs_bit[i] = 0;
 }

 if(usps_crc >= 4096) {
  fcs_bit[12] = 1;
  usps_crc -= 4096;
 }
 if(usps_crc >= 2048) {
  fcs_bit[11] = 1;
  usps_crc -= 2048;
 }
 if(usps_crc >= 1024) {
  fcs_bit[10] = 1;
  usps_crc -= 1024;
 }
 if(usps_crc >= 512) {
  fcs_bit[9] = 1;
  usps_crc -= 512;
 }
 if(usps_crc >= 256) {
  fcs_bit[8] = 1;
  usps_crc -= 256;
 }
 if(usps_crc >= 128) {
  fcs_bit[7] = 1;
  usps_crc -= 128;
 }
 if(usps_crc >= 64) {
  fcs_bit[6] = 1;
  usps_crc -= 64;
 }
 if(usps_crc >= 32) {
  fcs_bit[5] = 1;
  usps_crc -= 32;
 }
 if(usps_crc >= 16) {
  fcs_bit[4] = 1;
  usps_crc -= 16;
 }
 if(usps_crc >= 8) {
  fcs_bit[3] = 1;
  usps_crc -= 8;
 }
 if(usps_crc >= 4) {
  fcs_bit[2] = 1;
  usps_crc -= 4;
 }
 if(usps_crc >= 2) {
  fcs_bit[1] = 1;
  usps_crc -= 2;
 }
 if(usps_crc == 1) {
  fcs_bit[0] = 1;
 }
}
