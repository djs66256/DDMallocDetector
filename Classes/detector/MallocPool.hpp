//
//  MallocPool.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef MallocPool_hpp
#define MallocPool_hpp

#include <stdio.h>
#include <vector>
#include <mutex>
#include <memory>
#include "Allocator.hpp"
#include "MallocStorage.hpp"
#include "MallocCollector.hpp"

namespace MD {
    class MallocPool {
    public:
        void Attach(MemoryStorage *s) {
            std::lock_guard<std::mutex> l(lock_);
            running_pool_.emplace_back(s);
        }
        
        void Detatch(MemoryStorage *s) {
            std::lock_guard<std::mutex> l(lock_);
            auto idx = std::find(running_pool_.begin(), running_pool_.end(), s);
            if (idx != running_pool_.end()) {
                dead_pool_.push_back(*idx);
                running_pool_.erase(idx);
            }
        }
        
        void ClearAll() {
            std::lock_guard<std::mutex> l(lock_);
            
            std::for_each(dead_pool_.begin(), dead_pool_.end(), [](MemoryStorage *s) {
                delete s;
            });
            dead_pool_.clear();
            
            std::for_each(running_pool_.begin(), running_pool_.end(), [](MemoryStorage *s) {
                s->clear();
            });
        }
        
    private:
        std::mutex lock_;
        std::vector<MemoryStorage *> running_pool_;
        std::vector<MemoryStorage *> dead_pool_;
    };
}

#endif /* MallocPool_hpp */
