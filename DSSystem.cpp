#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
using namespace std;

/*
����������£�
�������ݵ���...������ɣ�
-------------
1.������
2.ջ
3.����
4.�˳�ϵͳ => �����ڴ�����
-------------
��ѡ��1

-------------
��ǰ���ݽṹ�ǣ�xxx
1.�鿴
2.����
3.ɾ��
4.��ѯ
5.������һ���˵�
-------------
��ѡ��
*/

class CStack
{
public:
    friend class File;
	// CStack() CStack(int)
	CStack(int size = 3) // ���캯�����������Ա�������г�ʼ��
	{
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	// ����������� Ĭ��������ǳ����
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
	// ��ֵ���غ���  stack1 = stack1
	void operator=(const CStack &src)
	{
		cout << "operator=" << endl;

		// ��ֹ�Ը�ֵ
		if (this == &src)
			return;

		// ���ͷ�thisָ��������е��ⲿ��Դ
		delete[]mpstack;

		// ����src���õĶ�����Դ�ߴ磬���¿��ٿռ䣬��������
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	~CStack() // �����������ͷŶ���
	{
		delete[]mpstack;
		mpstack = NULL;
	}
	void push(int val) // ��ջ
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // ��ջ
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
	int *mpstack; // �洢ջ������
	int mtop; // ��ʾջ���±�
	int msize; // ��ʾջ���ܳ���

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

// ��OOPʵ��һ��ѭ������
class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // ���캯��
	{
		msize = size;
		mfront = mrear = 0;
		mpQue = new int[msize];
	}
	~CCircleQueue() // ��������
	{
		delete[]mpQue;
		mpQue = NULL;
	}



	void addQue(int val) // ���
	{
		if (full())
			resize();
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;
	}
	void delQue() // ����
	{
		if (empty())
			return;
		mfront = (mfront + 1) % msize;
	}
	int front() // ���ض�ͷԪ��
	{
		return mpQue[mfront];
	}
	int back() // ���ض�βԪ��
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
	bool full() { return (mrear + 1) % msize == mfront; } // ����
	bool empty() { return mrear == mfront; } // �п�
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
	int *mpQue; //�������Ԫ�ص����ݽṹ
	int mfront; //��ͷ�±�
	int mrear; //��β�±�
	int msize; //���ݵ��ܳ���
	CCircleQueue(const CCircleQueue &src) // �������캯��
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
	void operator=(const CCircleQueue &src) // ��ֵ���غ���
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
	void resize() // 2������ѭ������
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

// OOPʵ��һ������ṹ
class Link
{
public:
	Link() // ���캯��
	{
		mphead = new Node(); // new Node;
	}
	~Link() // ��������
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
	void remove(int val) // ɾ������ֵΪval�Ľڵ�
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
				cout <<"ɾ���ɹ���";
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
	// �ڵ�����
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

	// private����������͸�ֵ���غ���
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};

class File
{

public:
    //�ļ�����
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
    //�ļ�����
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
        /*int length=0;   //���ݳ���

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

// ���ݽṹϵͳ��
class DSSystem
{
public:
	void run() // ϵͳ����������
	{
		// 1.�����ļ��е�����
        cout<<"�ļ����ڼ�����..."<<endl;
		file.FLoad(mstack,mqueue,mlink);
        cout<<"�ļ�������ɣ�"<<endl;
		// 2.��ʾ���˵�
		cout << "-------------" << endl;
		cout << "1.������" << endl;
		cout << "2.ջ" << endl;
		cout << "3.����" << endl;
		cout << "4.�˳�ϵͳ" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
		cin >> mDsChoice;

		switch (mDsChoice)
		{
		case 1:
		case 2:
		case 3:
			runChild();
			break;
		case 4:
			cout << "����������..."<<endl;
			// �������ݣ�д���ļ�
            file.FSave(mstack,mqueue,mlink);
			cout << "����ɹ�����ӭ�´�ʹ�ã�" << endl;
			return;
		}
	}
	void run1()
	{
	   cout << "-------------" << endl;
		cout << "1.������" << endl;
		cout << "2.ջ" << endl;
		cout << "3.����" << endl;
		cout << "4.�˳�ϵͳ" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
		cin >> mDsChoice;

		switch (mDsChoice)
		{
		case 1:
		case 2:
		case 3:
			runChild();
			break;
		case 4:
			cout << "����������..."<<endl;
			// �������ݣ�д���ļ�
            file.FSave(mstack,mqueue,mlink);
			cout << "����ɹ�����ӭ�´�ʹ�ã�" << endl;
			return;
		}
	}

	void runChild() // ϵͳ�����˵�����������
	{
		int choice = 0;
		string DSName;
		if(mDsChoice==1)
            DSName="������";
        else if(mDsChoice==2)
            DSName="ջ";
        else
            DSName="����";

        do{
		cout << "-------------" << endl;
		cout << "��ǰѡ������ݽṹ��:" << DSName << endl;
		cout << "1.�鿴" << endl;
		cout << "2.����" << endl;
		cout << "3.ɾ��" << endl;
		cout << "4.��ѯ" << endl;
		cout << "5.����" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
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
            cout <<"������Ҫ���ӵ�ֵ��(����-1����)"<<endl;
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
                cout <<"������Ҫɾ����ֵ:";
                cin >>m;
                cout <<"ɾ���ɹ���"<<endl;
                mlink.remove(m);
            }
            else if(2 == mDsChoice)
            {
                cout <<"��ջԪ�ص�ֵ��";
                cout <<mstack.top()<<endl;
                mstack.pop();
                cout <<endl;
            }
            else
            {
                cout <<"����Ԫ�ص�ֵ��";
                cout <<mqueue.front()<<endl;
                mqueue.delQue();
                cout <<endl;
            }
            break;
        case 4:
            int k;
            cout <<"������Ҫ��ѯ��Ԫ�أ�";
            cin >>k;
             if(1 == mDsChoice)
            {
                if(mlink.FindValue(k))
                    cout <<"��ѯ�ɹ���"<<endl;
                else
                    cout <<"��ѯʧ�ܣ�û�и�ֵ��"<<endl;
            }
            else if(2 == mDsChoice)
            {
                if(mstack.FindValue(k))
                    cout <<"��ѯ�ɹ���"<<endl;
                else
                    cout <<"��ѯʧ�ܣ�û�и�ֵ��"<<endl;
            }
            else
            {
                if(mqueue.FindValue(k))
                    cout <<"��ѯ�ɹ���"<<endl;
                else
                    cout <<"��ѯʧ�ܣ�û�и�ֵ��"<<endl;
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

	int mDsChoice; // ��ʾ���˵�ѡ������ݽṹ
};

int main()
{
	DSSystem sys;
	sys.run();

	return 0;
}
