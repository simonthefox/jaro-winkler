//
//  StringMetric.h
//  jaro-winkler
//
//  Created by Simon on 10/9/16.
//  Copyright © 2016 simonthefox. All rights reserved.
//

#ifndef StringMetric_h
#define StringMetric_h

#include <stdio.h>

float jaro(const char *s, const char *t);
float jaro_winkler(const char *s, const char *t);

#endif /* StringMetric_h */
