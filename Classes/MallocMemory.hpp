//
//  MallocMemory.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef MallocMemory_hpp
#define MallocMemory_hpp

#include <stdio.h>
#include <chrono>
#include <time.h>
#include <malloc/malloc.h>

namespace MD {
    enum class Action {
        Unknow,
        Malloc,
        Free,
    };
    
    class Memory {
    public:
        
        Action action = Action::Unknow;
        malloc_zone_t *zone = nullptr;
        std::int64_t size = 0;
        clock_t start_time;
        clock_t end_time;
        
        void start() {
            start_time = clock();
        }
        void stop() {
            end_time = clock();
        }
        
        clock_t duration() {
            return end_time - start_time;
        }
        
        double duration_interval() {
            return duration() / CLOCKS_PER_SEC;
        }
        
        Memory& set(malloc_zone_t *z, Action act, std::int64_t size) {
            zone = z;
            action = act;
            size = size;
            return *this;
        }
        
        Memory() {};
        Memory(const Memory& mem)
        : action(mem.action), zone(mem.zone), size(mem.size),
        start_time(mem.start_time), end_time(mem.end_time) { }
        
        Memory(const Memory&& mem)
        : action(mem.action), zone(mem.zone), size(mem.size),
        start_time(mem.start_time), end_time(mem.end_time) { }
        
        Memory& operator = (Memory& mem) {
            action = mem.action;
            zone = mem.zone;
            size = mem.size;
            start_time = mem.start_time;
            end_time = mem.end_time;
            return *this;
        }
        ~Memory() {}
    private:
    };
}

#endif /* MallocMemory_hpp */
