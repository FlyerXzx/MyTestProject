#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

/*
OOPʵ��һ���Թ�·����Ѱ������
�������Ҫ�����£�

�������Թ�·������������5 5
�������Թ��ľ���·����Ϣ(0��ʾ���ߣ�1��ʾ������)��
0 0 1 0 0
0 0 0 0 0
1 0 0 1 1
0 1 0 1 0
1 0 0 0 0
��ʼѰ���Թ�·��...

û�ҵ�����ӡ��ʾ��Ϣ���Թ������ڿ�ͨ�е�·����
�ҵ��ˣ����Թ�·����ӡһ��
* * 1 0 0
0 * * 1 0
1 0 * 0 1
0 1 * 1 0
1 0 * * *

*/
// ��������
// ���巽��
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;
const int WAY_NUM = 4;
// ��������״̬�õ�
const int YES = 5;
const int NO = 6;

// �����Թ��ڵ�����
class MazeNode
{
public:
    friend class Maze;
    friend class CStack;
	MazeNode()
	{
		for (int i = 0; i < WAY_NUM; ++i)
		{
			mstate[i] = YES;
		}
	}
private:
	int mval; // �ڵ��ֵinitMazeNode
	int mx; // �ڵ�����
	int my; // �ڵ�����
	int mstate[WAY_NUM]; // �ڵ��ĸ������״̬
};
// ����˳��ջ�ṹ
class CStack
{
public:
    friend class Maze;
    CStack(int size=128):mtop(0),msize(size)
    {
        mpstack=new MazeNode[size];
    }
    ~CStack()
    {
        delete[] mpstack;
        mpstack = NULL;
    }
    void push(MazeNode &node)
    {
        if(full())
            resize();
        mpstack[mtop++] = node;
    }
    void pop()
    {
        if(empty())
            return;
        --mtop;
    }
    MazeNode top()
    {
        if(empty())
        {
            MazeNode m;
            m.mval = -1;
            return m;
        }
        return mpstack[mtop-1];
    }
    bool empty()
    {
        return 0 == mtop;
    }
    bool full()
    {
        return msize == mtop;
    }
private:
	MazeNode *mpstack;
	int mtop;
	int msize;

	CStack(const CStack &src);
	void operator=(const CStack&);

