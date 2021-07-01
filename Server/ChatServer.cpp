#include "ChatServer.h"

ChatServer::ChatServer()
{
	ServerInit();
	listNode = new UserListNode();
	//127.0.0.1 是本机IP，如果是服务器 则要修改IP
	database = new MysqlDataBase("127.0.0.1", "root", "wzz10499104", "IM");
	database->ConnectDataBase();
}

ChatServer::~ChatServer()
{
	delete database;
}

//使得服务器初始化到监听状态 
void ChatServer::ServerInit()
{
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8888);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//127.0.0.1 是本机IP，如果是服务器 则要修改IP

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

//接受客户端的请求，如果一个用户的用户名和密码都正确才算是连接上服务器。负责就删除已连接套接字描述符
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

	//接收客户端
	ssize_t RecvSize = recv(ClientSockfd,(void*)&Information,sizeof(Information),0);
	if (-1==RecvSize||0==RecvSize)
	{
		close(ClientSockfd);
		return false;
	}
	if (1==Information.RegisterFlag)//登陆
	{
		//判断用户名和密码是否正确，实际应用从数据库查询
		string SQLstr("select * from user where id = '");
		SQLstr.append(Information.RegisterIndexName).append("'");
		char** SQLrow = database->SelectDataBase(SQLstr.c_str());
		int TheLoginFlag = 0;
		if (SQLrow == NULL)//数据库查不到，就关闭客户端连接请求
		{
			TheLoginFlag = 0;
			RecvSize = send(ClientSockfd,&TheLoginFlag,sizeof(int),0);
			close(ClientSockfd);
			return false;
		}
		else
		{	//账号密码对的上
			if (!strcmp(Information.RegisterIndexName,SQLrow[0])&&!strcmp(Information.RegisterPwd,SQLrow[2]))
			{
				//给客户端返回登录状态，正确登录返回1
				cout << "confirmation successful" << endl;
				TheLoginFlag = 1;

				//将已经登录的用户保存到online用户列表中
				UserKey userKey(Information.RegisterIndexName,SQLrow[1],ClientSockfd);
				listNode->PushNode(userKey);
				listNode->ListShow();

				//对当前用户发起一个线程会话
				RecvSize = send(ClientSockfd, &TheLoginFlag, sizeof(int), 0);
				ChatUserThread* userThread = new ChatUserThread(userKey,listNode);
				userThread->ChatUserStart();
				cout << " user " << SQLrow[0] << ":" << SQLrow[1] << " online...." << endl;
				return true;
			}
			else//密码不对
			{
				TheLoginFlag = 0;
				RecvSize = send(ClientSockfd, &TheLoginFlag, sizeof(int), 0);
				close(ClientSockfd);
				return false;
			}
		}
	}
	else//注册账号
	{
		cout << "user name:" << Information.RegisterIndexName << endl << "user password:" << Information.RegisterPwd << endl;
		char RegisterAccount[10] = { 0 };
		ifstream inInfo("auto_account.dat");//ifstream是从硬盘到内存
		inInfo.read(RegisterAccount, sizeof(RegisterAccount));//从文件中读取sizeof(RegisterAccount)个字符，到RegisterAccount中
		inInfo.close();//关闭inInfo

		int AcNum = atoi(RegisterAccount);//将获取到的字符 转成数字
		AcNum++;//计数加一
		string TheStr;
		stringstream TheSS;
		TheSS << AcNum;
		TheSS >> TheStr;
		ofstream OutInfo("auto_account.dat");
		OutInfo.write(TheStr.c_str(), strlen(TheStr.c_str()));//又一次写回去.dat文件中
		if (!OutInfo)
		{
			cout << "write info fail" << endl;
		}
		cout << RegisterAccount << endl;//统计注册用户个数 相当于用户索引号

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