#include <iostream.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
struct snake_head//������ͷ�ṹ�壬Ĭ��Ϊ����Ԫ�ع��з���
{

	int x;//������ͷ��ǰ��xֵ
	int y;//������ͷ��ǰ��yֵ
	int dir;//��ͷ���ƶ�����1,2,3,4�ֱ�Ϊ��������
	int speed;//��ͷ���ƶ��ٶ�
};
class food
{
private:
	friend class snake;//����Ϊsnake�����Ԫ��
protected:
	int x,y;//ʳ�����ϽǵĶ�������

public:
	food();//���캯����Ĭ��ʳ������СΪ2���س���
	~food();//����������������������ʧ
	void draw();//��ʳ��
	void hide();//����ʳ��
	int getx();//��ȡx
	int gety();//��ȡy
	void set(int,int);//����ʳ����ֵ�����
 	bool flag;//�ж��Ƿ�ǰ��Ҫ����ʳ��
};
void food::set(int xx,int yy)
{
	this->x=xx;
	this->y=yy;
}

food::food()//�ڹ���ʳ��ʱ����Ҫ�ж��Ƿ��������ϣ��Ժ�����
{
 cout<<"food���캯������"<<endl;
  flag=false;
 //srand((unsigned)time(NULL));
 //x=rand()%1024;//��������x
 //y=rand()%480;//��������y
 //x=500;
 //y=200;
}
food::~food()
{
	cout<<"food������������"<<endl;
	hide();

}
void food::draw()
{
	solidrectangle(x,y,x+10,y+10);
}
void food::hide()
{
	clearrectangle(x,y,x+10,y+10);
}
int food::getx()
{
	return x;
}
int food::gety()
{
	return y;
}
class snake
{
private:
	friend class food;
protected:	
	snake_head head;
	int length;//�ߵĳ���
	vector <snake_head> body;
	
public:
    snake();//�ߵĹ��캯��������Ϸ��ʼʱ���е���ok
	~snake();//�ߵ���������������Ϸ����ʱ���е���ok
	void move(int);//���ݵ�ǰ�������������ƶ�ok
	int iscollision();//�ж���ͷ�Ƿ�������ײ�¼�,�ֱ�Ϊײǽʱ����0��ײʳ���Ƿ���1��ײ�Լ�����2��û����ײ����3
    bool iseat(int,int);//�ж��Ƿ��߳Ե���ʳ��
    void draw_snake();//����ok
	void hide_snake();//�ߵ�����ok
	void add_body();//�����ߵ����峤��	ok
	bool live;//�ж��Ƿ����,��ʼʱ����Ϊ����
};
snake::snake()
{
	cout<<"snake���캯������"<<endl;
	live=true;
	length=0;
	head.x=500;
	head.y=300;
	head.dir=3;
	head.speed=10;
	body.push_back(head);//body[0]����������ͷ����Ϣ
	
}
snake::~snake()
{
	cout<<"snake������"<<endl;
}
void snake::move(int d)//�߽����ƶ���ʵ�ֺ���
{
	body[0].dir=d;
	for(int i=length;i>=1;i--)//�߽����ƶ��Ĺؼ�,���ߵ�ÿһ���ڵ������ֵ����ǰһ���ڵ��ֵ
	 {
      body[i].x=body[i-1].x;
	  body[i].y=body[i-1].y;
	  body[i].dir=body[i-1].dir;
	 
	 }
	switch (d)
	{
	case 1:  //��
		{
			head.y-=head.speed;
			body[0].y-=head.speed;
		}break;
	case 2:  //��
		{
            head.y+=head.speed;
			body[0].y+=head.speed;
		}break;
	case 3: //��
		{
			head.x-=head.speed;
			body[0].x-=head.speed;
		}break;
	case 4:  //��
		{
			head.x+=head.speed;
			body[0].x+=head.speed;
		}break;

	}
}
void snake::draw_snake()//���߲���
{
 int top,left;
 for(int i=0;i<=length;i++)
 {
	 left=body[i].x;
	 top=body[i].y;
	 solidrectangle(left,top,left+10,top+10);
 }
 
}
void snake::hide_snake()//�����ߵ�����
{
int top,left;
 for(int i=0;i<=length;i++)
 {
	 left=body[i].x;
	 top=body[i].y;
	 clearrectangle(left,top,left+10,top+10);
 }
}
void snake::add_body()//���������ȵ�����
{
	snake_head h;
	int dir=body[length].dir;
	switch(dir)
	{
	case 1:
		{
		h.x=body[length].x;
		h.y=body[length].y+10;
		h.dir=dir;
		body.push_back(h);//�������ӵĽڵ���������
		length++;//���ȼ�1
		
		
		}break;
	case 2:
		{
			h.x=body[length].x;
			h.y=body[length].y-10;
			body.push_back(h);
			length++;
		}break;
	case 3:
		{
			h.x=body[length].x+10;
			h.y=body[length].y;
			body.push_back(h);
			length++;
		}break;
	case 4:
		{
			h.x=body[length].x-10;
			h.y=body[length].y;
			body.push_back(h);
            length++;
		}break;

	}
	int len=length-1;
	 body[length].dir=body[len].dir; 
	 cout<<length<<endl;
	
}
int snake::iscollision()
{
	//�ж��Ƿ����������ײ
	if(body[length].x+2==body[0].x){live=false;return 2;}//������׷β�¼�������������������ײ
	for (int i=1;i<=length;i++)
	{
		if((body[0].y+2==body[i].y)||(body[0].y==body[i].y+2)){live=false;return 2;}
	}
	if(body[0].x-10<=0||body[0].x+10>=1014||body[0].y-10<=0||body[0].y+10>=470){live=false;return 0;}
	
	return 3;
}
bool snake::iseat(int fx,int fy)
{
	if(body[0].x==fx&&body[0].y==fy){cout<<"eat"<<endl;return true;}
 else return false;
}
void draw_wall()
{
	rectangle(10,10,1014,470);
}