	void resize()
	{
	    MazeNode *pcur=new MazeNode[2*msize];
	    for(int i=0;i<msize;i++)
        {
            pcur[i]=mpstack[i];
        }
        delete[] mpstack;
        mpstack=pcur;
        msize*=2;
	}
};
// �����Թ�����
class Maze
{
public:
	Maze(int row, int col)
	{
	    mrow=row;
	    mcol=col;
	    mpMaze = new MazeNode*[row];
	    for(int i=0;i < row;i++)
        {
            mpMaze[i]=new MazeNode[col];
        }
	}
	~Maze()
	{
	    for(int i=0;i<mrow;i++)
        {
            delete[] mpMaze[i];
        }
        delete[] mpMaze;
        mpMaze=NULL;
	}
	void adjustMaze()
	{
	    for(int i=0;i<mrow;i++)
            for(int j=0;j<mcol;j++)
        {
            if(0 != i && 0 == mpMaze[i-1][j].mval)
                mpMaze[i][j].mstate[UP] = YES;
            if(mrow !=i+1 && 0 == mpMaze[i+1][j].mval)
                mpMaze[i][j].mstate[DOWN] = YES;
            if(0 != j && 0 == mpMaze[i][j].mval)
                mpMaze[i][j].mstate[LEFT] = YES;
            if(mcol != j+1 && 0 == mpMaze[i][j+1].mval)
                mpMaze[i][j].mstate[RIGHT] = YES;
        }
	}
	void initMazeNode(int data,int x,int y)
	{
	    mpMaze[x][y].mval = data;
	    mpMaze[x][y].mx = x;
	    mpMaze[x][y].my = y;
	    mpMaze[x][y].mstate[UP] = NO;
	    mpMaze[x][y].mstate[DOWN] = NO;
	    mpMaze[x][y].mstate[LEFT] = NO;
	    mpMaze[x][y].mstate[RIGHT] = NO;
	}
	void findMazePath()
	{
	    int i=0,j=0;
	    stack.push(mpMaze[i][j]);
	    MazeNode mNode=stack.top();
        while(mNode.mx < mrow || mNode.my < mcol)
        {
            mNode=stack.top();
            if(mNode.mx == mrow-1 && mNode.my == mcol-1)
            {
                break;
            }
            i=mNode.mx;
            j=mNode.my;
            if((mcol != j+1) && (YES == mpMaze[i][j].mstate[RIGHT]))
            {
                if(mcol != j+2)
                    mpMaze[i][j+2].mstate[LEFT] = NO;
                if(-1 != i-1)
                    mpMaze[i-1][j+1].mstate[DOWN] = NO;
                if(-1 != j)
                {
                   mpMaze[i][j].mstate[RIGHT] = NO;
                }
                if(mrow != i+1)
                    mpMaze[i+1][j+1].mstate[UP] = NO;
                stack.push(mpMaze[i][j+1]);
            }else if((mrow !=i+1) && (YES == mpMaze[i][j].mstate[DOWN]))
            {
                if(mrow != i+2)
                    mpMaze[i+2][j].mstate[UP] = NO;
                if(-1 != i)
                    mpMaze[i][j].mstate[DOWN] = NO;
                if(-1!= j-1)
                    mpMaze[i+1][j-1].mstate[RIGHT] = NO;
                if(mcol != j+1)
                    mpMaze[i+1][j+1].mstate[LEFT] = NO;
                stack.push(mpMaze[i+1][j]);
            }else if((0 !=j) && (YES == mpMaze[i][j].mstate[LEFT]))
            {
                 if(-1 != j-2)
                    mpMaze[i][j-2].mstate[RIGHT] = NO;
                 if(-1 != i-1)
                    mpMaze[i-1][j-1].mstate[DOWN] = NO;
                 if(mcol != j)
                    mpMaze[i][j].mstate[LEFT] = NO;
                 if(mrow != i+1)
                    mpMaze[i+1][j-1].mstate[UP] = NO;
                 stack.push(mpMaze[i][j-1]);
            }else if((0 !=i) && (YES == mpMaze[i][j].mstate[UP]))
            {
                if(-1 != i-2)
                    mpMaze[i-2][j].mstate[DOWN] = NO;
                if(mcol != j+1)
                    mpMaze[i-1][j+1].mstate[LEFT] = NO;
                 if(mrow != i)
                    mpMaze[i][j].mstate[UP] = NO;
                if(-1 != j-1)
                    mpMaze[i-1][j-1].mstate[RIGHT] = NO;
                stack.push(mpMaze[i-1][j]);
            }else
            {
                stack.pop();
                mNode=stack.top();
                if(-1 == mNode.mval)
                {
                    cout <<"�Թ������ڿ�ͨ�е�·����"<<endl;
                    break;
                }
            }
        }
	}
        void showResult()
        {
            for(int i=0;i<stack.mtop;i++)
            {
              mpMaze[stack.mpstack[i].mx][stack.mpstack[i].my].mval= '*';
            }

            for(int i=0;i<mrow;i++)
            {
                for(int j=0;j<mcol;j++)
            {
                if(mpMaze[i][j].mval == '*')
                    cout <<"* ";
                else
                cout <<mpMaze[i][j].mval <<" ";
            }
            cout <<endl;
            }
        }
private:
	int mrow;
	int mcol;
	MazeNode **mpMaze;
	CStack stack;
	//Ϊ�˷�ֹ����ǳ�����������⣬˽�л�����������
	Maze(const Maze&);
	void operator=(const Maze&);
};
int main()
{
	cout << "�������Թ�·������������";
	int row, col;
	cin >>row>>col;
	Maze maze(row, col);

	cout << "�������Թ��ľ���·����Ϣ(0��ʾ���ߣ�1��ʾ������)��" << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int data;
			cin >> data;
			maze.initMazeNode(data, i, j);
		}
	}

	// �����Թ����нڵ�ķ��������״̬
	maze.adjustMaze();

	// Ѱ���Թ�·��
	maze.findMazePath();
	cout <<endl;

	// ��ӡѰ�ҽṹ
	maze.showResult();

	return 0;
}
