//
//  AxisAnchors.hpp
//  DDMallocDetector
//
//  Created by hzduanjiashun on 2018/4/2.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef AxisAnchors_hpp
#define AxisAnchors_hpp

#include <stdio.h>
#include <cmath>
#include <string>
#include <functional>
#include <strstream>
#include <vector>
#include <assert.h>
#include "Layer.hpp"

namespace MD {
    class Anchors {
    public:
        virtual std::size_t count() { return 0; }
        virtual double positionAt(std::size_t idx) { return 0; } // return percentage
        virtual std::string nameAt(std::size_t idx) { return std::string(); }
    };
    
    template<class _T>
    class LinearAnchors : public Anchors {
    public:
        typedef _T value_type;
        typedef std::function<std::string (double)> formatter_type;
        
        LinearAnchors() {};
        LinearAnchors(value_type min, value_type max, int count) 
        : min_(min), max_(max), count_(count) {
          assert(max > min);
          assert(count > 1);
        }
        
        std::size_t count() override { return count_; }
        double positionAt(std::size_t idx) override { return double(idx) / (count_ - 1); }
        std::string nameAt(std::size_t idx) override {
            if (formatter_) {
                std::string name = formatter_(value_type(double(max_ - min_) / (count_ - 1) * idx));
                return name;
            }
            else {
                std::string name;
                std::strstream s;
                s << idx;
                s >> name;
                return name;
            }
        }
        
        void setRange(value_type min, value_type max) { min_ = min; max_ = max; }
        value_type min() { return min_; }
        value_type max() { return max_; }
        void setFormatter(formatter_type f) {
            formatter_ = f;
        }
        
    private:
        value_type min_ = 0, max_ = 0;
        int count_ = 10;
        formatter_type formatter_;
    };
    
    template<class _T>
    class DiscreteAnchors : public Anchors {
    public:
        typedef _T value_type;
        typedef std::function<std::string (value_type&)> formatter_type;
        typedef std::shared_ptr<std::vector<value_type>> value_list_type;

        DiscreteAnchors() {}
        DiscreteAnchors(value_list_type points) : points_(points), display_count_(points->size()) { }

        void setPoints(value_list_type points) {
            points_ = points;
            UpdateDuration();
        }
        
        void setMaxCount(int maxCount) {
            assert(maxCount > 1);
            max_count_ = maxCount;
            UpdateDuration();
        }

        std::size_t count() override { return display_count_; }
        double positionAt(std::size_t idx) override { return double(idx) * duration_ / (points_->size() - 1); }
        std::string nameAt(std::size_t idx) override {
            if (formatter_) {
                std::string name = formatter_(points_->at(idx * duration_));
                return name;
            }
            else {
                std::string name;
                std::strstream s;
                s << idx;
                s >> name;
                return name;
            }
        }
        void setFormatter(formatter_type f) {
            formatter_ = f;
        }

    private:
        void UpdateDuration() {
            if (points_ && points_->size() > max_count_) {
                display_count_ = points_->size();
                duration_ = 1;
                do {
                    duration_ *= 2;
                    display_count_ /= 2;
                } while (display_count_ > max_count_);
            }
            else {
                display_count_ = points_ ? points_->size() : 0;
                duration_ = 1;
            }
        }
        
        int64_t max_count_ = 10, display_count_ = 0;
        int64_t duration_ = 1;
        value_list_type points_;
        formatter_type formatter_;
    };
}

#endif /* AxisAnchors_hpp */
