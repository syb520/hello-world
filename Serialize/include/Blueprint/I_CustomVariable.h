/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  �ļ�: I_CustomVariable.h 
 *  ����: luwei
 *  ����: 2018/09/17
 *  �汾: 1.0 
 *  ˵��: 
 ******************************************************************/  
  
#ifndef SERIALIZE_I_CUSTOMVARIABLE_H_  
#define SERIALIZE_I_CUSTOMVARIABLE_H_

#include "../Serialize/Serialize/Serialize_Micro.h" 
#include "../Serialize/Serialize/Serialize_Execr_T.h"
//#include "../Serialize_API.h"

//���ʼ���
enum AccessLevel {
    E_Public,
    E_Protected,
    E_Private
};

class Fs_NodeVariable 
{
public:
    INodePropertyObject* NodeProperty{ nullptr };
    int Type;
    AccessLevel Access;
};

class FsBp_CustomVariable 
{
    // ���л�
    MAKE_SERIALIZE_WITH_GUID(FsBp_CustomVariable, FsBp_CustomVariable, 
        20202020, ClassName, ParentClass, Access, Members)

public:
    std::string ClassName;
    std::string ParentClass;
    AccessLevel Access;
    std::map<std::string, Fs_NodeVariable> Members;

};


#endif  // SERIALIZE_I_CUSTOMVARIABLE_H_