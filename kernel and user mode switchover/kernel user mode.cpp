

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>


//�źŴ�����
void sig_usr(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("�յ���SIGUSR1�źţ�����Ϣ10��......!\n");
        sleep(10);
        printf("�յ���SIGUSR1�źţ�����Ϣ10����ϣ�������......!\n");
    }
    else if (signo == SIGUSR2)
    {
        printf("�յ���SIGUSR2�źţ�����Ϣ10��......!\n");
        sleep(10);
        printf("�յ���SIGUSR2�źţ�����Ϣ10����ϣ�������......!\n");
    }
    else
    {
        printf("�յ���δ��׽���ź�%d!\n", signo);
    }
}

int main(int argc, char* const* argv)
{

    //���յ�  kill -usr1 ����ID   �ͻ�����ں�̬��Ϣ 10��   main �е� �������  ���� �����

    if (signal(SIGUSR1, sig_usr) == SIG_ERR)  //ϵͳ����������1���Ǹ��źţ�����2���Ǹ�����ָ�룬����һ����Ը��źŵĲ�׽������
    { 
        printf("�޷���׽SIGUSR1�ź�!\n");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("�޷���׽SIGUSR2�ź�!\n");
    }


    //���´��������û�̬
    for (;;)
    {
        sleep(1); //��Ϣ1��    
        printf("��Ϣ1��~~~~!\n");
    }
    printf("�ټ�!\n");
    return 0;
}


