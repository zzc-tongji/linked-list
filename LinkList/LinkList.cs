using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinkList
{
    class LinkList<TLinkList>
    {
        /*      类：字段      */

        public const Int32 MaxLenth = 8;            //所有链表的最大长度

        //状态常量
        public const Int32 OkNi = 2;                //当前操作成功，但下次操作不可行
        public const Int32 Ok = 1;                  //操作成功
        public const Int32 Infeasible = 0;          //操作不可行（实际未操作）
        public const Int32 OutOfMemory = -1;        //无法分配结点所需的内存

        /*      类：方法      */

        //判定两个T类对象是否相同
        public static Boolean AreEqual<TAreEqual>(TAreEqual t1, TAreEqual t2)
        {
            return EqualityComparer<TAreEqual>.Default.Equals(t1, t2);
        }

        /*      对象：字段      */

        //状态标志
        private Boolean _isTwoWay;   //是否为双向链表
        private Boolean _isCircle;   //是否为循环链表
        private Boolean _isEmpty;    //当前链表是否为空（只含头结点的情形仍判定为空）
        private Int32 _lenth;        //当前链表长度（数据结点个数，不含头结点）

        //链表的内容
        private Node<TLinkList> _content;

        //方法GetNextValue专用变量
        private Node<TLinkList> _pointer;

        /*      构造与析构方法      */

        //构造方法（2个参数）
        public LinkList(Boolean isTwoWay, Boolean isCircle)
        {
            _isTwoWay = isTwoWay;
            _isCircle = isCircle;
            _isEmpty = true;
            _lenth = 0;
            _content = new Node<TLinkList>(default(TLinkList), null, null, true);
            if (_isCircle)
            {
                _content.SetNext(_content);
            }
            if (_isCircle && _isTwoWay)
            {
                _content.SetLast(_content);
            }
            ResetPointer();
        }

        /*      对象：功能方法      */

        //Get方法系列

        public Boolean GetIsTwoWay()
        {
            return _isTwoWay;
        }

        public Boolean GetIsCircle()
        {
            return _isCircle;
        }

        public Boolean GetIsEmpty()
        {
            return _isEmpty;
        }

        public Int32 GetLenth()
        {
            return _lenth;
        }

        public Node<TLinkList> GetContent()
        {
            return _content;
        }

        //在链表原第location个结点前插入一个新结点（新结点的值为v）
        public Int32 InsectNode(Int32 location, TLinkList value)
        {
            Int32 loc;
            Node<TLinkList> temp;
            Node<TLinkList> p;
            Node<TLinkList> q;
            /*      可行性判定       */
            //链表不能超过最大长度
            if (_lenth >= MaxLenth)
            {
                return Infeasible;
            }
            //尝试申请空间
            try
            {
                temp = new Node<TLinkList>(value, null, null, false);
            }
            catch (OutOfMemoryException)
            {
                return OutOfMemory;
            }
            //判定是否超出插入范围
            if (location < 1 || location > _lenth + 1)
            {
                return Infeasible;
            }
            /*      正式插入操作      */
            //定位
            p = _content;
            loc = 0;
            while (loc < location - 1)
            {
                p = p.GetNext();
                loc ++;
            }
            q = p.GetNext();
            //向后连接
            p.SetNext(temp);
            temp.SetNext(q);
            //若是双向链表，则向前连接
            if (_isTwoWay)
            {
                if (q != null)
                {
                    q.SetLast(temp);
                }
                temp.SetLast(p);
            }
            //状态变更
            if (_isEmpty)
            {
                _isEmpty = false;
            }
            _lenth += 1;
            return Ok;
        }

        //删除链表原第location个结点（该结点的值通过引用v返回）
        public Int32 DeleteNode(Int32 location, ref TLinkList value)
        {
            Int32 loc;
            Node<TLinkList> p;
            Node<TLinkList> q;
            Node<TLinkList> temp;
            /*      可行性判定       */
            //链表不能为空
            if (_isEmpty)
            {
                return Infeasible;
            }
            if (location < 1 || location > _lenth)
            {
                return Infeasible;
            }
            p = _content;
            loc = 0;
            /*      正式插入操作      */
            //定位
            while (loc < location - 1)
            {
                p = p.GetNext();
                loc++;
            }
            temp = p.GetNext();
            q = temp.GetNext();
            //提取数值
            value = temp.GetValue();
            //改变后向指针
            p.SetNext(q);
            //若是双向链表，改变前向指针
            if (_isTwoWay)
            {
                if (q != null)
                {
                    q.SetLast(p);
                }
            }
            //系统自动释放结点的内存空间
            /*
                free(temp_i1);
            */
            //状态变更
            _lenth -= 1;
            if (_lenth == 0)
            {
                _isEmpty = true;
            }
            return Ok;
        }

        //删除链表原第location个结点
        public Int32 DeleteNode(Int32 location)
        {
            Int32 loc;
            Node<TLinkList> p;
            Node<TLinkList> q;
            Node<TLinkList> temp;
            /*      可行性判定       */
            //链表不能为空
            if (_isEmpty)
            {
                return Infeasible;
            }
            if (location < 1 || location > _lenth)
            {
                return Infeasible;
            }
            p = _content;
            loc = 0;
            /*      正式插入操作      */
            //定位
            while (loc < location - 1)
            {
                p = p.GetNext();
                loc++;
            }
            temp = p.GetNext();
            q = temp.GetNext();
            //改变后向指针
            p.SetNext(q);
            //若是双向链表，改变前向指针
            if (_isTwoWay)
            {
                if (q != null)
                {
                    q.SetLast(p);
                }
            }
            //系统自动释放结点的内存空间
            /*
                free(temp_i1);
            */
            //状态变更
            _lenth -= 1;
            if (_lenth == 0)
            {
                _isEmpty = true;
            }
            return Ok;
        }

        //清空链表
        public void ClearAll()
        {
            //系统自动释放所有结点的内存空间
            /*
                free(...);
            */
            _content = new Node<TLinkList>(default(TLinkList), null, null, true);
            if (_isCircle)
            {
                _content.SetNext(_content);
            }
            if (_isCircle && _isTwoWay)
            {
                _content.SetLast(_content);
            }
            _isEmpty = true;
            _lenth = 0;
            _pointer = _content;
        }

        //查找链表中结点值为v的元素，位置通过引用location返回
        //1.如果找不到，location为0
        //2.计算位置时，头结点不包括在内
        public void SearchNode(ref Int32 location, TLinkList value)
        {
            Node<TLinkList> end;   //末尾数据结点
            Node<TLinkList> p;
            //如果链表为空，直接结束
            if (_isEmpty)
            {
                location = 0;
                return;
            }
            //end的定位
            end = _content;
            if (_isTwoWay && _isCircle)
            {
                end = end.GetLast();
            }
            else if (_isCircle)
            {
                while (end.GetNext() != _content)
                {
                    end = end.GetNext();
                }
            }
            else
            {
                while (end.GetNext() != null)
                {
                    end = end.GetNext();
                }
            }
            //查找
            location = 0;
            p = _content.GetNext();
            while (true)
            {
                location += 1;
                //if (p.GetValue().Equals(_value))
                if (AreEqual<TLinkList>(p.GetValue(), value))
                {
                    return;
                }
                if (p == end)
                {
                    break;
                }
                p = p.GetNext();
            }
            location = 0;
            return;
        }

        //将pointer指向下一个节点，并取出值（通过v返回）
        public Int32 GetNextValue(ref TLinkList value)
        {
            if (_isCircle)
            {
                if (_pointer.GetNext() == _content)
                {
                    return Infeasible;
                }
                else
                {
                    _pointer = _pointer.GetNext();
                    value = _pointer.GetValue();
                    if (_pointer.GetNext() == _content)
                    {
                        return OkNi;
                    }
                    else
                    {
                        return Ok;
                    }
                }
            }
            else
            {
                if (_pointer.GetNext() == null)
                {
                    return Infeasible;
                }
                _pointer = _pointer.GetNext();
                value = _pointer.GetValue();
                if (_pointer.GetNext() == null)
                {
                    return OkNi;
                }
                else
                {
                    return Ok;
                }
            }
        }

        //pointer指针复位
        public void ResetPointer()
        {
            _pointer = _content;
        }
    }
}
