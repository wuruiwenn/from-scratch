#pragma once

#include <iostream>
#include <type_traits>
#include <string>

/*
	一个类型提取方法
	基于模板实现
	例如 T = const volatile int*&
    type_name()将返回：volatile const int*&
    绕这么一大圈，不是为了 改变修饰符的顺序，修饰符顺序只是按照C++规则得到的
    本质是因为，T不能直接字符串化。__PRETTY_FUNCTION__宏是可以拿到类型T的裸类型T的，也是const char*字符串形式
    但是拿不到修饰符（const，volatile等）
    std::is_volatile<>这类方法，都是编译期获取类型的动作
*/
namespace wrw
{

	namespace pretty_function
	{
#if defined(__clang__)
		// Clang 下，PRETTY_FUNCTION 的格式是： "const char *wrw::get_function_full_name() [T = int]"
#define DBG_MACRO_PRETTY_FUNCTION __PRETTY_FUNCTION__
		static constexpr size_t PREFIX_LENGTH = sizeof("const char *wrw::get_function_full_name() [T = ") - 1;
		static constexpr size_t SUFFIX_LENGTH = sizeof("]") - 1;

#elif defined(__GNUC__) && !defined(__clang__)
		// GCC 下，PRETTY_FUNCTION 的格式是： "const char* wrw::get_function_full_name() [with T = int]"
#define DBG_MACRO_PRETTY_FUNCTION __PRETTY_FUNCTION__
		static constexpr size_t PREFIX_LENGTH = sizeof("const char* wrw::get_function_full_name() [with T = ") - 1;
		static constexpr size_t SUFFIX_LENGTH = sizeof("]") - 1;

#elif defined(_MSC_VER)
		// MSVC 下，用 __FUNCSIG__，格式例如： "const char *__cdecl wrw::get_function_full_name<int>(void)"
#define DBG_MACRO_PRETTY_FUNCTION __FUNCSIG__
		static constexpr size_t PREFIX_LENGTH = sizeof("const char *__cdecl wrw::get_function_full_name<") - 1;
		static constexpr size_t SUFFIX_LENGTH = sizeof(">(void)") - 1;

#else
#error "This compiler is currently not supported by dbg_macro."
#endif
	};
	//工具 辅助函数
	template<typename T>
	const char* get_function_full_name()
	{
		return DBG_MACRO_PRETTY_FUNCTION;
	}

	template<typename T>
	typename std::enable_if<std::rank<T>::value == 0, std::string>::type get_type_pure_name()
	{
		namespace pf = pretty_function;
		std::string name = get_function_full_name<T>();
		return name.substr(pf::PREFIX_LENGTH, name.size() - pf::PREFIX_LENGTH - pf::SUFFIX_LENGTH);
	}

	template<typename T>
	std::string get_T_modifier_and_type_name_str()
	{
		if (std::is_volatile<T>::value) {
			if (std::is_pointer<T>::value)
				return get_T_modifier_and_type_name_str<typename std::remove_volatile<T>::type>() + " volatile";
			else
				return "volatile " + get_T_modifier_and_type_name_str<typename std::remove_volatile<T>::type>();
		}
		if (std::is_const<T>::value) {
			if (std::is_pointer<T>::value)
				return get_T_modifier_and_type_name_str<typename std::remove_const<T>::type>() + " const";
			else
				return "const " + get_T_modifier_and_type_name_str<typename std::remove_const<T>::type>();
		}
		if (std::is_pointer<T>::value)
			return get_T_modifier_and_type_name_str<typename std::remove_pointer<T>::type>() + "*";

		if (std::is_lvalue_reference<T>::value)
			return get_T_modifier_and_type_name_str<typename std::remove_reference<T>::type>() + "&";

		if (std::is_rvalue_reference<T>::value)
			return get_T_modifier_and_type_name_str<typename std::remove_reference<T>::type>() + "&&";

		//return get_type_pure_name(type_tag<T>{});
		return get_type_pure_name<T>();
	}

};
