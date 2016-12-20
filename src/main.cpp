#include <stdio.h>
#include <math.h>
#include <time.h>
#include "common.h"
#include "BloomFilter.h"

#define MAXLEN 100

static unsigned char words[MAXLEN] = "";

static inline void createString(int len)
{
    static unsigned char alpha[] = "01123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    static unsigned int length = sizeof("01123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") - 1;
    for (int i = 0; i < len; ++i)
    {
        words[i] = alpha[random() % length];
    }
    words[len] = 0;
}

int main()
{
    srand(time(NULL));
    BloomFilter filter(1000000);
    for (int i = 0; i < 1000000; ++i)
    {
        int len = (random() % (MAXLEN - 1)) + 1;
        createString(len);
        //LOG_DEBUG("generate words: %s", words);
        filter.addKey(words, len);
    }

    for (int i = 0; i < 10000; ++i)
    {
        int len = (random() % (MAXLEN - 1)) + 1;
        createString(len);
        //LOG_DEBUG("generate words: %s", words);
        filter.hasKey(words, len);
    }
}
