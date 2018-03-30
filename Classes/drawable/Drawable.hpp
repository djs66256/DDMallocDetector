//
//  Drawable.hpp
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/28.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include <stdio.h>

namespace MD {
class Drawable {
public:
    virtual void Draw() = 0;
};
}

#endif /* Drawable_hpp */
