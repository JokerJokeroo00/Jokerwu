#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
struct sysuser				//定义用户结构体 
{
	char usernum[12];		//用户账号 
	char password[8];		//用户密码 
	struct sysuser *next;	//指向下一节点 
};

struct book
{
	int number;         //编号
    char name[30];      //书名
    char zuozhe[10];	//作者 
    int kucun;			//库存 
    int xiancun;		//现存 
    int year;           //借出时间--年
    int month;          //借出时间--月
    int day;            //借出时间--日
    struct book *next;  //指向下一节点 
};

void print_main_title()			//打印大标题 
{
	time_t time_login;			
	struct tm *p;
    time(&time_login);			//获取当前时间 
    p=gmtime(&time_login);
    printf("欢迎使用图书管理系统\n");
    printf("现在时间：%d年%d月%d日 %d:%d:%d\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);  //为了在借书还书时登记时间，系统需要有时间模块 
}

int check_usernum(struct sysuser *user)    //检查是用户账号否被注册过 
{
	int check=0;						
	char usrno[12];						//用于接收user的内容 
	strcpy(usrno,user->usernum);		//复制字符串 
	char usrno_f[12];					//用于暂存文件内的账号信息 
	FILE *fp;							
	fp=fopen("user.txt","r+");					//读写 
	if (fp==NULL)fopen("user.txt","w");			//若无use.txt文件，创建一个只写的文件 
	while(fscanf(fp,"%s%*s",usrno_f)!=EOF)		//扫描文件内的内容至文件结束 
    {
        if(strcmp(usrno,usrno_f)==0)			//两字符串内容相同 
        {
            check=1;
            break;
        }
    }
    fclose(fp);							//关闭文件 
	return check;                         //被注册过返回1，没被注册过返回0 
} 

int create_user()                          //注册 
{
	struct sysuser su;
	FILE *fp;
	fp=fopen("user.txt","a");				//向文本尾部增添内容 
	if(fp==NULL)fopen("user.txt","w");		//如果没有文件那就创建只写格式的文件 
    loop1:                           //语句标号，后面goto此处 
	system("CLS");					//清屏 
	printf("注册新用户\n");
	printf("输入账号用户名：");
	scanf("%s",su.usernum);			//键盘键入用户名 
	if(check_usernum(&su)==0)		//用户名未被注册过 
	{
		printf("输入密码(长度小于等于8位)：");
		int i=0;
		while(0<i<8&&(su.password[i]=getch())!='\r')			//getch()函数在输入时不会再屏幕上显示内容 
		{
			if(su.password[i]=='\b')    //输入时按了backspace
			{
				if(i<=0);				//i<=时不操作 
                else i--;
			}
			else
			{
				i++;
				if(i>8)
				{
					printf("输入密码超过8位，前8位有效");
					i=i-1; 
				}
			}
		}
		su.password[i]='\0';			//添加字符串结束标志 
		char check_password[8];			//定义校对用的字符串 
		printf("\n再次输入密码：");
		i=0;
		for(i=0;i<8;i++)
            check_password[i]='\0';
        i=0;
        while(0<i<8&&(check_password[i]=getch())!='\r')
        {
        	if(su.password[i]=='\b')    //输入时按了backspace 
			{
				if(i<=0);
                else i--;
			}
			else
			{
				i++;
				if(i>8)
				{
					printf("输入密码超过8位，前8位有效");
					i=i-1;
				}
			}
		}
		check_password[i]='\0';								//添加字符串结束标志
		int check=1;                                          //开始比较su.password[i]和check_password[8]
		if(strcmp(check_password,su.password)==0);
		else
		{
			printf("\n两次密码输入不一致，请重新注册");
			Sleep(2000);									//休眠两秒钟 
			goto loop1; 									//返回之前的步骤 
		}
		fprintf(fp, "%s %s", su.usernum, su.password);        //写入文件 
        fprintf(fp,"\n");
        fclose(fp);
        printf("\n注册成功\n");
		printf("按任意键返回主菜单");
        char ch;											
        ch=getch();											//接收到字符后清屏 
        system("CLS");
        return 1;
	}
	else
	{
		printf("此账号已被注册\n");
		printf("按任意键返回");
		char ch;
    	ch=getch();								//接收到字符后返回 
   		goto loop1;
	}
}

int checkUserValid(struct sysuser *user)			//检查账号合法性
{
	FILE *user_file_p;
	user_file_p=fopen("user.txt","r");				//只读打开文件 
	if(user_file_p==NULL)
	user_file_p=fopen("user.txt","w");				//若文件不存在，建立新文件（只写） 
	char usr[30],pwd[10];			//保存输入的账号密码 
	char usr_f[30];					//从user.txt中读取 
	int check=0;
	strcpy(usr,user->usernum);		//复制字符串 
	strcat(usr," ");				//在账号密码之间添加一个空格 
	strcpy(pwd,user->password);
	strcat(usr,pwd);				//将密码添加到usr后面 
	strcat(usr,"\n");				//添加一个回车符 
	while(feof(user_file_p)==0)		//文件没到末尾时循环 
	{
		fgets(usr_f,30,user_file_p);			//从文件中读取一行
		if(strcmp(usr,usr_f)==0)			//两字符串相等 
        {
            check=1;
            break;
        }
	}
	if(fclose(user_file_p))						//关闭文件 
    {
        printf("Can not close the file!\n");
        exit(0);
    }
    return check;
}

struct sysuser id;			//全局变量，之后在登记借出或还书的时候会用到 
int login()					//登陆
{
	char ch;
	int check=0;
	system("CLS");			//清屏 
	print_main_title();		//调用函数打印大标题 
	printf("\n");
	printf("输入账号：");
	scanf("%s",id.usernum);
	printf("输入密码（密码不会再屏幕上显示）：");
	int i=0;
	while(0<i<8&&(id.password[i]=getch())!='\r')
	{
		if(id.password[i]=='\b')
		{
			if(i<=0);
			else i--;
		}
		else
		{
			i++;
			if(i>8)
			{
				printf("密码超过8位");
				i--; 
			}
		}
	}
	id.password[i]='\0';
	if(checkUserValid(&id)==1)			//检查账户合法性 
	{
		check=1;
		printf("\n登陆成功\n");
		printf("按任意键进入主菜单...");
		ch=getch();
		system("CLS");
	}
	else
	{
		printf("账号或密码错误，请重新登陆\n");
		printf("按任意键返回\n");
		ch=getch();
		system("CLS");
	}
	return check;
}

int check_void_file()					//检查library.txt是否为空 
{
	FILE *fp;
	fp=fopen("library.txt","r+");
	char ch;
	ch=fgetc(fp);			//读取一个字符 
	fclose(fp);
	if(ch==EOF)return 0;		//如果读取到的字符是文件结束标志那就返回0，代表空 
	return 1;
}

struct book *make_linklist()			//从library.txt中读取数据
{
	struct book *head;
	head=(struct book *)malloc(sizeof(struct book));
	head->next=NULL;
	FILE *fp;
	fp=fopen("library.txt", "r+");					//读写 
	if(fp==NULL)fp=fopen("library.txt","w+");		//如果不存在，创建文件（读写） 
	if(check_void_file()==0)                        //调用函数检查数据库是否为空 
	{
		printf("图书数据库为空\n");
		return head;
	}
	struct book *p;
	p=head;
	char ch;
	while(feof(fp)==0)								//文件没到末尾时循环 
	{
		struct book *new_book_init;
		new_book_init=(struct book *)malloc(sizeof(struct book));
		fscanf(fp, "%d",&new_book_init->number);
		ch = fgetc(fp); 
        fscanf(fp, "%[^\n]%*c",new_book_init->name); 					//格式化读取，[^\n]允许输入空格 
        fscanf(fp, "%[^\n]%*c",new_book_init->zuozhe);             
        fscanf(fp, "%d",&new_book_init->kucun);
        ch=fgetc(fp);													//将空格读出 
        fscanf(fp, "%d",&new_book_init->xiancun);
        ch=fgetc(fp);													//将空格读出 
        new_book_init->next=NULL;
        p->next=new_book_init; 
        p=p->next;
	}
	fclose(fp);
    return head;
} 

int input_new_book(struct book *head)			//增加新书 
{
	FILE *fp;
    struct book newbook;
    struct book *p; 
    p=head; 
    if(p->next==NULL)
    {
        printf("空链表");
    }
    input_loop:								//语句标号 
    fp=fopen("library.txt","a+");			//为读写打开文件 
    system("CLS");							//清屏 
    printf("录入新图书\n");
    printf("编号的要求为30位以内的数字\n");
    printf("书名的要求为10个英文字符以内\n"); 	//或者是5个汉字 
    input_number_loop:
    printf("输入新书的编号：");
    scanf("%d",&newbook.number);
	while(p->next!=NULL)
    {
        if(newbook.number==p->number)				//检查图书库内是否已经有该书 
        {
            printf("该书已存在,请核对后重新输入\n");
            system("PAUSE");
            printf("\n");
            goto input_number_loop;
        }
        p=p->next;
    }
    p=head;
    input_name_loop:
    printf("输入新书的书名：");
    fflush(stdin);						//fflush()用于强迫将缓冲区内的数据写回stdin中
    scanf("%[^'\n']",newbook.name);		//书名允许输入空格 
    while(p->next!=NULL)
    {
    	if(strcmp(p->name,newbook.name)==0)				//比对图书库中是否已经有此书 
        {
            printf("该书已存在！请核对后重新输入\n");
            system("PAUSE");
            printf("\n");
            goto input_name_loop;
        }
        p=p->next;
	}
	p=head;
	fflush(stdin);
	input_zuozhe_loop:
	printf("输入新书的作者：");
	scanf("%[^'\n']",newbook.zuozhe);
	fflush(stdin);
	p=head;
	printf("输入新书的库存：");
	scanf("%d",&newbook.kucun);
	newbook.xiancun=newbook.kucun;				//现存量等于库存量 
	newbook.year=0;
	newbook.month=0;
	newbook.day=0;
	newbook.next=NULL;
	fprintf(fp,"%d ",newbook.number);			//开始将数据写入txt文件 
	fprintf(fp,"%s\n",newbook.name);
	fprintf(fp,"%s\n",newbook.zuozhe);
	fprintf(fp,"%d %d\n",newbook.kucun,newbook.xiancun);
	fclose(fp);
	printf("录入成功！\n");
	printf("录入书本的资料如下：\n");
	printf("编号：%d\n",newbook.number);
	printf("书名：%s\n",newbook.name);
	printf("作者：%s\n",newbook.zuozhe);
	printf("\n");
	printf("是否继续录入？1、是 2、否");
	fflush(stdin);
	char ch;
	scanf("%c",&ch);
	if(ch=='1')
	{
		goto input_loop;
	}
	else
	{
		printf("\n即将返回主菜单...");
		Sleep(3000);
		return 1; 
	}
}

void print_booknode(struct book *t)					//打印出书本信息 
{

    if(t!=NULL)						//t不空时执行
    {
        printf("编号：%d\n",t->number);
        printf("书名：%s\n",t->name);
        printf("作者：%s\n",t->zuozhe);
		if(t->xiancun>0)
		printf("有库存\n");
    }
    else
    {
        printf("没有找到该书！\n");
        printf("按任意键返回主菜单...\n");
        getch();
    }
}

struct book *search_by_number(struct book *head, int number)		//按照编号寻找图书 
{
    struct book *p;
    p=head->next; 
    if(p==NULL)
        return NULL;
    while(p->next!=NULL) 
    {
        if (p->number==number)
            return p;				//找到对应书本，返回指针 
        p=p->next;
    }
}

void override_to_file(struct book *head)			//覆盖链表到library.txt，清空原library.txt的数据
{
	FILE *fp;
	fp=fopen("library.txt","w");			//只写打开文件
	struct book *p;
	p=head->next;
	while(p->next!=NULL)
	{
		fprintf(fp,"%d ",p->number);
		fprintf(fp,"%s\n",p->name);
		fprintf(fp,"%s\n",p->zuozhe);
		fprintf(fp,"%d ",p->kucun);
		fprintf(fp,"%d ",p->xiancun);
        fprintf(fp,"\n");
        p=p->next;
	}
	fclose(fp);
}

int check_sysuser_void_file()			//检查user文件是否为空 
{
	FILE *fp;
	fp=fopen("user.txt","r+");
	char ch;
	ch=fgetc(fp);
	fclose(fp);
	if(ch==EOF)return 0;			//如果读取到的字符为文件结束标志则表示文件为空 
	return 1;
}

struct sysuser *make_sysuser_linklist()			//从user.txt中读取数据至链表
{
	struct sysuser *sysuser_head;
	sysuser_head = (struct sysuser *)malloc(sizeof(struct sysuser));
	sysuser_head->next=NULL;
	FILE *fp;
	fp=fopen("user.txt","r+");					//为读写打开文件 
	if(fp==NULL)
	fp=fopen("user.txt","w+");					//如果文件不存在，为读写创建一个文件
	 
	if(check_sysuser_void_file()==0)			//调用函数检查user文件是否为空 
	{
		printf("用户信息库为空！");
		return sysuser_head;
	}
	struct sysuser *p;
	p=sysuser_head;
	char ch;
	while(feof(fp)==0)					//文件没结束时循环 
	{
		struct sysuser *new_sysuser_init;
		new_sysuser_init=(struct sysuser *)malloc(sizeof(struct sysuser));
		fscanf(fp,"%s",&new_sysuser_init->usernum);
		ch=fgetc(fp);									//读取空格 
		fscanf(fp,"%[^\n]%*c",new_sysuser_init->password);
		new_sysuser_init->next=NULL;
		p->next=new_sysuser_init; 
        p=p->next;
	}
	fclose(fp);
    return sysuser_head;
} 

void override_to_sysuser_file(struct sysuser *sysuser_head)				//覆盖链表到user.txt，清空原user.txt的数据
{
	FILE *fp; 
    fp=fopen("user.txt","w");
    struct sysuser *p;
    p=sysuser_head->next;  
    while(p->next!=NULL)
    {
        fprintf(fp,"%s ",p->usernum);
        fprintf(fp,"%s\n",p->password);
        p=p->next;  
    }
    fclose(fp);
}

void input_borrow_list(struct book *t,struct sysuser id)				//借书记录 
{
	FILE *fp;
	fp=fopen("borrow.txt","a");					//在文件末尾添加数据 
	if(fp==NULL)
	fp=fopen("borrow.txt","w");					//如果文件不存在，为只写创建一个文件 
	fprintf(fp,"%d %s %d %d %d ",t->number,id.usernum,t->year,t->month,t->day);			//记录借的书籍编号、借阅者的账号、借阅时间 
	fprintf(fp,"未还\n");		//标记未归还 
	fclose(fp);
}

void input_lend_list(struct book *t,struct sysuser id)			//归还记录 
{
	FILE *fp;
	fp=fopen("borrow.txt","a");			//在文件末尾添加数据 
	if(fp==NULL)
	fp=fopen("borrow.txt","w");			//如果文件不存在，为只写创建一个文件
	fprintf(fp,"%d %s %d %d %d ",t->number,id.usernum,t->year,t->month,t->day);			//记录还的书籍编号、还书者的账号、还书时间 
	fprintf(fp,"已还\n");		//标记已还 
	fclose(fp);
}

int main()			//开始主函数 
{
	while(1)			//使用无限循环 
	{
	
		char temp;		//临时参数，用于接收输入的编号，对应操作的步骤 
		loop:				//语句标号 
			system("CLS");
			print_main_title();			//打印主标题 
			printf("1、注册\n");		//打印操作界面 
			printf("2、登陆\n");
			printf("输入编号：");
			scanf("%c",&temp);
			int login_check_temp=1;			//用于检查是否登录成功 
			switch(temp)
			{
				case '1':			//注册 
				    create_user();		//调用注册函数 
    	    		goto loop;			//注册完成后回到主界面 
    	    	case '2':
    	    		login_check_temp=login();		//调用登录函数的同时检查是否登录成功 
    	    		if(login_check_temp==0)			//登录不成功的话返回
      		  		goto loop;
       		 		char menu_select;			//登录后使用的编号 
       		 		struct sysuser *sysuser_head; 
					struct book *head;
	   		 		char ch;
	    			char str_tmp[100];
	   		 		while(1)
	   		 		{
	   		 			head=make_linklist();
	   		 			main_loop:
	    				system("CLS");
	    				print_main_title();
	    				printf("1、借书\n");		//打印操作界面 
	    				printf("2、归还\n");
						printf("3、图书入库\n");
						printf("4、退出\n");
						printf("输入要使用功能的编号：");
						scanf("%c",&menu_select);
						struct sysuser *m;
						time_t timep;			//获取时间 
						struct tm *time_p;
						time(&timep);
						time_p=gmtime(&timep);
						int year=0;
						int month=0;
						int day=0;
						struct book *t;
						int booknum;			//定义之后搜索用到的图书的编号 
						int back_select;		//还书界面的操作选择编号 
						switch(menu_select)
						{
							case '1':		//借书 
							borrow_main_loop:			//语句标号 
								system("CLS"); 			//清屏 
								printf("借书\n");		//操作界面提示 
								printf("1、输入书的编号\n");
								printf("2、返回上一级\n");
								printf("请输入要执行的操作：");
								int book_borrow;			//借书界面的操作编号 
								scanf("%d",&book_borrow);
								switch(book_borrow)
								{
									case 1:
										book_borrow_loop:			//语句标号 
											system("CLS");			//清屏 
											printf("输入书的编号：");
											scanf("%d",&booknum);
											t=search_by_number(head,booknum);		//调用函数，按照书号寻找图书 
											if(t!=NULL)			//找到图书 
											{
												system("CLS");		//清屏 
												printf("借书\n");
												print_booknode(t);		//打印书本信息 
												if(t->xiancun>0)		//馆内现存量大于0 
												{
													printf("确定要借这本书吗？1、是 2、否");
													int temp1;		//操作编号 
													scanf("%d",&temp1);
													if(temp1==1)
													{
														t->xiancun-=1;
														t->year=1900+time_p->tm_year;
		                            					t->month=time_p->tm_mon+1;
		                            					t->day=time_p->tm_mday;
														input_borrow_list(t,id);		//记录借出信息 
		                            					printf("成功借出！");
		                            					override_to_file(head);			//写入文件 
		                            					system("PAUSE");
		                           						goto borrow_main_loop;
		                            					break;
													}
													if(temp1==2)
													{
														goto borrow_main_loop;		//返回 
													}
												}
												else
												{
													printf("此书已被借完\n");		//现存量不足 
													system("PAUSE"); 
													goto borrow_main_loop;
												}												
											}
											else			//未找到输入编号对应的图书 
											{
												printf("馆内无此书\n");
												system("PAUSE");
												goto borrow_main_loop;
											} 
									case 2:
										goto main_loop;		//返回上一级 
										break;
								}
							case '2':			//还书	 
								back_loop:
									system("CLS");
									printf("还书\n");
									printf("1、输入书的编号\n");
									printf("2、返回上一级\n");
									printf("请输入要执行的操作");
									scanf("%d",&back_select);		//接收操作编号 
									switch(back_select)
									{
										case 1:
											printf("输入书的编号：");
											int temp2;					//操作编号 
											scanf("%d",&temp2);
											t=search_by_number(head,temp2);		//按照编号找到图书 
											if(t!=NULL)
											{
												system("CLS");		//清屏 
												printf("还书\n");
												print_booknode(t);		//打印图书信息 
												printf("确定要还这本书？1、是 2、否");
												scanf("%d",&temp2);
												if(temp2==1)
												{
													t->xiancun+=1;
													t->year=1900+time_p->tm_year;
		                            				t->month=time_p->tm_mon+1;
		                            				t->day=time_p->tm_mday;
		                            				input_lend_list(t,id);			//记录还书信息 
		                            				printf("成功还书！");
		                            				override_to_file(head);			//写入文件 
		                            				system("PAUSE");
		                            				goto back_loop;
		                            				break;
												}
												else
												{
													goto back_loop;
													break;
												}
											}
											else
											{
												printf("馆内无此书，请输入正确的编号！\n");
												system("PAUSE");
												goto back_loop;
											}
											break;
										case 2:
											goto main_loop;			//返回上一级 
									}
							case '3':			//图书入库 
								input_new_book(head);		//调用函数，图书入库 
								goto main_loop;
								break;
							case '4':
								goto loop;		//退出 
						}
					}
			}
	}
}









