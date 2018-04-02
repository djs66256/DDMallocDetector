//
//  AnalysisPerThread.cpp
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include "AnalysisPerThread.hpp"
#include <mutex>

namespace MD {
    void AnalysisPerThread::Run() {
        PerThreadData::thread_memory_type thread_memory;
        
        auto func = [&](MemoryStorage* storage){
            auto mlist = std::make_shared<PerThreadData::memory_list_type>();
            std::string name = storage->name();
            auto begin = storage->data().begin();
            auto& beginItem = *begin;
            PerThreadData::memory_info_type
            max(beginItem.start_time, beginItem.size),
            min(beginItem.start_time, beginItem.size);
            std::for_each(begin, storage->data().end(), [&](const Memory& mem){
                mlist->push_back({mem.start_time, mem.size});
                if (max.second < mem.size) {
                    max.first = mem.start_time;
                    max.second = mem.size;
                }
                if (min.second > mem.size) {
                    min.first = mem.start_time;
                    min.second = mem.size;
                }
            });
            auto threadData = PerThreadData::ThreadInfo(std::move(name), std::move(mlist), min, max);
            threadData.start_time = beginItem.start_time;
            thread_memory.emplace_back(std::move(threadData));
        };
        
        pool().EnumerateRunningPool(func);
        pool().EnumerateDeadPool(func);
        
        data_->thread_memory_ = std::move(thread_memory);
    }
}
