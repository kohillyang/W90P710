
.global taskSwitchAsm
.global getNextSp
.global SysTick_handler
.type getNextSp function


//必须将  SysTick_handler声明成函数，否则将会尝试切换成arm状态而触发一个硬fault
.type SysTick_handler function

SysTick_handler:
	push {lr}               //跳转到C函数时会改变r0和lr的值，r0已经被硬件自动压栈,保存lr即可，在中断中使用的是msp


	cpsid i         		//关闭中断
	bl Led_handler          //闪烁led，表示进入中断函数

	mrs r0,psp
	mov r1,sp                //目测stm指令会造成一点小麻烦，用push好了，需要保存sp

	mov sp,r0
	push {r4-r7}         //将当前任务的寄存器压入psp中
	mov r0,sp
/*
    *根据当前的栈指针判断当前的任务id，
    *保存当前的任务的sp指针，参数为r0
    *返回下一个任务的psp指针,函数的参数根据调用规则保存在r0中
 	*r0保存了下个任务的psp
 	*lr的值已经改变
 	*当r0的值为0的时候表示任务从未运行过
 */
 	push {r1} 				//函数中可能会修改r1，需要先保存
	bl getNextSp
	pop {r1}
 //上下文保存完毕，设置栈指针完毕

	mov sp,r0         //从进程栈中弹出下个任务的寄存器
	pop {r4-r7}
	mov r0,sp

	msr psp,r0              //将进程堆栈指针写入psr
	cpsie i                 //打开中断

	mov sp,r1              //恢复sp
	pop {pc}           //弹出pc，跳转到下个任务出执行




