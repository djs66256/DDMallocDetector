//
//  AnalysisTask.hpp
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AnalysisTask_hpp
#define AnalysisTask_hpp

#include <stdio.h>
#include <atomic>
#include "MallocPool.hpp"

namespace MD {
    class AnalysisTask {
    public:
        AnalysisTask() : canceled_(false), running_(false) {}
        void Start();
        void Cancel();
        bool canceled();
        bool running() { return running_.load(); }
    protected:
        MallocPool& pool() const;
        virtual void Run() = 0;
    private:
        std::atomic<bool> canceled_;
        std::atomic<bool> running_;
    };
}

#endif /* AnalysisTask_hpp */
