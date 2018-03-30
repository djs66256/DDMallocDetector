//
//  Macros.h
//  cfunction
//
//  Created by hzduanjiashun on 2018/3/30.
//  Copyright © 2018年 Daniel. All rights reserved.
//

#ifndef Macros_h
#define Macros_h

#define MD_NO_COPY(TypeName)            \
    TypeName(const TypeName&) = delete; \
    TypeName(const TypeName&&) = delete;

#define MD_NO_ASSIGN(TypeName)                      \
    TypeName& operater= (const TypeName&) = delete; \
    TypeName& operater= (const TypeName&&) = delete;

#define MD_NO_COPY_ASSIGN(TypeName) \
    MD_NO_COPY(TypeName)            \
    MD_NO_ASSIGN(TypeName)

#endif /* Macros_h */
