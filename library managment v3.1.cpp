#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
struct sysuser				//�����û��ṹ�� 
{
	char usernum[12];		//�û��˺� 
	char password[8];		//�û����� 
	struct sysuser *next;	//ָ����һ�ڵ� 
};

struct book
{
	int number;         //���
    char name[30];      //����
    char zuozhe[10];	//���� 
    int kucun;			//��� 
    int xiancun;		//�ִ� 
    int year;           //���ʱ��--��
    int month;          //���ʱ��--��
    int day;            //���ʱ��--��
    struct book *next;  //ָ����һ�ڵ� 
};

void print_main_title()			//��ӡ����� 
{
	time_t time_login;			
	struct tm *p;
    time(&time_login);			//��ȡ��ǰʱ�� 
    p=gmtime(&time_login);
    printf("��ӭʹ��ͼ�����ϵͳ\n");
    printf("����ʱ�䣺%d��%d��%d�� %d:%d:%d\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);  //Ϊ���ڽ��黹��ʱ�Ǽ�ʱ�䣬ϵͳ��Ҫ��ʱ��ģ�� 
}

int check_usernum(struct sysuser *user)    //������û��˺ŷ�ע��� 
{
	int check=0;						
	char usrno[12];						//���ڽ���user������ 
	strcpy(usrno,user->usernum);		//�����ַ��� 
	char usrno_f[12];					//�����ݴ��ļ��ڵ��˺���Ϣ 
	FILE *fp;							
	fp=fopen("user.txt","r+");					//��д 
	if (fp==NULL)fopen("user.txt","w");			//����use.txt�ļ�������һ��ֻд���ļ� 
	while(fscanf(fp,"%s%*s",usrno_f)!=EOF)		//ɨ���ļ��ڵ��������ļ����� 
    {
        if(strcmp(usrno,usrno_f)==0)			//���ַ���������ͬ 
        {
            check=1;
            break;
        }
    }
    fclose(fp);							//�ر��ļ� 
	return check;                         //��ע�������1��û��ע�������0 
} 

int create_user()                          //ע�� 
{
	struct sysuser su;
	FILE *fp;
	fp=fopen("user.txt","a");				//���ı�β���������� 
	if(fp==NULL)fopen("user.txt","w");		//���û���ļ��Ǿʹ���ֻд��ʽ���ļ� 
    loop1:                           //����ţ�����goto�˴� 
	system("CLS");					//���� 
	printf("ע�����û�\n");
	printf("�����˺��û�����");
	scanf("%s",su.usernum);			//���̼����û��� 
	if(check_usernum(&su)==0)		//�û���δ��ע��� 
	{
		printf("��������(����С�ڵ���8λ)��");
		int i=0;
		while(0<i<8&&(su.password[i]=getch())!='\r')			//getch()����������ʱ��������Ļ����ʾ���� 
		{
			if(su.password[i]=='\b')    //����ʱ����backspace
			{
				if(i<=0);				//i<=ʱ������ 
                else i--;
			}
			else
			{
				i++;
				if(i>8)
				{
					printf("�������볬��8λ��ǰ8λ��Ч");
					i=i-1; 
				}
			}
		}
		su.password[i]='\0';			//����ַ���������־ 
		char check_password[8];			//����У���õ��ַ��� 
		printf("\n�ٴ��������룺");
		i=0;
		for(i=0;i<8;i++)
            check_password[i]='\0';
        i=0;
        while(0<i<8&&(check_password[i]=getch())!='\r')
        {
        	if(su.password[i]=='\b')    //����ʱ����backspace 
			{
				if(i<=0);
                else i--;
			}
			else
			{
				i++;
				if(i>8)
				{
					printf("�������볬��8λ��ǰ8λ��Ч");
					i=i-1;
				}
			}
		}
		check_password[i]='\0';								//����ַ���������־
		int check=1;                                          //��ʼ�Ƚ�su.password[i]��check_password[8]
		if(strcmp(check_password,su.password)==0);
		else
		{
			printf("\n�����������벻һ�£�������ע��");
			Sleep(2000);									//���������� 
			goto loop1; 									//����֮ǰ�Ĳ��� 
		}
		fprintf(fp, "%s %s", su.usernum, su.password);        //д���ļ� 
        fprintf(fp,"\n");
        fclose(fp);
        printf("\nע��ɹ�\n");
		printf("��������������˵�");
        char ch;											
        ch=getch();											//���յ��ַ������� 
        system("CLS");
        return 1;
	}
	else
	{
		printf("���˺��ѱ�ע��\n");
		printf("�����������");
		char ch;
    	ch=getch();								//���յ��ַ��󷵻� 
   		goto loop1;
	}
}

int checkUserValid(struct sysuser *user)			//����˺źϷ���
{
	FILE *user_file_p;
	user_file_p=fopen("user.txt","r");				//ֻ�����ļ� 
	if(user_file_p==NULL)
	user_file_p=fopen("user.txt","w");				//���ļ������ڣ��������ļ���ֻд�� 
	char usr[30],pwd[10];			//����������˺����� 
	char usr_f[30];					//��user.txt�ж�ȡ 
	int check=0;
	strcpy(usr,user->usernum);		//�����ַ��� 
	strcat(usr," ");				//���˺�����֮�����һ���ո� 
	strcpy(pwd,user->password);
	strcat(usr,pwd);				//��������ӵ�usr���� 
	strcat(usr,"\n");				//���һ���س��� 
	while(feof(user_file_p)==0)		//�ļ�û��ĩβʱѭ�� 
	{
		fgets(usr_f,30,user_file_p);			//���ļ��ж�ȡһ��
		if(strcmp(usr,usr_f)==0)			//���ַ������ 
        {
            check=1;
            break;
        }
	}
	if(fclose(user_file_p))						//�ر��ļ� 
    {
        printf("Can not close the file!\n");
        exit(0);
    }
    return check;
}

struct sysuser id;			//ȫ�ֱ�����֮���ڵǼǽ�������ʱ����õ� 
int login()					//��½
{
	char ch;
	int check=0;
	system("CLS");			//���� 
	print_main_title();		//���ú�����ӡ����� 
	printf("\n");
	printf("�����˺ţ�");
	scanf("%s",id.usernum);
	printf("�������루���벻������Ļ����ʾ����");
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
				printf("���볬��8λ");
				i--; 
			}
		}
	}
	id.password[i]='\0';
	if(checkUserValid(&id)==1)			//����˻��Ϸ��� 
	{
		check=1;
		printf("\n��½�ɹ�\n");
		printf("��������������˵�...");
		ch=getch();
		system("CLS");
	}
	else
	{
		printf("�˺Ż�������������µ�½\n");
		printf("�����������\n");
		ch=getch();
		system("CLS");
	}
	return check;
}

