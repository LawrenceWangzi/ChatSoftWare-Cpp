#ifndef MESSAGE_H
#define MESSAGE_H
struct Message
{
    int ToTheUserIndex;
    int FromTheUserIndex;
    char FromTheUserName[20];
    char message[256];
};

#endif // MESSAGE_H
