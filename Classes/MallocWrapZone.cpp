//
//  MallocWrapZone.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/27.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include "MallocWrapZone.hpp"
#include <mutex>
#include <sys/mman.h>
#include "MallocCollector.hpp"

namespace MD {
    
    void MallocWrapZones::MallocWrapZone::Wrap() {
        mprotect(orig_zone_ptr_, sizeof(malloc_zone_t), PROT_READ|PROT_WRITE);
        orig_zone_ptr_->malloc = Wrap::malloc;
        mprotect(orig_zone_ptr_, sizeof(malloc_zone_t), PROT_READ);
    }
    
    void MallocWrapZones::MallocWrapZone::UnWrap() {
        orig_zone_ptr_->malloc = orig_zone_.malloc;
    }
}
