//
//  StringMetric.c
//  jaro-winkler
//
//  Created by Simon on 10/9/16.
//  Copyright © 2016 simonthefox. All rights reserved.
//

#include "StringMetric.h"
#include <string.h>
#include <stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

char* jaro_common(const char *s, const char *t, size_t H, size_t lenS, size_t lenT);
size_t jaro_num_transpositions(const char *s, const char *t, size_t lenS);
size_t jaro_longest_prefix(const char *s, const char *t);

float jaro_winkler(const char *s, const char *t) {
  float j = jaro(s, t);
  size_t P = jaro_longest_prefix(s, t);
  size_t P_ = MIN(P, 4);
  printf("jaro = %f, P = %zu, P' = %zu\n", j, P, P_);
  return j + (P_/10.0f)*(1.0f-j);
}

float jaro(const char *s, const char *t) {
  if (!s || !t) return -1.0f;
  
  size_t lenS = strlen(s);
  size_t lenT = strlen(t);
  if (lenS == 0 || lenT == 0) return 0.0f;
  
  size_t H = MIN(lenS, lenT)/2;
  printf("|s| = %zu, |t| = %zu, H = %zu\n", lenS, lenT, H);
  
  char *s_ = jaro_common(s, t, H, lenS, lenT);
  char *t_ = jaro_common(t, s, H, lenT, lenS);
  
  printf("s' = %s\n", s_);
  printf("t' = %s\n", t_);
  
  size_t lenS_ = strlen(s_);
  size_t lenT_ = strlen(t_);
  
  size_t T = jaro_num_transpositions(s_, t_, lenS_);
  
  free(s_);
  free(t_);
  
  float j1 = lenS_/(float)(lenS);
  float j2 = lenT_/(float)(lenT);
  float j3 = lenS_ == 0? 0.0f: (lenS_ - T)/(float)(lenS_);
  printf("|s'| = %zu, |t'| = %zu, T = %zu, j1 = %f, j2 = %f, j3 = %f\n", lenS_, lenT_, T, j1, j2, j3);
  return 0.333333f * (j1 + j2 + j3);
}

char* jaro_common(const char *s, const char *t, size_t H, size_t lenS, size_t lenT) {
  char letters[256] = { 0 };
  const char *p = t;
  const char *q = t+H;
  for (size_t i = 0; i <= H; ++i) {
    ++letters[t[i]];
  }
  
  char *s_ = (char *)calloc(lenS+1, sizeof(char));
  size_t j = 0;
  const char *r = s;
  while (*r) {
    if (letters[*r]) {
      s_[j++] = *r;
    }
    
    ++r;
    if (q-p < 2*H) {
      // increase one end
      if (p == t) {
        if (q != t+lenT-1) {
          ++q;
          ++letters[*q];
        }
      }
      else {
        --letters[*p];
        ++p;
      }
    }
    else {
      // shift both
      --letters[*p];
      ++p;
      if (q != t+lenT-1) {
        ++q;
        ++letters[*q];
      }
    }
    
    if (p >= t+lenT) break;
    if (q >= t+lenT) break;
  }
  
  return s_;
}

size_t jaro_num_transpositions(const char *s, const char *t, size_t lenS) {
  size_t T = 0;
  const char *p = s;
  const char *q = t;
  while (*p && *q) {
    if (*p != *q) {
      ++T;
    }
    ++p;
    ++q;
  }
  while (*p++) {
    ++T;
  }
  while (*q++) {
    ++T;
  }
  return MIN(lenS, T/2);
}

size_t jaro_longest_prefix(const char *s, const char *t) {
  size_t P = 0;
  while (*s && *t && *s == *t) {
    ++P;
    ++s;
    ++t;
  }
  return P;
}
