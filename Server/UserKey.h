#ifndef USERKEY
#define USERKEY
#include <arpa/inet.h>
#include <string>
using namespace std;

struct UserInformation//��½�û���Ϣ����ע���û���Ϣ
{
	char RegisterIndexName[20] = {0};//��½�˺�
	char RegisterPwd[20] = {0};//��½����
	int RegisterFlag;//��־ 0 1
};
class UserKey
{
public:
	UserKey(){};
	UserKey(string KeyIndex,string KeyName,int KeyCsockfd);
	~UserKey();

	string KeyIndex;
	string KeyName;
	int KeyCsockfd;

};


#endif //USERKEY