int check_void_file()					//���library.txt�Ƿ�Ϊ�� 
{
	FILE *fp;
	fp=fopen("library.txt","r+");
	char ch;
	ch=fgetc(fp);			//��ȡһ���ַ� 
	fclose(fp);
	if(ch==EOF)return 0;		//�����ȡ�����ַ����ļ�������־�Ǿͷ���0������� 
	return 1;
}

struct book *make_linklist()			//��library.txt�ж�ȡ����
{
	struct book *head;
	head=(struct book *)malloc(sizeof(struct book));
	head->next=NULL;
	FILE *fp;
	fp=fopen("library.txt", "r+");					//��д 
	if(fp==NULL)fp=fopen("library.txt","w+");		//��������ڣ������ļ�����д�� 
	if(check_void_file()==0)                        //���ú���������ݿ��Ƿ�Ϊ�� 
	{
		printf("ͼ�����ݿ�Ϊ��\n");
		return head;
	}
	struct book *p;
	p=head;
	char ch;
	while(feof(fp)==0)								//�ļ�û��ĩβʱѭ�� 
	{
		struct book *new_book_init;
		new_book_init=(struct book *)malloc(sizeof(struct book));
		fscanf(fp, "%d",&new_book_init->number);
		ch = fgetc(fp); 
        fscanf(fp, "%[^\n]%*c",new_book_init->name); 					//��ʽ����ȡ��[^\n]��������ո� 
        fscanf(fp, "%[^\n]%*c",new_book_init->zuozhe);             
        fscanf(fp, "%d",&new_book_init->kucun);
        ch=fgetc(fp);													//���ո���� 
        fscanf(fp, "%d",&new_book_init->xiancun);
        ch=fgetc(fp);													//���ո���� 
        new_book_init->next=NULL;
        p->next=new_book_init; 
        p=p->next;
	}
	fclose(fp);
    return head;
} 

