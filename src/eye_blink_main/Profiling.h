// Arduino profiling code
// http://www.dudley.nu/arduino_profiling
// William F. Dudley Jr.
// 2014 January 5

#ifndef PROFILING_H

#if PROFILING

#ifndef MAXPROF
#define MAXPROF 30
#endif

#define PF(n) do{prof_line=n;}while(0)
#define mydelay(v) do{PF(MAXPROF-1);delay(v);}while(0)

#if PROFILING_MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN volatile unsigned int prof_array[MAXPROF];
EXTERN volatile unsigned int prof_line;
EXTERN volatile unsigned char prof_has_dumped;

#if PROFILING_MAIN

#define _DL(x) Serial.print(x)
#define _DLn(x) Serial.println(x)

void clear_profiling_data (void) {
    unsigned char c;
    for(c = 0 ; c < MAXPROF ; c++) {
        prof_array[c] = 0;
    }
}

void dump_profiling_data(void) {
    unsigned char c;
    prof_has_dumped = 1;
    PF(0);
    for(c = 0 ; c < MAXPROF ; c++) {
        _DL((int)c);
        _DL(" ");
        _DLn((unsigned int)prof_array[c]);
        prof_array[c] = 0;
    }
}
#endif

#else
#define PF(n)
#define mydelay(v) delay(v)
#endif

#define PROFILING_H 1
#endif
