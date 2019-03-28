#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
using namespace std;

/*
软件运行如下：
加载数据当中...加载完成！
-------------
1.单链表
2.栈
3.队列
4.退出系统 => 保存内存数据
-------------
请选择：1

-------------
当前数据结构是：xxx
1.查看
2.增加
3.删除
4.查询
5.返回上一级菜单
-------------
请选择：
*/

class CStack
{
public:
    friend class File;
	// CStack() CStack(int)
	CStack(int size = 3) // 构造函数，给对象成员变量进行初始化
	{
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	// 拷贝构造对象 默认做的是浅拷贝
	CStack(const CStack &src)
	{
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	// 赋值重载函数  stack1 = stack1
	void operator=(const CStack &src)
	{
		cout << "operator=" << endl;

		// 防止自赋值
		if (this == &src)
			return;

		// 先释放this指向对象现有的外部资源
		delete[]mpstack;

		// 根据src引用的对象资源尺寸，重新开辟空间，拷贝数据
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	~CStack() // 析构函数，释放对象
	{
		delete[]mpstack;
		mpstack = NULL;
	}
	void push(int val) // 入栈
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // 出栈
	{
		if (empty())
			return;
		--mtop;
	}
	int top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop-1];
	}
	bool FindValue(int val)
	{
	    if(empty())
            return false;
        int p=mtop;
        while(0 != p)
        {
            if(val == mpstack[--p])
                return true;
            --p;
        }
        return false;
	}
	void show()
	{
	    if(empty())
            return;
        int p=mtop;
        while(0 != p)
        {
            cout <<mpstack[--p]<<" ";
        }
        cout<<endl;
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }
	int* GetStackDatas(int &length)
	{
	    length=mtop;
	    int *p=new int[length];
	    for(int i=0;i<length;i++)
        {
            p[i] = mpstack[i];
        }
        return p;
	}
private:
	int *mpstack; // 存储栈的数据
	int mtop; // 表示栈顶下标
	int msize; // 表示栈的总长度

	void resize()
	{
		int *ptmp = new int[msize * 2];
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete []mpstack;
		mpstack = ptmp;
		msize *= 2;
	}
};

// 用OOP实现一个循环队列
class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // 构造函数
	{
		msize = size;
		mfront = mrear = 0;
		mpQue = new int[msize];
	}
	~CCircleQueue() // 析构函数
	{
		delete[]mpQue;
		mpQue = NULL;
	}



