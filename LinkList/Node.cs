using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinkList
{
    class Node<TNode>
    {
        /*      对象：字段      */

        //结点的值
        //这里定义：结点相同当且仅当结点的值相同。
        //所以，同一链表中不能含有值相同的结点！
        TNode _value;

        //指向后一个结点
        Node<TNode> _next;
        //指向前一个结点
        Node<TNode> _last;
        //该节点是否为头结点
        //头结点：仅用于链表管理，无有效的值
        Boolean _isHead;

        /*      对象：覆盖定义从Object类继承的方法      */

        //覆盖定义ToString方法
        override public string ToString()
        {
            return _value.ToString();
        }

        /*      对象构造方法与析构方法      */

        //构造方法（4个参数）
        public Node(TNode value, Node<TNode> next, Node<TNode> last, Boolean ishead)
        {
            SetValue(value);
            SetNext(next);
            SetLast(last);
            SetIsHead(ishead);
        }

        /*      对象：功能方法      */

        //Get方法系列

        public TNode GetValue()
        {
            return _value;
        }

        public Node<TNode> GetNext()
        {
            return _next;
        }

        public Node<TNode> GetLast()
        {
            return _last;
        }

        public Boolean GetIsHead()
        {
            return _isHead;
        }

        //Set方法系列

        public void SetValue(TNode value)
        {
            _value = value;
        }

        public void SetNext(Node<TNode> next)
        {
            _next = next;
        }

        public void SetLast(Node<TNode> last)
        {
            _last = last;
        }

        public void SetIsHead(Boolean isHead)
        {
            _isHead = isHead;
        }
    }
}
