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
#include <functional>
#include "Allocator.hpp"
#include "MallocStorage.hpp"
#include "MallocCollector.hpp"

namespace MD {
    class MallocPool {
    public:
        typedef std::vector<MemoryStorage*, VMAllocator<MemoryStorage *>> pool_type;
        
        const pool_type& runningPool() const { return running_pool_; }
        const pool_type& deadPool() const { return dead_pool_; }
        
        void Attach(MemoryStorage *s) {
            std::lock_guard<std::mutex> l(lock_);
            running_pool_.emplace_back(s);
        }
        
        void Detatch(MemoryStorage *s) {
            std::lock_guard<std::mutex> l(lock_);
            auto idx = std::find(running_pool_.begin(), running_pool_.end(), s);
            if (idx != running_pool_.end()) {
                dead_pool_.emplace_back(std::move(*idx));
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
        
        void EnumerateRunningPool(std::function<void(MemoryStorage*)> cb) {
            std::lock_guard<std::mutex> l(lock_);
            
            std::for_each(running_pool_.begin(), running_pool_.end(), cb);
        }
        
        void EnumerateDeadPool(std::function<void(MemoryStorage*)> cb) {
            std::lock_guard<std::mutex> l(lock_);
            
            std::for_each(dead_pool_.begin(), dead_pool_.end(), cb);
        }
        
    private:
        std::mutex lock_;
        pool_type running_pool_;
        pool_type dead_pool_;
    };
}

#endif /* MallocPool_hpp */
