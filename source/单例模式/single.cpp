#include"single.h"

Single::Single() {}

Single Single::ins;//单例的定义
Single* Single::GetIns() {
	return &ins;
}