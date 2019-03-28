#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>

using namespace std;
class CCircleQueue
{
    public:
	CCircleQueue(int size=10) // ���캯��
	{
    mpQue=new int[size];
    mfront=0;
    mrear=0;
    msize=size;
     }
	~CCircleQueue(); // ��������
	CCircleQueue(const CCircleQueue &src); // �������캯��
	void operator=(const CCircleQueue &src); // ��ֵ���غ���

	void addQue(int val); // ���
	void delQue(); // ����
	int front(); // ���ض�ͷԪ��
	int back(); // ���ض�βԪ��

	bool full(); // ����
	bool empty(); // �п�

private:
	int *mpQue; //�������Ԫ�ص����ݽṹ
	int mfront; //��ͷ�±�
	int mrear; //��β�±�
	int msize; //���ݵ��ܳ���

	void resize(); // 2������ѭ������

};

/*CCircleQueue::CCircleQueue(int size=10)
{
    mpQue=new int[size];
    mfront=0;
    mrear=0;
    msize=size;
}*/
CCircleQueue::~CCircleQueue()
{
    delete[] mpQue;
    mpQue=NULL;
}

CCircleQueue::CCircleQueue(const CCircleQueue &src)
{
        mpQue = new int[src.msize];
        mfront = src.mfront;
		mrear = src.mrear;
		msize=src.msize;
		for(int i=mfront;i!=mrear;i=(i+1)%msize)
        {
            mpQue[i]=src.mpQue[i];
        }

}
void CCircleQueue::oaperator =(const CCircleQueue &src)
{
    if(this==&src)
        return;
    delete[] mpQue;
     mpQue = new int[src.msize];
        mfront = src.mfront;
		mrear = src.mrear;
		msize=src.msize;
		for(int i=mfront;i!=mrear;i=(i+1)%msize)
        {
            mpQue[i]=src.mpQue[i];
        }
}
void CCircleQueue::addQue(int val) //���
{
    if(full())
    {
        resize();
    }
    mpQue[mrear]=val;
    mrear=(mrear+1)%msize;
    cout<<val<<" ";
}

void CCircleQueue::delQue()    //����
{
    if(empty())
    {
        throw "Queue is error";
    }
    mfront=(mfront+1)%msize;
}

int CCircleQueue::front()
{
    if(empty())
        throw "Queue is error";
    int data=mpQue[mfront];
    return data;
}

int CCircleQueue::back()
{
    if(empty())
        throw "Queue is error";
    int data=mpQue[mrear-1+msize]%msize;
    return data;
}

bool CCircleQueue::full()
{
   return (mrear + 1) % msize == mfront;
}

bool CCircleQueue::empty()
{
    return mrear == mfront;
}

void CCircleQueue::resize()
{
    int* newQue=new int[2*msize];
    for(int i=mfront,j=0;i!=mrear;i=(i+1)%msize,j++)
    {
        newQue[i]=mpQue[i];
    }

    delete[] mpQue;
    mpQue=newQue;
    mfront=0;
    mrear=j;
    msize*=2;
}

int main()
{
    CCircleQueue queue;
    srand(time(NULL));

    for(int i = 0; i < 10; ++i)
    {
        queue.addQue(rand()%100+ 1);
    }

    cout <<endl;
    while(!queue.empty())
    {
        int top = queue.front();
        cout <<top <<" ";
        queue.delQue();
    }

    cout <<endl;
    return 0;
}
