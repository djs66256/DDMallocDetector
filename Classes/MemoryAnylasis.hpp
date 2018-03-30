//
//  MemoryAnylasis.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef MemoryAnylasis_hpp
#define MemoryAnylasis_hpp

#include <stdio.h>
#include "MemoryDetector.hpp"

namespace MD {
    class MemoryAnylasis : public MemoryDetector::Observer {
    public:
        void connect();
        
        void OnDataOverflow();
        
        ~MemoryAnylasis();
    };
}

#endif /* MemoryAnylasis_hpp */
