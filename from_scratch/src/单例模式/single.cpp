#include"single.h"

Single::Single() {}

Single Single::ins;//�����Ķ���
Single* Single::GetIns() {
	return &ins;
}