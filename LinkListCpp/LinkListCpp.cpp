#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
using namespace std;

/* 定义'STATUS'及其取值 */

typedef int STATUS;
const int OK 			= 1;
const int ERROR 		= 0;
const int INFEASIBLE 	=-1;	//不可行

//----------------------------------------------------------------------------------------------------//

/*                                                链表                                                */

/* 定义数据元素、数据结构和其他全局变量 */

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

/* 声明数据操作 */

//单链表

//单链表的初始化
STATUS LINK_LIST_init(NODE *(&list));
//单链表的销毁
STATUS LINK_LIST_delete(NODE *(&list));
//单链表的清空
STATUS LINK_LIST_clear(NODE *(&list));
//单链表的复制
STATUS LINK_LIST_copy(NODE *(&list),NODE *(&list_c));
//单链表的输入
STATUS LINK_LIST_input(NODE *(&list));
//单链表的输出
STATUS LINK_LIST_output(NODE *(&list));
//对单链表进行非递减排序
STATUS LINK_LIST_sort(NODE *(&list));
//在单链表第location个元素前插入一个新元素elem
STATUS LINK_LIST_insert_ELEM(NODE *(&list),const int &location,const LINK_LIST_ELEM_TYPE &elem);
//删除单链表第location个元素，返回该元素到elem
STATUS LINK_LIST_delete_ELEM(NODE *(&list),const int &location,LINK_LIST_ELEM_TYPE &elem);
//查找elem元素，返回元素位置到location
STATUS LINK_LIST_search_ELEM(NODE *(&list),int &location,const LINK_LIST_ELEM_TYPE &elem);
//单链表（非递减排序）插入一个新元素elem
STATUS LINK_LIST_SORT_insert_ELEM(NODE *(&list),const LINK_LIST_ELEM_TYPE &elem);
//单链表list_1,list_2（非递减排序）的合并，返回新表list
STATUS LINK_LIST_SORT_combine(NODE *(&list),NODE *(&list_1),NODE *(&list_2));

//双向链表

//双向链表的初始化
STATUS D_LINK_LIST_init(D_NODE *(&list));
//双向链表的销毁
STATUS D_LINK_LIST_delete(D_NODE *(&list));
//双向链表的清空
STATUS D_LINK_LIST_clear(D_NODE *(&list));
//双向链表的输入
STATUS D_LINK_LIST_input(D_NODE *(&list));
//双向链表的输出
STATUS D_LINK_LIST_output(D_NODE *(&list));
//双向链表的复制
STATUS D_LINK_LIST_copy(D_NODE *(&list),D_NODE *(&list_c));
//对双向链表进行非递减排序
STATUS D_LINK_LIST_sort(D_NODE *(&list));
//在双向链表第location个元素前插入一个新元素elem
STATUS D_LINK_LIST_insert_ELEM(D_NODE *(&list),const int &location,const LINK_LIST_ELEM_TYPE &elem);
//删除双向链表第location个元素，返回该元素到elem
STATUS D_LINK_LIST_delete_ELEM(D_NODE *(&list),const int &location,LINK_LIST_ELEM_TYPE &elem);
//查找elem元素，返回元素位置到location
STATUS D_LINK_LIST_search_ELEM(D_NODE *(&list),int &location,const LINK_LIST_ELEM_TYPE &elem);
//双向链表（非递减排序）插入一个新元素elem
STATUS D_LINK_LIST_SORT_insert_ELEM(D_NODE *(&list),const LINK_LIST_ELEM_TYPE &elem);
//双向链表list_1,list_2（非递减排序）的合并，返回新表list
STATUS D_LINK_LIST_SORT_combine(D_NODE *(&list),D_NODE *(&list_1),D_NODE *(&list_2));

//工具函数
int LINK_LIST_lenth(NODE *(&list)); 		//返回单链表的长度
int D_LINK_LIST_lenth(D_NODE *(&list)); 	//返回双向链表的长度
void LINK_LIST_TOOL_input(LINK_LIST_ELEM_TYPE &a); 	//输入元素
//void LINK_LIST_TOOL_input(int &a); 		//输入序号

/* 定义数据操作 */

//单链表的初始化
STATUS LINK_LIST_init(NODE *(&list))
{
	list=(NODE *) malloc(sizeof(NODE));
	if (!list) return ERROR;
	list->data=0;
	list->next=NULL;
	return OK;
}

