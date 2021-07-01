#include "ChatUserThread.h"



ChatUserThread::ChatUserThread(UserKey Userkey, UserListNode* listnode):
	ThreadMUser(Userkey), ThreadMList(listnode)
{
}


ChatUserThread::~ChatUserThread()
{
}

void ChatUserThread::ChatUserStart()
{
	cout << "starting thread..." << endl;
	int StartRet = prhread_create(&ChatPthread, NULL, ThreadRun, this);//�����߳� ������ص�����
	if (0 != StartRet)
		cout << "fail to create thread" << endl;
}


//��2��ָ�뺯��**

//����ָ��ĺ�����һ�����������ķ���ֵ��ָ�룻
void* ChatUserThread::ThreadRun(void* ThreadArg)
{
	cout << "Thread Start To Run" << endl;
	ChatUserThread* RunThread = (ChatUserThread*)(ThreadArg);
	int OnlineUserLength = RunThread->ThreadMList->ListLength();
	//���� �����û����ȵ��ͻ����û�
	send(RunThread->ThreadMUser.KeyCsockfd.&OnlineUserLength,sizeof(int));

	//�����������û���Ϣ����Ϣ���͸��ͻ����û�
	OnlineChatUserInfo OLCuf;
	ListNode* CurrentNode = RunThread->ThreadMList->ListGetHeadNode()->NextNode;
	while (CurrentNode!=NULL)
	{
		memset(&OLCuf,0,sizeof(OLCuf));
		strcpy(OLCuf.index,CurrentNode->Userkey.KeyIndex.c_str());
		strcpy(OLCuf.name, CurrentNode->Userkey.KeyName.c_str());
		send(RunThread->ThreadMUser.KeyCsockfd, &OLCuf, sizeof(OLCuf), 0);
		CurrentNode = CurrentNode->NextNode;
		cout << "send infos finish"<<endl;
	}
	Message message;
	while (1)
	{
		int msgRet = recv(RunThread->ThreadMUser.KeyCsockfd,&message,sizeof(message),0);
		if (-1==msgRet||0==msgRet)//����ֵ  <0 ����  =0 ���ӹر�
		{
			RunThread->ThreadMList->PopNode(RunThread->ThreadMUser.KeyCsockfd);
			cout << "user id is" << RunThread->ThreadMUser.KeyIndex << ":" << RunThread->ThreadMUser.KeyName << " offline " << endl;
			close(RunThread->ThreadMUser.KeyCsockfd);//�رտͻ��������߳�
			break;
		}
		strcpy(message.TheFromUserName,RunThread->ThreadMUser.KeyName.c_str());
		//����һ���˻��Ƿ���ȫ���ˣ�
		if (0==message.TheToUserIndex)//����ȫ����
		{
			cout << "receive a message from" << message.TheFromUserIndex << ": " << message.message << endl;
			
			ListNode* CurListnode = RunThread->ThreadMList->ListGetHeadNode()->NextNode;
			while (CurListnode!=NULL)
			{
				send(CurListnode->Userkey.KeyCsockfd, &message, sizeof(message),0);
				cout << "send index to " << CurListnode->Userkey.KeyIndex << "finish" << endl;
				CurListnode = CurrentNode->NextNode;
			}
		}
		else//���͸�ĳһ����
		{
			string TheString;
			stringstream TheSS;
			TheSS << message.TheToUserIndex;
			TheSS >> TheString;
			cout << message.TheToUserIndex << endl;
			int TheCSockfd = RunThread->ThreadMList->ListSelectSockfd(TheString.c_str());
			int TheRet = send(TheCSockfd, &message, sizeof(message), 0);
			cout << TheCSockfd << endl;
			if (-1==TheRet||0==TheRet)
			{
				cout << " send message to someuser fail " << endl;
			}
		}

	}
	cout << "the thread is die" << endl;
	return NULL;
}	