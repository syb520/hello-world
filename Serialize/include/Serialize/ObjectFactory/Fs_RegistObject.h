/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  文件: Fs_RegistObject.h
 *  作者: luwei
 *  日期: 2018/07/24
 *  版本: 1.0 
 *  说明: 
 ******************************************************************/  
  
#ifndef SERIALIZE_REGISTOBJECT_H_  
#define SERIALIZE_REGISTOBJECT_H_
                   
#include "Fs_ClsObjectProxy.h"
#include "Fs_ObjectCreator.h"
#include "Fs_CallbackHelper.h"

//
#ifdef MAKE_REGIST_OBJECT_WITH_GUID
#undef MAKE_REGIST_OBJECT_WITH_GUID
#define MAKE_REGIST_OBJECT_WITH_GUID(_OBJ_,_IOBJ_,_ID_SELF_,_REPLACED_,...) \
    FS_RegistObject_N(_OBJ_,_IOBJ_,1,_ID_SELF_,_REPLACED_,__VA_ARGS__)
#endif

//
#ifdef MAKE_REGIST_OBJECT_CALLBACK_WITH_GUID
#undef MAKE_REGIST_OBJECT_CALLBACK_WITH_GUID
#define MAKE_REGIST_OBJECT_CALLBACK_WITH_GUID(_OBJ_,_IOBJ_,_ID_SELF_,_REPLACED_,_CALLBACK_,...) \
    FS_RegistObject_F(_OBJ_,_IOBJ_,2,_ID_SELF_,_REPLACED_,_CALLBACK_,__VA_ARGS__)
#endif

//
#ifdef MAKE_REGIST_OBJECT
#undef MAKE_REGIST_OBJECT
#define MAKE_REGIST_OBJECT(_OBJ_,_IOBJ_,_REPLACED_,...) \
    FS_RegistObject_N(_OBJ_,_IOBJ_,3,MAKE_GUID(_OBJ_),_REPLACED_,__VA_ARGS__)
#endif

//
#ifdef MAKE_REGIST_OBJECT_CALLBACK
#undef MAKE_REGIST_OBJECT_CALLBACK
#define MAKE_REGIST_OBJECT_CALLBACK(_OBJ_,_IOBJ_,_REPLACED_,_CALLBACK_,...) \
    FS_RegistObject_F(_OBJ_,_IOBJ_,4,MAKE_GUID(_OBJ_),_REPLACED_,_CALLBACK_,__VA_ARGS__)
#endif

