class Link
{
public:
	Link()// ���캯��
	{
	    mphead=new Node();
	}
	~Link() // ��������
	{
        Node *p=mphead;
        while(p!=nullptr)
        {
            mphead=mphead->mpnext
            delete p;
            p=mphead;
        }
	}
	void insertHead(int val)
	{
	    Node *p=new Node(val);
	    p->mpnext=mphead->mpnext;
	    mphead->next=p;
	}
	void insertTail(int val)
	{
	    /*Node *m=new Node(val);
	    Node *p=mphead->mpnext;
	    while(p->mpnext!=nullptr)
        {
            p=p->mpnext;
        }
        p->mpnext=m;*/

        Node *pcur = mphead;
		while (pcur->mpnext != nullptr)
		{
			pcur = pcur->mpnext;
		}
		pcur->mpnext = new Node(val);

	}
	void remove(int val) // ɾ������ֵΪval�Ľڵ�
	{
	    /*Node *p=mphead->mpnext;
	    Node *q=mphead;
	    while(p->mpnext!=nullptr)
        {
            if(p.mdata==val)
            {
                q->mpnext=p->mpnext;
                delete p;
            }
            p=q->mpnext;
        }*/
        Node *ppre = mphead;
		Node *pcur = mphead->mpnext;

		while (pcur != nullptr)
		{
			if (pcur->mdata == val)
			{
				ppre->mpnext = pcur->mpnext;
				delete pcur;
				pcur = ppre->mpnext;
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
	    Node *p=mphead->mpnext;
	    while(p!=nullptr)
        {
            cout<<p.mdata<<" ";
            p=p->mpnext;
        }
        cout<<endl;
	}
private:
	// �ڵ�����
	struct Node
	{
		Node(int data = 0)
		{
			mdata = data;
			mpnext = nullptr;
		}
		int mdata;
		Node *mpnext;
	};

	// private����������͸�ֵ���غ���
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};
