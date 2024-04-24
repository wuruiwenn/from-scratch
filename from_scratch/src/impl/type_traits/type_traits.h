#pragma once

//������ �ж�int����Ϊ��

namespace wrw
{

	struct false_type {
		static constexpr bool value = false;
	};

	struct true_type {
		static constexpr bool value = true;
	};

	template<class T>//��ģ�嶨��
	struct is_int :false_type {
	};

	template<>//�ػ�
	struct is_int<int> :true_type {
	};

	//ģ�崦��
	//���������������const int��int&

	template<class T>//��ģ�嶨��
	struct remove_const {
		using type = T;
	};

	template<class T>//�ػ�
	struct remove_const<const T> {
		using type = T;
	};

	template<class T>//��ģ�嶨��
	struct remove_ref {
		using type = T;
	};

	template<class T>//�ػ�
	struct remove_ref<T &> {
		using type = T;
	};

	template<class T>
	struct remove_ref<T &&> {
		using type = T;
	};

	//is_int�����汾
	template<class T>
	struct is_int_helper :is_int<typename remove_ref<typename remove_const<T>::type>::type> {

	};

	//Ҳ��ֱ��������ֱ��ʹ��"�̳еķ�ʽ" �����е���������� �����ػ��������ǱȽ��鷳
	//template<class T>//const T�ػ�
	//struct is_int<const T> :is_int<T> {
	//};
	//};

	//template<class T>//T & �ػ�
	//struct is_int<T &> :is_int<T> {
	//};

	//template<class T>//T && �ػ�
	//struct is_int<T &&> :is_int<T> {
	//};
}
