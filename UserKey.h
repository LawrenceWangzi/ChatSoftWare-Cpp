#ifndef USERKEY
#define USERKEY
//#include <arpa/inet>
#include <string>
using namespace std;

struct UserInformation//登陆信息
{
	char RegisterIndexName[20] = {0};
	char RegisterPwd[20] = {0};
	int RegisterFlag;//标志 0 1
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


