#ifndef MESSAGE
#define MESSAGE
struct Message
{
	int TheToUserIndex;//如果为0，则执行所有用户
	int TheFromUserIndex;
	char TheFromUserName[20];
	char message[256];//存放消息的字符串数组
};

#endif // !MESSAGE
