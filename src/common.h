#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG

#define LOG(format, args...) \
    fprintf(stderr, format, ##args)

#else

#define LOG(level, format, args...) ;

#endif

#define LOG_DEBUG(format, args...) \
    LOG("[DEBUG] " format "\n", ##args)

#define LOG_INFO(format, args...) \
    LOG("[INFO] " format "\n", ##args)

#define LOG_WARN(format, args...) \
    LOG("[WARN] " format "\n", ##args)

#define LOG_NOTICE(format, args...) \
    LOG("[NOTICE] " format "\n", ##args)

#ifdef __cplusplus
}
#endif

template<typename Head, typename... Tail>
void CPPLOG(Head head, Tail... tail)
{
    cerr << head;
    CPPLOG(tail...);
}

#endif
