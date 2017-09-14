#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
using namespace std;

/* ����'STATUS'����ȡֵ */

typedef int STATUS;
const int OK 			= 1;
const int ERROR 		= 0;
const int INFEASIBLE 	=-1;	//������

//----------------------------------------------------------------------------------------------------//

/*                                                ����                                                */

/* ��������Ԫ�ء����ݽṹ������ȫ�ֱ��� */

typedef int LINK_LIST_ELEM_TYPE;

struct NODE
{
	LINK_LIST_ELEM_TYPE data;
	NODE *next;
};

struct D_NODE
{
	LINK_LIST_ELEM_TYPE data;
	D_NODE *prior;
	D_NODE *next;
};

/* �������ݲ��� */

//������

//������ĳ�ʼ��
STATUS LINK_LIST_init(NODE *(&list));
//�����������
STATUS LINK_LIST_delete(NODE *(&list));
//����������
STATUS LINK_LIST_clear(NODE *(&list));
//������ĸ���
STATUS LINK_LIST_copy(NODE *(&list),NODE *(&list_c));
//�����������
STATUS LINK_LIST_input(NODE *(&list));
//����������
STATUS LINK_LIST_output(NODE *(&list));
//�Ե�������зǵݼ�����
STATUS LINK_LIST_sort(NODE *(&list));
//�ڵ������location��Ԫ��ǰ����һ����Ԫ��elem
STATUS LINK_LIST_insert_ELEM(NODE *(&list),const int &location,const LINK_LIST_ELEM_TYPE &elem);
//ɾ���������location��Ԫ�أ����ظ�Ԫ�ص�elem
STATUS LINK_LIST_delete_ELEM(NODE *(&list),const int &location,LINK_LIST_ELEM_TYPE &elem);
//����elemԪ�أ�����Ԫ��λ�õ�location
STATUS LINK_LIST_search_ELEM(NODE *(&list),int &location,const LINK_LIST_ELEM_TYPE &elem);
//�������ǵݼ����򣩲���һ����Ԫ��elem
STATUS LINK_LIST_SORT_insert_ELEM(NODE *(&list),const LINK_LIST_ELEM_TYPE &elem);
//������list_1,list_2���ǵݼ����򣩵ĺϲ��������±�list
STATUS LINK_LIST_SORT_combine(NODE *(&list),NODE *(&list_1),NODE *(&list_2));

//˫������

//˫������ĳ�ʼ��
STATUS D_LINK_LIST_init(D_NODE *(&list));
//˫�����������
STATUS D_LINK_LIST_delete(D_NODE *(&list));
//˫����������
STATUS D_LINK_LIST_clear(D_NODE *(&list));
//˫�����������
STATUS D_LINK_LIST_input(D_NODE *(&list));
//˫����������
STATUS D_LINK_LIST_output(D_NODE *(&list));
//˫������ĸ���
STATUS D_LINK_LIST_copy(D_NODE *(&list),D_NODE *(&list_c));
//��˫��������зǵݼ�����
STATUS D_LINK_LIST_sort(D_NODE *(&list));
//��˫�������location��Ԫ��ǰ����һ����Ԫ��elem
STATUS D_LINK_LIST_insert_ELEM(D_NODE *(&list),const int &location,const LINK_LIST_ELEM_TYPE &elem);
//ɾ��˫�������location��Ԫ�أ����ظ�Ԫ�ص�elem
STATUS D_LINK_LIST_delete_ELEM(D_NODE *(&list),const int &location,LINK_LIST_ELEM_TYPE &elem);
//����elemԪ�أ�����Ԫ��λ�õ�location
STATUS D_LINK_LIST_search_ELEM(D_NODE *(&list),int &location,const LINK_LIST_ELEM_TYPE &elem);
//˫�������ǵݼ����򣩲���һ����Ԫ��elem
STATUS D_LINK_LIST_SORT_insert_ELEM(D_NODE *(&list),const LINK_LIST_ELEM_TYPE &elem);
//˫������list_1,list_2���ǵݼ����򣩵ĺϲ��������±�list
STATUS D_LINK_LIST_SORT_combine(D_NODE *(&list),D_NODE *(&list_1),D_NODE *(&list_2));

//���ߺ���
int LINK_LIST_lenth(NODE *(&list)); 		//���ص�����ĳ���
int D_LINK_LIST_lenth(D_NODE *(&list)); 	//����˫������ĳ���
void LINK_LIST_TOOL_input(LINK_LIST_ELEM_TYPE &a); 	//����Ԫ��
//void LINK_LIST_TOOL_input(int &a); 		//�������

/* �������ݲ��� */

//������ĳ�ʼ��
STATUS LINK_LIST_init(NODE *(&list))
{
	list=(NODE *) malloc(sizeof(NODE));
	if (!list) return ERROR;
	list->data=0;
	list->next=NULL;
	return OK;
}

//�����������
STATUS LINK_LIST_delete(NODE *(&list))
{
	int temp_1=1;
	LINK_LIST_ELEM_TYPE temp_2;
	while ( LINK_LIST_delete_ELEM(list,temp_1,temp_2)==OK )
	{}
	if (list)
	{
		free(list);
	}
	return OK;
}

