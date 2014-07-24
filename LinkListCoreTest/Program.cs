using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinkList
{
    class Program
    {
        static void Main(string[] args)
        {
            LinkList<String> test_NT_NC = new LinkList<String>(false, false);
            LinkList<String> test_NT_C = new LinkList<String>(false, true);
            LinkList<String> test_T_NC = new LinkList<String>(true, false);
            LinkList<String> test_T_C = new LinkList<String>(true, true);

            //插入测试1
            for (Int32 i = 1; i <= 6; i++)
            {
                test_NT_NC.InsectNode(i, i.ToString());
                test_NT_C.InsectNode(i, i.ToString());
                test_T_NC.InsectNode(i, i.ToString());
                test_T_C.InsectNode(i, i.ToString());
            }
            //输出
            display(test_NT_NC, "test_NT_NC");
            display(test_NT_C, "test_NT_C");
            display(test_T_NC, "test_T_NC");
            display(test_T_C, "test_T_C");
            Console.ReadLine();
            Console.Clear();

            //删除测试
            for (Int32 i = 1; i <= 10; i++)
            {
                test_NT_NC.DeleteNode(1);
                test_NT_C.DeleteNode(1);
                test_T_NC.DeleteNode(1);
                test_T_C.DeleteNode(1);
            }
            //输出
            display(test_NT_NC, "test_NT_NC");
            display(test_NT_C, "test_NT_C");
            display(test_T_NC, "test_T_NC");
            display(test_T_C, "test_T_C");
            Console.ReadLine();
            Console.Clear();

            //插入测试2
            for (Int32 i = 1; i <= 20; i++)
            {
                test_NT_NC.InsectNode(i, i.ToString());
                test_NT_C.InsectNode(i, i.ToString());
                test_T_NC.InsectNode(i, i.ToString());
                test_T_C.InsectNode(i, i.ToString());
            }
            //输出
            display(test_NT_NC, "test_NT_NC");
            display(test_NT_C, "test_NT_C");
            display(test_T_NC, "test_T_NC");
            display(test_T_C, "test_T_C");
            Console.ReadLine();
            Console.Clear();

            //搜索测试
            Int32 loc = 0;
            display(test_NT_NC, "test_NT_NC");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.WriteLine("查找数据：" + i);
                test_NT_NC.SearchNode(ref loc, i.ToString());
                Console.Out.WriteLine("位置信息：" + loc);
                Console.Out.WriteLine();
            }
            Console.ReadLine();
            Console.Clear();
            display(test_NT_C, "test_NT_C");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.WriteLine("查找数据：" + i);
                test_NT_C.SearchNode(ref loc, i.ToString());
                Console.Out.WriteLine("位置信息：" + loc);
                Console.Out.WriteLine();
            }
            Console.ReadLine();
            Console.Clear();
            display(test_T_NC, "test_T_NC");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.WriteLine("查找数据：" + i);
                test_T_NC.SearchNode(ref loc, i.ToString());
                Console.Out.WriteLine("位置信息：" + loc);
                Console.Out.WriteLine();
            }
            Console.ReadLine();
            Console.Clear();
            display(test_T_C, "test_T_C");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.WriteLine("查找数据：" + i);
                test_T_C.SearchNode(ref loc, i.ToString());
                Console.Out.WriteLine("位置信息：" + loc);
                Console.Out.WriteLine();
            }
            Console.ReadLine();
            Console.Clear();

            //GetNextValue测试
            String val = "\u0000";
            display(test_NT_NC, "test_NT_NC");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.Write(test_NT_NC.GetNextValue(ref val) + "   ");
                Console.Out.WriteLine(val);
                val = null;
            }
            test_NT_NC.ResetPointer();
            Console.ReadLine();
            Console.Clear();
            display(test_NT_C, "test_NT_C");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.Write(test_NT_C.GetNextValue(ref val) + "   ");
                Console.Out.WriteLine(val);
                val = null;
            }
            test_NT_C.ResetPointer();
            Console.ReadLine();
            Console.Clear();
            display(test_T_NC, "test_T_NC");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.Write(test_T_NC.GetNextValue(ref val) + "   ");
                Console.Out.WriteLine(val);
                val = null;
            }
            test_T_NC.ResetPointer();
            Console.ReadLine();
            Console.Clear();
            display(test_T_C, "test_T_C");
            for (Int32 i = 1; i <= 12; i++)
            {
                Console.Out.Write(test_T_C.GetNextValue(ref val) + "   ");
                Console.Out.WriteLine(val);
                val = null;
            }
            test_T_C.ResetPointer();
            Console.ReadLine();
            Console.Clear();

            //清空测试
            test_NT_NC.ClearAll();
            test_NT_C.ClearAll();
            test_T_NC.ClearAll();
            test_T_C.ClearAll();
            //输出
            display(test_NT_NC, "test_NT_NC");
            display(test_NT_C, "test_NT_C");
            display(test_T_NC, "test_T_NC");
            display(test_T_C, "test_T_C");
            Console.ReadLine();
            Console.Clear();

            //结束
            Console.Out.WriteLine("测试结束！");
            Console.Out.WriteLine();
            Console.Out.WriteLine("按任意键退出...");
            Console.ReadLine();
        }

        //链表t的所有结点的指针均正确无误 当且仅当 链表t在方法中输出正确的结果
        static void display(LinkList<String> t, String s)
        {
            Node<String> pr;
            Console.Out.WriteLine("链表:");
            Console.Out.WriteLine(s);
            //当前链表的状态
            Console.Out.WriteLine("当前链表的状态：");
            Console.Out.Write("isTwoWay = " + t.GetIsTwoWay() + "   ");
            Console.Out.Write("isCircle = " + t.GetIsCircle() + "   ");
            Console.Out.Write("isEmpty  = " + t.GetIsEmpty() + "   ");
            Console.Out.WriteLine("lenth = " + t.GetLenth());
            //当前的链表内容为
            Console.Out.WriteLine("当前的链表内容为：");
            pr = t.GetContent();
            pr = pr.GetNext();
            if (t.GetIsCircle())
            {
                while (pr != t.GetContent())
                {
                    Console.Out.Write(pr.GetValue() + " ");
                    pr = pr.GetNext();
                }
            }
            else
            {
                while (pr != null)
                {
                    Console.Out.Write(pr.GetValue() + " ");
                    pr = pr.GetNext();
                }
            }
            Console.Out.WriteLine();
            //链表内容逆向输出
            Console.Out.WriteLine("链表内容逆向输出：");
            pr = t.GetContent();
            if (t.GetIsTwoWay())
            {
                if (t.GetIsCircle())
                {
                    pr = pr.GetLast();
                    while (pr != t.GetContent())
                    {
                        Console.Out.Write(pr.GetValue() + " ");
                        pr = pr.GetLast();
                    }
                }
                else
                {
                    while (pr.GetNext() != null)
                    {
                        pr = pr.GetNext();
                    }
                    while (pr != t.GetContent())
                    {
                        Console.Out.Write(pr.GetValue() + " ");
                        pr = pr.GetLast();
                    }
                }
                Console.Out.WriteLine();
            }
            else
            {
                Console.Out.WriteLine("（不需要测试）");
            }
            Console.Out.WriteLine();
        }
    }
}
