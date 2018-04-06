//
//  Normalize.hpp
//  DDMallocDetector
//
//  Created by daniel on 2018/4/1.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef Normalize_h
#define Normalize_h

#include <vector>
#include <tuple>
#include <functional>
#include <memory>
#include <cmath>
#include <assert.h>

namespace MD {
    namespace Normalize {
        
        template<class _T = std::pair<class _T1, class _T2>>
        class Normalize {
        public:
            typedef _T value_type;
            typedef typename std::vector<_T> value_list_type;
            typedef typename std::shared_ptr<value_list_type> value_list_type_ptr;
            
            virtual value_list_type_ptr operator()(value_list_type_ptr list) {
                return list;
            }
        };
        
        template<class _T = std::pair<class _T1, class _T2>>
        class CompositeNormalize : public Normalize<_T> {
        public:
            typedef Normalize<_T> super;
            typedef typename super::value_list_type_ptr value_list_type_ptr;
            CompositeNormalize(value_list_type_ptr list) : list_(list) {}
            CompositeNormalize& then(Normalize<_T>& normalize) {
                list_ = normalize(list_);
                return *this;
            }
            CompositeNormalize& then(Normalize<_T>&& normalize) {
                // to lvalue
                return then(normalize);
            }

            value_list_type_ptr list() { return list_; }
            
        private:
            value_list_type_ptr list_;
        };
        
        template<class _T>
        inline CompositeNormalize<_T> make_normalize(std::shared_ptr<_T> value) {
            return CompositeNormalize<_T>(value);
        }
        
        template<class _T = std::pair<class _T1, class _T2>>
        class Scale : public Normalize<_T> {
            public:
            typedef Normalize<_T> root;
            typedef typename root::value_type value_type;
            typedef typename root::value_list_type_ptr value_list_type_ptr;
            typedef typename value_type::first_type first_type;
            typedef typename value_type::second_type second_type;

            Scale& scale(std::function<void(value_type&)> scaleFunc) { scaleFunc_ = scaleFunc; return *this; }
            value_list_type_ptr operator()(value_list_type_ptr list) {
                if (scaleFunc_) {
                    std::for_each(list->begin(), list->end(), [&](value_type& v) {
                        scaleFunc_(v);
                    });
                }
                return list;
            }
            private:
            std::function<void(value_type&)> scaleFunc_;
        };

        template<class _T = std::pair<class _T1, class _T2>>
        class Compress : public Normalize<_T> {
            public:
            typedef Normalize<_T> root;
            typedef typename root::value_type value_type;
            typedef typename root::value_list_type value_list_type;
            typedef typename root::value_list_type_ptr value_list_type_ptr;

            Compress(std::size_t maxSize) : max_size_(maxSize) {
                assert(maxSize > 4);
            }

            value_list_type_ptr operator()(value_list_type_ptr list) {
//                std::size_t size = floor(double(list->size()) / double(max_size_ - 1));
                if (max_size_ <= 1 || list->size() <= max_size_) return list;
                
                auto delta = (list->at(list->size() - 1).first - list->at(0).first) / (max_size_ - 1);
                if (delta <= 1) {
//                    printf("first: %ld, last: %ld, count: %ld\n", list->at(list->size() - 1).first, list->at(0).first, list->size());
                    return list;
                }
                auto x = list->at(0).first;
                value_list_type_ptr new_ptr = std::make_shared<value_list_type>();
                for (auto i = list->begin(); i != list->end(); ) {
                    auto new_value = value_type(x, 0);
                    while ((*i).first <= x && i != list->end()) {
                        new_value.second += (*i).second;
                        new_value.first = (*i).first;
                        ++i;
                    }
                    new_ptr->emplace_back(std::move(new_value));
                    x += delta;
                }
                return new_ptr;
            }

            private:
            std::size_t max_size_ = 256;
        };
    }
}

#endif /* Normalize_h */
