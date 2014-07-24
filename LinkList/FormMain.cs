using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


namespace LinkList
{
    public partial class FromMain : Form
    {
        /*      对象：字段      */

        //用于演示的链表
        LinkList<String> _demo;

        //接受输入并等待传给demo的参数
        Boolean _twoWay;
        Boolean _circle;
        Int32 _location;
        String _value;

        //下列各项用于判定buttonInsect.Enabled是否为true
        Boolean _insectEnableLocation;
        Boolean _insectEnableValue;

        //用来操作Enable属性的对象数组
        Label[] labelOutput = new Label[9];
        PictureBox[] pictureBoxNext = new PictureBox[9];
        PictureBox[] pictureBoxLast = new PictureBox[9];
        PictureBox[] pictureBoxInsect = new PictureBox[9];
        PictureBox[] pictureBoxDelete = new PictureBox[9];
        PictureBox[] pictureBoxSearch = new PictureBox[9];
        PictureBox[] pictureBoxLastCircle = new PictureBox[9];

        //用于绘图的相关对象
        Graphics _graph;
        Pen _blackPen;
        Pen _grayPen;

        /*      对象：辅助方法      */

        //重置全部
        private void ResetAll()
        {
            //“链表状态”所有显示元素不可见
            EraseAll();
            //“全部重置”按钮不可用
            ButtonResetAll.Enabled = false;
            //“链表属性”分组框可用
            gropeBoxAttribute.Enabled = true;
            radioButtonNT.Checked = true;
            radioButtonNC.Checked = true;
            //“链表操作”选项卡控制器不可用
            tabControlOperate.Enabled = false;
            tabControlOperate.SelectedIndex = 0;
            //所有的文本框内容清空
            textBoxInsectLocation.Clear();
            textBoxInsectValue.Clear();
            textBoxDeleteLocation.Clear();
            textBoxSearchValue.Clear();
            //单击“设置”后，输入不合法，无法插入
            ButtonInsect.Enabled = false;
            //单击“设置”后，链表为空，无法删除
            ButtonDelete.Enabled = false;
            //重置链表demo
            if (_demo != null)
            {
                _demo.ClearAll();
            }
            _demo = null;
            //更改“链表长度”标签
            ChangeStateOfLabelLenth();
            //“设定”按钮获得焦点
            ButtonSet.Focus();
        }