//单链表的销毁
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

//单链表的清空
STATUS LINK_LIST_clear(NODE *(&list))
{
	int temp_1=1;
	LINK_LIST_ELEM_TYPE temp_2;
	while ( LINK_LIST_delete_ELEM(list,temp_1,temp_2)==OK )
	{}
	return OK;
}

//单链表的复制
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

//单链表的输入
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
		cout << "请给出单链表的类型（循环—1，非循环—0）：";
		LINK_LIST_TOOL_input(circ);
		while (!(circ==0||circ==1))
		{
			cout << "数据不合法，请重新输入：";
			LINK_LIST_TOOL_input(circ);
		}
		cout << "需要建立" << (circ?"":"非") << "循环单链表。" << endl;
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
		cout << "请给出需要输入的元素数量（整数，范围0~~1248576）:";
		LINK_LIST_TOOL_input(lenth);
		while(lenth<0||lenth>1248576)
		{
			cout << "数据不合法，请重新输入：";
			LINK_LIST_TOOL_input(lenth);
		}
		cout << "需要输入" << lenth << "个数据。" << endl;
		cout << endl;
	}
	if (1)
	{
		cout << "请依次输入各个元素，每个元素之间用回车分隔：" << endl;
		cout << setiosflags(ios::fixed) << setprecision(0) << "（整数，范围" << (-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (pow(2.0,(double)(8*sizeof(int)-1))-1) << "）" << endl;
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

//单链表的输出
STATUS LINK_LIST_output(NODE *(&list))
{
	NODE *p;
	int counter;
	p=list;
	cout << "*******************************" << endl;
	cout << "* 单链表总长：" << setw(7) << setfill(' ') << ( p->data>= 10000000 ? p->data-10000000 : p->data ) << "个元素   *" << endl;
	cout << "* 单链表内容                  *" << endl;
	for (p=list->next,counter=1;(p && p!=list);p=p->next,counter++)
	{
		cout << "*    No." << setw(7) << setfill('0') << counter << " ";
		cout << setw(11) << setfill(' ') << p->data << "   *" << endl;
	}
	cout << "*******************************" << endl;
	cout << endl;
	return OK;
}

//对单链表进行非递减排序
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

//在单链表原第location个元素前插入一个新元素elem
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

//删除单链表原第location个元素，返回该元素到elem
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

//查找elem元素，返回元素位置到location
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

//单链表（非递减排序）插入一个新元素elem
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

//单链表list_1,list_2（非递减排序）的合并，返回新表list
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
		p->next=list_2_c->next;	//连接
		for (;p->next!=end_2;p=p->next)
		{}
		p->next=end;	//末端处理
		list->data+=LINK_LIST_lenth(list_2_c);
		LINK_LIST_sort(list);
		return OK;
	}
	else
	{
		return ERROR;
	}
}

//双向链表的初始化
STATUS D_LINK_LIST_init(D_NODE *(&list))
{
	list=(D_NODE *) malloc(sizeof(D_NODE));
	if (!list) return ERROR;
	list->data=0;
	list->prior=NULL;
	list->next=NULL;
	return OK;
}

//双向链表的销毁
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

//双向链表的清空
STATUS D_LINK_LIST_clear(D_NODE *(&list))
{
	int temp_1=1;
	LINK_LIST_ELEM_TYPE temp_2;
	while ( D_LINK_LIST_delete_ELEM(list,temp_1,temp_2)==OK )
	{}
	return OK;
}

//双向链表的复制
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

