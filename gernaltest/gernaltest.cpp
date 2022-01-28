#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_quit(int signo)
{
	printf("收到了SIGQUIT信号!\n");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		printf("无法为SIGQUIT信号设置缺省处理(终止进程)!\n");
		exit(1);
	}
}

int main(int argc, char** argv)
{
	sigset_t newmask, oldmask;
	if (signal(SIGQUIT,sig_quit)==SIG_ERR)
	{
		printf("无法捕获SIGQUIT信号!\n");
		exit(1);
	}
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	//函数原型：
	//	int sigprocmask(int how, const sigset_t * restrict set, sigset_t * restrict oldset);
	//函数说明：一个进程的信号屏蔽字规定了当前阻塞而不能递送给该进程的信号集。sigprocmask()可以用来检测或改变目前的信号屏蔽字，
	//	其操作依参数how来决定，如果参数oldset不是NULL指针，那么目前的信号屏蔽字会由此指针返回。如果set是一个非空指针，则参数how指示
	//	如何修改当前信号屏蔽字。每个进程都有一个用来描述哪些信号递送到进程时将被阻塞的信号集，该信号集中的所有信号在递送到进程后都将被阻塞。
	//	参数how的取值不同，带来的操作行为也不同，该参数可选值如下：
	//	1．SIG_BLOCK:　该值代表的功能是将newset所指向的信号集中所包含的信号加到当前的信号掩码中，作为新的信号屏蔽字(原有信号屏蔽字 + set屏蔽字)。
	//	2．SIG_UNBLOCK : 将参数newset所指向的信号集中的信号从当前的信号掩码中移除。
	//	3．SIG_SETMASK : 设置当前信号掩码为参数newset所指向的信号集中所包含的信号。

	//	oldset 记录之前的信号屏蔽字，程序开始第一次调用sigprocmask() 后，oldset里面理论上是不含有任何信号的。因为调用sigprocmask()前, 我们没有取拦截任何信号
	//	注意事项：sigprocmask()函数只为单线程的进程定义的，在多线程中要使用pthread_sigmask变量，在使用之前需要声明和初始化。
	//	返回值：执行成功返回0，失败返回 - 1。

	if (sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
	{
		printf("SIGBLOCK失败!\n");
		exit(1);
	}
	printf("我要开始休息十秒了------------begin--,此时我无法接收SIGQUIT信号!\n");
	sleep(10);
	printf("我已经休息了十秒了------------end----!\n");
	if (sigismember(&newmask, SIGQUIT))
	{
		printf("SIGQUIT信号被屏蔽了!\n");
	}
	else
	{
		printf("SIGQUIT信号没有被屏蔽!\n");
	}
	if (sigismember(&newmask, SIGHUP))
	{
		printf("SIGHUP信号被屏蔽了!\n");
	}
	else
	{
		printf("SIGHUP信号没有被屏蔽了!\n");
	}

	if (sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
	{
		printf("sigprocmask(SIG_SETMAK) 设置失败\n");
	}

	printf("sigprocmask(SIG_SETMAK) 设置成功\n");

	if (sigismember(&oldmask,SIGQUIT))
	{
		printf("SIGHUP信号被屏蔽了\n");
	}
	else
	{
		printf("SIGQUIT信号没有被屏蔽,您可以发送SIGQUIT信号了,我要SLEEP(10)秒钟\n");
		int mysl = sleep(10);
		if (mysl > 0)
		{
			printf("sleep 还没有睡够,剩余%d秒\n", mysl);
		}
	}

	printf("再见!");

	return 0;
}