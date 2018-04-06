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

namespace MD {
    
    MemoryDetector *MemoryDetector::GetInstance() {
        static MemoryDetector *detector = nullptr;
        if (detector == nullptr) {
            detector = new MemoryDetector;
        }
        return detector;
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
