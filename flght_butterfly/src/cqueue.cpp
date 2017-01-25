/*
 * cqueue.cpp
 *
 *  Created on: 2017年1月25日
 *      Author: kohill
 */
#include <queue>
#include "cqueue.h"
static std::queue<unsigned char> nrf_queue;
extern "C" void nrf_send_buf_enque(const unsigned char *p,size_t len){
	if(nrf_queue.size()>512){
		//缓冲区满
		return;
	}
	while(len--){
		nrf_queue.push(*p);
		++p;
	}
}
extern "C" void nrf_send_buf_deque32(unsigned char *p){
	int len = nrf_queue.size();
	for(int i = 0 ; i<32 && i<len ; i++){
		p[i]= nrf_queue.front();
		nrf_queue.pop();
	}
	for(int i = len-1;i<32;i++){
		p[i]=0;
	}
}
extern "C" size_t nrf_send_buf_getlen(){
	return nrf_queue.size();
}


