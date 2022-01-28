#include <stdio.h>
#include <unistd.h>
#include <signal.h>
//#include <signal.h>

int main(int argc, char** argv)
{
	//系统函数，设置某个信号来的时候处理程序（用哪个函数处理）
	//signal(SIGHUP,SIG_IGN); //SIG_IGN标志：我要求忽略这个信号，请操作系统不要用缺省的处理方式来对待我（不要把我杀掉）；

	pid_t pid;
	printf("learn nginx is very happy things! \n");
	pid = fork();
	if (pid < 0 )
	{
		printf("fork()进程出错!\n");
	}
	else if (pid==0)
	{
		printf("子进程开始执行!\n");
		setsid();  //新建一个不同session,但是进程组组长调用setsid()是无效的
		int i = 0;
		while (1)
		{
			sleep(1);
			printf("子进程休息一秒 %d\n", i++);
			if (i==3600)
			{
				i = 0;
			}
		}
	}
	else
	{
		printf("父进程开始执行!\n");
		int i = 0;
		while (1)
		{
			sleep(1);
			printf("父进程休息一秒 %d\n", i++);
			if (i == 3600)
			{
				i = 0;
			}
		}

	}


	return 0;
}