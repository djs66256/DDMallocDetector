//
//  MallocCollector.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/27.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef MallocCollector_hpp
#define MallocCollector_hpp

#include <stdio.h>
#include "MallocStorage.hpp"
#include "MallocCollector.hpp"

namespace MD {
    
    typedef Storage<Memory> MemoryStorage;
    
    struct CollectorChecker {
        static int64_t max();
        static void overflow(MemoryStorage* storage);
    };
    
    typedef Collector<MemoryStorage, Memory, CollectorChecker> MemoryCollector;
    
    namespace Wrap {
        
        
        extern void *malloc(malloc_zone_t *zone, size_t size);
//        void free(malloc_zone_t *zone, void *ptr) {
//
//        }
    }
}

#endif /* MallocCollector_hpp */
