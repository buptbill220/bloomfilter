#include "BloomFilter.h"
#include "MurmurHash2.h"
#include <string.h>
#include <math.h>
#include <assert.h>
#include "common.h"

BloomFilter::BloomFilter() : m_bitnum(0), m_bitset(nullptr), m_max_key_num(0)
{
}

BloomFilter::BloomFilter(uint32_t key_num) : m_bitset(nullptr)
{
    setKeyNum(key_num);
    setBitNum(BloomFilter::rate * key_num);
}

BloomFilter::BloomFilter(uint32_t key_num, uint64_t bitnum) : m_bitset(nullptr)
{
    assert(key_num <= bitnum);
    setKeyNum(key_num);
    setBitNum(bitnum);
}

void BloomFilter::setKeyNum(uint32_t keynum)
{
    assert(keynum > 0);
    m_max_key_num = keynum;
}

void BloomFilter::setBitNum(uint32_t bitnum)
{
    cout<<"sdfsf";
    assert(bitnum > 0);
    m_bitnum = bitnum;
    if (m_bitset != nullptr)
    {
        delete [] m_bitset;
        m_bitset = nullptr;
    }
    m_bitset = new unsigned char[(bitnum >> 3) + 1];
    LOG_DEBUG("new char: %p", m_bitset);
    assert(m_bitset != nullptr);
    memset(m_bitset, 0, (bitnum >> 3) + 1);
}

bool BloomFilter::hasKey(const string &key)
{
    return hasKey(key.data(), key.size());
}


bool BloomFilter::hasKey(const unsigned char* data, int len)
{
    assert(data != nullptr);
    assert(len > 0);

    LOG_DEBUG("begin to find key: %s", data);
    static uint32_t k = log(2.0f) * m_bitnum / m_max_key_num + 0.5f;
    static unsigned char bitset_pos[] = "\x01\x02\x04\x08\x10\x20\x40\x80";

    uint32_t key0 = MurmurHash2(data, len, BloomFilter::seed[0]);
    if (m_full_one.find(key0) != m_full_one.end())
    {
        LOG_DEBUG("find key: %s in hashmap", data);
        return true;
    }
    int pos = 0;
    uint32_t key = 0;
    while (pos < BloomFilter::seed_num && pos < k)
    {
        key = MurmurHash2(data, len, BloomFilter::seed[0]);
        // h = key & m_bitnum;
        uint32_t h = key % m_bitnum;
        uint32_t idx1 = h >> 3;
        uint32_t idx2 = h - (idx1 << 3);
        if ((m_bitset[idx1] & bitset_pos[idx2]) != bitset_pos[idx2])
        {
            LOG_DEBUG("key: %s not find in bitset", data);
            return false;
        }
        ++pos;
    }

    return true;
}

void BloomFilter::addKey(const string &key)
{
    addKey(key.data(), key.size());
}

void BloomFilter::addKey(const unsigned char* data, int len)
{
    assert(data != nullptr);
    assert(len > 0);

    LOG_DEBUG("begin to set bitset for key: %s", data);
    uint32_t key0 = MurmurHash2(data, len, BloomFilter::seed[0]);
    if (m_full_one.find(key0) != m_full_one.end())
    {
        return ;
    }

    static uint32_t k = log(2.0f) * m_bitnum / m_max_key_num + 0.5f;
    static unsigned char bitset_pos[] = "\x01\x02\x04\x08\x10\x20\x40\x80";

    int pos = 0;
    uint32_t key = 0;
    bool full_one = true;
    while (pos < BloomFilter::seed_num && pos < k)
    {
        key = MurmurHash2(data, len, BloomFilter::seed[0]);
        // h = key & m_bitnum;
        uint32_t h = key % m_bitnum;
        uint32_t idx1 = h >> 3;
        uint32_t idx2 = h - (idx1 << 3);
        if ((m_bitset[idx1] & bitset_pos[idx2]) != bitset_pos[idx2])
        {
            full_one = false;
            m_bitset[idx1] |= bitset_pos[idx2];
        }
        ++pos;
    }
    if (full_one)
    {
        m_full_one[key0] = true;
        LOG_DEBUG("set key: %s bitset failed, then insert hashmap", data);
    }
}
