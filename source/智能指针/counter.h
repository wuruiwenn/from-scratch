#pragma once


//用于shared_ptr、weak_ptr的计数器

struct Counter {
	int share_cnt = 0;
	int weak_cnt = 0;
};