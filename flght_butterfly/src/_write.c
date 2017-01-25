//
// This file is part of the µOS++ III distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// Do not include on semihosting and when freestanding
#if !defined(OS_USE_SEMIHOSTING) && !(__STDC_HOSTED__ == 0)

// ----------------------------------------------------------------------------

#include <errno.h>
#include "diag/Trace.h"

// ----------------------------------------------------------------------------

// When using retargetted configurations, the standard write() system call,
// after a long way inside newlib, finally calls this implementation function.

// Based on the file descriptor, it can send arrays of characters to
// different physical devices.

// Currently only the output and error file descriptors are tested,
// and the characters are forwarded to the trace device, mainly
// for demonstration purposes. Adjust it for your specific needs.

// For freestanding applications this file is not used and can be safely
// ignored.
#include "cqueue.h"
ssize_t
_write (int fd, const char* buf, size_t nbyte);
#include <NRF24L01.h>
ssize_t
_write (int fd __attribute__((unused)), const char* buf __attribute__((unused)),
	size_t nbyte __attribute__((unused)))
{
	nrf_send_buf_enque(buf,nbyte);
	return nbyte;
}

// ----------------------------------------------------------------------------

#endif // !defined(OS_USE_SEMIHOSTING) && !(__STDC_HOSTED__ == 0)