int input_new_book(struct book *head)			//�������� 
{
	FILE *fp;
    struct book newbook;
    struct book *p; 
    p=head; 
    if(p->next==NULL)
    {
        printf("������");
    }
    input_loop:								//����� 
    fp=fopen("library.txt","a+");			//Ϊ��д���ļ� 
    system("CLS");							//���� 
    printf("¼����ͼ��\n");
    printf("��ŵ�Ҫ��Ϊ30λ���ڵ�����\n");
    printf("������Ҫ��Ϊ10��Ӣ���ַ�����\n"); 	//������5������ 
    input_number_loop:
    printf("��������ı�ţ�");
    scanf("%d",&newbook.number);
	while(p->next!=NULL)
    {
        if(newbook.number==p->number)				//���ͼ������Ƿ��Ѿ��и��� 
        {
            printf("�����Ѵ���,��˶Ժ���������\n");
            system("PAUSE");
            printf("\n");
            goto input_number_loop;
        }
        p=p->next;
    }
    p=head;
    input_name_loop:
    printf("���������������");
    fflush(stdin);						//fflush()����ǿ�Ƚ��������ڵ�����д��stdin��
    scanf("%[^'\n']",newbook.name);		//������������ո� 
    while(p->next!=NULL)
    {
    	if(strcmp(p->name,newbook.name)==0)				//�ȶ�ͼ������Ƿ��Ѿ��д��� 
        {
            printf("�����Ѵ��ڣ���˶Ժ���������\n");
            system("PAUSE");
            printf("\n");
            goto input_name_loop;
        }
        p=p->next;
	}
	p=head;
	fflush(stdin);
	input_zuozhe_loop:
	printf("������������ߣ�");
	scanf("%[^'\n']",newbook.zuozhe);
	fflush(stdin);
	p=head;
	printf("��������Ŀ�棺");
	scanf("%d",&newbook.kucun);
	newbook.xiancun=newbook.kucun;				//�ִ������ڿ���� 
	newbook.year=0;
	newbook.month=0;
	newbook.day=0;
	newbook.next=NULL;
	fprintf(fp,"%d ",newbook.number);			//��ʼ������д��txt�ļ� 
	fprintf(fp,"%s\n",newbook.name);
	fprintf(fp,"%s\n",newbook.zuozhe);
	fprintf(fp,"%d %d\n",newbook.kucun,newbook.xiancun);
	fclose(fp);
	printf("¼��ɹ���\n");
	printf("¼���鱾���������£�\n");
	printf("��ţ�%d\n",newbook.number);
	printf("������%s\n",newbook.name);
	printf("���ߣ�%s\n",newbook.zuozhe);
	printf("\n");
	printf("�Ƿ����¼�룿1���� 2����");
	fflush(stdin);
	char ch;
	scanf("%c",&ch);
	if(ch=='1')
	{
		goto input_loop;
	}
	else
	{
		printf("\n�����������˵�...");
		Sleep(3000);
		return 1; 
	}
}

void print_booknode(struct book *t)					//��ӡ���鱾��Ϣ 
{

    if(t!=NULL)						//t����ʱִ��
    {
        printf("��ţ�%d\n",t->number);
        printf("������%s\n",t->name);
        printf("���ߣ�%s\n",t->zuozhe);
		if(t->xiancun>0)
		printf("�п��\n");
    }
    else
    {
        printf("û���ҵ����飡\n");
        printf("��������������˵�...\n");
        getch();
    }
}

struct book *search_by_number(struct book *head, int number)		//���ձ��Ѱ��ͼ�� 
{
    struct book *p;
    p=head->next; 
    if(p==NULL)
        return NULL;
    while(p->next!=NULL) 
    {
        if (p->number==number)
            return p;				//�ҵ���Ӧ�鱾������ָ�� 
        p=p->next;
    }
}

