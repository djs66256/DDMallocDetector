//
//  ThreadLocal.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/27.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef ThreadLocal_hpp
#define ThreadLocal_hpp

#include <stdio.h>
#include <pthread/pthread.h>
#include <memory>

namespace MD {
//    template<class _Tp>
//    static void Deallocator(void *p) {
//        delete p;
//    }
    
    template<class T>
    struct Constructor {
        T *operator()() {
            return new T();
        }
    };
    
    template<class _Tp, class _Constructor = Constructor<_Tp>>
    class ThreadLocal {
    public:
        typedef _Tp value_type;
        ThreadLocal(pthread_key_t key) : key_(key) {}
        
        value_type* value() {
            pthread_key_t key = key_;
            value_type* value = reinterpret_cast<value_type *>(pthread_getspecific(key));
            if (value == nullptr) {
                value = _Constructor()();// new value_type();
                pthread_setspecific(key, reinterpret_cast<void *>(value));
            }
            return value;
        }
        
        value_type* operator->() { return value(); }
        
    private:
        
        static void deallocate(void *p) {
            value_type *v = reinterpret_cast<value_type *>(p);
            delete v;
        }
        
        pthread_key_t key_;
    };
}

#endif /* ThreadLocal_hpp */
