/******************************************************************* 
 *  Copyright(c) 2000-2017 SnailGame 
 *  All rights reserved. 
 *   
 *  �ļ�: Define.h
 *  ����: luwei
 *  ����: 2018/08/03
 *  �汾: 1.0 
 *  ˵��: 
 ******************************************************************/  
  
#ifndef SERIALIZE_DEFINE_H_  
#define SERIALIZE_DEFINE_H_


namespace Fs_Micro
{

#define MAKE_ARG_LIST_1(op, arg, ...)   op(arg)
#define MAKE_ARG_LIST_2(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_1(op, __VA_ARGS__))
#define MAKE_ARG_LIST_3(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_2(op, __VA_ARGS__))
#define MAKE_ARG_LIST_4(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_3(op, __VA_ARGS__))
#define MAKE_ARG_LIST_5(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_4(op, __VA_ARGS__))
#define MAKE_ARG_LIST_6(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_5(op, __VA_ARGS__))
#define MAKE_ARG_LIST_7(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_6(op, __VA_ARGS__))
#define MAKE_ARG_LIST_8(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_7(op, __VA_ARGS__))
#define MAKE_ARG_LIST_9(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_8(op, __VA_ARGS__))
#define MAKE_ARG_LIST_10(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_9(op, __VA_ARGS__))
#define MAKE_ARG_LIST_11(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_10(op, __VA_ARGS__))
#define MAKE_ARG_LIST_12(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_11(op, __VA_ARGS__))
#define MAKE_ARG_LIST_13(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_12(op, __VA_ARGS__))
#define MAKE_ARG_LIST_14(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_13(op, __VA_ARGS__))
#define MAKE_ARG_LIST_15(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_14(op, __VA_ARGS__))
#define MAKE_ARG_LIST_16(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_15(op, __VA_ARGS__))
#define MAKE_ARG_LIST_17(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_16(op, __VA_ARGS__))
#define MAKE_ARG_LIST_18(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_17(op, __VA_ARGS__))
#define MAKE_ARG_LIST_19(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_18(op, __VA_ARGS__))
#define MAKE_ARG_LIST_20(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_19(op, __VA_ARGS__))
#define MAKE_ARG_LIST_21(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_20(op, __VA_ARGS__))
#define MAKE_ARG_LIST_22(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_21(op, __VA_ARGS__))
#define MAKE_ARG_LIST_23(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_22(op, __VA_ARGS__))
#define MAKE_ARG_LIST_24(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_23(op, __VA_ARGS__))
#define MAKE_ARG_LIST_25(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_24(op, __VA_ARGS__))
#define MAKE_ARG_LIST_26(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_25(op, __VA_ARGS__))
#define MAKE_ARG_LIST_27(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_26(op, __VA_ARGS__))
#define MAKE_ARG_LIST_28(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_27(op, __VA_ARGS__))
#define MAKE_ARG_LIST_29(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_28(op, __VA_ARGS__))
#define MAKE_ARG_LIST_30(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_29(op, __VA_ARGS__))
#define MAKE_ARG_LIST_31(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_30(op, __VA_ARGS__))
#define MAKE_ARG_LIST_32(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_31(op, __VA_ARGS__))
#define MAKE_ARG_LIST_33(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_32(op, __VA_ARGS__))
#define MAKE_ARG_LIST_34(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_33(op, __VA_ARGS__))
#define MAKE_ARG_LIST_35(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_34(op, __VA_ARGS__))
#define MAKE_ARG_LIST_36(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_35(op, __VA_ARGS__))
#define MAKE_ARG_LIST_37(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_36(op, __VA_ARGS__))
#define MAKE_ARG_LIST_38(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_37(op, __VA_ARGS__))
#define MAKE_ARG_LIST_39(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_38(op, __VA_ARGS__))
#define MAKE_ARG_LIST_40(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_39(op, __VA_ARGS__))
#define MAKE_ARG_LIST_41(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_40(op, __VA_ARGS__))
#define MAKE_ARG_LIST_42(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_41(op, __VA_ARGS__))
#define MAKE_ARG_LIST_43(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_42(op, __VA_ARGS__))
#define MAKE_ARG_LIST_44(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_43(op, __VA_ARGS__))
#define MAKE_ARG_LIST_45(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_44(op, __VA_ARGS__))
#define MAKE_ARG_LIST_46(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_45(op, __VA_ARGS__))
#define MAKE_ARG_LIST_47(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_46(op, __VA_ARGS__))
#define MAKE_ARG_LIST_48(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_47(op, __VA_ARGS__))
#define MAKE_ARG_LIST_49(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_48(op, __VA_ARGS__))
#define MAKE_ARG_LIST_50(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_49(op, __VA_ARGS__))
#define MAKE_ARG_LIST_51(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_50(op, __VA_ARGS__))
#define MAKE_ARG_LIST_52(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_51(op, __VA_ARGS__))
#define MAKE_ARG_LIST_53(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_52(op, __VA_ARGS__))
#define MAKE_ARG_LIST_54(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_53(op, __VA_ARGS__))
#define MAKE_ARG_LIST_55(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_54(op, __VA_ARGS__))
#define MAKE_ARG_LIST_56(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_55(op, __VA_ARGS__))
#define MAKE_ARG_LIST_57(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_56(op, __VA_ARGS__))
#define MAKE_ARG_LIST_58(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_57(op, __VA_ARGS__))
#define MAKE_ARG_LIST_59(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_58(op, __VA_ARGS__))
#define MAKE_ARG_LIST_60(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_59(op, __VA_ARGS__))
#define MAKE_ARG_LIST_61(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_60(op, __VA_ARGS__))
#define MAKE_ARG_LIST_62(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_61(op, __VA_ARGS__))
#define MAKE_ARG_LIST_63(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_62(op, __VA_ARGS__))
#define MAKE_ARG_LIST_64(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_63(op, __VA_ARGS__))
#define MAKE_ARG_LIST_65(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_64(op, __VA_ARGS__))
#define MAKE_ARG_LIST_66(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_65(op, __VA_ARGS__))
#define MAKE_ARG_LIST_67(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_66(op, __VA_ARGS__))
#define MAKE_ARG_LIST_68(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_67(op, __VA_ARGS__))
#define MAKE_ARG_LIST_69(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_68(op, __VA_ARGS__))
#define MAKE_ARG_LIST_70(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_69(op, __VA_ARGS__))
#define MAKE_ARG_LIST_71(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_70(op, __VA_ARGS__))
#define MAKE_ARG_LIST_72(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_71(op, __VA_ARGS__))
#define MAKE_ARG_LIST_73(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_72(op, __VA_ARGS__))
#define MAKE_ARG_LIST_74(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_73(op, __VA_ARGS__))
#define MAKE_ARG_LIST_75(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_74(op, __VA_ARGS__))
#define MAKE_ARG_LIST_76(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_75(op, __VA_ARGS__))
#define MAKE_ARG_LIST_77(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_76(op, __VA_ARGS__))
#define MAKE_ARG_LIST_78(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_77(op, __VA_ARGS__))
#define MAKE_ARG_LIST_79(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_78(op, __VA_ARGS__))
#define MAKE_ARG_LIST_80(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_79(op, __VA_ARGS__))
#define MAKE_ARG_LIST_81(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_80(op, __VA_ARGS__))
#define MAKE_ARG_LIST_82(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_81(op, __VA_ARGS__))
#define MAKE_ARG_LIST_83(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_82(op, __VA_ARGS__))
#define MAKE_ARG_LIST_84(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_83(op, __VA_ARGS__))
#define MAKE_ARG_LIST_85(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_84(op, __VA_ARGS__))
#define MAKE_ARG_LIST_86(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_85(op, __VA_ARGS__))
#define MAKE_ARG_LIST_87(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_86(op, __VA_ARGS__))
#define MAKE_ARG_LIST_88(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_87(op, __VA_ARGS__))
#define MAKE_ARG_LIST_89(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_88(op, __VA_ARGS__))
#define MAKE_ARG_LIST_90(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_89(op, __VA_ARGS__))
#define MAKE_ARG_LIST_91(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_90(op, __VA_ARGS__))
#define MAKE_ARG_LIST_92(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_91(op, __VA_ARGS__))
#define MAKE_ARG_LIST_93(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_92(op, __VA_ARGS__))
#define MAKE_ARG_LIST_94(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_93(op, __VA_ARGS__))
#define MAKE_ARG_LIST_95(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_94(op, __VA_ARGS__))
#define MAKE_ARG_LIST_96(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_95(op, __VA_ARGS__))
#define MAKE_ARG_LIST_97(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_96(op, __VA_ARGS__))
#define MAKE_ARG_LIST_98(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_97(op, __VA_ARGS__))
#define MAKE_ARG_LIST_99(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_98(op, __VA_ARGS__))
#define MAKE_ARG_LIST_100(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_99(op, __VA_ARGS__))
#define MAKE_ARG_LIST_101(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_100(op, __VA_ARGS__))
#define MAKE_ARG_LIST_102(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_101(op, __VA_ARGS__))
#define MAKE_ARG_LIST_103(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_102(op, __VA_ARGS__))
#define MAKE_ARG_LIST_104(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_103(op, __VA_ARGS__))
#define MAKE_ARG_LIST_105(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_104(op, __VA_ARGS__))
#define MAKE_ARG_LIST_106(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_105(op, __VA_ARGS__))
#define MAKE_ARG_LIST_107(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_106(op, __VA_ARGS__))
#define MAKE_ARG_LIST_108(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_107(op, __VA_ARGS__))
#define MAKE_ARG_LIST_109(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_108(op, __VA_ARGS__))
#define MAKE_ARG_LIST_110(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_109(op, __VA_ARGS__))
#define MAKE_ARG_LIST_111(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_110(op, __VA_ARGS__))
#define MAKE_ARG_LIST_112(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_111(op, __VA_ARGS__))
#define MAKE_ARG_LIST_113(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_112(op, __VA_ARGS__))
#define MAKE_ARG_LIST_114(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_113(op, __VA_ARGS__))
#define MAKE_ARG_LIST_115(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_114(op, __VA_ARGS__))
#define MAKE_ARG_LIST_116(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_115(op, __VA_ARGS__))
#define MAKE_ARG_LIST_117(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_116(op, __VA_ARGS__))
#define MAKE_ARG_LIST_118(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_117(op, __VA_ARGS__))
#define MAKE_ARG_LIST_119(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_118(op, __VA_ARGS__))
#define MAKE_ARG_LIST_120(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_119(op, __VA_ARGS__))

#define MAKE_STR(str) #str

#define SEPERATOR ,
#define CON_STR_1(element, ...) MAKE_STR(element)
#define CON_STR_2(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_1(__VA_ARGS__))
#define CON_STR_3(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_2(__VA_ARGS__))
#define CON_STR_4(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_3(__VA_ARGS__))
#define CON_STR_5(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_4(__VA_ARGS__))
#define CON_STR_6(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_5(__VA_ARGS__))
#define CON_STR_7(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_6(__VA_ARGS__))
#define CON_STR_8(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_7(__VA_ARGS__))
#define CON_STR_9(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_8(__VA_ARGS__))
#define CON_STR_10(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_9(__VA_ARGS__))
#define CON_STR_11(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_10(__VA_ARGS__))
#define CON_STR_12(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_11(__VA_ARGS__))
#define CON_STR_13(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_12(__VA_ARGS__))
#define CON_STR_14(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_13(__VA_ARGS__))
#define CON_STR_15(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_14(__VA_ARGS__))
#define CON_STR_16(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_15(__VA_ARGS__))
#define CON_STR_17(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_16(__VA_ARGS__))
#define CON_STR_18(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_17(__VA_ARGS__))
#define CON_STR_19(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_18(__VA_ARGS__))
#define CON_STR_20(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_19(__VA_ARGS__))
#define CON_STR_21(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_20(__VA_ARGS__))
#define CON_STR_22(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_21(__VA_ARGS__))
#define CON_STR_23(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_22(__VA_ARGS__))
#define CON_STR_24(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_23(__VA_ARGS__))
#define CON_STR_25(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_24(__VA_ARGS__))
#define CON_STR_26(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_25(__VA_ARGS__))
#define CON_STR_27(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_26(__VA_ARGS__))
#define CON_STR_28(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_27(__VA_ARGS__))
#define CON_STR_29(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_28(__VA_ARGS__))
#define CON_STR_30(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_29(__VA_ARGS__))
#define CON_STR_31(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_30(__VA_ARGS__))
#define CON_STR_32(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_31(__VA_ARGS__))
#define CON_STR_33(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_32(__VA_ARGS__))
#define CON_STR_34(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_33(__VA_ARGS__))
#define CON_STR_35(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_34(__VA_ARGS__))
#define CON_STR_36(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_35(__VA_ARGS__))
#define CON_STR_37(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_36(__VA_ARGS__))
#define CON_STR_38(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_37(__VA_ARGS__))
#define CON_STR_39(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_38(__VA_ARGS__))
#define CON_STR_40(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_39(__VA_ARGS__))
#define CON_STR_41(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_40(__VA_ARGS__))
#define CON_STR_42(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_41(__VA_ARGS__))
#define CON_STR_43(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_42(__VA_ARGS__))
#define CON_STR_44(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_43(__VA_ARGS__))
#define CON_STR_45(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_44(__VA_ARGS__))
#define CON_STR_46(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_45(__VA_ARGS__))
#define CON_STR_47(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_46(__VA_ARGS__))
#define CON_STR_48(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_47(__VA_ARGS__))
#define CON_STR_49(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_48(__VA_ARGS__))
#define CON_STR_50(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_49(__VA_ARGS__))
#define CON_STR_51(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_50(__VA_ARGS__))
#define CON_STR_52(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_51(__VA_ARGS__))
#define CON_STR_53(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_52(__VA_ARGS__))
#define CON_STR_54(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_53(__VA_ARGS__))
#define CON_STR_55(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_54(__VA_ARGS__))
#define CON_STR_56(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_55(__VA_ARGS__))
#define CON_STR_57(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_56(__VA_ARGS__))
#define CON_STR_58(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_57(__VA_ARGS__))
#define CON_STR_59(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_58(__VA_ARGS__))
#define CON_STR_60(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_59(__VA_ARGS__))
#define CON_STR_61(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_60(__VA_ARGS__))
#define CON_STR_62(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_61(__VA_ARGS__))
#define CON_STR_63(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_62(__VA_ARGS__))
#define CON_STR_64(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_63(__VA_ARGS__))
#define CON_STR_65(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_64(__VA_ARGS__))
#define CON_STR_66(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_65(__VA_ARGS__))
#define CON_STR_67(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_66(__VA_ARGS__))
#define CON_STR_68(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_67(__VA_ARGS__))
#define CON_STR_69(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_68(__VA_ARGS__))
#define CON_STR_70(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_69(__VA_ARGS__))
#define CON_STR_71(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_70(__VA_ARGS__))
#define CON_STR_72(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_71(__VA_ARGS__))
#define CON_STR_73(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_72(__VA_ARGS__))
#define CON_STR_74(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_73(__VA_ARGS__))
#define CON_STR_75(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_74(__VA_ARGS__))
#define CON_STR_76(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_75(__VA_ARGS__))
#define CON_STR_77(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_76(__VA_ARGS__))
#define CON_STR_78(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_77(__VA_ARGS__))
#define CON_STR_79(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_78(__VA_ARGS__))
#define CON_STR_80(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_79(__VA_ARGS__))
#define CON_STR_81(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_80(__VA_ARGS__))
#define CON_STR_82(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_81(__VA_ARGS__))
#define CON_STR_83(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_82(__VA_ARGS__))
#define CON_STR_84(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_83(__VA_ARGS__))
#define CON_STR_85(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_84(__VA_ARGS__))
#define CON_STR_86(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_85(__VA_ARGS__))
#define CON_STR_87(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_86(__VA_ARGS__))
#define CON_STR_88(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_87(__VA_ARGS__))
#define CON_STR_89(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_88(__VA_ARGS__))
#define CON_STR_90(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_89(__VA_ARGS__))
#define CON_STR_91(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_90(__VA_ARGS__))
#define CON_STR_92(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_91(__VA_ARGS__))
#define CON_STR_93(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_92(__VA_ARGS__))
#define CON_STR_94(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_93(__VA_ARGS__))
#define CON_STR_95(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_94(__VA_ARGS__))
#define CON_STR_96(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_95(__VA_ARGS__))
#define CON_STR_97(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_96(__VA_ARGS__))
#define CON_STR_98(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_97(__VA_ARGS__))
#define CON_STR_99(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_98(__VA_ARGS__))
#define CON_STR_100(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_99(__VA_ARGS__))
#define CON_STR_101(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_100(__VA_ARGS__))
#define CON_STR_102(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_101(__VA_ARGS__))
#define CON_STR_103(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_102(__VA_ARGS__))
#define CON_STR_104(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_103(__VA_ARGS__))
#define CON_STR_105(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_104(__VA_ARGS__))
#define CON_STR_106(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_105(__VA_ARGS__))
#define CON_STR_107(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_106(__VA_ARGS__))
#define CON_STR_108(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_107(__VA_ARGS__))
#define CON_STR_109(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_108(__VA_ARGS__))
#define CON_STR_110(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_109(__VA_ARGS__))
#define CON_STR_111(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_110(__VA_ARGS__))
#define CON_STR_112(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_111(__VA_ARGS__))
#define CON_STR_113(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_112(__VA_ARGS__))
#define CON_STR_114(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_113(__VA_ARGS__))
#define CON_STR_115(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_114(__VA_ARGS__))
#define CON_STR_116(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_115(__VA_ARGS__))
#define CON_STR_117(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_116(__VA_ARGS__))
#define CON_STR_118(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_117(__VA_ARGS__))
#define CON_STR_119(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_118(__VA_ARGS__))
#define CON_STR_120(element, ...) MAKE_STR(element) SEPERATOR MARCO_EXPAND(CON_STR_119(__VA_ARGS__))

#define MAKE_PLACEHOLDER_LIST_0(...)
#define MAKE_PLACEHOLDER_LIST_1(arg, ...)                                                         std::placeholders::_1
#define MAKE_PLACEHOLDER_LIST_2(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_1(__VA_ARGS__)),  std::placeholders::_2  
#define MAKE_PLACEHOLDER_LIST_3(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_2(__VA_ARGS__)),  std::placeholders::_3  
#define MAKE_PLACEHOLDER_LIST_4(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_3(__VA_ARGS__)),  std::placeholders::_4  
#define MAKE_PLACEHOLDER_LIST_5(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_4(__VA_ARGS__)),  std::placeholders::_5  
#define MAKE_PLACEHOLDER_LIST_6(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_5(__VA_ARGS__)),  std::placeholders::_6  
#define MAKE_PLACEHOLDER_LIST_7(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_6(__VA_ARGS__)),  std::placeholders::_7  
#define MAKE_PLACEHOLDER_LIST_8(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_7(__VA_ARGS__)),  std::placeholders::_8  
#define MAKE_PLACEHOLDER_LIST_9(arg, ...)    MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_8(__VA_ARGS__)),  std::placeholders::_9 
#define MAKE_PLACEHOLDER_LIST_10(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_9(__VA_ARGS__)),  std::placeholders::_10 
#define MAKE_PLACEHOLDER_LIST_11(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_10(__VA_ARGS__)), std::placeholders::_11
#define MAKE_PLACEHOLDER_LIST_12(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_11(__VA_ARGS__)), std::placeholders::_12  
#define MAKE_PLACEHOLDER_LIST_13(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_12(__VA_ARGS__)), std::placeholders::_13  
#define MAKE_PLACEHOLDER_LIST_14(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_13(__VA_ARGS__)), std::placeholders::_14  
#define MAKE_PLACEHOLDER_LIST_15(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_14(__VA_ARGS__)), std::placeholders::_15  
#define MAKE_PLACEHOLDER_LIST_16(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_15(__VA_ARGS__)), std::placeholders::_16  
#define MAKE_PLACEHOLDER_LIST_17(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_16(__VA_ARGS__)), std::placeholders::_17  
#define MAKE_PLACEHOLDER_LIST_18(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_17(__VA_ARGS__)), std::placeholders::_18  
#define MAKE_PLACEHOLDER_LIST_19(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_18(__VA_ARGS__)), std::placeholders::_19 
#define MAKE_PLACEHOLDER_LIST_20(arg, ...)   MARCO_EXPAND(MAKE_PLACEHOLDER_LIST_19(__VA_ARGS__)), std::placeholders::_20


#define RSEQ_N() \
         119,118,117,116,115,114,113,112,111,110,\
         109,108,107,106,105,104,103,102,101,100,\
         99,98,97,96,95,94,93,92,91,90, \
         89,88,87,86,85,84,83,82,81,80, \
         79,78,77,76,75,74,73,72,71,70, \
         69,68,67,66,65,64,63,62,61,60, \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define ARG_N(\
         _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
         _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
         _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
         _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
         _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
         _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
         _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, \
         _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
         _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, \
         _111, _112, _113, _114, _115, _116, _117, _118, _119, N, ...) N

#define MARCO_EXPAND(...)   __VA_ARGS__
#define FIELD(t)            t

