#include <stdio.h>
#include <stdlib.h>  //malloc,exit
#include <unistd.h>  //fork
#include <signal.h>
#include <sys/wait.h>  //waitpid

//�źŴ�����
void sig_usr(int signo)
{
    int  status;

    switch (signo)
    {
    case SIGUSR1:
        printf("�յ���SIGUSR1�źţ�����id=%d!\n", getpid());
        break;

    case SIGCHLD:
        printf("�յ���SIGCHLD�źţ�����id=%d!\n", getpid());
        //������ѧ��һ���º���waitpid������Ҳ��wait,����ʦҪ�������պ�ʹ��waitpid���ɣ�
        //���waitpid˵���˻�ȡ�ӽ��̵���ֹ״̬���������ӽ��̾Ͳ����Ϊ��ʬ�����ˣ�
        pid_t pid = waitpid(-1, &status, WNOHANG); //��һ������Ϊ-1����ʾ�ȴ��κ��ӽ��̣�
                                      //�ڶ��������������ӽ��̵�״̬��Ϣ(����������ϸ�˽⣬���԰ٶ�һ��)��
                                       //�������������ṩ����ѡ�WNOHANG��ʾ��Ҫ�����������waitpid()��������
        if (pid == 0)       //�ӽ���û����������������������֣�������Ӧ�ò����������                        
            return;
        if (pid == -1)      //���ʾ���waitpid�����д����д���Ҳ��ⷵ�س�ȥ�����ǹܲ�����ô��
            return;
        //�ߵ������ʾ  �ɹ�����Ҳreturn��
        return;
        break;
    } //end switch
}

int main(int argc, char* const* argv)
{
    pid_t  pid;

    printf("���̿�ʼִ��!\n");

    //�ȼ򵥴���һ���ź�
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)  //ϵͳ����������1���Ǹ��źţ�����2���Ǹ�����ָ�룬����һ����Ը��źŵĲ�׽������
    {
        printf("�޷���׽SIGUSR1�ź�!\n");
        exit(1);
    }

    if (signal(SIGCHLD, sig_usr) == SIG_ERR)
    {
        printf("�޷���׽SIGCHLD�ź�!\n");
        exit(1);
    }

    //---------------------------------
    pid = fork();  //����һ���ӽ���

    //Ҫ�ж��ӽ����Ƿ񴴽��ɹ�
    if (pid < 0)
    {
        printf("�ӽ��̴���ʧ�ܣ����ź�!\n");
        exit(1);
    }

    //���ڣ������̺��ӽ���ͬʱ��ʼ ������ 
    for (;;)
    {
        sleep(1); //��Ϣ1��
        printf("��Ϣ1�룬����id=%d!\n", getpid());
    }
    printf("�ټ���!\n");
    return 0;
}


