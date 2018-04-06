//
//  MemoryDetector.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/27.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include <atomic>
#include <mutex>
#include "MemoryDetector.hpp"


extern "C" malloc_zone_t **malloc_zones;
extern "C" int32_t malloc_num_zones;

typedef void (malloc_logger_t)(uint32_t type, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3, uintptr_t result, uint32_t num_hot_frames_to_skip);

extern "C" malloc_logger_t *__syscall_logger;

namespace MD {
    static void malloc_logger_func(uint32_t type, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3, uintptr_t result, uint32_t num_hot_frames_to_skip) {
        MemoryDetector::GetInstance()->AddSyscallCount();
    }
    
    // Should init at start, do not need lock.
    MemoryDetector *MemoryDetector::GetInstance() {
        static MemoryDetector *detector = nullptr;
        if (detector == nullptr) {
            detector = new MemoryDetector;
        }
        return detector;
    }
    
    MemoryDetector::MemoryDetector() : max_data_count_(MAX_DATA_COUNT) {
        __syscall_logger = malloc_logger_func;
    }
    
    void MemoryDetector::DetectorAllZones() noexcept {
        for (int i = 0; i < malloc_num_zones; i++) {
            malloc_zone_t *z = malloc_zones[i];
            wrap_zones().WrapZone(z);
        }
    }
    
    void MemoryDetector::DetectorDefaultZone() noexcept {
        malloc_zone_t *z = malloc_zones[0];
        wrap_zones().WrapZone(z);
    }
}
