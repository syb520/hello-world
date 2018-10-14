/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Serialize_Execr.h
 *  作者: luwei
 *  日期: 2018/08/06
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_SERIALIZE_EXECR_H_  
#define SERIALIZE_SERIALIZE_EXECR_H_

#include "../../I_Serialize.h"

class Fs_ClsObject;

namespace Fs_Serialize
{
    class Serialize_Execr
    {
    public:
        virtual ~Serialize_Execr() {}
        virtual std::size_t GetClassId() = 0;
        virtual Fs_ClsObject* CreateClsObj(unsigned int, void*) = 0;
        virtual void Serialze(Fs_ClsObject*, Fs_Utility::IDataProp*, std::size_t) = 0;
        virtual void DeSerialze(Fs_ClsObject*, Fs_Utility::IDataPropIterator*, std::size_t) = 0;
        virtual void ModifyAttribute(Fs_ClsObject*, Fs_Utility::IDataPropIterator*, Fs_Utility::ModifyType) = 0;
    };
}

#endif  // SERIALIZE_SERIALIZE_EXECR_H_