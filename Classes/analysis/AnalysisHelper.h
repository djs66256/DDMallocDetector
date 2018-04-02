//
//  AnalysisHelper.h
//  DDMallocDetector
//
//  Created by daniel on 2018/4/3.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AnalysisHelper_h
#define AnalysisHelper_h

#include <assert.h>
#include <vector>

namespace MD {
    
    template <std::size_t _Step = 2, std::size_t _Start = 1>
    struct StepByLog {
        static_assert(_Step > 1, "");
        static_assert(_Start >= 1, "");
        
        std::vector<std::size_t> operator()(std::size_t min, std::size_t max) {
            assert(max > min);
            std::vector<std::size_t> steps;
            std::size_t value = _Start;
            while(value < min) value *= _Step;
            steps.push_back(value);
            while (true) {
                value *= _Step;
                if (value > max) break;
                steps.push_back(value);
            };
            return steps;
        }
    };
    
    template <std::size_t _Step = 8>
    struct StepByLinear {
        static_assert(_Step > 0, "");
        
        std::vector<std::size_t> operator()(std::size_t min, std::size_t max) {
            assert(max > min);
            std::vector<std::size_t> steps;
            std::size_t value = min;
            steps.push_back(value);
            while (true) {
                value += _Step;
                if (value > max) break;
                steps.push_back(value);
            }
            return steps;
        }
    };
}

#endif /* AnalysisHelper_h */
