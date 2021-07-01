#include "ChatServer.h"

ChatServer::ChatServer()
{
	ServerInit();
	listNode = new UserListNode();
	//127.0.0.1 �Ǳ���IP������Ƿ����� ��Ҫ�޸�IP
	database = new MysqlDataBase("127.0.0.1", "root", "wzz10499104", "IM");
	database->ConnectDataBase();
}

ChatServer::~ChatServer()
{
	delete database;
}

//ʹ�÷�������ʼ��������״̬ 
void ChatServer::ServerInit()
{
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8888);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//127.0.0.1 �Ǳ���IP������Ƿ����� ��Ҫ�޸�IP

	ServerSockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == ServerSockfd)
	{
		return;
	}

	int BindRet = bind(ServerSockfd, (struct sockadd*)&ServerAddr, sizeof(ServerAddr));
	if (-1 == BindRet)
	{
		close(ServerSockfd);
		ServerSockfd = -1;
		return;
	}
	BindRet = listen(ServerSockfd, 1024);
	if (-1==BindRet)
	{
		close(ServerSockfd);
		ServerSockfd = -1;
		return;
	}
}

//���ܿͻ��˵��������һ���û����û��������붼��ȷ�����������Ϸ������������ɾ���������׽���������
bool ChatServer::AcceptMessageClient()
{
	if (-1 == ServerSockfd)
		return false;


	int ClientSockfd = accept(ServerSockfd,NULL,NULL);
	if (-1==ClientSockfd)
	{
		return false;
	}
	UserInformation Information;

	//���տͻ���
	ssize_t RecvSize = recv(ClientSockfd,(void*)&Information,sizeof(Information),0);
	if (-1==RecvSize||0==RecvSize)
	{
		close(ClientSockfd);
		return false;
	}
	if (1==Information.RegisterFlag)//��½
	{
		//�ж��û����������Ƿ���ȷ��ʵ��Ӧ�ô����ݿ��ѯ
		string SQLstr("select * from user where id = '");
		SQLstr.append(Information.RegisterIndexName).append("'");
		char** SQLrow = database->SelectDataBase(SQLstr.c_str());
		int TheLoginFlag = 0;
		if (SQLrow == NULL)//���ݿ�鲻�����͹رտͻ�����������
		{
			TheLoginFlag = 0;
			RecvSize = send(ClientSockfd,&TheLoginFlag,sizeof(int),0);
			close(ClientSockfd);
			return false;
		}
		else
		{	//�˺�����Ե���
			if (!strcmp(Information.RegisterIndexName,SQLrow[0])&&!strcmp(Information.RegisterPwd,SQLrow[2]))
			{
				//���ͻ��˷��ص�¼״̬����ȷ��¼����1
				cout << "confirmation successful" << endl;
				TheLoginFlag = 1;

				//���Ѿ���¼���û����浽online�û��б���
				UserKey userKey(Information.RegisterIndexName,SQLrow[1],ClientSockfd);
				listNode->PushNode(userKey);
				listNode->ListShow();

				//�Ե�ǰ�û�����һ���̻߳Ự
				RecvSize = send(ClientSockfd, &TheLoginFlag, sizeof(int), 0);
				ChatUserThread* userThread = new ChatUserThread(userKey,listNode);
				userThread->ChatUserStart();
				cout << " user " << SQLrow[0] << ":" << SQLrow[1] << " online...." << endl;
				return true;
			}
			else//���벻��
			{
				TheLoginFlag = 0;
				RecvSize = send(ClientSockfd, &TheLoginFlag, sizeof(int), 0);
				close(ClientSockfd);
				return false;
			}
		}
	}
	else//ע���˺�
	{
		cout << "user name:" << Information.RegisterIndexName << endl << "user password:" << Information.RegisterPwd << endl;
		char RegisterAccount[10] = { 0 };
		ifstream inInfo("auto_account.dat");//ifstream�Ǵ�Ӳ�̵��ڴ�
		inInfo.read(RegisterAccount, sizeof(RegisterAccount));//���ļ��ж�ȡsizeof(RegisterAccount)���ַ�����RegisterAccount��
		inInfo.close();//�ر�inInfo

		int AcNum = atoi(RegisterAccount);//����ȡ�����ַ� ת������
		AcNum++;//������һ
		string TheStr;
		stringstream TheSS;
		TheSS << AcNum;
		TheSS >> TheStr;
		ofstream OutInfo("auto_account.dat");
		OutInfo.write(TheStr.c_str(), strlen(TheStr.c_str()));//��һ��д��ȥ.dat�ļ���
		if (!OutInfo)
		{
			cout << "write info fail" << endl;
		}
		cout << RegisterAccount << endl;//ͳ��ע���û����� �൱���û�������

		send(ClientSockfd, RegisterAccount, sizeof(RegisterAccount), 0);
		string SQLstr("insert into user values('");
		SQLstr.append(RegisterAccount).append("','").append(Information.RegisterIndexName).append("','").append(Information.RegisterPwd).append("')");
		database->InsertDataBase(SQLstr.c_str());
		close(ClientSockfd);
	}
	return true;

	
}

void ChatServer::CloseConnectServer()
{
	close(ServerSockfd);
}