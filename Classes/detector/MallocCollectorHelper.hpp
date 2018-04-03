//
//  MallocCollectorHelper.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef MallocCollectorHelper_hpp
#define MallocCollectorHelper_hpp

#include <stdio.h>
#include <memory>
#include <malloc/malloc.h>
#include "MallocMemory.hpp"

namespace MD {
    
    namespace CollectorDefault {
        template <class _S>
        struct CollectorChecker {
            static int64_t max() {
                return 1024*1024;
            }
            static void overflow(_S* storage) {
                
            }
        };
    }
    
    template <class _S, class _I, class _C = CollectorDefault::CollectorChecker<_S>>
    class Collector {
    public:
        typedef _S storage_type;
        typedef _I item_type;
        typedef _C checker_type;
        
        Collector(storage_type* s) : s_(s) {
            i_.start();
        }
        
        Collector& setZone(malloc_zone_t *z) {
            i_.zone = z;
            return *this;
        }
        
        Collector& setAction(Action act) {
            i_.action = act;
            return *this;
        }
        
        Collector& setSize(std::int64_t size) {
            i_.size = size;
            return *this;
        }
        
        Collector& set(malloc_zone_t *z, Action act, std::int64_t size) {
            i_.zone = z;
            i_.action = act;
            i_.size = size;
            return *this;
        }
        
        ~Collector() {
            i_.stop();
            
            int64_t cnt = s_->collect(std::move(i_));
            if (cnt > checker_type::max()) {
                checker_type::overflow(s_);
            }
        }
        
    private:
        storage_type* s_;
        item_type i_;
    };
}

#endif /* MallocCollectorHelper_hpp */
