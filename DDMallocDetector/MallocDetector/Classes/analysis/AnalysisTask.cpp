//
//  AnalysisTask.cpp
//  DDMallocDetector
//
//  Created by daniel on 2018/3/31.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include "AnalysisTask.hpp"
#include "MemoryDetector.hpp"

namespace MD {
    MallocPool& AnalysisTask::pool() const {
        return MemoryDetector::GetInstance()->pool();
    }
    
    void AnalysisTask::Start() {
        if (MemoryDetector::GetInstance()->Running()) {
            throw MemoryDetector::ProtectException();
        }
        else {
            if (!canceled()) {
                running_.store(true);
                Run();
                running_.store(false);
            }
        }
    }

    void AnalysisTask::Cancel() {
        canceled_.store(true);
    }

    bool AnalysisTask::canceled() {
      return canceled_.load();
    }
}
