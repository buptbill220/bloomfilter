#ifndef __BloomFilter__
#define __BloomFilter__

#include <stdint.h>
#include <unordered_map>
#include <string>

using namespace std;

class BloomFilter
{
    private:
        // 哈希函数种子
        static constexpr uint32_t seed[] = { 10414199, 11551117, 11926069,
                                            12016621, 12180073, 12180073,
                                            13001147, 13112711, 13294123,
                                            14111311
        };

        // 哈希函数个数，即是种子数量，采用murmurhash32
        // 文献地址：http://pages.cs.wisc.edu/~cao/papers/summary-cache/node8.html
        static constexpr uint32_t seed_num = 10;
        static constexpr uint32_t rate = 20;
    private:
        // bit长度
        uint64_t m_bitnum;
        // bit内存地址
        unsigned char *m_bitset;
        // 最大的key个数
        uint32_t m_max_key_num;
        // hash值全为1情况下，不确定是否存在，把hash编码存在map里
        std::unordered_map<uint32_t, bool> m_full_one;
    public:
        BloomFilter();
        BloomFilter(uint32_t key_num);
        BloomFilter(uint32_t key_num, uint64_t bitnum);
        
        ~BloomFilter()
        {
            if (m_bitset)
            {
                delete [] m_bitset;
                m_bitset =  nullptr;
            }
        }

        void setKeyNum(uint32_t keynum);

        void setBitNum(uint32_t bitnum);

        bool hasKey(const string &key);

        bool hasKey(const unsigned char* data, int len);

        void addKey(const string &key);

        void addKey(const unsigned char* data, int len);
};

#endif
