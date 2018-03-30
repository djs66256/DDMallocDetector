//
//  MemoryAnylasis.cpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#include "MemoryAnylasis.hpp"

namespace MD {
    
    void MemoryAnylasis::connect() {
        MemoryDetector::GetInstance()->addObserver(this);
    }

    void MemoryAnylasis::OnDataOverflow() {
        MemoryDetector::GetInstance()->Stop();
    }
    
    MemoryAnylasis::~MemoryAnylasis() {
        MemoryDetector::GetInstance()->removeObserver(this);
    }
}