//双向链表的输入
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
		cout << "请给出双向链表的类型（循环—1，非循环—0）：";
		LINK_LIST_TOOL_input(circ);
		while (!(circ==0||circ==1))
		{
			cout << "数据不合法，请重新输入：";
			LINK_LIST_TOOL_input(circ);
		}
		cout << "需要建立" << (circ?"":"非") << "循环双向链表。" << endl;
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
		cout << "请给出需要输入的元素数量（整数，范围0~~1248576）:";
		LINK_LIST_TOOL_input(lenth);
		while(lenth<0||lenth>1248576)
		{
			cout << "数据不合法，请重新输入：";
			LINK_LIST_TOOL_input(lenth);
		}
		cout << "需要输入" << lenth << "个数据。" << endl;
		cout << endl;
	}
	if (1)
	{
		cout << "请依次输入各个元素，每个元素之间用回车分隔：" << endl;
		cout << setiosflags(ios::fixed) << setprecision(0) << "（整数，范围" << (-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (pow(2.0,(double)(8*sizeof(int)-1))-1) << "）" << endl;
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

//双向链表的输出
STATUS D_LINK_LIST_output(D_NODE *(&list))
{
	D_NODE *p;
	int counter;
	p=list;
	cout << "*******************************" << endl;
	cout << "* 双向链表总长：" << setw(7) << setfill(' ') << ( p->data>= 10000000 ? p->data-10000000 : p->data ) << "个元素 *" << endl;
	cout << "* 双向链表内容：              *" << endl;
	for (p=list->next,counter=1;(p && p!=list);p=p->next,counter++)
	{
		cout << "*    No." << setw(7) << setfill('0') << counter << " ";
		cout << setw(11) << setfill(' ') << p->data << "   *" << endl;
	}
	cout << "*******************************" << endl;
	cout << endl;
	return OK;
}

//对双向链表进行非递减排序
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

//在双向链表原第location个元素前插入一个新元素elem
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

//删除双向链表原第location个元素，返回该元素到elem
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

//查找elem元素，返回元素位置到location
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

//双向链表（非递减排序）插入一个新元素elem
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

//双向链表list_1,list_2（非递减排序）的合并，返回新表list
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
		if (1)	//连接
		{
			p->next=list_2_c->next;
			list_2_c->prior=p;
		}
		for (;p->next!=end_2;p=p->next)
		{}
		if (1)	//末端处理
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

//返回单链表的长度
int LINK_LIST_lenth(NODE *(&list))
{
	if (list->data<10000000)
		return (list->data);
	else
		return (list->data-10000000);
}

//返回双向链表的长度
int D_LINK_LIST_lenth(D_NODE *(&list))
{
	if (list->data<10000000)
		return (list->data);
	else
		return (list->data-10000000);
}

/* 定义其他函数 */

//输入元素
void LINK_LIST_TOOL_input(LINK_LIST_ELEM_TYPE &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << endl;
		cout << "****输入异常！****" << endl;
		cout<< endl;
		cout << "程序退出..." << endl;
		cout << endl;
		system("PAUSE");
		exit(-1);
	}
}

/*
//输入序号
void LINK_LIST_TOOL_input(int &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << "****输入异常！****" << endl;
		cout<< endl;
		cout << "程序退出..." << endl;
		cout << endl;
		system("PAUSE");
		exit(-1);
	}
}
*/

//----------------------------------------------------------------------------------------------------//

/* 主函数实现 */

//输入元素
void input(LINK_LIST_ELEM_TYPE &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << "****输入异常！****" << endl;
		cout<< endl;
		cout << "程序退出..." << endl;
		cout << endl;
		system("PAUSE");
		exit(-1);
	}
}