void override_to_file(struct book *head)			//��������library.txt�����ԭlibrary.txt������
{
	FILE *fp;
	fp=fopen("library.txt","w");			//ֻд���ļ�
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

int check_sysuser_void_file()			//���user�ļ��Ƿ�Ϊ�� 
{
	FILE *fp;
	fp=fopen("user.txt","r+");
	char ch;
	ch=fgetc(fp);
	fclose(fp);
	if(ch==EOF)return 0;			//�����ȡ�����ַ�Ϊ�ļ�������־���ʾ�ļ�Ϊ�� 
	return 1;
}

struct sysuser *make_sysuser_linklist()			//��user.txt�ж�ȡ����������
{
	struct sysuser *sysuser_head;
	sysuser_head = (struct sysuser *)malloc(sizeof(struct sysuser));
	sysuser_head->next=NULL;
	FILE *fp;
	fp=fopen("user.txt","r+");					//Ϊ��д���ļ� 
	if(fp==NULL)
	fp=fopen("user.txt","w+");					//����ļ������ڣ�Ϊ��д����һ���ļ�
	 
	if(check_sysuser_void_file()==0)			//���ú������user�ļ��Ƿ�Ϊ�� 
	{
		printf("�û���Ϣ��Ϊ�գ�");
		return sysuser_head;
	}
	struct sysuser *p;
	p=sysuser_head;
	char ch;
	while(feof(fp)==0)					//�ļ�û����ʱѭ�� 
	{
		struct sysuser *new_sysuser_init;
		new_sysuser_init=(struct sysuser *)malloc(sizeof(struct sysuser));
		fscanf(fp,"%s",&new_sysuser_init->usernum);
		ch=fgetc(fp);									//��ȡ�ո� 
		fscanf(fp,"%[^\n]%*c",new_sysuser_init->password);
		new_sysuser_init->next=NULL;
		p->next=new_sysuser_init; 
        p=p->next;
	}
	fclose(fp);
    return sysuser_head;
} 

void override_to_sysuser_file(struct sysuser *sysuser_head)				//��������user.txt�����ԭuser.txt������
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

void input_borrow_list(struct book *t,struct sysuser id)				//�����¼ 
{
	FILE *fp;
	fp=fopen("borrow.txt","a");					//���ļ�ĩβ������� 
	if(fp==NULL)
	fp=fopen("borrow.txt","w");					//����ļ������ڣ�Ϊֻд����һ���ļ� 
	fprintf(fp,"%d %s %d %d %d ",t->number,id.usernum,t->year,t->month,t->day);			//��¼����鼮��š������ߵ��˺š�����ʱ�� 
	fprintf(fp,"δ��\n");		//���δ�黹 
	fclose(fp);
}

void input_lend_list(struct book *t,struct sysuser id)			//�黹��¼ 
{
	FILE *fp;
	fp=fopen("borrow.txt","a");			//���ļ�ĩβ������� 
	if(fp==NULL)
	fp=fopen("borrow.txt","w");			//����ļ������ڣ�Ϊֻд����һ���ļ�
	fprintf(fp,"%d %s %d %d %d ",t->number,id.usernum,t->year,t->month,t->day);			//��¼�����鼮��š������ߵ��˺š�����ʱ�� 
	fprintf(fp,"�ѻ�\n");		//����ѻ� 
	fclose(fp);
}

int main()			//��ʼ������ 
{
	while(1)			//ʹ������ѭ�� 
	{
	
		char temp;		//��ʱ���������ڽ�������ı�ţ���Ӧ�����Ĳ��� 
		loop:				//����� 
			system("CLS");
			print_main_title();			//��ӡ������ 
			printf("1��ע��\n");		//��ӡ�������� 
			printf("2����½\n");
			printf("�����ţ�");
			scanf("%c",&temp);
			int login_check_temp=1;			//���ڼ���Ƿ��¼�ɹ� 
			switch(temp)
			{
				case '1':			//ע�� 
				    create_user();		//����ע�ắ�� 
    	    		goto loop;			//ע����ɺ�ص������� 
    	    	case '2':
    	    		login_check_temp=login();		//���õ�¼������ͬʱ����Ƿ��¼�ɹ� 
    	    		if(login_check_temp==0)			//��¼���ɹ��Ļ�����
      		  		goto loop;
       		 		char menu_select;			//��¼��ʹ�õı�� 
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
	    				printf("1������\n");		//��ӡ�������� 
	    				printf("2���黹\n");
						printf("3��ͼ�����\n");
						printf("4���˳�\n");
						printf("����Ҫʹ�ù��ܵı�ţ�");
						scanf("%c",&menu_select);
						struct sysuser *m;
						time_t timep;			//��ȡʱ�� 
						struct tm *time_p;
						time(&timep);
						time_p=gmtime(&timep);
						int year=0;
						int month=0;
						int day=0;
						struct book *t;
						int booknum;			//����֮�������õ���ͼ��ı�� 
						int back_select;		//�������Ĳ���ѡ���� 
						switch(menu_select)
						{
							case '1':		//���� 
							borrow_main_loop:			//����� 
								system("CLS"); 			//���� 
								printf("����\n");		//����������ʾ 
								printf("1��������ı��\n");
								printf("2��������һ��\n");
								printf("������Ҫִ�еĲ�����");
								int book_borrow;			//�������Ĳ������ 
								scanf("%d",&book_borrow);
								switch(book_borrow)
								{
									case 1:
										book_borrow_loop:			//����� 
											system("CLS");			//���� 
											printf("������ı�ţ�");
											scanf("%d",&booknum);
											t=search_by_number(head,booknum);		//���ú������������Ѱ��ͼ�� 
											if(t!=NULL)			//�ҵ�ͼ�� 
											{
												system("CLS");		//���� 
												printf("����\n");
												print_booknode(t);		//��ӡ�鱾��Ϣ 
												if(t->xiancun>0)		//�����ִ�������0 
												{
													printf("ȷ��Ҫ���Ȿ����1���� 2����");
													int temp1;		//������� 
													scanf("%d",&temp1);
													if(temp1==1)
													{
														t->xiancun-=1;
														t->year=1900+time_p->tm_year;
		                            					t->month=time_p->tm_mon+1;
		                            					t->day=time_p->tm_mday;
														input_borrow_list(t,id);		//��¼�����Ϣ 
		                            					printf("�ɹ������");
		                            					override_to_file(head);			//д���ļ� 
		                            					system("PAUSE");
		                           						goto borrow_main_loop;
		                            					break;
													}
													if(temp1==2)
													{
														goto borrow_main_loop;		//���� 
													}
												}
												else
												{
													printf("�����ѱ�����\n");		//�ִ������� 
													system("PAUSE"); 
													goto borrow_main_loop;
												}												
											}
											else			//δ�ҵ������Ŷ�Ӧ��ͼ�� 
											{
												printf("�����޴���\n");
												system("PAUSE");
												goto borrow_main_loop;
											} 
									case 2:
										goto main_loop;		//������һ�� 
										break;
								}
							case '2':			//����	 
								back_loop:
									system("CLS");
									printf("����\n");
									printf("1��������ı��\n");
									printf("2��������һ��\n");
									printf("������Ҫִ�еĲ���");
									scanf("%d",&back_select);		//���ղ������ 
									switch(back_select)
									{
										case 1:
											printf("������ı�ţ�");
											int temp2;					//������� 
											scanf("%d",&temp2);
											t=search_by_number(head,temp2);		//���ձ���ҵ�ͼ�� 
											if(t!=NULL)
											{
												system("CLS");		//���� 
												printf("����\n");
												print_booknode(t);		//��ӡͼ����Ϣ 
												printf("ȷ��Ҫ���Ȿ�飿1���� 2����");
												scanf("%d",&temp2);
												if(temp2==1)
												{
													t->xiancun+=1;
													t->year=1900+time_p->tm_year;
		                            				t->month=time_p->tm_mon+1;
		                            				t->day=time_p->tm_mday;
		                            				input_lend_list(t,id);			//��¼������Ϣ 
		                            				printf("�ɹ����飡");
		                            				override_to_file(head);			//д���ļ� 
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
												printf("�����޴��飬��������ȷ�ı�ţ�\n");
												system("PAUSE");
												goto back_loop;
											}
											break;
										case 2:
											goto main_loop;			//������һ�� 
									}
							case '3':			//ͼ����� 
								input_new_book(head);		//���ú�����ͼ����� 
								goto main_loop;
								break;
							case '4':
								goto loop;		//�˳� 
						}
					}
			}
	}
}









