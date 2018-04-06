//
//  MallocCollector.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/27.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include <malloc/malloc.h>
#include <pthread.h>
#include <vector>
#include <string>
#include "ThreadLocal.hpp"
#include "MallocStorage.hpp"
#include "MallocCollector.hpp"
#include "MallocWrapZone.hpp"
#include "MemoryDetector.hpp"

namespace MD {
    int64_t CollectorChecker::max() {
        return MemoryDetector::GetInstance()->max_data_count();
    }
    void CollectorChecker::overflow(MemoryStorage* storage) {
        MemoryDetector::GetInstance()->DataOverflowNotifaction();
    }
    
    namespace Wrap {
        static pthread_key_t key_;
        
        pthread_key_t key() {
            return key_;
        }
        
        void deallocate(void *p) {
            MemoryStorage *s = reinterpret_cast<MemoryStorage *>(p);
            s->end();
            
            MemoryDetector::GetInstance()->pool().Detatch(s);
        }
        
        struct InitKey {
            InitKey() {
                pthread_key_create(&key_, deallocate);
            }
        };
        static class InitKey initKey_;
        
        struct Constructor {
            MemoryStorage* operator()() {
                pthread_t pid = pthread_self();
                auto p = new MemoryStorage(pid);
                
                if (pthread_main_np()) {
                    p->setMainThread();
                }
                
                char buf[128] = {0};
                pthread_getname_np(pid, buf, sizeof(buf));
                p->setName(buf);
                
                MemoryDetector::GetInstance()->pool().Attach(p);
                return p;
            }
        };
        
        class ThreadStore : public ThreadLocal<MemoryStorage, Constructor> {
        public:
            ThreadStore() : ThreadLocal<MemoryStorage, Constructor>(key()) {}
        };
        
        void *malloc(malloc_zone_t *zone, size_t size) {
            malloc_zone_t* orig_zone = MemoryDetector::GetInstance()->wrap_zones().orig_zone_value(zone);
            if (MemoryDetector::GetInstance()->isEnabled()) {
                ThreadStore s;
                MemoryCollector c(s.value());
                c.set(zone, Action::Malloc, size);
                void *p = orig_zone->malloc(zone, size);
                
                return p;
            }
            else {
                void *p = orig_zone->malloc(zone, size);
                
                return p;
            }
        }
    }
}
