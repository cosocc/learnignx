#include <stdio.h>
#include <stdlib.h>  //malloc
#include <unistd.h>
#include <signal.h>

//�źŴ�����
void sig_quit(int signo)
{
    printf("�յ���SIGQUIT�ź�!\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
    {
        printf("�޷�ΪSIGQUIT�ź�����ȱʡ����(��ֹ����)!\n");
        exit(1);
    }
}

int main(int argc, char* const* argv)
{
    sigset_t newmask, oldmask; //�źż����µ��źż���ԭ�е��źż���������źż�
    if (signal(SIGQUIT, sig_quit) == SIG_ERR)  //ע���źŶ�Ӧ���źŴ�����,"ctrl+\" 
    {
        printf("�޷���׽SIGQUIT�ź�!\n");
        exit(1);   //�˳����򣬲����Ǵ�����룬0��ʾ�����˳�����0��ʾ���󣬵�����ʲô����û���ر�涨������������һ��Ҳ�ò������Ȳ�������
    }

    sigemptyset(&newmask); //newmask�źż��������źŶ���0����ʾ��Щ�źŶ�û��������
    sigaddset(&newmask, SIGQUIT); //����newmask�źż��е�SIGQUIT�ź�λΪ1��˵���ˣ�����SIGQUIT�ź�ʱ�����̾��ղ���������Ϊ1���Ǹ��źű���������

    //sigprocmask()�����øý�������Ӧ���źż�
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)  //��һ����������SIG_BLOCK�������� ���� �µ��ź������� Ϊ ����ǰ�ź������� �� �ڶ�������ָ����źż��Ĳ���
    {                                                 //һ�� �����̡� �ĵ�ǰ�ź������֣��տ�ʼȫ������0�ģ������൱�ڰѵ�ǰ "����"���ź����������ó� newmask��������SIGQUIT)��
                                                      //������������Ϊ�գ�������ϵ�(���ñ�sigprocmask()֮ǰ��)�źż��ᱣ�浽��������������ں����������������Իָ��ϵ��źż����߳�
        printf("sigprocmask(SIG_BLOCK)ʧ��!\n");
        exit(1);
    }
    printf("��Ҫ��ʼ��Ϣ10����--------begin--����ʱ���޷�����SIGQUIT�ź�!\n");
    sleep(10);   //����ڼ��޷��յ�SIGQUIT�źŵģ�
    printf("���Ѿ���Ϣ��10����--------end----!\n");
    if (sigismember(&newmask, SIGQUIT))  //����һ��ָ�����ź�λ�Ƿ���λ(Ϊ1)�����Ե���newmask
    {
        printf("SIGQUIT�źű�������!\n");
    }
    else
    {
        printf("SIGQUIT�ź�û�б�����!!!!!!\n");
    }
    if (sigismember(&newmask, SIGHUP))  //��������һ��ָ�����ź�λ�Ƿ���λ,���Ե���newmask
    {
        printf("SIGHUP�źű�������!\n");
    }
    else
    {
        printf("SIGHUP�ź�û�б�����!!!!!!\n");
    }

    //������Ҫȡ����SIGQUIT�źŵ�����(����)--���źż���ԭ��ȥ
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) //��һ����������SIGSETMASK�������� ����  �µ��ź�������Ϊ �ڶ������� ָ����źż�������������û��
    {
        printf("sigprocmask(SIG_SETMASK)ʧ��!\n");
        exit(1);
    }

    printf("sigprocmask(SIG_SETMASK)�ɹ�!\n");

    if (sigismember(&oldmask, SIGQUIT))  //����һ��ָ�����ź�λ�Ƿ���λ,������Եĵ�Ȼ��oldmask
    {
        printf("SIGQUIT�źű�������!\n");
    }
    else
    {
        printf("SIGQUIT�ź�û�б����Σ������Է���SIGQUIT�ź��ˣ���Ҫsleep(10)����!!!!!!\n");
        int mysl = sleep(10);
        if (mysl > 0)
        {
            printf("sleep��û˯����ʣ��%d��\n", mysl);
        }
    }
    printf("�ټ���!\n");
    return 0;
}


