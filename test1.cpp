#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#define N  60  //抽点人数 
#define M  30//第三次点名及以后每次要抽的人 
using namespace std;
//public static int Parse(string s,NumberStyles style);
 // public static bool TryParse(string s, out int result);
vector<vector<string> > biao; //声明一个字符串向量数组的向量
class Student{
    public:
    double grade;//绩点
    string name;
    int id;
     
};

class Course{
	public:
	Course(){
		sum=0;
		
		len=0;
		
	}
    
// Arr[0][0]为第零次课第0名学生是否签到，值为1代表已签到
//0为未签到
	int sum;//点名总次数 
    int Arr[20][90];
    int absent[90];  
 //该数组记录没来的学生id
    int len;
//len记录失信的人数 
    Student s[90];
    //该门课程的90名学生
    
    
};

// input: int max 期待随机数的最大值，int min,期待随机数的最小值，int num 需要的随机数的个数
// output: vector<int> 装载产生的随机数（随机数都是不同的） 
//该函数将在[min,max]间随机产生不同的N个数 
std::vector<int> CreateRandomNums(int min,int max, int num)
{
	std::vector<int> res;
	res.clear();
	if (max - min + 1 < num)
	{
		return res;
	}
	srand(time(0));
	for (int i=0; i < num; i++)
	{
		while (true)
		{
			int temp= rand() % (max + 1 - min) + min ;
			vector<int>::iterator iter= find(res.begin(),res.end(),temp) ;
			if (res.end() == iter)
			{
				res.push_back(temp);
				break;
			}		
		}
	}
	return res;
}

//该函数为前三次点名时抽取绩点较低的人 
int Roll1 (Course* m,int i,int q){
    int j,t;
    int fz1=0,flag=0;//有效点名次数，即要返回的值
     
    for(j=0;j<q;j++){//j代表第j位同学
        if(m->Arr[i][m->s[j].id]==0) {
		fz1++; 
		if(m->len==0) {
		m->absent[m->len]=m->s[j].id  ; (m->len)++;
			}
		else
		{
			for(t=0;t<m->len;t++)
		{
			if(m->s[j].id  ==m->absent[t])
			{
				flag=1;
				break;
			}

		}
		if(flag==0)//没重复
		{
			m->absent[m->len]=m->s[j].id  ; (m->len)++;
		} 
		else
		{
			flag=1;
		}
		
		}
		
		
		
		
		}//该同学没到，则有效点名次数+1，且将该人列入失信名单 
    }
    
    m->sum+=q;//点名次数增加  
    
//    //再随机抽取,试图找到0~3人逃课的，生成[q,90)的整数
//    r=(rand()%(90-q))+q;
//    if(m->Arr[i][r]==0) {fz1++; m->absent[m->len]=r; m->len++;}
//    m->sum++;

   return fz1;
   

}

//该函数为后17次点名，
int Roll2(Course* m,int i,int q){
    int j,fz2=0,k,r;
   
	for(j=0;j<m->len;j++){
		
		k=m->absent[j];
		if(m->Arr[i][k]==0){
			fz2++;
			
		}	
	} 
	m->sum = m->sum +m->len ;
//再随机抽取,试图找到0~3人逃课的，生成[q,90)的整数

//	 r=(rand()%(90-q))+q;
//    if(m->Arr[i][m->s[r].id]==0) {
//		fz2++; m->absent[m->len]=m->s[r].id; m->len++;}
//	m->sum++;
	
    return fz2;

}

string Trim(string& str)
    {
    //str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
    }
    
