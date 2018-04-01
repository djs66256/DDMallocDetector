//
//  AnalysisPerThread.hpp
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AnalysisPerThread_hpp
#define AnalysisPerThread_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include <memory>
#include "AnalysisTask.hpp"

namespace MD {
    class PerThreadData {
    public:
        typedef std::pair<time_t, std::size_t> memory_info_type;
        typedef std::vector<memory_info_type> memory_list_type;
        typedef std::shared_ptr<memory_list_type> memory_list_type_ptr;
        struct ThreadInfo {
            std::string name;
            memory_list_type_ptr memory;
            time_t start_time;
            memory_info_type max, min;
            ThreadInfo() : max(0, 0), min(0, 0) {};
            ThreadInfo(std::string&& name, memory_list_type_ptr&& mem, memory_info_type min, memory_info_type max)
            : name(std::move(name)), memory(std::move(mem)), max(max), min(min) {}
        };
        typedef std::vector<ThreadInfo> thread_memory_type;
        
        PerThreadData() : thread_memory_() {}
        
        thread_memory_type& thread_memory() {
            return thread_memory_;
        }
    private:
        friend class AnalysisPerThread;
        thread_memory_type thread_memory_;
    };
    
    
    class AnalysisPerThread : public AnalysisTask {
    public:
        AnalysisPerThread() : data_(std::make_shared<PerThreadData>()) {}
        std::shared_ptr<PerThreadData> data() {
          return data_;
        }

    protected:
        void Run() override;
        
    private:
        std::shared_ptr<PerThreadData> data_;
    };
}

#endif /* AnalysisPerThread_hpp */