#ifndef FS_RegistObject_N
#define FS_RegistObject_N(_OBJ_,_IOBJ_,_INDEX_,_ID_SELF_,_REPLACED_,...)                            \
class Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_ : public Fs_Creator_<_OBJ_, _IOBJ_, ##__VA_ARGS__>        \
{                                                                                                   \
public:                                                                                             \
    Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_() :Fs_Creator_(_ID_SELF_,#_OBJ_,_REPLACED_) {}              \
};                                                                                                  \
__declspec(selectany) Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_ g_Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_;
#endif

#ifndef FS_RegistObject_F
#define FS_RegistObject_F(_OBJ_,_IOBJ_,_INDEX_,_ID_SELF_,_REPLACED_,_CALLBACK_,...)                 \
class Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_ :                                                         \
    public Fs_Creator_F<_OBJ_, _IOBJ_, decltype(_CALLBACK_), ##__VA_ARGS__>                         \
{                                                                                                   \
public:                                                                                             \
    Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_() :Fs_Creator_F(_ID_SELF_,_CALLBACK_, #_OBJ_, _REPLACED_) {}\
};                                                                                                  \
__declspec(selectany) Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_ g_Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_;
#endif

#ifndef FS_RegistObject_T
#define FS_RegistObject_T(_OBJ_,_IOBJ_,_INDEX_,_ID_SELF_,_REPLACED_,_CALLBACK_,...)                 \
class Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_ : Fs_ObjectCreator                                        \
{                                                                                                   \
    const char* CreatorName() { return #_OBJ_; }                                                    \
public:                                                                                             \
    Fs_Creator_##_OBJ_##_IOBJ_##_INDEX_() {                                                         \
        IObjectFactory* pFactory = Fs_Serialize::GlobalSerializerApi()->GetObjectFactory();         \
        pFactory->Regist(_ID_SELF_, this, _replaced_);                                              \
    }                                                                                               \
    template<typename T, typename B>                                                                \
    inline static auto Fs_CREATOR_T() {                                                             \
        std::size_t _guid_ = typeid(T).hash_code();                                                 \
        auto _ = Fs_ALLCREATOR_T();                                                                 \
        if (_.find(_guid_) != _.end()) return _[_guid_];                                            \
        static Fs_Creator_<T, B> _creator(_guid_, #_OBJ_, true);                                    \
        _[_guid_] = &_creator;                                                                      \
        return _creator;                                                                            \
    }                                                                                               \
    inline static std::map<std::size_t, Fs_ObjectCreator*>& Fs_ALLCREATOR_T() {                     \
        static std::map<std::size_t, Fs_ObjectCreator*> _; return _; }                              \
}
#endif
//class TestBase
//{
//
//    //MAKE_SERIALIZE_WITH_GUID(TestBase, TestBase, 1234, m_base_int)
//
//private:
//    int m_base_int;
//};
//
//class Test : public TestBase
//{
//    //public:                                                                                                                       
//    //    static auto Fs_METAOBJECT(const Test&) {
//    //        struct METAOBJECT {                                                                                                        
//    //            using type = void;                                                                                                     
//    //            using size_type = std::integral_constant<size_t, 1>;                                                                   
//    //            constexpr static const char* name() { return "Test"; }                                                               
//    //            constexpr static size_t value() { return size_type::value; }                                                           
//    //            constexpr decltype(auto) static staticMetaObject() { return std::make_tuple(&Test::m_int); }
//    //            static std::array<const char* const, size_type::value> metaIndexArray() { return Fs_METAINDEXARRAY(); }                
//    //            static auto Execr() { static Fs_Serialize::Serialize_ExecrT<Test> _instance(123, "Test"); return &_instance; }
//    //        }; static auto _ = METAOBJECT{};                                                                                           
//    //        return _;                                                                                                                  
//    //    } 
//    //
//    //protected:                                                                                                                     
//    //    virtual void Fs_Virtual() {}                                                                                                   
//    //    static std::array<const char* const, 1> Fs_METAINDEXARRAY() {                                                                  
//    //        static std::array<const char* const, 1> _ = { "m_int"  }; return _; }
//    
//        //template<class T, class Base>
//        //static std::enable_if_t<std::is_same<T, Base>::value || !Fs_Serialize::is_serialize<Base>::value> FS_REGISTSERIALIZEMETAOBJECT(int&) {
//        //    using EXECR = decltype(Fs_METAOBJECT(std::declval<T>()));
//        //    Fs_Serialize::GlobalSerializerApi()->GetSerializerMgr()->RegistSerializeExecr(EXECR::Execr());
//        //}
//        //template<class T, class Base>
//        //static std::enable_if_t<!std::is_same<T, Base>::value && Fs_Serialize::is_serialize<Base>::value> FS_REGISTSERIALIZEMETAOBJECT(int&&) {
//        //    using EXECR = decltype(Fs_METAOBJECT(std::declval<T>()));
//        //    Fs_Serialize::GlobalSerializerApi()->GetSerializerMgr()->RegistSerializeExecr(EXECR::Execr());                             
//        //    Base::FS_REGISTSERIALIZEMETAOBJECT();}
//        //
//        //struct Fs_AUTOREGISTER { Fs_AUTOREGISTER() { int i; Test::FS_REGISTSERIALIZEMETAOBJECT<Test, TestBase>(i); } };
//        //Fs_AUTOREGISTER _autoregister;
//
//    MAKE_SERIALIZE_WITH_GUID(Test, Test, 123, m_int)
//
//private:
//    int m_int;
//};
//
//MAKE_REGIST_OBJECT_WITH_GUID(Test, Test, 123, true)
//MAKE_REGIST_OBJECT_WITH_GUID(TestBase, TestBase, 1234, true)


#endif  // SERIALIZE_REGISTOBJECT_H_

