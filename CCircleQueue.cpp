#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>

using namespace std;
class CCircleQueue
{
    public:
	CCircleQueue(int size=10) // 构造函数
	{
    mpQue=new int[size];
    mfront=0;
    mrear=0;
    msize=size;
     }
	~CCircleQueue(); // 析构函数
	CCircleQueue(const CCircleQueue &src); // 拷贝构造函数
	void operator=(const CCircleQueue &src); // 赋值重载函数

	void addQue(int val); // 入队
	void delQue(); // 出队
	int front(); // 返回队头元素
	int back(); // 返回队尾元素

	bool full(); // 判满
	bool empty(); // 判空

private:
	int *mpQue; //保存队列元素的数据结构
	int mfront; //队头下标
	int mrear; //队尾下标
	int msize; //扩容的总长度

	void resize(); // 2倍扩容循环队列

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
void CCircleQueue::addQue(int val) //入队
{
    if(full())
    {
        resize();
    }
    mpQue[mrear]=val;
    mrear=(mrear+1)%msize;
    cout<<val<<" ";
}

void CCircleQueue::delQue()    //出队
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
