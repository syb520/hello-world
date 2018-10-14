/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Utility.h
 *  作者: luwei
 *  日期: 2018/08/07
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_UTILITY_H_  
#define SERIALIZE_UTILITY_H_

#include <xstring>
#include <type_traits>
#include "../include/I_Data_Helper.h"

namespace Fs_Utility {

    class GUID_Generator : public IGuidGenerator {
    public:
        virtual std::string Create();
        virtual std::string Create(std::size_t clsId);
        virtual std::string Create(std::size_t szID[4]);
        virtual std::string Create(std::size_t, std::size_t, std::size_t, std::size_t);
        virtual std::size_t Hash(const std::string&);
    };

    class Fs_GUID 
    {
        std::size_t _uuid[4];

    public:
        static Fs_GUID Build();
        static Fs_GUID Build(std::size_t clsId);
        static Fs_GUID Build(std::size_t szID[4]);
        static Fs_GUID Build(std::size_t, std::size_t, std::size_t, std::size_t);
        std::string Format();
        std::size_t Hash();
    };
}


#endif  // SERIALIZE_UTILITY_H_