	void addQue(int val) // 入队
	{
		if (full())
			resize();
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;
	}
	void delQue() // 出队
	{
		if (empty())
			return;
		mfront = (mfront + 1) % msize;
	}
	int front() // 返回队头元素
	{
		return mpQue[mfront];
	}
	int back() // 返回队尾元素
	{
		return mpQue[(mrear-1+msize)%msize];
	}
	bool FindValue(int val)
	{
	    if(empty())
            return false;
        int p=mfront;
        while(p != mrear)
        {
            if(val == mpQue[p])
                return true;
            p=(p+1)%msize;
        }
        return false;
	}
	void show()
	{
	    if(empty())
            return;
        int p=mfront;
        while(p != mrear)
        {
            cout <<mpQue[p]<<" ";
            p=(p+1)%msize;
        }
        cout<<endl;
	}
	int GetSize()
	{
	    int n=0;
	    for(int i = mfront;i != mrear;i = (i+1)%msize)
            n++;
        return n;
	}
	bool full() { return (mrear + 1) % msize == mfront; } // 判满
	bool empty() { return mrear == mfront; } // 判空
	int* GetQueueDatas(int &length)
	{
	    length=GetSize();
	    int *p=new int[length];
	    for(int i = mfront,j=0;i != mrear;i = (i+1)%msize)
        {
            p[j++]=mpQue[i];
        }
        return p;
	}

private:
	int *mpQue; //保存队列元素的数据结构
	int mfront; //队头下标
	int mrear; //队尾下标
	int msize; //扩容的总长度
	CCircleQueue(const CCircleQueue &src) // 拷贝构造函数
	{
		this->mpQue = new int[src.msize];
		for (int i = src.mfront;
			i != src.mrear;
			i=(i+1)%src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}
	void operator=(const CCircleQueue &src) // 赋值重载函数
	{
		if (this == &src)
			return;

		delete[]mpQue;

		this->mpQue = new int[src.msize];
		for (int i = src.mfront;
			i != src.mrear;
			i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}
	void resize() // 2倍扩容循环队列
	{
		int *ptmp = new int[msize * 2];
		int j = 0;
		for (int i = mfront;
			i != mrear;
			i = (i + 1) % msize, j++)
		{
			ptmp[j] = mpQue[i];
		}
		delete[]mpQue;
		mpQue = ptmp;
		mfront = 0;
		mrear = j;
		msize *= 2;
	}
};

// OOP实现一个链表结构
class Link
{
public:
	Link() // 构造函数
	{
		mphead = new Node(); // new Node;
	}
	~Link() // 析构函数
	{
		Node *pcur = mphead;
		while (pcur != NULL)
		{
			mphead = mphead->mpnext;
			delete pcur;
			pcur = mphead;
		}
	}
	void insertHead(int val)
	{
		Node *ptmp = new Node(val); // Node node(val);
		ptmp->mpnext = mphead->mpnext;
		mphead->mpnext = ptmp;
	}
	void insertTail(int val)
	{
		Node *pcur = mphead;
		while (pcur->mpnext != NULL)
		{
			pcur = pcur->mpnext;
		}
		pcur->mpnext = new Node(val);
	}
	void remove(int val) // 删除所有值为val的节点
	{
		Node *ppre = mphead;
		Node *pcur = mphead->mpnext;

		while (pcur != NULL)
		{
			if (pcur->mdata == val)
			{
				ppre->mpnext = pcur->mpnext;
				delete pcur;
				pcur = ppre->mpnext;
				cout <<"删除成功！";
			}
			else
			{
				ppre = pcur;
				pcur = pcur->mpnext;
			}
		}
	}
	void show()
	{
		Node *pcur = mphead->mpnext;
		while (pcur != NULL)
		{
			cout << pcur->mdata << " ";
			pcur = pcur->mpnext;
		}
		cout << endl;
	}
	bool FindValue(int val)
	{
	    Node *pcur = mphead->mpnext;
	    while (pcur !=NULL)
        {
            if(val==pcur->mdata)
            {
                return true;
            }
            else
            {
                pcur = pcur->mpnext;
            }
        }
        return false;
	}
	void WriteFile(FILE * &fds)
	{
	    Node *pcur = mphead->mpnext;
		while (pcur != NULL)
		{
		    fprintf(fds,"%d ",pcur->mdata);
			pcur = pcur->mpnext;
		}
		fclose(fds);
	}
	int GetSize()
	{
	    int n=0;
	    Node *pcur=mphead->mpnext;
	    while(pcur != NULL)
        {
            n++;
            pcur=pcur->mpnext;
        }
        return n;
	}
	int* GetLinkDatas(int &length)
	{
	    length = GetSize();
	    int *p=new int[length];
	    Node *pcur=mphead->mpnext;
	    int i=0;
	    while(pcur != NULL)
        {
            p[i++] = pcur->mdata;
            pcur = pcur->mpnext;
        }
        return p;
	}

private:
	// 节点类型
	struct Node
	{
		Node(int data = 0)
		{
			mdata = data;
			mpnext = NULL;
		}
		int mdata;
		Node *mpnext;
	};

	// private化拷贝构造和赋值重载函数
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};

class File
{

public:
    //文件加载
    void FLoad(CStack &stack,CCircleQueue &queue,Link &link)
    {
        Sfds=fopen("F:\\stack.txt","r");
        if(NULL==Sfds)
        {
            cout <<"Cannot open stack file!"<<endl;
            return;
        }

        Qfds=fopen("F:\\queue.txt","r");
        if(NULL==Qfds)
        {
            cout <<"Cannot open queue file!"<<endl;
            return;
        }

        Lfds=fopen("F:\\linklist.txt","r");
        if(NULL == Lfds)
        {
            cout <<"Cannot open linklist file!"<<endl;
            return;
        }

        for(int i=0;fscanf(Sfds,"%d",ms+i)!=EOF;++i)
            stack.push(ms[i]);
        fclose(Sfds);

        for(int i=0;fscanf(Qfds,"%d",mq+i)!=EOF;++i)
            queue.addQue(mq[i]);
        fclose(Qfds);

        for(int i=0;fscanf(Lfds,"%d",ml+i)!=EOF;++i)
            link.insertTail(ml[i]);
        fclose(Lfds);
        /*FILE *pf1=fopen("F://stack.dat","rb");
        if(pf1 != NULL)
        {
            fseek(pf1,0,SEEK_END);
            int size=ftell(pf1);
            int number=size/sizeof(int);
            int *p=new int[number];
            fread(p,4,number,pf1);
            fclose(pf1);
            for(int i=0;i < number;++i)
            {
                stack.push(p[i]);
            }
            delete[] p;
        }

        FILE *pf2=fopen("F://queue.dat","rb");
        if(pf2 != NULL)
        {
            fseek(pf2,0,SEEK_END);
            int size=ftell(pf2);
            int number=size/sizeof(int);
            int *p=new int[number];
            fread(p,4,number,pf2);
            fclose(pf2);
            for(int i=0;i < number;++i)
            {
                queue.addQue(p[i]);
            }
            delete[] p;
        }

        FILE *pf3=fopen("F://link.dat","rb");
        if(pf3 != NULL)
        {
            fseek(pf3,0,SEEK_END);
            int size=ftell(pf3);
            int number=size/sizeof(int);
            int *p=new int[number];
            fread(p,4,number,pf3);
            fclose(pf3);
            for(int i=0;i < number;++i)
            {
                link.insertTail(p[i]);
            }
            delete[] p;
        }*/
    }
    //文件保存
    void FSave(CStack &stack,CCircleQueue &queue,Link &link)
    {
        FILE *Sfd,*Qfd,*Lfd;
        Sfd=fopen("F:\\stack.txt","w+");
        if(NULL == Sfd)
        {
            cout <<"Cannot open stack file!"<<endl;
            return;
        }
        /*while(!stack.empty())
        {
            //fwrite(stack)
            fprintf(Sfds,"%d ",stack.top());
            stack.pop();
        }*/
        for(int i=0;i<stack.mtop;i++)
            fprintf(Sfd,"%d ",stack.mpstack[i]);
        fclose(Sfd);

        Qfd=fopen("F:\\queue.txt","w+");
        if(NULL == Qfd)
        {
            cout <<"Cannot open queue file!"<<endl;
            return;
        }
        //fseek(Qfd, 0, SEEK_END);
        while(!queue.empty())
        {
            fprintf(Qfd,"%d ",queue.front());
		    queue.delQue();
        }
        fclose(Qfd);

        Lfd=fopen("F:\\linklist.txt","w+");
         if(NULL == Lfds
            )
        {
            cout <<"Cannot open linklist file!"<<endl;
            return;
        }
        //fseek(Lfd, 0, SEEK_END);
        link.WriteFile(Lfd);
        /*int length=0;   //数据长度

        FILE *pf1=fopen("F://stack.dat","wb");
        if(pf1 == NULL)
            return;
        int *p1=stack.GetStackDatas(length);
        fwrite(p1,4,length,pf1);
        fclose(pf1);
        delete[] p1;

        FILE *pf2=fopen("F://queue.dat","wb");
        if(pf2 == NULL)
            return;
        int *p2=queue.GetQueueDatas(length);
        fwrite(p2,4,length,pf2);
        fclose(pf2);
        delete[] p2;

        FILE *pf3=fopen("F://link.dat","wb");
        if(pf3 == NULL)
            return;
        int *p3=link.GetLinkDatas(length);
        cout<<p3[0]<<" "<<p3[1]<<" "<<endl;
        fwrite(p3,4,length,pf3);
        fclose(pf3);
        delete[] p3;*/
    }
private:
    FILE *Sfds;
    FILE *Qfds;
    FILE *Lfds;
    int ms[128];
    int mq[128];
    int ml[128];
};

// 数据结构系统类
class DSSystem
{
public:
	void run() // 系统的启动函数
	{
		// 1.加载文件中的数据
        cout<<"文件正在加载中..."<<endl;
		file.FLoad(mstack,mqueue,mlink);
        cout<<"文件加载完成！"<<endl;
		// 2.显示主菜单
		cout << "-------------" << endl;
		cout << "1.单链表" << endl;
		cout << "2.栈" << endl;
		cout << "3.队列" << endl;
		cout << "4.退出系统" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> mDsChoice;

		switch (mDsChoice)
		{
		case 1:
		case 2:
		case 3:
			runChild();
			break;
		case 4:
			cout << "保存数据中..."<<endl;
			// 保存数据，写入文件
            file.FSave(mstack,mqueue,mlink);
			cout << "保存成功！欢迎下次使用！" << endl;
			return;
		}
	}
	void run1()
	{
	   cout << "-------------" << endl;
		cout << "1.单链表" << endl;
		cout << "2.栈" << endl;
		cout << "3.队列" << endl;
		cout << "4.退出系统" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> mDsChoice;

		switch (mDsChoice)
		{
		case 1:
		case 2:
		case 3:
			runChild();
			break;
		case 4:
			cout << "保存数据中..."<<endl;
			// 保存数据，写入文件
            file.FSave(mstack,mqueue,mlink);
			cout << "保存成功！欢迎下次使用！" << endl;
			return;
		}
	}

	void runChild() // 系统二级菜单的启动函数
	{
		int choice = 0;
		string DSName;
		if(mDsChoice==1)
            DSName="单链表";
        else if(mDsChoice==2)
            DSName="栈";
        else
            DSName="队列";

        do{
		cout << "-------------" << endl;
		cout << "当前选择的数据结构是:" << DSName << endl;
		cout << "1.查看" << endl;
		cout << "2.增加" << endl;
		cout << "3.删除" << endl;
		cout << "4.查询" << endl;
		cout << "5.返回" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> choice;
		switch (choice)
		{
        case 1:
            if(1 == mDsChoice)
            {
                mlink.show();
            }
            else if(2 == mDsChoice)
            {
                mstack.show();
            }
            else
            {
                mqueue.show();
            }
            break;
        case 2:
            int val;
            cout <<"请输入要增加的值：(输入-1结束)"<<endl;
            while(1)
        {
            cin>>val;
            if(-1 == val)
                break;
                if(1 == mDsChoice)
            {
                mlink.insertTail(val);
            }
            else if(2 == mDsChoice)
            {
                mstack.push(val);
            }
            else
            {
                mqueue.addQue(val);
            }
        }
        break;
        case 3:
            int m;
                if(1 == mDsChoice)
            {
                cout <<"请输入要删除的值:";
                cin >>m;
                cout <<"删除成功！"<<endl;
                mlink.remove(m);
            }
            else if(2 == mDsChoice)
            {
                cout <<"出栈元素的值：";
                cout <<mstack.top()<<endl;
                mstack.pop();
                cout <<endl;
            }
            else
            {
                cout <<"出队元素的值：";
                cout <<mqueue.front()<<endl;
                mqueue.delQue();
                cout <<endl;
            }
            break;
        case 4:
            int k;
            cout <<"请输入要查询的元素：";
            cin >>k;
             if(1 == mDsChoice)
            {
                if(mlink.FindValue(k))
                    cout <<"查询成功！"<<endl;
                else
                    cout <<"查询失败，没有该值！"<<endl;
            }
            else if(2 == mDsChoice)
            {
                if(mstack.FindValue(k))
                    cout <<"查询成功！"<<endl;
                else
                    cout <<"查询失败，没有该值！"<<endl;
            }
            else
            {
                if(mqueue.FindValue(k))
                    cout <<"查询成功！"<<endl;
                else
                    cout <<"查询失败，没有该值！"<<endl;
            }
            break;
        case 5:
            break;
		}
     }while(5 != choice);
     run1();
   }

private:
	CStack mstack;
	CCircleQueue mqueue;
	Link mlink;
    File file;

	int mDsChoice; // 表示主菜单选择的数据结构
};

int main()
{
	DSSystem sys;
	sys.run();

	return 0;
}
