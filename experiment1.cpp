#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
int f[250001],a[250001],d[501][501];//可以开一维数组表示地图,大小为n*m即250000
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};//表示四个方向(上下左右),在bfs里使用
int n,m,maxn,cnt,l,r;
int find(int x)//并查集--查找
{
    if(f[x]==x)//等于就返回x
    {
        return x;
    }
     f[x]=find(f[x]);//不等于就继续递归
     return f[x];
     //也就是return f[x]=find(f[x]);
}
void merge(int x,int y)//判断,连通块
{
    int fx=find(x),fy=find(y);
    if(fx!=fy)//不同就更新f[fx]=fy
    {
        f[fx]=fy;
  } 
}
bool bfs(int x)//bfs搜索
{
    for(int i=1;i<=n*m;i++)//对于一维数组初始化
    {
        f[i]=i;//初始化每个值都等于它的下标
    }
    for(int i=1;i<=n;i++)//两层循环，bfs
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=0;k<4;k++)//前面定义好了四个方向,这个循环是来搜索4个方向的
            {
                int xx=i+dx[k],yy=j+dy[k];//两个新坐标
                if(xx<1||xx>n||yy<1||yy>m)//如果出边界
                {
                    continue;//尝试下一个方向
                }
                if(abs(d[i][j]-d[xx][yy])>x)//路程太远（超过x）
                {
                    continue;//尝试下一个方向
                }
                merge((i-1)*m+j,(xx-1)*m+yy);//连通块(前面提到)
            }
        }
    }
    for(int i=1;i<cnt;i++)//综合前面的并查集连通块，开始判断是否给定点都连通
    {
        if(find(a[i])!=find(a[i+1]))//如果有给定点无法连通
        {
            return false;//直接返回假，提前结束函数
        }
    }
    return true;//到这里表明给定点都能连通,返回真
}
void erfen()//二分
{
    l=-1,r=maxn+1;
    int mid;
    //使用l和r作为边界
    while(l+1<r)//只要l不越界
    {
        mid=(l+r+1)/2;//求出中间值
        if(bfs(mid))//这里的判断函数就是前面提到的bfs
        {
            l=mid;//判断函数返回真,l更新为mid
        }
        else 
        {
            r=mid-1;//判断函数返回假,r更新为mid-1
        }
        //就这样逐渐夹逼,最终得出结果
    }
}
int main()//主函数
{
    scanf("%d%d",&n,&m);//输入数据
    for(int i=1;i<=n;i++)//双层循环输入
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&d[i][j]);//输入海拔
            maxn=max(maxn,d[i][j]);//不断记录最高海拔值
        }
    }
    for(int i=1;i<=n;i++)//双层循环输入
    {
        for(int j=1;j<=m;j++)
        {
            int p;//只能是0或1
            scanf("%d",&p);//读入是否为路标
            if(p==1)//如果是路标
            {
                a[++cnt]=(i-1)*m+j;//更新a数组，记录路标
            }
        }
    }
    erfen();//开始二分
    printf("%d",r);//r即为最后的D值
    system("pause");
    return 0;//结束
}