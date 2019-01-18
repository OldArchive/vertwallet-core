#ifndef GROESTL_H
#define GROESTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void groestl_hash(const char* input, char* output);
#ifdef __cplusplus
}
#endif

#endif