    //note use MACRO_CONCAT like A##_##B direct may cause marco expand error
#define MACRO_CONCAT(A, B) MACRO_CONCAT1(A, B)
#define MACRO_CONCAT1(A, B) A##_##B

#define MAKE_ARG_LIST(N, op, arg, ...) \
        MACRO_CONCAT(MAKE_ARG_LIST, N)(op, arg, __VA_ARGS__)

#define GET_ARG_COUNT_INNER(...)    MARCO_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...)          GET_ARG_COUNT_INNER(__VA_ARGS__, RSEQ_N())

#define MAKE_STR_LIST(...) \
    MACRO_CONCAT(CON_STR, GET_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__)

#define MAKE_N_STR_LIST(N, ...) \
    MACRO_CONCAT(CON_STR, N)(__VA_ARGS__)

#define MAKE_PLACEHOLDER_LIST(N, arg, ...) \
    MACRO_CONCAT(MAKE_PLACEHOLDER_LIST, N)(arg, ##__VA_ARGS__)

#define BIND_MEMBER_FUNC_N(RET, Func, Inst, N,...) \
    std::bind<RET>(&Func, Inst, MAKE_PLACEHOLDER_LIST(N, ##__VA_ARGS__))

#define BIND_MEMBER_FUNC(RET, Func, Inst, ...) \
    BIND_MEMBER_FUNC_N(RET, Func, Inst, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)

#define BIND_MEMBER_FUNC_NOARGS(RET, Func, Inst) \
    std::bind<RET>(&Func, Inst)

#define BIND_FUNC_N(RET, Func, N,...) \
    std::bind<RET>(&Func, MAKE_PLACEHOLDER_LIST(N, ##__VA_ARGS__))

#define BIND_FUNC(RET, Func, ...) \
    BIND_FUNC_N(RET, Func, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)

#define BIND_FUNC_NOARGS(RET, Func) \
    std::bind<RET>(&Func)

#define AGR_IN
#define AGR_IN_OUT
#define AGR_OUT
}


#endif  // SERIALIZE_DEFINE_H_