/*
//输入序号
void input(int &a)
{
	if (! (cin >> a))
	{
		cout << endl;
		cout << "****输入异常！****" << endl;
		cout<< endl;
		cout << "程序退出..." << endl;
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
		cout << "****输入异常！****" << endl;
		cout<< endl;
		cout << "程序退出..." << endl;
		cout << endl;
		system("PAUSE");
		return -1;
	}
	while (1)
	{
		cout << endl;
		cout << "**************************************************************" << endl;
		cout << "*                                                            *" << endl;
		cout << "*                            链表                            *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  控制:                                                     *" << endl;
		cout << "*      00.初始化程序                                         *" << endl;
		cout << "*      99.退出程序                                           *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  单链表:                                                   *" << endl;
		cout << "*      11.单链表l的输入                                      *" << endl;
		cout << "*      12.单链表l的输出                                      *" << endl;
		cout << "*      13.对单链表l进行非递减排序                            *" << endl;
		cout << "*      14.在单链表l的原第i个元素前插入一个新元素e            *" << endl;
		cout << "*      15.删除单链表l的原第i个元素，返回该元素               *" << endl;
		cout << "*      16.查找单链表l的元素e，返回元素e在单链表中的位置      *" << endl;
		cout << "*      17.在单链表l1（非递减排序）插入一个元素e              *" << endl;
		cout << "*      18.单链表l1,l2（非递减排序）的合并，返回新表lr        *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  双向链表:                                                 *" << endl;
		cout << "*      21.双向链表dl的输入                                   *" << endl;
		cout << "*      22.双向链表dl的输出                                   *" << endl;
		cout << "*      23.对双向链表dl进行非递减排序                         *" << endl;
		cout << "*      24.在双向链表dl的原第i个元素前插入一个新元素e         *" << endl;
		cout << "*      25.删除双向链表dl的原第i个元素，返回该元素            *" << endl;
		cout << "*      26.查找双向链表dl的元素e，返回元素e在双向链表中的位置 *" << endl;
		cout << "*      27.在双向链表dl（非递减排序）插入一个元素e            *" << endl;
		cout << "*      28.双向链表dl1,dl2（非递减排序）的合并，返回新表dlr   *" << endl;
		cout << "*                                                            *" << endl;
		cout << "*  注意：                                                    *" << endl;
		cout << "*      请按要求输入！不合法的输入将可能导致程序直接退出！    *" << endl;
		cout << "*                                                            *" << endl;
		cout << "**************************************************************" << endl;
		cout << endl;
		cout << "请选择：";
		input(func);
		cout << endl;
		switch (func)
		{
			case 0: //初始化程序
			{
				LINK_LIST_clear(l);
				LINK_LIST_clear(l1);
				LINK_LIST_clear(l2);
				LINK_LIST_clear(lr);
				D_LINK_LIST_clear(dl);
				D_LINK_LIST_clear(dl1);
				D_LINK_LIST_clear(dl2);
				D_LINK_LIST_clear(dlr);
				cout << "****初始化，操作成功！****" << endl;
				cout << endl;
				system("PAUSE");
				break;
			}
			case 99: //退出程序
			{
				LINK_LIST_delete(l);
				LINK_LIST_delete(l1);
				LINK_LIST_delete(l2);
				LINK_LIST_delete(lr);
				D_LINK_LIST_delete(dl);
				D_LINK_LIST_delete(dl1);
				D_LINK_LIST_delete(dl2);
				D_LINK_LIST_delete(dlr);
				cout << "程序退出..." << endl;
				cout << endl;
				system("PAUSE");
				return 0;
			}
			case 11: //单链表l的输入
			{
				cout << "需要输入单链表l" << endl;
				cout << endl;
				if ( LINK_LIST_input(l) )
				{
					cout << "****操作成功！****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 12: //单链表l的输出
			{
				cout << "****单链表l输出如下：****" << endl;
				cout << endl;
				LINK_LIST_output(l);
				system("PAUSE");
				break;
			}
			case 13: //对单链表l进行非递减排序
			{
				LINK_LIST_output(l);
				cout << "需要对表l进行非递减排序。" << endl;
				cout << endl;
				if ( LINK_LIST_sort(l) )
				{
					cout << "****操作成功！****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 14: //在单链表l的原第i个元素前插入一个新元素e
			{
				LINK_LIST_output(l);
				cout << "请给出需要插入的元素：";
				input(e);
				cout << "请给出插入位置：";
				input(loc);
				cout << endl;
				cout << "需要将元素" << e << "插入原单链表l中第" << loc <<  "个元素前。" << endl;
				cout << endl;
				status=LINK_LIST_insert_ELEM(l,loc,e);
				if (status==1)
				{
					cout << "****操作成功！****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else if(status==0)
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				else
				{
					cout << "****插入位置不合法，无法操作！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 15: //删除单链表l的原第i个元素，返回该元素
			{
				LINK_LIST_output(l);
				cout << "请给出需要删除元素的位置：";
				input(loc);
				cout << endl;
				cout << "需要删除原单链表l中的第" << loc <<  "个元素。" << endl;
				cout << endl;
				status=LINK_LIST_delete_ELEM(l,loc,e);
				if (status==1)
				{
					cout << "被删除的元素：" << e << "。" << endl;
					cout << endl;
					cout << "****操作成功！****" << endl;
					cout << endl;
					LINK_LIST_output(l);
				}
				else
				{
					cout << "****删除位置不合法，无法操作！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 16: //查找单链表l的元素e，返回元素e在单链表中的位置
			{
				LINK_LIST_output(l);
				cout << setiosflags(ios::fixed) << "请给出需要查找的元素（整数，范围" << (int)(-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (int)(pow(2.0,(double)(8*sizeof(int)-1))) << "）:";
				input(e);
				cout << endl;
				cout << "需要查找的元素为" << e << "。" << endl;
				cout << endl;
				LINK_LIST_search_ELEM(l,loc,e);
				if (!loc)
				{
					cout << "元素" << e << "不存在于单链表l中。" << endl;
					cout << endl;
				}
				else
				{
					cout << "元素" << e << "在单链表l中的序号为NO." << setw(7) << setfill('0') << loc << "。" << endl;
					cout << endl;
				}
		 		system("PAUSE");
		 	 	break;
			}
			case 17: //在单链表l1（非递减排序）插入一个元素e
			{
				cout << "请输入一个满足非递减排序的单链表l1：" << endl;
				cout << "（若不满足，则自动排序）" << endl;
				cout << endl;
				if (LINK_LIST_input(l1) && LINK_LIST_sort(l1))
				{
					cout << "插入前l1：" << endl;
					LINK_LIST_output(l1);
					cout << "请输入需要插入的元素：";
					input(e);
					cout << endl;
					cout << "需要插入单链表l1（非递减排序）的元素：" << e << "。" << endl;
					cout << endl;
					if (! LINK_LIST_SORT_insert_ELEM(l1,e))
					{
						cout << "插入出错！操作失败。" << endl;
						cout << endl;
						system("PAUSE");
						break;
					}
					cout << "****操作成功！****" << endl;
					cout << endl;
					cout << "插入后l1：" << endl;
					LINK_LIST_output(l1);
				}
				else
				{
					cout << "****输入出错！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 18: //单链表l1,l2（非递减排序）的合并，返回新表lr
			{
				cout << "请输入第1个满足非递减排序的单链表：" << endl;
				cout << "（若不满足，则自动排序）" << endl;
				cout << endl;
				if (! LINK_LIST_input(l1))
				{
					cout << "****输入出错！****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				cout << "请输入第2个满足非递减排序的单链表：" << endl;
				cout << "（若不满足，则自动排序）" << endl;
				cout << endl;
				if (! LINK_LIST_input(l2))
				{
					cout << "****输入出错！****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				if ( ( (l1->data>=10000000) && (l2->data<10000000) ) || ( (l1->data<10000000) && (l2->data>=10000000) ) )
				{
					cout << "****l1,l2不同时为循环/非循环单链表，无法操作****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				LINK_LIST_sort(l1);
				LINK_LIST_sort(l2);
				cout << "单链表l1,l2为：" << endl;
				cout << endl;
				LINK_LIST_output(l1);
				LINK_LIST_output(l2);
				if (! LINK_LIST_SORT_combine(lr,l1,l2))
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				else
				{
					cout << "需要合并单链表l1与单链表l2，放入单链表lr。" << endl;
					cout << endl;
					cout << "****操作成功！****" << endl;
					cout << endl;
					cout << "单链表lr为：" << endl;
					cout << endl;
					LINK_LIST_output(lr);
				}
				system("PAUSE");
				break;
			}
			case 21: //双向链表dl的输入
			{
				cout << "需要输入双向链表dl" << endl;
				cout << endl;
				if ( D_LINK_LIST_input(dl) )
				{
					cout << "****操作成功！****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 22: //双向链表dl的输出
			{
				cout << "****双向链表dl输出如下：****" << endl;
				cout << endl;
				D_LINK_LIST_output(dl);
				system("PAUSE");
				break;
			}
			case 23: //对双向链表dl进行非递减排序
			{
				D_LINK_LIST_output(dl);
				cout << "需要对表dl进行非递减排序。" << endl;
				cout << endl;
				if ( D_LINK_LIST_sort(dl) )
				{
					cout << "****操作成功！****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 24: //在双向链表dl的原第i个元素前插入一个新元素e
			{
				D_LINK_LIST_output(dl);
				cout << "请给出需要插入的元素：";
				input(e);
				cout << "请给出插入位置：";
				input(loc);
				cout << endl;
				cout << "需要将元素" << e << "插入原双向链表dl中第" << loc <<  "个元素前。" << endl;
				cout << endl;
				status=D_LINK_LIST_insert_ELEM(dl,loc,e);
				if (status==1)
				{
					cout << "****操作成功！****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else if(status==0)
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				else
				{
					cout << "****插入位置不合法，无法操作！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 25: //删除双向链表dl的原第i个元素，返回该元素
			{
				D_LINK_LIST_output(dl);
				cout << "请给出需要删除元素的位置：";
				input(loc);
				cout << endl;
				cout << "需要删除原双向链表dl中的第" << loc <<  "个元素。" << endl;
				cout << endl;
				status=D_LINK_LIST_delete_ELEM(dl,loc,e);
				if (status==1)
				{
					cout << "被删除的元素：" << e << "。" << endl;
					cout << endl;
					cout << "****操作成功！****" << endl;
					cout << endl;
					D_LINK_LIST_output(dl);
				}
				else
				{
					cout << "****删除位置不合法，无法操作！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 26: //查找双向链表dl的元素e，返回元素e在双向链表中的位置
			{
				D_LINK_LIST_output(dl);
				cout << setiosflags(ios::fixed) << "请给出需要查找的元素（整数，范围" << (int)(-pow(2.0,(double)(8*sizeof(int)-1))) << "~~" << (int)(pow(2.0,(double)(8*sizeof(int)-1))) << "）:";
				input(e);
				cout << endl;
				cout << "需要查找的元素为" << e << "。" << endl;
				cout << endl;
				D_LINK_LIST_search_ELEM(dl,loc,e);
				if (!loc)
				{
					cout << "元素" << e << "不存在于双向链表dl中。" << endl;
					cout << endl;
				}
				else
				{
					cout << "元素" << e << "在双向链表dl中的序号为NO." << setw(7) << setfill('0') << loc << "。" << endl;
					cout << endl;
				}
		 		system("PAUSE");
		 	 	break;
			}
			case 27: //在双向链表dl1（非递减排序）插入一个元素e
			{
				cout << "请输入一个满足非递减排序的双向链表dl1：" << endl;
				cout << "（若不满足，则自动排序）" << endl;
				cout << endl;
				if (D_LINK_LIST_input(dl1) && D_LINK_LIST_sort(dl1))
				{
					cout << "插入前dl1：" << endl;
					D_LINK_LIST_output(dl1);
					cout << "请输入需要插入的元素：";
					input(e);
					cout << endl;
					cout << "需要插入双向链表dl1（非递减排序）的元素：" << e << "。" << endl;
					cout << endl;
					if (! D_LINK_LIST_SORT_insert_ELEM(dl1,e))
					{
						cout << "插入出错！操作失败。" << endl;
						cout << endl;
						system("PAUSE");
						break;
					}
					cout << "****操作成功！****" << endl;
					cout << endl;
					cout << "插入后dl1：" << endl;
					D_LINK_LIST_output(dl1);
				}
				else
				{
					cout << "****输入出错！****" << endl;
					cout << endl;
				}
				system("PAUSE");
				break;
			}
			case 28: //双向链表dl1,dl2（非递减排序）的合并，返回新表dlr
			{
				cout << "请输入第1个满足非递减排序的双向链表：" << endl;
				cout << "（若不满足，则自动排序）" << endl;
				cout << endl;
				if (! D_LINK_LIST_input(dl1))
				{
					cout << "****输入出错！****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				cout << "请输入第2个满足非递减排序的双向链表：" << endl;
				cout << "（若不满足，则自动排序）" << endl;
				cout << endl;
				if (! D_LINK_LIST_input(dl2))
				{
					cout << "****输入出错！****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				if ( ( (dl1->data>=10000000) && (dl2->data<10000000) ) || ( (dl1->data<10000000) && (dl2->data>=10000000) ) )
				{
					cout << "****dl1,dl2不同时为循环/非循环双向链表，无法操作****" << endl;
					cout << endl;
					system("PAUSE");
					break;
				}
				D_LINK_LIST_sort(dl1);
				D_LINK_LIST_sort(dl2);
				cout << "双向链表dl1,dl2为：" << endl;
				cout << endl;
				D_LINK_LIST_output(dl1);
				D_LINK_LIST_output(dl2);
				if (! D_LINK_LIST_SORT_combine(dlr,dl1,dl2))
				{
					cout << "****操作失败！****" << endl;
					cout << endl;
				}
				else
				{
					cout << "需要合并双向链表dl1与双向链表dl2，放入双向链表dlr。" << endl;
					cout << endl;
					cout << "****操作成功！****" << endl;
					cout << endl;
					cout << "双向链表dlr为：" << endl;
					cout << endl;
					D_LINK_LIST_output(dlr);
				}
				system("PAUSE");
				break;
			}
			default:
			{
				cout << "****输入错误，请重新输入！****" << endl;
				cout << endl;
				system("PAUSE");
				break;
			}
		}
	}
}