void Dataimport(Course* a,Course* b,Course* c,Course* d,Course* e ){ //对csv数据集进行处理 
	ifstream fin("sample.csv"); //打开文件流操作
    string line;
    int t=0,j,i;
    while (t<=112)   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
    	t++;
    	getline(fin, line);
        if(t>0)
        {
	        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
	        vector<string> fields; //声明一个字符串向量
	        string field;
	        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
	        {
	            fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
	        }
	        
	        biao.push_back(fields);  //将字符串数组添加到表数组中，变成二维数组
		}
    } 
        	for(j=0;j<90;j++)
        	{
        		double ff=0.1;
        		for(i=0;i<5;i++)
        		{
        			if(biao[21][j+1][i]<='9'&&biao[21][j+1][i]>='0')
        			{
        				if(i==0)
						{
							a->s[j].grade=biao[21][j+1][i]-'0';
						}
        				else if(i==2||i==3||i==4)
        				{
        					a->s[j].grade=a->s[j].grade+(biao[21][j+1][i]-'0')*ff;
        				
        					ff=ff*0.1;
						}
					}
				}
			}
	        	for(j=0;j<90;j++)
        	{
        		double ff=0.1;
        		for(i=0;i<5;i++)
        		{
        			if(biao[43][j+1][i]<='9'&&biao[43][j+1][i]>='0')
        			{
        				if(i==0)
						{
							b->s[j].grade=biao[43][j+1][i]-'0';
						}
        				else if(i==2||i==3||i==4)
        				{
        					b->s[j].grade=b->s[j].grade+(biao[43][j+1][i]-'0')*ff;
        					ff=ff*0.1;
						}
					}
				}
            }
				for(j=0;j<90;j++)
        	{
        			double ff=0.1;
        		for(i=0;i<5;i++)
        		{
        			if(biao[65][j+1][i]<='9'&&biao[65][j+1][i]>='0')
        			{
        				if(i==0)
						{
							c->s[j].grade=biao[65][j+1][i]-'0';
						}
        				else if(i==2||i==3||i==4)
        				{
        					c->s[j].grade=c->s[j].grade+(biao[65][j+1][i]-'0')*ff;
        					ff=ff*0.1;
						}
					}
				}
            }
				for(j=0;j<90;j++)
        	{
        			double ff=0.1;
        		for(i=0;i<5;i++)
        		{
        			if(biao[87][j+1][i]<='9'&&biao[87][j+1][i]>='0')
        			{
        				if(i==0)
						{
							d->s[j].grade=biao[87][j+1][i]-'0';
						}
        				else if(i==2||i==3||i==4)
        				{
        					d->s[j].grade=d->s[j].grade+(biao[87][j+1][i]-'0')*ff;
        					ff=ff*0.1;
						}
					}
				}
            }
				for(j=0;j<90;j++)
        	{
        		double ff=0.1;
        		for(i=0;i<5;i++)
        		{
        			if(biao[109][j+1][i]<='9'&&biao[109][j+1][i]>='0')
        			{
        				if(i==0)
						{
							e->s[j].grade=biao[109][j+1][i]-'0';
						}
        				else if(i==2||i==3||i==4)
        				{
        					e->s[j].grade=e->s[j].grade+(biao[109][j+1][i]-'0')*ff;
        					ff=ff*0.1;
						}
					}
				}
           }
        	for(i=0;i<20;i++)
	        {
	                for(j=0;j<90;j++)
	                {
	                    a->Arr[i][j]=(int)(biao[i+1][j+1][0])-'0';
	                    //cout<<a->Arr[i][j]<<" ";
	                } 
	                //cout<<endl;
	        }
	        for(i=22;i<42;i++)
	        {
	                for(j=0;j<90;j++)
	                {
	                    b->Arr[i-22][j]=(int)(biao[i+1][j+1][0])-'0';
	                } 
	        }	
	           for(i=44;i<64;i++)
	        {
	                for(j=0;j<90;j++)
	                {
	                    c->Arr[i-44][j]=(int)(biao[i+1][j+1][0])-'0';
	                }
	        }
	           for(i=66;i<86;i++)
	        {
	                for(j=0;j<90;j++)
	                {
	                    d->Arr[i-66][j]=(int)(biao[i+1][j+1][0])-'0';
	                }

	        }
	           for(i=88;i<108;i++)
	        {
	                for(j=0;j<90;j++)
	                {
	                    e->Arr[i-88][j]=(int)(biao[i+1][j+1][0])-'0';
	                }
	             
	        }
	        //对类数据处理
			for(i=0;i<90;i++)
			{
				a->s[i].id=i;
				b->s[i].id=i;
				c->s[i].id=i;
				d->s[i].id=i;
				e->s[i].id=i;
				 
			} 
}
bool cmp(Student m,Student n){
    return m.grade<n.grade;
}

int main(){
    double eva;
    Course a,b,c,d,e;//此为五门课程
    int i,j;
    int fz=0,fm=0;//即eva的分子，有效点名的次数
    string arr;
    //a课程的点名
    Dataimport(&a,&b,&c,&d,&e);//对数据集进行处理 

        int q;//q之前为绩点较低的人，点名着重注意他们
    //a
	    sort(a.s,a.s+90,cmp);

        for(i=0;i<90;i++){
            if(a.s[i].grade>3.2){
                q=i;
               //cout<<"fz1  "<<q<<endl;
                break;
            }
        }
	    for(i=0;i<20;i++)
	    {
	    	if(i<3){
                fz=fz+Roll1(&a,i,q);//将a课程送入函数,
                //cout<<"fz1  "<<fz<<endl;
	        }
	        else {
	            fz=fz+Roll2(&a,i,q);
	            //cout<<"fz2  "<<fz<<endl;
	        }   
	       
		}
		fm+=a.sum;//分母加上a课程的点名总次数 
	
      //b
      	    sort(b.s,b.s+90,cmp);
        for(i=0;i<90;i++){
            if(b.s[i].grade>3.2){
                q=i;
                
                break;
            }
        }
	    for(i=0;i<20;i++)
	    {
	    	if(i<3){
                fz=fz+Roll1(&b,i,q);
	        }
	        else {
	            fz=fz+Roll2(&b,i,q);
	        }   
	       
		}
		fm+=b.sum;  
//c
	    sort(c.s,c.s+90,cmp);
        for(i=0;i<90;i++){
            if(c.s[i].grade>3.2){
                q=i;
                
                break;
            }
        }
	    for(i=0;i<20;i++)
	    {
	    	if(i<3){
                fz=fz+Roll1(&c,i,q);
	        }
	        else {
	            fz=fz+Roll2(&c,i,q);
	        }   
		}
		fm+=c.sum;
    //d
	    sort(d.s,d.s+90,cmp);
        for(i=0;i<90;i++){
            if(d.s[i].grade>3.2){
                q=i;
               
                break;
            }
        }
	    for(i=0;i<20;i++)
	    {
	    	if(i<3){
                fz=fz+Roll1(&d,i,q);
	        }
	        else {
	            fz=fz+Roll2(&d,i,q);
	        }   
	       
		}
		fm+=d.sum;
        //e
        sort(e.s,e.s+90,cmp);
        for(i=0;i<90;i++){
            if(e.s[i].grade>3.2){
                q=i;
        
                break;
            }
        }
	    for(i=0;i<20;i++)
	    {
	    	if(i<3){
                fz=fz+Roll1(&e,i,q);
	        }
	        else {
	            fz=fz+Roll2(&e,i,q);
	        }   	       
		}
		fm+=e.sum;
		//cout<<fz<<" "<<fm<<endl;
        eva=1.0*fz/fm;      
        cout<<eva;
}
