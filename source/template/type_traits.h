#pragma once

//这里以 判断int类型为例

namespace wrw
{

	struct false_type {
		static constexpr bool value = false;
	};

	struct true_type {
		static constexpr bool value = true;
	};

	template<class T>//主模板定义
	struct is_int :false_type {
	};

	template<>//特化
	struct is_int<int> :true_type {
	};

	//模板处理
	//处理特殊情况，如const int，int&

	template<class T>//主模板定义
	struct remove_const {
		using type = T;
	};

	template<class T>//特化
	struct remove_const<const T> {
		using type = T;
	};

	template<class T>//主模板定义
	struct remove_ref {
		using type = T;
	};

	template<class T>//特化
	struct remove_ref<T &> {
		using type = T;
	};

	template<class T>
	struct remove_ref<T &&> {
		using type = T;
	};

	//is_int降级版本
	template<class T>
	struct is_int_helper :is_int<typename remove_ref<typename remove_const<T>::type>::type> {

	};

	//也可直接这样，直接使用"继承的方式" 对所有的特殊的类型 进行特化处理，就是比较麻烦
	//template<class T>//const T特化
	//struct is_int<const T> :is_int<T> {
	//};
	//};

	//template<class T>//T & 特化
	//struct is_int<T &> :is_int<T> {
	//};

	//template<class T>//T && 特化
	//struct is_int<T &&> :is_int<T> {
	//};
}
