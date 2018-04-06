//
//  AnalysisByTime.hpp
//  DDMallocDetector
//
//  Created by daniel on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AnalysisByTime_hpp
#define AnalysisByTime_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <iostream>
#include "AnalysisTask.hpp"
#include "AnalysisHelper.h"

namespace MD {
    
    template<class _S = StepByLog<>>
    class AnalysisByTime final : public AnalysisTask {
    public:
        typedef std::pair<std::size_t, double> item_type;
        typedef std::vector<item_type> list_type;
        typedef std::shared_ptr<list_type> list_type_ptr;
        struct ThreadInfo {
            list_type_ptr list;
            std::string name;
            
            void Print() {
                std::cout << name << std::endl;
                std::for_each(list->begin(), list->end(), [](auto p) {
                    std::cout << "(" << p.first << "," << p.second << ")" << std::endl;
                });
            }
        };
        typedef std::vector<ThreadInfo> thread_list_type;
        typedef std::shared_ptr<thread_list_type> thread_list_type_ptr;
        
        AnalysisByTime(std::size_t min, std::size_t max)
        : min_(std::max(std::size_t(1), min)), max_(max), step_value_(_S()(min_, max_)) {
        }
        
        thread_list_type_ptr data() { return data_; }
        list_type_ptr all_list() { return all_list_; }
    
    protected:
        void Run() override;
        
    private:
        
        list_type_ptr MakeEmptyList() {
            auto list = std::make_shared<list_type>();
            std::for_each(step_value_.begin(), step_value_.end(), [&](auto s) {
                list->push_back(std::make_pair(s, std::size_t(0)));
            });
            return list;
        }
        
        std::size_t min_ = 0;
        std::size_t max_ = 0;
        thread_list_type_ptr data_ = std::make_shared<thread_list_type>();
        list_type_ptr all_list_ = std::make_shared<list_type>();
        std::vector<std::size_t> step_value_;
    };
    
    template<class _S>
    void AnalysisByTime<_S>::Run() {
        struct Counter {
            std::size_t size;
            double duration = 0;
            int count = 0;
            Counter(std::size_t s) : size(s) {}
        };
        std::vector<Counter> g_counter;
        std::for_each(step_value_.begin(), step_value_.end(), [&](auto s) {
            g_counter.emplace_back(Counter(s));
        });
        
        auto func = [&](auto st) {
            std::vector<Counter> counter;
            std::for_each(step_value_.begin(), step_value_.end(), [&](auto s) {
                counter.emplace_back(Counter(s));
            });
            
            std::for_each(st->data().begin(), st->data().end(), [&](auto& mem) {
                std::size_t size = mem.size;
                
                std::size_t prev = 0;
                for (std::size_t i = 0; i < counter.size(); prev = i, ++i) {
                    if (size <= counter.at(i).size) {
                        auto& c = counter.at(prev);
                        c.duration += mem.end_time - mem.start_time;
                        c.count += 1;
                        
                        auto& gc = g_counter.at(prev);
                        gc.duration += mem.end_time - mem.start_time;
                        gc.count += 1;
                        break;
                    }
                }
//                auto prev = counter.begin();
//                for (auto i = counter.begin(); i != counter.end(); prev = i, ++i) {
//                    if (size <= (*i).size) {
//                        auto c = *prev;
//                        c.duration += mem.end_time - mem.start_time;
//                        c.count += 1;
//                        break;
//                    }
//                }
            });
            
            list_type_ptr list = std::make_shared<list_type>();
            std::for_each(counter.begin(), counter.end(), [&](auto& c) {
                list->emplace_back(std::make_pair(c.size, c.count == 0 ? 0 : c.duration / c.count));
            });
            
            ThreadInfo threadInfo;
            threadInfo.name = st->name();
            threadInfo.list = list;
            data_->emplace_back(std::move(threadInfo));
        };
        
        pool().EnumerateRunningPool(func);
        pool().EnumerateDeadPool(func);
        
        std::for_each(g_counter.begin(), g_counter.end(), [&](auto& c) {
            all_list_->emplace_back(c.size, c.count == 0 ? 0 : c.duration / c.count);
        });
    }
}

#endif /* AnalysisByTime_hpp */