char game_over()
{
	cout<<"\t--------------------------------------------------------------------"<<endl;
	cout<<"\t-------------------------game over----------------------------------"<<endl;
	cout<<"\t-------------------------will you continue?(y/n)-------------------------"<<endl;
	char a=getchar();
	return a;
}
int game_screen()
{
	cout<<"\t--------------------------------------------------------------------"<<endl;
	cout<<"\t------------------------1.game start--------------------------------"<<endl;
	cout<<"\t------------------------2.help--------------------------------------"<<endl;
	cout<<"\t------------------------3.record------------------------------------"<<endl;
	cout<<"\t------------------------4.quit--------------------------------------"<<endl;
	cout<<"\t------------------------your choice---------------------------------"<<endl;
	int choice;
	cin>>choice;
	return choice;
}
void help_screen()
{
	cout<<"\t----------------------------------------------------------------------"<<endl;
	cout<<"\tpress 'w': up,press 's':down,press 'a':left,press 'd':right,press 'e' to exit"<<endl;
	cout<<"\t----------------------------------------------------------------------"<<endl;
}
void game_init()
{
initgraph(1024,480);//��ʼ����
	draw_wall();//��ǽ
}
void give_food(int&x1,int&y1)
{
	int x,y;
srand((unsigned)time(NULL));
do
{
  x=rand()%1004;//��������x
  y=rand()%460;//��������y
}while((x%10!=0)||(y%10!=0));
x1=x;y1=y;
}
void game_loop(int dir,snake&s)
{
	
	do
	{
     s.draw_snake();
    Sleep(200);
	s.hide_snake();
	s.move(dir);


	}while(!kbhit());
    char a=getch();
	switch(a)
	{
	case 'w':
		{
			dir=1;
		}break;
	case 's':
		{
			dir=2;
		}break;
	case 'a':
		{
			dir=3;
		}break;
	case 'd':
		{
			dir=4;
		}break;
	}

}

void play()
{
	snake s;
	food f;
	game_init();
	int x,y,sign=1,dir=1;
while(sign==1)
{
	if(f.flag==false)
	{
	 give_food(x,y);
	 f.set(x,y);
	 f.draw();
	 f.flag=true;
	}
	do
	{
     s.draw_snake();
    Sleep(450);
	s.hide_snake();
	s.move(dir);
    if(s.iseat(f.getx(),f.gety())==true){f.flag=false;s.add_body();}
	if(s.iscollision()==0||s.iscollision()==2){sign=-1;break;}

	}while(!kbhit());
    char a=getch();
	switch(a)
	{
	case 'w':
		{
			dir=1;
		}break;
	case 's':
		{
			dir=2;
		}break;
	case 'a':
		{
			dir=3;
		}break;
	case 'd':
		{
			dir=4;
		}break;
	case 'e':
		{
			sign=-1;
		}break;
	}
	
	
}
 closegraph();	

}