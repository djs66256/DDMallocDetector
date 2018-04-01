//
//  AnalysisBySize.hpp
//  DDMallocDetector
//
//  Created by daniel on 2018/4/1.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AnalysisBySize_hpp
#define AnalysisBySize_hpp

#include <stdio.h>
#include <cmath>
#include <map>
#include <algorithm>
#include "AnalysisTask.hpp"

namespace MD {
    
    template <std::size_t _Step = 2, std::size_t _Start = 8>
    struct StepByLog {
        static_assert(_Step >= 2, "");
        static_assert(_Start >= 1, "");
        
        std::vector<std::size_t> operator()(std::size_t min, std::size_t max) {
            std::vector<std::size_t> steps;
            std::size_t value = _Start;
            while(value < min) value *= _Step;
            steps.push_back(value);
            while(value <= max) {
                value *= _Step;
                steps.push_back(value);
            }
            steps.push_back(ULONG_MAX);
            return steps;
        }
    };
    
    template<class _S = StepByLog<>>
    class AnalysisBySize : public AnalysisTask {
    public:
        // <size, count>
        typedef std::pair<std::size_t, std::size_t> item_type;
        typedef std::vector<item_type> list_type;
        typedef std::shared_ptr<list_type> list_type_ptr;
        
        struct ThreadInfo {
            list_type_ptr list;
            
        private:
            friend class AnalysisBySize;
            void count(std::size_t size) {
                auto prev = list->end();
                for (auto i = list->begin(); i != list->end(); prev = i, ++i) {
                    if (size < (*i).first) {
                        if (prev != list->end()) {
                            ++((*prev).second);
                            break;
                        }
                        else {
                            // first
                            ++((*i).second);
                            break;
                        }
                    }
                }
            }
        };
        typedef std::vector<ThreadInfo> thread_info_list_type;
        
        AnalysisBySize(std::size_t min, std::size_t max)
        : min_(std::max(std::size_t(1), min)), max_(max), step_value_(_S()(min_, max_)) {
            std::max(1, 2);
        }
        
        std::shared_ptr<thread_info_list_type> data() {
            return thread_info_list_;
        }
    protected:
        void Run() override;
        list_type_ptr MakeEmptyList() {
            auto list = std::make_shared<list_type>();
            std::for_each(step_value_.begin(), step_value_.end(), [&](auto s) {
                list->push_back(std::make_pair(s, std::size_t(0)));
            });
            return list;
        }
        
    private:
        std::size_t min_ = 0;
        std::size_t max_ = 0;
        std::shared_ptr<thread_info_list_type> thread_info_list_ = std::make_shared<thread_info_list_type>();
        std::vector<std::size_t> step_value_;
    };
    
    
    template<class _S>
    void AnalysisBySize<_S>::Run() {
        auto func = [&](auto s) {
            ThreadInfo threadInfo;
            threadInfo.list = MakeEmptyList();
            std::for_each(s->data().begin(), s->data().end(), [&](auto& mem) {
                threadInfo.count(mem.size);
            });
            thread_info_list_->emplace_back(threadInfo);
        };
        pool().EnumerateRunningPool(func);
        pool().EnumerateDeadPool(func);
    }
}

#endif /* AnalysisBySize_hpp */
