#ifndef CACHE_H
#define CACHE_H
#include <stdint.h>

// SmallBoomConfig parameters:

#define L1_BLOCK_SZ_BYTES 64 // L1缓存行大小为64bytes
#define L1_BLOCK_BITS      6 // 对应6位offset
#define L1_SETS           64 // 64个SET
#define L1_SET_BITS        6 // 对应6位 set index（Idx）
#define L1_WAYS            4 // 4路组相连
#define L1_SZ_BYTES (L1_SETS*L1_WAYS*L1_BLOCK_SZ_BYTES) // cache size，代表cache可以缓存最大数据的大小

/*--------------------------------
|          Cache address         |
----------------------------------
|    tag    |    idx   |  offset |
----------------------------------
| 38 <-> 12 | 11 <-> 6 | 5 <-> 0 |
----------------------------------*/

#define FULL_MASK         0xFFFFFFFFFFFFFFFF
#define TAG_MASK          (FULL_MASK << (L1_SET_BITS + L1_BLOCK_BITS)) 
#define OFF_MASK          (~(FULL_MASK << L1_BLOCK_BITS))
#define SET_MASK          (~(TAG_MASK | OFF_MASK))

// 申请一个五倍cache大小的数组，由于未初始化，数组里的数据为随机垃圾数据，其所在地址起点为: dummyMem
uint8_t dummyMem[5 * L1_SZ_BYTES];

/** 入口参数
 * @param addr 需要从cache中冲刷掉的内容在主存中的起始地址
 * @param sz   冲刷的数据长度(以byte为单位)
 */
void flushCache(uint64_t addr, uint64_t sz) {
    // 首先计算出想要冲刷 sz 大小的数据需要冲刷的Set数：
    // 计算方式为 需要冲刷的set数 = 冲刷的数据长度 sz/64(缓存行大小)，如果冲刷的数据长度>整个L1 cache大小，那么就冲刷所有的 set
    uint64_t numSetsClear = sz >> L1_BLOCK_BITS;
    if ((sz & OFF_MASK) != 0) numSetsClear += 1;
    if (numSetsClear > L1_SETS) numSetsClear = L1_SETS; 
    
    // 准备中间变量和指定内存地址对应cache仲裁器的tag部分
    // dummyMem <= alignedMem < dummyMem + sizeof(dummyMem)
    // alignedMem has idx = 0 and offset = 0 
    uint8_t dummy = 0;
    uint64_t alignedMem = (((uint64_t)dummyMem) + L1_SZ_BYTES) & TAG_MASK;

    // 进入flush循环
    for (uint64_t i = 0; i < numSetsClear; ++i) {
        // 计算需要冲刷的每一个set的指定内存地址对应cache仲裁器的idx部分
        uint64_t setOffset = (((addr & SET_MASK) >> L1_BLOCK_BITS) + i) << L1_BLOCK_BITS;
        
        for(uint64_t j = 0; j < 4 * L1_WAYS; ++j) {
            // 由于采取随机替换策略，因此驱逐4*4次不同的tag，驱逐概率 = 1-0.75^16 ≈ 0.99
            uint64_t wayOffset = j << (L1_BLOCK_BITS + L1_SET_BITS);
            // 通过这条语句来加载指定地址的垃圾数据到 dummy 数组中，同时CPU会把这些垃圾数据更新到
            // data cache根据映射关系对应的部分，从而实现对data cache指定空间的刷新操作
            dummy = *((uint8_t*)(alignedMem + setOffset + wayOffset));
        }
    }
}

#endif