        //擦除所有图形
        private void EraseAll()
        {
            Int32 temp;
            //擦除值框
            for (temp = 0; temp <= 8; temp++)   //Tips：从0开始，包括头节点！
            {
                labelOutput[temp].Visible = false;
            }
            //擦除Next箭头
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxNext[temp].Visible = false;
            }
            //擦除Last箭头
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxLast[temp].Visible = false;
            }
            //擦除终止在头节点的Next箭头头部
            pictureBoxNextCircle.Visible = false;
            //擦除起始于头节点的Last箭头头部
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxLastCircle[temp].Visible = false;
            }
            //擦除小箭头
            EraseTag();
            //擦除头节点指向自身的标记
            pictureBox_NextCircleEmpty.Visible = false;
            pictureBox_LastCircleEmpty.Visible = false;
            //擦除程序自行绘制的线条
            _graph.Clear(SystemColors.Control);
        }

        //擦除所有小箭头
        private void EraseTag()
        {
            Int32 temp;
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxInsect[temp].Visible = false;
            }
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxDelete[temp].Visible = false;
            }
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxSearch[temp].Visible = false;
            }
        }

        //擦除图形，但是保留下列部分：
        //1. 头节点
        //2. 若demo为空的循环链表中，则还保留头节点指向自己的指针
        private void Erase()
        {
            Int32 temp;
            //擦除值框
            for (temp = 1; temp <= 8; temp++)   //Tips：从1开始，未包括头节点！
            {
                labelOutput[temp].Visible = false;
            }
            //擦除Next箭头
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxNext[temp].Visible = false;
            }
            //擦除Last箭头
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxLast[temp].Visible = false;
            }
            //擦除终止在头节点的Next箭头头部
            pictureBoxNextCircle.Visible = false;
            //擦除起始于头节点的Last箭头头部
            for (temp = 1; temp <= 8; temp++)
            {
                pictureBoxLastCircle[temp].Visible = false;
            }
            //擦除小箭头
            EraseTag();
            //擦除头节点指向自身的标记
            pictureBox_NextCircleEmpty.Visible = false;
            pictureBox_LastCircleEmpty.Visible = false;
            //根据链表类型重绘上述标记
            if (_demo != null)
            {
                if (_demo.GetIsEmpty())
                {
                    if (_demo.GetIsCircle())
                    {
                        pictureBox_NextCircleEmpty.Visible = true;
                        if (_demo.GetIsTwoWay())
                        {
                            pictureBox_LastCircleEmpty.Visible = true;
                        }
                    }
                }
            }
            else
            {
                ResetAll();
            }
            //擦除程序自行绘制的线条
            _graph.Clear(SystemColors.Control);
        }

        //绘出链表demo当前状态下的图形
        private void Draw()
        {
            if (_demo != null)
            {
                Int32 temp_i1;
                Int32 temp_i2;
                String temp_s = null;
                //专用指针复位
                _demo.ResetPointer();
                //绘图：头节点
                labelOutputHead.Visible = true;
                //如果demo不是空的
                if (_demo.GetIsEmpty() == false)
                {
                    //绘图：值框
                    for (temp_i1 = 1; (temp_i2 = _demo.GetNextValue(ref temp_s)) != 0; temp_i1++)
                    {
                        labelOutput[temp_i1].Text = temp_s;
                        if (temp_i2 == 2)
                        {
                            break;
                        }
                    }
                    //绘图：箭头
                    for (temp_i2 = 1; temp_i2 <= temp_i1; temp_i2++)
                    {
                        labelOutput[temp_i2].Visible = true;
                        pictureBoxNext[temp_i2].Visible = true;
                        if (_demo.GetIsTwoWay())
                        {
                            pictureBoxLast[temp_i2].Visible = true;
                        }
                    }
                    //绘图：如果是循环链表，绘出与头节点有关Next和Last的箭头
                    if (_demo.GetIsCircle())
                    {
                        //基准点设置
                        Int32 basePointX = pictureBoxNextCircle.Location.X;
                        Int32 basePointY = pictureBoxNextCircle.Location.Y;
                        //平移值和间隔值设定
                        Int32 moveValue = 22;
                        Int32 intervalValue = 34;
                        //定位黑色顶点
                        Point blackTail = new Point(basePointX + 11, basePointY - 5 + 57 * temp_i1);
                        Point blackM1 = new Point(basePointX + 11 + moveValue, basePointY - 5 + 57 * temp_i1);
                        Point blackM2 = new Point(basePointX + 11 + moveValue, basePointY - 5 + 57 * temp_i1);
                        Point blackM3 = new Point(basePointX + 11 + moveValue, basePointY + 8);
                        Point blackM4 = new Point(basePointX + 11 + moveValue, basePointY + 8);
                        Point blackHead = new Point(basePointX + 11, basePointY + 8);
                        //微调黑色顶点
                        blackM2.X -= 2;
                        blackM3.X -= 2;
                        //绘出黑色的折线
                        _graph.DrawLine(_blackPen, blackTail, blackM1);
                        _graph.DrawLine(_blackPen, blackM2, blackM3);
                        _graph.DrawLine(_blackPen, blackM4, blackHead);
                        //绘出黑色箭头
                        pictureBoxNextCircle.Visible = true;
                        //如果是双向链表，绘出图头节点有关的Last箭头
                        if (_demo.GetIsTwoWay())
                        {
                            //定位灰色顶点
                            Point grayTail = new Point(basePointX + 11, basePointY - 5);
                            Point grayM1 = new Point(basePointX + 11 + moveValue + intervalValue, basePointY - 5);
                            Point grayM2 = new Point(basePointX + 11 + moveValue + intervalValue, basePointY - 5);
                            Point grayM3 = new Point(basePointX + 11 + moveValue + intervalValue, basePointY + 8 + 57 * temp_i1);
                            Point grayM4 = new Point(basePointX + 11 + moveValue + intervalValue, basePointY + 8 + 57 * temp_i1);
                            Point grayHead = new Point(basePointX + 11, basePointY + 8 + 57 * temp_i1);
                            //微调灰色顶点
                            grayM2.X -= 2;
                            grayM3.X -= 2;
                            //绘出灰色的折线
                            _graph.DrawLine(_grayPen, grayTail, grayM1);
                            _graph.DrawLine(_grayPen, grayM2, grayM3);
                            _graph.DrawLine(_grayPen, grayM4, grayHead);
                            //绘出灰色箭头
                            pictureBoxLastCircle[temp_i1].Visible = true;
                        }
                    }
                }
                //如果demo是空的
                else
                {
                    //绘图：如果是循环链表，绘出循环链表空标志
                    if (_demo.GetIsCircle())
                    {
                        pictureBox_NextCircleEmpty.Visible = true;
                        if (_demo.GetIsTwoWay())
                        {
                            pictureBox_LastCircleEmpty.Visible = true;
                        }
                    }
                }
            }
            else
            {
                ResetAll();
            }
        }

        //设定“插入节点”选项卡和“删除节点”选项卡上控件的状态
        private void SetStateOfTabInsectDelete()
        {
            //清除所有小箭头
            EraseTag();
            //改变按钮状态
            if (_demo != null)
            {
                if (_demo.GetLenth() < 8)
                {
                    textBoxInsectLocation.Enabled = true;
                    textBoxInsectValue.Enabled = true;
                }
                else
                {
                    ButtonInsect.Enabled = false;
                    textBoxInsectLocation.Enabled = false;
                    textBoxInsectValue.Enabled = false;
                }
                if (_demo.GetLenth() > 0)
                {
                    textBoxDeleteLocation.Enabled = true;
                }
                else
                {
                    ButtonDelete.Enabled = false;
                    textBoxDeleteLocation.Enabled = false;
                }
            }
            else
            {
                tabControlOperate.Enabled = false;
            }
            //清空“新节点的位置”和“新节点的值”两个文本框
            textBoxInsectLocation.Clear();
            textBoxInsectValue.Clear();
            //清空“需删除节点的位置”文本框
            textBoxDeleteLocation.Clear();
            //清空“节点的值”文本框
            textBoxSearchValue.Clear();
        }

        //更改“插入节点”选项卡“新节点的位置”标签的状态
        private void ChangeStateOfLabelInsectLocationAble(Int32 state)
        {
            if (state == 1)
            {
                labelInsectLocationAble.ForeColor = Color.Green;
                labelInsectLocationAble.Text = "位置有效";
            }
            else
            {
                labelInsectLocationAble.ForeColor = Color.Red;
                labelInsectLocationAble.Text = "位置无效";
            }
        }

        //更改“插入节点”选项卡“新节点的值”标签的状态
        private void ChangeStateOfLabelInsectValueAble(Int32 state)
        {
            if (state == 1)
            {
                labelInsectValueAble.ForeColor = Color.Green;
                labelInsectValueAble.Text = "内容有效";
            }
            else if (state == 0)
            {
                labelInsectValueAble.ForeColor = Color.Red;
                labelInsectValueAble.Text = "链表中已有相同内容";
            }
            else
            {
                labelInsectValueAble.ForeColor = Color.Red;
                labelInsectValueAble.Text = "内容为空";
            }
        }

        //更改“删除节点”选项卡“需删除节点的位置”标签的状态
        private void ChangeStateOfLabelDeleteAble(Int32 state)
        {
            if (state == 1)
            {
                labelDeleteAble.ForeColor = Color.Green;
                labelDeleteAble.Text = "位置有效";
            }
            else
            {
                labelDeleteAble.ForeColor = Color.Red;
                labelDeleteAble.Text = "位置无效";
            }
        }

        //更改“搜索节点”选项卡“搜索结果”标签的状态
        private void ChangeStateOfLabelSearchResult(Int32 state)
        {
            if (state == 1)
            {
                labelSearchResult.ForeColor = Color.Green;
                labelSearchResult.Text = "该节点在链表中，位置如图";
            }
            else
            {
                labelSearchResult.ForeColor = Color.Red;
                labelSearchResult.Text = "该节点不在链表中";
            }
        }

        //更改“链表长度”标签的状态
        private void ChangeStateOfLabelLenth()
        {
            Int32 temp;
            if (_demo == null)
            {
                labelLenth.ForeColor = Color.Red;
                labelLenth.Text = "链表不存在，不能进行操作！";
            }
            else
            {
                temp = _demo.GetLenth();
                if (temp == 0)
                {
                    labelLenth.ForeColor = Color.Blue;
                    labelLenth.Text = "链表当前长度：0，不能进行删除操作！";
                }
                else if (temp == 8)
                {
                    labelLenth.ForeColor = Color.Blue;
                    labelLenth.Text = "链表当前长度：8，不能进行插入操作！";
                }
                else
                {
                    labelLenth.ForeColor = Color.Green;
                    labelLenth.Text = "链表当前长度：" + temp;
                };
            }
        }

        //取消程序对键盘上一些按键的响应
        protected override bool ProcessDialogKey(Keys keyData)
        {
            switch (keyData)
            {
                case Keys.Up:
                case Keys.Left:
                case Keys.Down:
                case Keys.Right:
                case Keys.Tab:
                case Keys.Control:
                case Keys.Alt:
                case Keys.Escape:
                    return true;
                default:
                    return base.ProcessDialogKey(keyData);
            }
        }

        //禁用窗体的关闭按钮
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams myCp = base.CreateParams;
                myCp.ClassStyle = myCp.ClassStyle | 0x200;
                return myCp;
            }
        }

        /*      对象：构造方法和事件      */

        public FromMain()
        {
            InitializeComponent();
            //初始化自定义对象
            _twoWay = _circle = false;
            _location = 0;
            _value = null;
            //对象数组初始化
            {
                labelOutput[0] = labelOutputHead;
                labelOutput[1] = labelOutput1;
                labelOutput[2] = labelOutput2;
                labelOutput[3] = labelOutput3;
                labelOutput[4] = labelOutput4;
                labelOutput[5] = labelOutput5;
                labelOutput[6] = labelOutput6;
                labelOutput[7] = labelOutput7;
                labelOutput[8] = labelOutput8;
            }
            {
                pictureBoxNext[0] = null;
                pictureBoxNext[1] = pictureBoxNextH1;
                pictureBoxNext[2] = pictureBoxNext12;
                pictureBoxNext[3] = pictureBoxNext23;
                pictureBoxNext[4] = pictureBoxNext34;
                pictureBoxNext[5] = pictureBoxNext45;
                pictureBoxNext[6] = pictureBoxNext56;
                pictureBoxNext[7] = pictureBoxNext67;
                pictureBoxNext[8] = pictureBoxNext78;
            }
            {
                pictureBoxLast[0] = null;
                pictureBoxLast[1] = pictureBoxLast1H;
                pictureBoxLast[2] = pictureBoxLast21;
                pictureBoxLast[3] = pictureBoxLast32;
                pictureBoxLast[4] = pictureBoxLast43;
                pictureBoxLast[5] = pictureBoxLast54;
                pictureBoxLast[6] = pictureBoxLast65;
                pictureBoxLast[7] = pictureBoxLast76;
                pictureBoxLast[8] = pictureBoxLast87;
            }
            {
                pictureBoxInsect[0] = null;
                pictureBoxInsect[1] = pictureBoxInsect1;
                pictureBoxInsect[2] = pictureBoxInsect2;
                pictureBoxInsect[3] = pictureBoxInsect3;
                pictureBoxInsect[4] = pictureBoxInsect4;
                pictureBoxInsect[5] = pictureBoxInsect5;
                pictureBoxInsect[6] = pictureBoxInsect6;
                pictureBoxInsect[7] = pictureBoxInsect7;
                pictureBoxInsect[8] = pictureBoxInsect8;
            }
            {
                pictureBoxDelete[0] = null;
                pictureBoxDelete[1] = pictureBoxDelete1;
                pictureBoxDelete[2] = pictureBoxDelete2;
                pictureBoxDelete[3] = pictureBoxDelete3;
                pictureBoxDelete[4] = pictureBoxDelete4;
                pictureBoxDelete[5] = pictureBoxDelete5;
                pictureBoxDelete[6] = pictureBoxDelete6;
                pictureBoxDelete[7] = pictureBoxDelete7;
                pictureBoxDelete[8] = pictureBoxDelete8;
            }
            {
                pictureBoxSearch[0] = null;
                pictureBoxSearch[1] = pictureBoxSearch1;
                pictureBoxSearch[2] = pictureBoxSearch2;
                pictureBoxSearch[3] = pictureBoxSearch3;
                pictureBoxSearch[4] = pictureBoxSearch4;
                pictureBoxSearch[5] = pictureBoxSearch5;
                pictureBoxSearch[6] = pictureBoxSearch6;
                pictureBoxSearch[7] = pictureBoxSearch7;
                pictureBoxSearch[8] = pictureBoxSearch8;
            }
            {
                pictureBoxLastCircle[0] = null;
                pictureBoxLastCircle[1] = pictureBoxLastCircle1;
                pictureBoxLastCircle[2] = pictureBoxLastCircle2;
                pictureBoxLastCircle[3] = pictureBoxLastCircle3;
                pictureBoxLastCircle[4] = pictureBoxLastCircle4;
                pictureBoxLastCircle[5] = pictureBoxLastCircle5;
                pictureBoxLastCircle[6] = pictureBoxLastCircle6;
                pictureBoxLastCircle[7] = pictureBoxLastCircle7;
                pictureBoxLastCircle[8] = pictureBoxLastCircle8;
            }
            //初始化用于绘图相关对象
            _graph = panelDraw.CreateGraphics();
            _blackPen = new Pen(Color.Black, 4);
            _grayPen = new Pen(Color.FromArgb(160, 160, 160), 4);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ResetAll();
        }

        private void buttonQuit_Click(object sender, EventArgs e)
        {
            _demo = null;
            Application.Exit();
        }

        private void buttonResetAll_Click(object sender, EventArgs e)
        {
            ResetAll();
        }

        private void buttonSet_Click(object sender, EventArgs e)
        {
            try
            {
                _demo = new LinkList<String>(_twoWay, _circle);
            }
            catch (OutOfMemoryException)
            {
                MessageBox.Show
                    (
                        "无法获取链表所需的内存空间！",
                        "错误",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    );
                Application.Exit();
            }
            //绘图
            Draw();
            //“链表属性”不可用
            gropeBoxAttribute.Enabled = false;
            //“链表操作”可用
            tabControlOperate.Enabled = true;
            //“全部重置”按钮可用
            ButtonResetAll.Enabled = true;
            //所有的文本框内容清空
            textBoxInsectLocation.Clear();
            textBoxInsectValue.Clear();
            textBoxDeleteLocation.Clear();
            textBoxSearchValue.Clear();
            //更改“链表长度”标签
            ChangeStateOfLabelLenth();
            //“全部重置”按钮获得焦点
            ButtonResetAll.Focus();
        }

        private void radioButtonT_CheckedChanged(object sender, EventArgs e)
        {
            _twoWay = radioButtonT.Checked;
        }

        private void radioButtonC_CheckedChanged(object sender, EventArgs e)
        {
            _circle = radioButtonC.Checked;
        }

        private void tabControlOperate_Selecting(object sender, TabControlCancelEventArgs e)
        {
            SetStateOfTabInsectDelete();
        }

        private void textBoxInsectLocation_TextChanged(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                //读入位置值
                try
                {
                    _location = Int32.Parse(textBoxInsectLocation.Text);
                }
                catch (Exception)
                {
                    _location = -1;
                }
                //将输入有效性判定结果设置到标签，同时尝试更改按钮状态，显示插入位置
                if (_location >= 1 && _location <= _demo.GetLenth() + 1 && _location <= 8)   //插入位置合理
                {
                    //标签设置
                    ChangeStateOfLabelInsectLocationAble(1);
                    //尝试更改按钮状态
                    _insectEnableLocation = true;
                    if (_insectEnableValue)
                    {
                        ButtonInsect.Enabled = true;
                    }
                    //更新显示插入位置的小箭头
                    EraseTag();
                    pictureBoxInsect[_location].Visible = true;
                }
                else   //插入位置不合理
                {
                    //标签设置
                    ChangeStateOfLabelInsectLocationAble(0);
                    //尝试更改按钮状态
                    _insectEnableLocation = false;
                    ButtonInsect.Enabled = false;
                    //清除显示插入位置的小箭头
                    EraseTag();
                }
                //该文本框内容全选
                textBoxInsectLocation.SelectAll();
            }
            else
            {
                ResetAll();
            }
        }

        private void textBoxInsectValue_TextChanged(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                Int32 temp_i1 = 0;
                //读入内容
                _value = textBoxInsectValue.Text;
                //将输入有效性判定结果设置到标签，同时尝试更改按钮状态
                if (_value != "" && _value != null)   //文本框内容不为空
                {
                    //搜索
                    _demo.SearchNode(ref temp_i1, _value);
                    if (temp_i1 == 0)   //文本框不与链表中已有内容重复
                    {
                        //标签设置
                        ChangeStateOfLabelInsectValueAble(1);
                        //尝试更改按钮状态
                        _insectEnableValue = true;
                        if (_insectEnableLocation)
                        {
                            ButtonInsect.Enabled = true;
                        }
                    }
                    else  //文本框与链表中已有内容重复
                    {

                        ChangeStateOfLabelInsectValueAble(0);
                        //尝试更改按钮状态
                        _insectEnableValue = false;
                        ButtonInsect.Enabled = false;
                    }
                }
                else    //文本框内容为空为空
                {
                    //标签设置
                    ChangeStateOfLabelInsectValueAble(-1);
                    //尝试更改按钮状态
                    _insectEnableValue = false;
                    ButtonInsect.Enabled = false;
                }
            }
            else
            {
                ResetAll();
            }

        }

        private void buttonInsect_Click(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                if (_demo.InsectNode(_location, _value) == -1)
                {
                    MessageBox.Show
                    (
                        "无法获取节点所需的内存空间！",
                        "错误",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    );
                    Application.Exit();
                }
                //重新绘图
                Erase();
                Draw();
                //更改两个按钮的状态
                SetStateOfTabInsectDelete();
                //更改“链表长度”标签
                ChangeStateOfLabelLenth();
                //“新节点位置”文本框获得焦点
                textBoxInsectLocation.Focus();
            }
            else
            {
                ResetAll();
            }
        }

        private void textBoxDeleteLocation_TextChanged(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                //读入位置值
                try
                {
                    _location = Int32.Parse(textBoxDeleteLocation.Text);
                }
                catch (Exception)
                {
                    _location = -1;
                }
                //将输入有效性判定结果设置到标签，同时尝试更改按钮状态，显示删除位置
                if (_location >= 1 && _location <= _demo.GetLenth() && _location <= 8)   //删除位置合理
                {
                    //标签设置
                    ChangeStateOfLabelDeleteAble(1);
                    //更改按钮状态
                    ButtonDelete.Enabled = true;
                    //更新显示删除位置的小箭头
                    EraseTag();
                    pictureBoxDelete[_location].Visible = true;
                }
                else   //插入位置不合理
                {
                    //标签设置
                    ChangeStateOfLabelDeleteAble(0);
                    //更改按钮状态
                    ButtonDelete.Enabled = false;
                    //清除显示删除位置的小箭头
                    EraseTag();
                }
                //该文本框内容全选
                textBoxDeleteLocation.SelectAll();
            }
            else
            {
                ResetAll();
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                _demo.DeleteNode(_location);
                //重新绘图
                Erase();
                Draw();
                //更改两个按钮的状态
                SetStateOfTabInsectDelete();
                //更改“链表长度”标签
                ChangeStateOfLabelLenth();
                //“需删除节点位置”文本框获得焦点
                textBoxDeleteLocation.Focus();
            }
            else
            {
                ResetAll();
            }
        }

        private void textBoxSearchValue_TextChanged(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                Int32 temp = 0;
                //搜索
                _demo.SearchNode(ref temp, textBoxSearchValue.Text);
                //将搜索结果设置到标签并尝试显示
                if (temp != 0)   //找到
                {
                    //标签设置
                    ChangeStateOfLabelSearchResult(1);
                    //更新显示删除位置的小箭头
                    EraseTag();
                    pictureBoxSearch[temp].Visible = true;
                }
                else   //找不到
                {
                    //标签设置
                    ChangeStateOfLabelSearchResult(0);
                    //清除显示删除位置的小箭头
                    EraseTag();
                }
            }
            else
            {
                ResetAll();
            }
        }

        private void buttonRadomBuild_Click(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                Int32 temp;
                Random r = new Random();
                _demo.ClearAll();
                for (temp = 1; temp <= 8; temp++)
                {
                    if (_demo.InsectNode(1, r.Next(0, 99999).ToString()) == -1)
                    {
                        MessageBox.Show
                            (
                               "无法获取节点所需的内存空间！",
                               "错误",
                               MessageBoxButtons.OK,
                               MessageBoxIcon.Error
                            );
                        Application.Exit();
                    }
                }
                //重新绘图
                Erase();
                Draw();
                //更改“链表长度”标签
                ChangeStateOfLabelLenth();
            }
            else
            {
                ResetAll();
            }
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            if (_demo != null)
            {
                _demo.ClearAll();
                //擦除
                Erase();
                //更改“链表长度”标签
                ChangeStateOfLabelLenth();
            }
            else
            {
                ResetAll();
            }
        }
    }
}
