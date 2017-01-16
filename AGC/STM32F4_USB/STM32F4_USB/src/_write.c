
#include <errno.h>

#include <stm32f4xx.h>
#include <stdint.h>
#include <sys/types.h>
#include <GUI.h>

ssize_t
_write(int fd, const char* buf, size_t nbyte);
ssize_t _write(int fd, const char* buf, size_t nbyte) {
//	for(u32 i = 0;i<nbyte;i++){
//		while(!(USART1->SR & USART_FLAG_TXE));
//		USART1->DR = (buf[i] & (uint16_t)0x01FF);
//	}
//	trace_write(buf,nbyte);
	char buff[nbyte+1];
	for(int i = 0;i<nbyte;i++){
		buff[i] = buf[i];
	}
	buff[nbyte]=0;
	GUI_DispString(buff);

	return nbyte;
}

