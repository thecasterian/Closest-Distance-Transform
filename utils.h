#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

/* Use for an unused variable or parameter to prevent a warning. */
#define UNUSED __attribute__((unused))

#define max(a, b) ({typeof(a) _a = a; typeof(b) _b = b; _a > _b ? _a : _b;})
#define min(a, b) ({typeof(a) _a = a; typeof(b) _b = b; _a < _b ? _a : _b;})

#define SWAP(a, b) do {typeof(a) tmp = a; a = b; b = tmp;} while (0)

double sq(const double);

int lower_bound(const int, const double [], const double);
int upper_bound(const int, const double [], const double);

int divceil(int, int);

#endif