#include <iostream>
#include <malloc.h>
#include <stdio.h>
using namespace std;
#define MaxSize 100
#define M 4
#define N 4

#define MaxSize 100
typedef struct {
    int i;  //方块行
    int j;  //方块列
    int di; //方块位号
} Box;
typedef struct {
    Box path[MaxSize]; //该条路径
    int steps;         //每条路径的步数
} Solution;

typedef struct {
    Box data[MaxSize];
    int top;
} StType;

void InitStack(StType*& s) //初始化栈
{
    s = (StType*)malloc(sizeof(StType));
    s->top = -1;
}
void DestroyStack(StType*& s) //销毁栈
{
    free(s);
}
bool StackEmpty(StType* s) //判断栈是否为空
{
    return (s->top == -1);
}
bool Push(StType*& s, Box e) //进栈元素e
{
    if (s->top == MaxSize - 1)
        return false;
    s->top++;
    s->data[s->top] = e;
    return true;
}
bool Pop(StType*& s, Box& e) //出栈元素e
{
    if (s->top == -1)
        return false;
    e = s->data[s->top];
    s->top--;
    return true;
}
bool GetTop(StType* s, Box& e) //取栈顶元素e
{
    if (s->top == -1)
        return false;
    e = s->data[s->top];
    return true;
}

//迷宫问题
int mg[6][6] = {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 1, 1}, {1, 0, 1, 0, 0, 1},
                {1, 0, 0, 0, 1, 1}, {1, 1, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}};
bool mgpath_pro(int xi, int yi, int xe, int ye) {
    Box path[xe * ye], e; //定义路径数组存储走过的方格，e为临时方格
    Solution solution[MaxSize]; //定义解决方案数组
    int i, j, di, i1, j1, k, steps,
        n = -1; // i，j，di，为前一步的坐标与方向矢量，i1，j1为下一步的方向矢量，k表示路径中的方块数
    bool find;  //判断路是否可走
    StType* st; //创建栈存放路径
    InitStack(st);
    e.i = xi;
    e.j = yi;
    e.di = -1;                //设置e为入口
    Push(st, e);              //入口进栈
    mg[xi][yi] = -1;          //入口值设为-1，防止重复
    while (!StackEmpty(st)) { //循环开始，寻找路径
        GetTop(st, e);        //获取最后一步
        i = e.i;
        j = e.j;
        di = e.di;                //记录最后一步的坐标与矢量
        if (i == xe && j == ye) { //找到出口开始输出
            n++;                  //路径条数加一
            k = 0;
            while (!StackEmpty(st)) {
                Pop(st, e);
                solution[n].path[k++] = e; //将路径存入path中
                steps = k;                 // l存储每条路径的步数
            }
            solution[n].steps = steps;
            while (k > 0) {
                Push(st, solution[n].path[k - 1]);
                k--;
            }
            Pop(st, e);       //弹出最后一步
            mg[e.i][e.j] = 0; //恢复最后一步为空位
        }
        find = false; //初始化路径为无
        while (di < 4 && !find) {
            di++;
            switch (di) {
            case 0:
                i1 = i - 1;
                j1 = j;
                break;
            case 1:
                i1 = i;
                j1 = j + 1;
                break;
            case 2:
                i1 = i + 1;
                j1 = j;
                break;
            case 3:
                i1 = i;
                j1 = j - 1;
                break;
            }
            if (mg[i1][j1] == 0)
                find = true; //方块为0，即存在路径
        }
        if (find) {                    //找到了可走方块
            st->data[st->top].di = di; //修改最后一步方向向量
            e.i = i1;
            e.j = j1;
            e.di = -1;       //记录可走方块
            Push(st, e);     //可走方块进栈
            mg[i1][j1] = -1; //避免重复
        } else {
            Pop(st, e);       //弹出最后一步
            mg[e.i][e.j] = 0; //恢复最后一步为空位
        }
    }
    DestroyStack(st);
    cout << "共有" << n + 1 << "种路径" << endl;
    int best[2]; //创建最佳路径数组，best[0]存放路径编号，best[1]存放路径数
    best[0] = 0;
    best[1] = solution[0].steps;
    for (int i = 0; i <= n; i++) {
        cout << "路径" << i + 1 << "如下" << endl;
        if (solution[i].steps < best[1]) {
            best[1] = solution[i + 1].steps;
        }
        for (int k = solution[i].steps; k > 0; k--) {
            cout << '(' << solution[i].path[k - 1].i
                 << solution[i].path[k - 1].j << ')'; //逆向输出路径
        }
        cout << endl;
    }
    cout << "最佳路径为路径" << best[0] + 1 << endl
         << "其长度为" << best[1] << endl;
    return false;
}

int main() {
    mgpath_pro(1, 1, 4, 4);
    return 0;
}