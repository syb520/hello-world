/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Fs_ObjectCreator.h
 *  作者: luwei
 *  日期: 2018/07/16
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_OBJECTCREATOR_H_
#define SERIALIZE_OBJECTCREATOR_H_

#include <tuple>
#include <utility>
#include <type_traits>
#include "../../I_Serialize.h"


class Fs_ObjectCreator
{
public:
    virtual ~Fs_ObjectCreator() { }
    virtual const char* CreatorName() = 0;
};

template<class ClsObj, class... ARGS>
class Fs_ObjectCreatorProxy : public Fs_ObjectCreator
{
public:
    typedef ClsObj* (*_CREATORFUNC_)(unsigned int, ARGS...);

public:
    ClsObj* Create(unsigned int apiId, ARGS... args) {

        // 使用用户默认构造函数构造
        ClsObj* ptr = nullptr;
        if (OnCreateByUserFunctor(apiId, &ptr, std::make_tuple(std::forward<ARGS>(args)...)))
            return ptr;

        //
        _CREATORFUNC_ func = nullptr;

        // 获取默认构造回调函数
        func = OnGetFunctor();

        // 调用
        if (func)
            return func(apiId, std::forward<ARGS>(args)...);

        return nullptr;
    }

protected:
    virtual bool OnCreateByUserFunctor(unsigned int, ClsObj** ptr, std::tuple<ARGS...>& t) { (void)(ptr); (void)(t); return false; }
    virtual _CREATORFUNC_ OnGetFunctor() { return nullptr; }
};

template<class T, class B, class ... ARGS>
class Fs_Creator_ : public Fs_ObjectCreatorProxy<Fs_ClsObject, ARGS...>
{
    const char* _name;
    const char* CreatorName() { return _name; }
public:
    Fs_Creator_(std::size_t _guid_, const char* _name_, bool _replaced_) : _name(_name_) {
        IObjectFactory* pFactory = Fs_Serialize::GlobalSerializerApi()->GetObjectFactory();
        pFactory->Regist(_guid_, this, _replaced_);
    }

    _CREATORFUNC_ OnGetFunctor() {
        return (&Fs_Creator_::Functor<ARGS...>);
    }

    template<class... _ARGS>
    static Fs_ClsObject* Functor(unsigned int apiId, _ARGS... args) {
        T* pObj = Fs_Obj_ObjectConstructor::CreateF<T, _ARGS...>(std::forward<_ARGS>(args)...);
        Fs_ClsObjectSerializeProxy<T, B>* pClsObjProxy = new Fs_ClsObjectSerializeProxy<T, B>(
            pObj, apiId, size_t((B*)pObj), size_t(pObj));
        return pClsObjProxy;
    }
};

template<class T, class B, class F, class ... ARGS>
class Fs_Creator_F : public Fs_ObjectCreatorProxy<Fs_ClsObject, ARGS...>
{
    F _f;
    const char* _name;
    const char* CreatorName() { return _name; }
public:
    Fs_Creator_F(std::size_t _guid_, F f, const char* _name_, bool _replaced_) : _f(f), _name(_name_) {
        IObjectFactory* pFactory = Fs_Serialize::GlobalSerializerApi()->GetObjectFactory();
        pFactory->Regist(_guid_, this, _replaced_);
    }

    bool OnCreateByUserFunctor(unsigned int apiId, Fs_ClsObject** ppClsObj, std::tuple<__VA_ARGS__>& t) {               
        std::function<B*(ARGS...)> CBFUNC = _f;
        T* pObj = nullptr;
        if (CBFUNC != nullptr) {                                                                                        
            pObj = dynamic_cast<T*>(_Fs_Obj_Callback_Functor_(CBFUNC, t));
                IObjectFactory* pFactory = Fs_Serialize::GlobalSerializerApi()->GetObjectFactory();                     
                Fs_ClsObjectSerializeProxy<T,B>* pClsObjProxy = new Fs_ClsObjectSerializeProxy<T,B>(
                    pObj,apiId,size_t((B*)pObj), size_t(pObj));                                                    
            *ppClsObj = pClsObjProxy;                                                                                   
        }                                                                                                               
        return (pObj != nullptr);                                                                                       
    }   
};

// template<class T, class ... ARGS>
// class Fs_Creator_T : public Fs_ObjectCreatorProxy<Fs_ClsObject, ARGS...>
// {
//     const char* _name;
//     const char* CreatorName() { return _name; }
// public:
//     Fs_Creator_F(std::size_t _guid_, const char* _name_, bool _replaced_) : _name(_name_) {
//         IObjectFactory* pFactory = Fs_Serialize::GlobalSerializerApi()->GetObjectFactory();
//         pFactory->Regist(_guid_, this, _replaced_);
//     }
// 
//     template<typename B>                                                                
//     inline static auto Fs_CREATOR_T() {                                                             
//         std::size_t _guid_ = typeid(B).hash_code();                                                 
//         auto _ = Fs_ALLCREATOR_T();
//         if (_.find(_guid_) != _.end()) return _[_guid_];                                            
//         static Fs_Creator_<T, B> _creator(_guid_, CreatorName(), true);
//         _[_guid_] = &_creator;                                                                      
//         return _creator;                                                                            
//     }                                                                                               
//     inline static std::map<std::size_t, Fs_ObjectCreator*>& Fs_ALLCREATOR_T() {                     
//         static std::map<std::size_t, Fs_ObjectCreator*> _; return _; 
//     }
// };

#endif  // SERIALIZE_OBJECTCREATOR_H_