//����������
STATUS LINK_LIST_clear(NODE *(&list))
{
	int temp_1=1;
	LINK_LIST_ELEM_TYPE temp_2;
	while ( LINK_LIST_delete_ELEM(list,temp_1,temp_2)==OK )
	{}
	return OK;
}

//������ĸ���
STATUS LINK_LIST_copy(NODE *(&list),NODE *(&list_c))
{
	NODE *p;
	NODE *q;
	NODE *temp;
	NODE *end;
	NODE *end_c;
	if (! LINK_LIST_init(list_c))
	{
		return ERROR;
	}
	list_c->data=list->data;
	if (list->data>=10000000)
	{
		end=list;
		end_c=list_c;
	}
	else
	{
		end_c=end=NULL;
	}
	p=list->next;
	q=list_c;
	while (p!=end)
	{
		if (temp=(NODE *) malloc(sizeof(NODE)))
		{
			temp->data=p->data;
			temp->next=end_c;
			q->next=temp;
		}
		else
		{
			return ERROR;
		}
		p=p->next;
		q=q->next;
	}
	return OK;
}

//�����������
STATUS LINK_LIST_input(NODE *(&list))
{
	int circ;
	int lenth;
	int loc=0;
	LINK_LIST_ELEM_TYPE e;
	NODE *p;
	NODE *q;
	LINK_LIST_clear(list);
	if (1)
	{
		cout << "���������������ͣ�ѭ����1����ѭ����0����";
		LINK_LIST_TOOL_input(circ);
		while (!(circ==0||circ==1))
		{
			cout << "���ݲ��Ϸ������������룺";
			LINK_LIST_TOOL_input(circ);
		}
		cout << "��Ҫ����" << (circ?"":"��") << "ѭ��������" << endl;
		cout << endl;
		if (circ)
		{
			list->data=10000000;
			list->next=list;
		}
		else
		{
			list->data=0;
			list->next=NULL;
		}
	}
	if (1)
	{
		cout << "�������Ҫ�����Ԫ����������������Χ0~~1248576��:";
		LINK_LIST_TOOL_input(lenth);
		while(lenth<0||lenth>1248576)
		{
			cout << "���ݲ��Ϸ������������룺";
			LINK_LIST_TOOL_input(lenth);
		}
		cout << "��Ҫ����" << lenth << "�����ݡ�" << endl;
		cout << endl;
	}
	if (1)
	{
		cout << "�������������Ԫ�أ�ÿ��Ԫ��֮���ûس��ָ���" << endl;
		cout << setiosflags(ios::fixed) << setprecision(0) << "����������Χ" << (-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (pow(2.0,(double)(8*sizeof(int)-1))-1) << "��" << endl;
		for (p=list;loc<lenth;p=p->next)
		{
			loc++;
			cout << "No." << setw(7) << setfill('0') << loc << " ";
			LINK_LIST_TOOL_input(e);
			if (1)
			{
				q=(NODE *) malloc(sizeof(NODE));
				if (!q)
				{
					return ERROR;
				}
				q->data=e;
				q->next=p->next;
				p->next=q;
				list->data+=1;
			}
		}
		cout << endl;
		return OK;
	}
}

//����������
STATUS LINK_LIST_output(NODE *(&list))
{
	NODE *p;
	int counter;
	p=list;
	cout << "*******************************" << endl;
	cout << "* �������ܳ���" << setw(7) << setfill(' ') << ( p->data>= 10000000 ? p->data-10000000 : p->data ) << "��Ԫ��   *" << endl;
	cout << "* ����������                  *" << endl;
	for (p=list->next,counter=1;(p && p!=list);p=p->next,counter++)
	{
		cout << "*    No." << setw(7) << setfill('0') << counter << " ";
		cout << setw(11) << setfill(' ') << p->data << "   *" << endl;
	}
	cout << "*******************************" << endl;
	cout << endl;
	return OK;
}

//�Ե�������зǵݼ�����
STATUS LINK_LIST_sort(NODE *(&list))
{
	NODE *p;
	NODE *q;
	NODE *end;
	LINK_LIST_ELEM_TYPE temp;
	if (list->data>=10000000)
	{
		end=list;
	}
	else
	{
		end=NULL;
	}
	p=list->next;
	if (p==end)
	{
		return OK;
	}
	q=p->next;
	if (q==end)
	{
		return OK;
	}
	while (p->next!=end)
	{
		q=p->next;
		while (q!=end)
		{
			if (p->data>q->data)
			{
				temp=p->data;
				p->data=q->data;
				q->data=temp;
			}
			q=q->next;
		}
		p=p->next;
	}
	return OK;
}

//�ڵ�����ԭ��location��Ԫ��ǰ����һ����Ԫ��elem
STATUS LINK_LIST_insert_ELEM(NODE *(&list),const int &location,const LINK_LIST_ELEM_TYPE &elem)
{
	int loc;
	NODE *temp;
	NODE *p;
	NODE *q;
	if (1)
	{
		temp=(NODE *) malloc(sizeof(NODE));
		if (!temp) return ERROR;
		temp->data=elem;
	}
	if ( location<1 || location>LINK_LIST_lenth(list)+1 )
	{
		return INFEASIBLE;
	}
	p=list;
	loc=0;
	while (loc<location-1)
	{
		p=p->next;
		loc++;
	}
	q=p->next;
	if (1)
	{
		p->next=temp;
		temp->next=q;
	}
	list->data+=1;
	return OK;
}

//ɾ��������ԭ��location��Ԫ�أ����ظ�Ԫ�ص�elem
STATUS LINK_LIST_delete_ELEM(NODE *(&list),const int &location,LINK_LIST_ELEM_TYPE &elem)
{
	int loc;
	NODE *p;
	NODE *q;
	NODE *temp;
	if (!list)
	{
		return ERROR;
	}
	if ( location<1 || location>LINK_LIST_lenth(list) )
	{
		return INFEASIBLE;
	}
	p=list;
	loc=0;
	while (loc<location-1)
	{
		p=p->next;
		loc++;
	}
	if (1)
	{
		temp=p->next;
		q=temp->next;
		p->next=q;
	}
	if (1)
	{
		elem=temp->data;
		free(temp);
	}
	list->data-=1;
	return OK;
}

//����elemԪ�أ�����Ԫ��λ�õ�location
STATUS LINK_LIST_search_ELEM(NODE *(&list),int &location,const LINK_LIST_ELEM_TYPE &elem)
{
	NODE *end;
	NODE *p;
	location=0;
	if (list->data>=10000000)
	{
		end=list;
	}
	else
	{
		end=NULL;
	}
	if (list->next==end)
	{
		return OK;
	}
	p=list->next;
	while (p!=end)
	{
		location+=1;
		if (p->data==elem)
		{
			return OK;
		}
		p=p->next;
	}
	location=0;
	return OK;
}

//�������ǵݼ����򣩲���һ����Ԫ��elem
STATUS LINK_LIST_SORT_insert_ELEM(NODE *(&list),const LINK_LIST_ELEM_TYPE &elem)
{
	NODE *end;
	NODE *p;
	int location=0;
	LINK_LIST_sort(list);
	if (list->data>=10000000)
	{
		end=list;
	}
	else
	{
		end=NULL;
	}
	p=list->next;
	while (p!=end)
	{
		location+=1;
		if (p->data>elem)
		{
			if (! LINK_LIST_insert_ELEM(list,location,elem))
			{
				return ERROR;
			}
			return OK;
		}
		p=p->next;
	}
	location+=1;
	if (! LINK_LIST_insert_ELEM(list,location,elem))
	{
		return ERROR;
	}
	return OK;
}

//������list_1,list_2���ǵݼ����򣩵ĺϲ��������±�list
STATUS LINK_LIST_SORT_combine(NODE *(&list),NODE *(&list_1),NODE *(&list_2))
{
	NODE *list_2_c;
	NODE *end;
	NODE *end_2;
	NODE *p;
	if
	(
		LINK_LIST_init(list) &&
		LINK_LIST_init(list_2_c)
	)
	{
		if (! LINK_LIST_lenth(list_1))
		{
			if (LINK_LIST_copy(list_2,list))
			{
				return OK;
			}
			else
			{
				return ERROR;
			}
		}
		else if (! LINK_LIST_lenth(list_2))
		{
			if (LINK_LIST_copy(list_1,list))
			{
				return OK;
			}
			else
			{
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}
	if
	(
		LINK_LIST_copy(list_1,list) &&
		LINK_LIST_copy(list_2,list_2_c)
	)
	{
		end=end_2=NULL;
		if (list->data>=10000000)
		{
			end=list;
			end_2=list_2_c;
		}
		for (p=list;p->next!=end;p=p->next)
		{}
		p->next=list_2_c->next;	//����
		for (;p->next!=end_2;p=p->next)
		{}
		p->next=end;	//ĩ�˴���
		list->data+=LINK_LIST_lenth(list_2_c);
		LINK_LIST_sort(list);
		return OK;
	}
	else
	{
		return ERROR;
	}
}

//˫������ĳ�ʼ��
STATUS D_LINK_LIST_init(D_NODE *(&list))
{
	list=(D_NODE *) malloc(sizeof(D_NODE));
	if (!list) return ERROR;
	list->data=0;
	list->prior=NULL;
	list->next=NULL;
	return OK;
}

//˫�����������
STATUS D_LINK_LIST_delete(D_NODE *(&list))
{
	int temp_1=1;
	LINK_LIST_ELEM_TYPE temp_2;
	while ( D_LINK_LIST_delete_ELEM(list,temp_1,temp_2)==OK )
	{}
	if (list)
	{
		free(list);
	}
	return OK;
}

//˫����������
STATUS D_LINK_LIST_clear(D_NODE *(&list))
{
	int temp_1=1;
	LINK_LIST_ELEM_TYPE temp_2;
	while ( D_LINK_LIST_delete_ELEM(list,temp_1,temp_2)==OK )
	{}
	return OK;
}

//˫������ĸ���
STATUS D_LINK_LIST_copy(D_NODE *(&list),D_NODE *(&list_c))
{
	D_NODE *p;
	D_NODE *q;
	D_NODE *temp;
	D_NODE *end;
	D_NODE *end_c;
	if (! D_LINK_LIST_init(list_c))
	{
		return ERROR;
	}
	list_c->data=list->data;
	if (list->data>=10000000)
	{
		end=list;
		end_c=list_c;
	}
	else
	{
		end_c=end=NULL;
	}
	p=list->next;
	q=list_c;
	while (p!=end)
	{
		if (temp=(D_NODE *) malloc(sizeof(D_NODE)))
		{
			temp->data=p->data;
			temp->prior=q;
			temp->next=end_c;
			q->next=temp;
		}
		else
		{
			return ERROR;
		}
		p=p->next;
		q=q->next;
	}
	return OK;
}

//˫�����������
STATUS D_LINK_LIST_input(D_NODE *(&list))
{
	int circ;
	int lenth;
	int loc=0;
	LINK_LIST_ELEM_TYPE e;
	D_NODE *p;
	D_NODE *q;
	D_LINK_LIST_clear(list);
	if (1)
	{
		cout << "�����˫����������ͣ�ѭ����1����ѭ����0����";
		LINK_LIST_TOOL_input(circ);
		while (!(circ==0||circ==1))
		{
			cout << "���ݲ��Ϸ������������룺";
			LINK_LIST_TOOL_input(circ);
		}
		cout << "��Ҫ����" << (circ?"":"��") << "ѭ��˫������" << endl;
		cout << endl;
		if (circ)
		{
			list->data=10000000;
			list->next=list;
		}
		else
		{
			list->data=0;
			list->next=NULL;
		}
	}
	if (1)
	{
		cout << "�������Ҫ�����Ԫ����������������Χ0~~1248576��:";
		LINK_LIST_TOOL_input(lenth);
		while(lenth<0||lenth>1248576)
		{
			cout << "���ݲ��Ϸ������������룺";
			LINK_LIST_TOOL_input(lenth);
		}
		cout << "��Ҫ����" << lenth << "�����ݡ�" << endl;
		cout << endl;
	}
	if (1)
	{
		cout << "�������������Ԫ�أ�ÿ��Ԫ��֮���ûس��ָ���" << endl;
		cout << setiosflags(ios::fixed) << setprecision(0) << "����������Χ" << (-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (pow(2.0,(double)(8*sizeof(int)-1))-1) << "��" << endl;
		for (p=list;loc<lenth;p=p->next)
		{
			loc++;
			cout << "No." << setw(7) << setfill('0') << loc << " ";
			LINK_LIST_TOOL_input(e);
			if (1)
			{
				q=(D_NODE *) malloc(sizeof(D_NODE));
				if (!q)
				{
					return ERROR;
				}
				q->data=e;
				q->next=p->next;
				q->prior=p;
				p->next=q;
				list->data+=1;
			}
		}
		cout << endl;
		return OK;
	}
}

//˫����������
STATUS D_LINK_LIST_output(D_NODE *(&list))
{
	D_NODE *p;
	int counter;
	p=list;
	cout << "*******************************" << endl;
	cout << "* ˫�������ܳ���" << setw(7) << setfill(' ') << ( p->data>= 10000000 ? p->data-10000000 : p->data ) << "��Ԫ�� *" << endl;
	cout << "* ˫���������ݣ�              *" << endl;
	for (p=list->next,counter=1;(p && p!=list);p=p->next,counter++)
	{
		cout << "*    No." << setw(7) << setfill('0') << counter << " ";
		cout << setw(11) << setfill(' ') << p->data << "   *" << endl;
	}
	cout << "*******************************" << endl;
	cout << endl;
	return OK;
}

//��˫��������зǵݼ�����
STATUS D_LINK_LIST_sort(D_NODE *(&list))
{
	D_NODE *p;
	D_NODE *q;
	D_NODE *end;
	LINK_LIST_ELEM_TYPE temp;
	if (list->data>=10000000)
	{
		end=list;
	}
	else
	{
		end=NULL;
	}
	p=list->next;
	if (p==end)
	{
		return OK;
	}
	q=p->next;
	if (q==end)
	{
		return OK;
	}
	while (p->next!=end)
	{
		q=p->next;
		while (q!=end)
		{
			if (p->data>q->data)
			{
				temp=p->data;
				p->data=q->data;
				q->data=temp;
			}
			q=q->next;
		}
		p=p->next;
	}
	return OK;
}

//��˫������ԭ��location��Ԫ��ǰ����һ����Ԫ��elem
STATUS D_LINK_LIST_insert_ELEM(D_NODE *(&list),const int &location,const LINK_LIST_ELEM_TYPE &elem)
{
	int loc;
	D_NODE *p;
	D_NODE *q;
	D_NODE *temp;
	if (1)
	{
		temp=(D_NODE *) malloc(sizeof(D_NODE));
		if (!temp) return ERROR;
		temp->data=elem;
	}
	if ( location<1 || location>D_LINK_LIST_lenth(list)+1 )
	{
		return INFEASIBLE;
	}
	p=list;
	loc=0;
	while (loc<location-1)
	{
		p=p->next;
		loc++;
	}
	q=p->next;
	if (1)
	{
		p->next=temp;
		temp->next=q;
	}
	if (1)
	{
		if (q)
		{
			q->prior=temp;
		}
		temp->prior=p;
	}
	list->data+=1;
	return OK;
}

//ɾ��˫������ԭ��location��Ԫ�أ����ظ�Ԫ�ص�elem
STATUS D_LINK_LIST_delete_ELEM(D_NODE *(&list),const int &location,LINK_LIST_ELEM_TYPE &elem)
{
	int loc;
	D_NODE *p;
	D_NODE *q;
	D_NODE *temp;
	if (!list)
	{
		return ERROR;
	}
	if ( location<1 || location>D_LINK_LIST_lenth(list) )
	{
		return INFEASIBLE;
	}
	p=list;
	loc=0;
	while (loc<location-1)
	{
		p=p->next;
		loc++;
	}
	if (1)
	{
		temp=p->next;
		q=temp->next;
		p->next=q;
		if (q)
		{
			q->prior=p;
		}
	}
	if (1)
	{
		elem=temp->data;
		free(temp);
	}
	list->data-=1;
	return OK;
}

//����elemԪ�أ�����Ԫ��λ�õ�location
STATUS D_LINK_LIST_search_ELEM(D_NODE *(&list),int &location,const LINK_LIST_ELEM_TYPE &elem)
{
	D_NODE *end;
	D_NODE *p;
	location=0;
	if (list->data>=10000000)
	{
		end=list;
	}
	else
	{
		end=NULL;
	}
	if (list->next==end)
	{
		return OK;
	}
	p=list->next;
	while (p!=end)
	{
		location+=1;
		if (p->data==elem)
		{
			return OK;
		}
		p=p->next;
	}
	location=0;
	return OK;
}

//˫�������ǵݼ����򣩲���һ����Ԫ��elem
STATUS D_LINK_LIST_SORT_insert_ELEM(D_NODE *(&list),const LINK_LIST_ELEM_TYPE &elem)
{
	D_NODE *end;
	D_NODE *p;
	int location=0;
	D_LINK_LIST_sort(list);
	if (list->data>=10000000)
	{
		end=list;
	}
	else
	{
		end=NULL;
	}
	p=list->next;
	while (p!=end)
	{
		location+=1;
		if (p->data>elem)
		{
			if (! D_LINK_LIST_insert_ELEM(list,location,elem))
			{
				return ERROR;
			}
			return OK;
		}
		p=p->next;
	}
	location+=1;
	if (! D_LINK_LIST_insert_ELEM(list,location,elem))
	{
		return ERROR;
	}
	return OK;
}

//˫������list_1,list_2���ǵݼ����򣩵ĺϲ��������±�list
STATUS D_LINK_LIST_SORT_combine(D_NODE *(&list),D_NODE *(&list_1),D_NODE *(&list_2))
{
	D_NODE *list_2_c;
	D_NODE *end;
	D_NODE *end_2;
	D_NODE *p;
	if
	(
		D_LINK_LIST_init(list) &&
		D_LINK_LIST_init(list_2_c)
	)
	{
		if (! D_LINK_LIST_lenth(list_1))
		{
			if (D_LINK_LIST_copy(list_2,list))
			{
				return OK;
			}
			else
			{
				return ERROR;
			}
		}
		else if (! D_LINK_LIST_lenth(list_2))
		{
			if (D_LINK_LIST_copy(list_1,list))
			{
				return OK;
			}
			else
			{
				return ERROR;
			}
		}
	}
	else
	{
		return ERROR;
	}
	if
	(
		D_LINK_LIST_copy(list_1,list) &&
		D_LINK_LIST_copy(list_2,list_2_c)
	)
	{
		end=end_2=NULL;
		if (list->data>=10000000)
		{
			end=list;
			end_2=list_2_c;
		}
		for (p=list;p->next!=end;p=p->next)
		{}
		if (1)	//����
		{
			p->next=list_2_c->next;
			list_2_c->prior=p;
		}
		for (;p->next!=end_2;p=p->next)
		{}
		if (1)	//ĩ�˴���
		{
			p->next=end;
			if (end)
			{
				end->prior=p;
			}
		}
		list->data+=D_LINK_LIST_lenth(list_2_c);
		D_LINK_LIST_sort(list);
		return OK;
	}
	else
	{
		return ERROR;
	}
}

//���ص�����ĳ���
int LINK_LIST_lenth(NODE *(&list))
{
	if (list->data<10000000)
		return (list->data);
	else
		return (list->data-10000000);
}

//����˫������ĳ���
int D_LINK_LIST_lenth(D_NODE *(&list))
{
	if (list->data<10000000)
		return (list->data);
	else
		return (list->data-10000000);
}

/* ������������ */

//����Ԫ��
void LINK_LIST_TOOL_input(LINK_LIST_ELEM_TYPE &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << endl;
		cout << "****�����쳣��****" << endl;
		cout<< endl;
		cout << "�����˳�..." << endl;
		cout << endl;
		system("PAUSE");
		exit(-1);
	}
}

/*
//�������
void LINK_LIST_TOOL_input(int &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << "****�����쳣��****" << endl;
		cout<< endl;
		cout << "�����˳�..." << endl;
		cout << endl;
		system("PAUSE");
		exit(-1);
	}
}
*/

//----------------------------------------------------------------------------------------------------//

/* ������ʵ�� */

//����Ԫ��
void input(LINK_LIST_ELEM_TYPE &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << "****�����쳣��****" << endl;
		cout<< endl;
		cout << "�����˳�..." << endl;
		cout << endl;
		system("PAUSE");
		exit(-1);
	}
}

/*
//�������
void input(int &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << "****�����쳣��****" << endl;
		cout<< endl;
		cout << "�����˳�..." << endl;
		cout << endl;
		system("PAUSE");
		exit(-1);
	}
}
*/

int main()
{
	NODE *l=NULL;
	NODE *l1=NULL;
	NODE *l2=NULL;
	NODE *lr=NULL;
	D_NODE *dl=NULL;
	D_NODE *dl1=NULL;
	D_NODE *dl2=NULL;
	D_NODE *dlr=NULL;
	LINK_LIST_ELEM_TYPE e;
	int loc;
	int func;
	int status;
	if
	(
		LINK_LIST_init(l)     &&
		LINK_LIST_init(l1)    &&
		LINK_LIST_init(l2)    &&
		LINK_LIST_init(lr)    &&
		D_LINK_LIST_init(dl)  &&
		D_LINK_LIST_init(dl1) &&
		D_LINK_LIST_init(dl2) &&
		D_LINK_LIST_init(dlr)
	)
	{}
	else
	{
		cout << endl;
		cout << "****�����쳣��****" << endl;
		cout<< endl;
		cout << "�����˳�..." << endl;
		cout << endl;
		system("PAUSE");
		return -1;
	}
	while (1)
	{
		cout << endl;
		cout << "**************************************************************" << endl;
		cout << "*                                                            *" << endl;
		cout << "*                            ����                            *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  ����:                                                     *" << endl;
		cout << "*      00.��ʼ������                                         *" << endl;
		cout << "*      99.�˳�����                                           *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  ������:                                                   *" << endl;
		cout << "*      11.������l������                                      *" << endl;
		cout << "*      12.������l�����                                      *" << endl;
		cout << "*      13.�Ե�����l���зǵݼ�����                            *" << endl;
		cout << "*      14.�ڵ�����l��ԭ��i��Ԫ��ǰ����һ����Ԫ��e            *" << endl;
		cout << "*      15.ɾ��������l��ԭ��i��Ԫ�أ����ظ�Ԫ��               *" << endl;
		cout << "*      16.���ҵ�����l��Ԫ��e������Ԫ��e�ڵ������е�λ��      *" << endl;
		cout << "*      17.�ڵ�����l1���ǵݼ����򣩲���һ��Ԫ��e              *" << endl;
		cout << "*      18.������l1,l2���ǵݼ����򣩵ĺϲ��������±�lr        *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  ˫������:                                                 *" << endl;
		cout << "*      21.˫������dl������                                   *" << endl;
		cout << "*      22.˫������dl�����                                   *" << endl;
		cout << "*      23.��˫������dl���зǵݼ�����                         *" << endl;
		cout << "*      24.��˫������dl��ԭ��i��Ԫ��ǰ����һ����Ԫ��e         *" << endl;
		cout << "*      25.ɾ��˫������dl��ԭ��i��Ԫ�أ����ظ�Ԫ��            *" << endl;
		cout << "*      26.����˫������dl��Ԫ��e������Ԫ��e��˫�������е�λ�� *" << endl;
		cout << "*      27.��˫������dl���ǵݼ����򣩲���һ��Ԫ��e            *" << endl;
		cout << "*      28.˫������dl1,dl2���ǵݼ����򣩵ĺϲ��������±�dlr   *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  ע�⣺                                                    *" << endl;
		cout << "*      �밴Ҫ�����룡���Ϸ������뽫���ܵ��³���ֱ���˳���    *" << endl;
		cout << "*                                                            *" << endl;
		cout << "**************************************************************" << endl;
		cout << endl;
		cout << "��ѡ��";
		input(func);
		cout << endl;
		switch (func)
		{
			case 0: //��ʼ������
			{
				LINK_LIST_clear(l);
				LINK_LIST_clear(l1);
				LINK_LIST_clear(l2);
				LINK_LIST_clear(lr);
				D_LINK_LIST_clear(dl);
				D_LINK_LIST_clear(dl1);
				D_LINK_LIST_clear(dl2);
				D_LINK_LIST_clear(dlr);
				cout << "****��ʼ���������ɹ���****" << endl;
				cout << endl;
				system("PAUSE");
				break;
			}
			case 99: //�˳�����
			{
				LINK_LIST_delete(l);
				LINK_LIST_delete(l1);
				LINK_LIST_delete(l2);
				LINK_LIST_delete(lr);
				D_LINK_LIST_delete(dl);
				D_LINK_LIST_delete(dl1);
				D_LINK_LIST_delete(dl2);
				D_LINK_LIST_delete(dlr);
				cout << "�����˳�..." << endl;
				cout << endl;
				system("PAUSE");
				return 0;
			}
			case 11: //������l������
			{
				cout << "��Ҫ���뵥����l" << endl;
				cout << endl;
				if ( LINK_LIST_input(l) )
				{
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 12: //������l�����
			{
				cout << "****������l������£�****" << endl;
				cout << endl;
				LINK_LIST_output(l);
				system("PAUSE");
				break;
			}
			case 13: //�Ե�����l���зǵݼ�����
			{
				LINK_LIST_output(l);
				cout << "��Ҫ�Ա�l���зǵݼ�����" << endl;
				cout << endl;
				if ( LINK_LIST_sort(l) )
				{
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 14: //�ڵ�����l��ԭ��i��Ԫ��ǰ����һ����Ԫ��e
			{
				LINK_LIST_output(l);
				cout << "�������Ҫ�����Ԫ�أ�";
				input(e);
				cout << "���������λ�ã�";
				input(loc);
				cout << endl;
				cout << "��Ҫ��Ԫ��" << e << "����ԭ������l�е�" << loc <<  "��Ԫ��ǰ��" << endl;
				cout << endl;
				status=LINK_LIST_insert_ELEM(l,loc,e);
				if (status==1)
				{
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else if(status==0)
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				else
				{
					cout << "****����λ�ò��Ϸ����޷�������****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 15: //ɾ��������l��ԭ��i��Ԫ�أ����ظ�Ԫ��
			{
				LINK_LIST_output(l);
				cout << "�������Ҫɾ��Ԫ�ص�λ�ã�";
				input(loc);
				cout << endl;
				cout << "��Ҫɾ��ԭ������l�еĵ�" << loc <<  "��Ԫ�ء�" << endl;
				cout << endl;
				status=LINK_LIST_delete_ELEM(l,loc,e);
				if (status==1)
				{
					cout << "��ɾ����Ԫ�أ�" << e << "��" << endl;
					cout << endl;
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else
				{
					cout << "****ɾ��λ�ò��Ϸ����޷�������****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 16: //���ҵ�����l��Ԫ��e������Ԫ��e�ڵ������е�λ��
			{
				LINK_LIST_output(l);
				cout << setiosflags(ios::fixed) << "�������Ҫ���ҵ�Ԫ�أ���������Χ" << (int)(-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (int)(pow(2.0,(double)(8*sizeof(int)-1))) << "��:";
				input(e);
				cout << endl;
				cout << "��Ҫ���ҵ�Ԫ��Ϊ" << e << "��" << endl;
				cout << endl;
				LINK_LIST_search_ELEM(l,loc,e);
				if (!loc)
				{
					cout << "Ԫ��" << e << "�������ڵ�����l�С�" << endl;
					cout << endl;
				}
				else
				{
					cout << "Ԫ��" << e << "�ڵ�����l�е����ΪNO." << setw(7) << setfill('0') << loc << "��" << endl;
					cout << endl;
				}
		 		system("PAUSE");
		 	 	break;
			}
			case 17: //�ڵ�����l1���ǵݼ����򣩲���һ��Ԫ��e
			{
				cout << "������һ������ǵݼ�����ĵ�����l1��" << endl;
				cout << "���������㣬���Զ�����" << endl;
				cout << endl;
				if (LINK_LIST_input(l1) && LINK_LIST_sort(l1))
				{
					cout << "����ǰl1��" << endl;
					LINK_LIST_output(l1);
					cout << "��������Ҫ�����Ԫ�أ�";
					input(e);
					cout << endl;
					cout << "��Ҫ���뵥����l1���ǵݼ����򣩵�Ԫ�أ�" << e << "��" << endl;
					cout << endl;
					if (! LINK_LIST_SORT_insert_ELEM(l1,e))
					{
						cout << "�����������ʧ�ܡ�" << endl;
						cout << endl;
						system("PAUSE");
						break;
					}
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					cout << "�����l1��" << endl;
					LINK_LIST_output(l1);
				}
				else
				{
					cout << "****�������****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 18: //������l1,l2���ǵݼ����򣩵ĺϲ��������±�lr
			{
				cout << "�������1������ǵݼ�����ĵ�����" << endl;
				cout << "���������㣬���Զ�����" << endl;
				cout << endl;
				if (! LINK_LIST_input(l1))
				{
					cout << "****�������****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				cout << "�������2������ǵݼ�����ĵ�����" << endl;
				cout << "���������㣬���Զ�����" << endl;
				cout << endl;
				if (! LINK_LIST_input(l2))
				{
					cout << "****�������****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				if ( ( (l1->data>=10000000) && (l2->data<10000000) ) || ( (l1->data<10000000) && (l2->data>=10000000) ) )
				{
					cout << "****l1,l2��ͬʱΪѭ��/��ѭ���������޷�����****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				LINK_LIST_sort(l1);
				LINK_LIST_sort(l2);
				cout << "������l1,l2Ϊ��" << endl;
				cout << endl;
				LINK_LIST_output(l1);
				LINK_LIST_output(l2);
				if (! LINK_LIST_SORT_combine(lr,l1,l2))
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				else
				{
					cout << "��Ҫ�ϲ�������l1�뵥����l2�����뵥����lr��" << endl;
					cout << endl;
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					cout << "������lrΪ��" << endl;
					cout << endl;
					LINK_LIST_output(lr);
				}
				system("PAUSE");
				break;
			}
			case 21: //˫������dl������
			{
				cout << "��Ҫ����˫������dl" << endl;
				cout << endl;
				if ( D_LINK_LIST_input(dl) )
				{
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 22: //˫������dl�����
			{
				cout << "****˫������dl������£�****" << endl;
				cout << endl;
				D_LINK_LIST_output(dl);
				system("PAUSE");
				break;
			}
			case 23: //��˫������dl���зǵݼ�����
			{
				D_LINK_LIST_output(dl);
				cout << "��Ҫ�Ա�dl���зǵݼ�����" << endl;
				cout << endl;
				if ( D_LINK_LIST_sort(dl) )
				{
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 24: //��˫������dl��ԭ��i��Ԫ��ǰ����һ����Ԫ��e
			{
				D_LINK_LIST_output(dl);
				cout << "�������Ҫ�����Ԫ�أ�";
				input(e);
				cout << "���������λ�ã�";
				input(loc);
				cout << endl;
				cout << "��Ҫ��Ԫ��" << e << "����ԭ˫������dl�е�" << loc <<  "��Ԫ��ǰ��" << endl;
				cout << endl;
				status=D_LINK_LIST_insert_ELEM(dl,loc,e);
				if (status==1)
				{
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else if(status==0)
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				else
				{
					cout << "****����λ�ò��Ϸ����޷�������****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 25: //ɾ��˫������dl��ԭ��i��Ԫ�أ����ظ�Ԫ��
			{
				D_LINK_LIST_output(dl);
				cout << "�������Ҫɾ��Ԫ�ص�λ�ã�";
				input(loc);
				cout << endl;
				cout << "��Ҫɾ��ԭ˫������dl�еĵ�" << loc <<  "��Ԫ�ء�" << endl;
				cout << endl;
				status=D_LINK_LIST_delete_ELEM(dl,loc,e);
				if (status==1)
				{
					cout << "��ɾ����Ԫ�أ�" << e << "��" << endl;
					cout << endl;
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else
				{
					cout << "****ɾ��λ�ò��Ϸ����޷�������****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 26: //����˫������dl��Ԫ��e������Ԫ��e��˫�������е�λ��
			{
				D_LINK_LIST_output(dl);
				cout << setiosflags(ios::fixed) << "�������Ҫ���ҵ�Ԫ�أ���������Χ" << (int)(-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (int)(pow(2.0,(double)(8*sizeof(int)-1))) << "��:";
				input(e);
				cout << endl;
				cout << "��Ҫ���ҵ�Ԫ��Ϊ" << e << "��" << endl;
				cout << endl;
				D_LINK_LIST_search_ELEM(dl,loc,e);
				if (!loc)
				{
					cout << "Ԫ��" << e << "��������˫������dl�С�" << endl;
					cout << endl;
				}
				else
				{
					cout << "Ԫ��" << e << "��˫������dl�е����ΪNO." << setw(7) << setfill('0') << loc << "��" << endl;
					cout << endl;
				}
		 		system("PAUSE");
		 	 	break;
			}
			case 27: //��˫������dl1���ǵݼ����򣩲���һ��Ԫ��e
			{
				cout << "������һ������ǵݼ������˫������dl1��" << endl;
				cout << "���������㣬���Զ�����" << endl;
				cout << endl;
				if (D_LINK_LIST_input(dl1) && D_LINK_LIST_sort(dl1))
				{
					cout << "����ǰdl1��" << endl;
					D_LINK_LIST_output(dl1);
					cout << "��������Ҫ�����Ԫ�أ�";
					input(e);
					cout << endl;
					cout << "��Ҫ����˫������dl1���ǵݼ����򣩵�Ԫ�أ�" << e << "��" << endl;
					cout << endl;
					if (! D_LINK_LIST_SORT_insert_ELEM(dl1,e))
					{
						cout << "�����������ʧ�ܡ�" << endl;
						cout << endl;
						system("PAUSE");
						break;
					}
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					cout << "�����dl1��" << endl;
					D_LINK_LIST_output(dl1);
				}
				else
				{
					cout << "****�������****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 28: //˫������dl1,dl2���ǵݼ����򣩵ĺϲ��������±�dlr
			{
				cout << "�������1������ǵݼ������˫������" << endl;
				cout << "���������㣬���Զ�����" << endl;
				cout << endl;
				if (! D_LINK_LIST_input(dl1))
				{
					cout << "****�������****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				cout << "�������2������ǵݼ������˫������" << endl;
				cout << "���������㣬���Զ�����" << endl;
				cout << endl;
				if (! D_LINK_LIST_input(dl2))
				{
					cout << "****�������****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				if ( ( (dl1->data>=10000000) && (dl2->data<10000000) ) || ( (dl1->data<10000000) && (dl2->data>=10000000) ) )
				{
					cout << "****dl1,dl2��ͬʱΪѭ��/��ѭ��˫�������޷�����****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				D_LINK_LIST_sort(dl1);
				D_LINK_LIST_sort(dl2);
				cout << "˫������dl1,dl2Ϊ��" << endl;
				cout << endl;
				D_LINK_LIST_output(dl1);
				D_LINK_LIST_output(dl2);
				if (! D_LINK_LIST_SORT_combine(dlr,dl1,dl2))
				{
					cout << "****����ʧ�ܣ�****" << endl;
					cout << endl;
				}
				else
				{
					cout << "��Ҫ�ϲ�˫������dl1��˫������dl2������˫������dlr��" << endl;
					cout << endl;
					cout << "****�����ɹ���****" << endl;
					cout << endl;
					cout << "˫������dlrΪ��" << endl;
					cout << endl;
					D_LINK_LIST_output(dlr);
				}
				system("PAUSE");
				break;
			}
			default:
			{
				cout << "****����������������룡****" << endl;
				cout << endl;
				system("PAUSE");
				break;
			}
		}
	}
}
