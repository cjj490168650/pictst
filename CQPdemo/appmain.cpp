/*
* CoolQ Demo for VC++ 
* Api Version 9
* Written by Coxxs & Thanks for the help of orzFly
*/

#include "stdafx.h"
#include "cqp.h"
#include "appmain.h" //Ӧ��AppID����Ϣ������ȷ��д�������Q�����޷�����
#include <string>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <regex>
//#define png jpg

using namespace std;

int ac = -1; //AuthCode ���ÿ�Q�ķ���ʱ��Ҫ�õ�
bool enabled = false;


/* 
* ����Ӧ�õ�ApiVer��Appid������󽫲������
*/
CQEVENT(const char*, AppInfo, 0)() {
	return CQAPPINFO;
}


/* 
* ����Ӧ��AuthCode����Q��ȡӦ����Ϣ��������ܸ�Ӧ�ã���������������������AuthCode��
* ��Ҫ�ڱ��������������κδ��룬���ⷢ���쳣���������ִ�г�ʼ����������Startup�¼���ִ�У�Type=1001����
*/
CQEVENT(int32_t, Initialize, 4)(int32_t AuthCode) {
	ac = AuthCode;
	return 0;
}


/*
* Type=1001 ��Q����
* ���۱�Ӧ���Ƿ����ã������������ڿ�Q������ִ��һ�Σ���������ִ��Ӧ�ó�ʼ�����롣
* ��Ǳ�Ҫ����������������ش��ڡ���������Ӳ˵������û��ֶ��򿪴��ڣ�
*/
CQEVENT(int32_t, __eventStartup, 0)() {

	return 0;
}


/*
* Type=1002 ��Q�˳�
* ���۱�Ӧ���Ƿ����ã������������ڿ�Q�˳�ǰִ��һ�Σ���������ִ�в���رմ��롣
* ������������Ϻ󣬿�Q���ܿ�رգ��벻Ҫ��ͨ���̵߳ȷ�ʽִ���������롣
*/
CQEVENT(int32_t, __eventExit, 0)() {

	return 0;
}

/*
* Type=1003 Ӧ���ѱ�����
* ��Ӧ�ñ����ú󣬽��յ����¼���
* �����Q����ʱӦ���ѱ����ã�����_eventStartup(Type=1001,��Q����)�����ú󣬱�����Ҳ��������һ�Ρ�
* ��Ǳ�Ҫ����������������ش��ڡ���������Ӳ˵������û��ֶ��򿪴��ڣ�
*/
CQEVENT(int32_t, __eventEnable, 0)() {
	enabled = true;
	return 0;
}


/*
* Type=1004 Ӧ�ý���ͣ��
* ��Ӧ�ñ�ͣ��ǰ�����յ����¼���
* �����Q����ʱӦ���ѱ�ͣ�ã��򱾺���*����*�����á�
* ���۱�Ӧ���Ƿ����ã���Q�ر�ǰ��������*����*�����á�
*/
CQEVENT(int32_t, __eventDisable, 0)() {
	enabled = false;
	return 0;
}


/*
* Type=21 ˽����Ϣ
* subType �����ͣ�11/���Ժ��� 1/��������״̬ 2/����Ⱥ 3/����������
*/
CQEVENT(int32_t, __eventPrivateMsg, 24)(int32_t subType, int32_t msgId, int64_t fromQQ, const char *msg, int32_t font) {
	if (!strcmp(msg, "pictst"))
	{
		//CQ_sendPrivateMsg(ac, fromQQ, "[CQ:image,file=deemo (1).jpg][CQ:image,file=deemo (2).jpg][CQ:image,file=deemo (3).jpg][CQ:image,file=deemo (4).jpg][CQ:image,file=deemo (5).jpg][CQ:image,file=deemo (6).jpg]");
		CQ_sendPrivateMsg(ac, fromQQ, "[CQ:share,url=http://m.qpic.cn/psb?/V12iQzsN1HppyH/sX*onP2CjwcyM0TDAKhMrmmE1KgD4StITIW73ANofWQ!/b/dDUBAAAAAAAA&bo=AAIAAgACAAIRCT4!&rf=viewer_4,image=http://m.qpic.cn/psb?/V12iQzsN1HppyH/sX*onP2CjwcyM0TDAKhMrmmE1KgD4StITIW73ANofWQ!/b/dDUBAAAAAAAA&bo=AAIAAgACAAIRCT4!&rf=viewer_4]");
	}
	//���Ҫ�ظ���Ϣ������ÿ�Q�������ͣ��������� return EVENT_BLOCK - �ضϱ�����Ϣ�����ټ�������  ע�⣺Ӧ�����ȼ�����Ϊ"���"(10000)ʱ������ʹ�ñ�����ֵ
	//������ظ���Ϣ������֮���Ӧ��/�������������� return EVENT_IGNORE - ���Ա�����Ϣ
	return EVENT_IGNORE;
}


/*
* Type=2 Ⱥ��Ϣ
*/
CQEVENT(int32_t, __eventGroupMsg, 36)(int32_t subType, int32_t msgId, int64_t fromGroup, int64_t fromQQ, const char *fromAnonymous, const char *msg, int32_t font) {
	//if (strstr(msg, "[CQ:at,qq=3513312871] ��ͼ"))
	if (regex_match(msg,regex("(\\[CQ:at,qq=3513312871\\])(\\s)(��)(.*)(ͼ)")))
	{
		const int game_count = 9;
		srand(int(time(0)));
		int rand_game = rand() % game_count, rand_pic=0;
		string name_game;
		//if (strstr(msg, "changed") || strstr(msg, "Changed") || strstr(msg, "CHANGED"))
		if (regex_search(msg,regex("��changedͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 171 + 1;
			name_game = "changed";
		}
		//else if (strstr(msg, "lanota") || strstr(msg, "Lanota") || strstr(msg, "LANOTA"))
		else if (regex_search(msg, regex("��lanotaͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 102 + 1;
			name_game = "lanota";
		}
		else if (regex_search(msg, regex("��cytus\\s2ͼ", regex_constants::icase)) || regex_search(msg, regex("��cytus\\siiͼ", regex_constants::icase)) || regex_search(msg, regex("��cytus2ͼ", regex_constants::icase)) || regex_search(msg, regex("��cytusiiͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 122 + 1;
			name_game = "cytus2";
		}
		//else if (strstr(msg, "cytus") || strstr(msg, "Cytus") || strstr(msg, "CYTUS"))
		else if (regex_search(msg, regex("��cytusͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 203 + 1;
			name_game = "cytus";
		}
		else if (regex_search(msg, regex("��deemoͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 294 + 1;
			name_game = "deemo";
		}
		else if (regex_search(msg, regex("��dynamixͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 250 + 1;
			name_game = "dynamix";
		}
		else if (regex_search(msg, regex("��voezͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 203 + 1;
			name_game = "voez";
		}
		else if (regex_search(msg, regex("��arcaeaͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 123 + 1;
			name_game = "arcaea";
		}
		else if (regex_search(msg, regex("��muse\\sdashͼ", regex_constants::icase)) || regex_search(msg, regex("��musedashͼ", regex_constants::icase)))
		{
			rand_pic = rand() % 62 + 1;
			name_game = "musedash";
		}
		else if (regex_search(msg, regex("��ɫͼ")))
		{
			rand_pic = rand() % 6 + 1;
			name_game = "ɫ";
		}
		else if(regex_search(msg, regex("��ͼ")))
		{
			if (rand_game == 0)
			{
				rand_pic = rand() % 171 + 1;
				name_game = "changed";
			}
			if (rand_game == 1)
			{
				rand_pic = rand() % 102 + 1;
				name_game = "lanota";
			}
			if (rand_game == 2)
			{
				rand_pic = rand() % 203 + 1;
				name_game = "cytus";
			}
			if (rand_game == 3)
			{
				rand_pic = rand() % 294 + 1;
				name_game = "deemo";
			}
			if (rand_game == 4)
			{
				rand_pic = rand() % 250 + 1;
				name_game = "dynamix";
			}
			if (rand_game == 5)
			{
				rand_pic = rand() % 203 + 1;
				name_game = "voez";
			}
			if (rand_game == 6)
			{
				rand_pic = rand() % 123 + 1;
				name_game = "arcaea";
			}
			if (rand_game == 7)
			{
				rand_pic = rand() % 62 + 1;
				name_game = "musedash";
			}
			if (rand_game == 8)
			{
				rand_pic = rand() % 122 + 1;
				name_game = "cytus2";
			}
		}
		if (rand_pic)
		{
			ostringstream ss;
			ss << "[CQ:image,file=" << name_game << " (" << rand_pic << ").jpg]"; //[CQ:image,file=1.jpg]
			string name_out = ss.str();
			CQ_sendGroupMsg(ac, fromGroup, name_out.c_str());
		}
	}
	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=4 ��������Ϣ
*/
CQEVENT(int32_t, __eventDiscussMsg, 32)(int32_t subType, int32_t msgId, int64_t fromDiscuss, int64_t fromQQ, const char *msg, int32_t font) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=101 Ⱥ�¼�-����Ա�䶯
* subType �����ͣ�1/��ȡ������Ա 2/�����ù���Ա
*/
CQEVENT(int32_t, __eventSystem_GroupAdmin, 24)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t beingOperateQQ) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=102 Ⱥ�¼�-Ⱥ��Ա����
* subType �����ͣ�1/ȺԱ�뿪 2/ȺԱ���� 3/�Լ�(����¼��)����
* fromQQ ������QQ(��subTypeΪ2��3ʱ����)
* beingOperateQQ ������QQ
*/
CQEVENT(int32_t, __eventSystem_GroupMemberDecrease, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, int64_t beingOperateQQ) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=103 Ⱥ�¼�-Ⱥ��Ա����
* subType �����ͣ�1/����Ա��ͬ�� 2/����Ա����
* fromQQ ������QQ(������ԱQQ)
* beingOperateQQ ������QQ(����Ⱥ��QQ)
*/
CQEVENT(int32_t, __eventSystem_GroupMemberIncrease, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, int64_t beingOperateQQ) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=201 �����¼�-���������
*/
CQEVENT(int32_t, __eventFriend_Add, 16)(int32_t subType, int32_t sendTime, int64_t fromQQ) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=301 ����-�������
* msg ����
* responseFlag ������ʶ(����������)
*/
CQEVENT(int32_t, __eventRequest_AddFriend, 24)(int32_t subType, int32_t sendTime, int64_t fromQQ, const char *msg, const char *responseFlag) {

	//CQ_setFriendAddRequest(ac, responseFlag, REQUEST_ALLOW, "");

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=302 ����-Ⱥ���
* subType �����ͣ�1/����������Ⱥ 2/�Լ�(����¼��)������Ⱥ
* msg ����
* responseFlag ������ʶ(����������)
*/
CQEVENT(int32_t, __eventRequest_AddGroup, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, const char *msg, const char *responseFlag) {

	//if (subType == 1) {
	//	CQ_setGroupAddRequestV2(ac, responseFlag, REQUEST_GROUPADD, REQUEST_ALLOW, "");
	//} else if (subType == 2) {
	//	CQ_setGroupAddRequestV2(ac, responseFlag, REQUEST_GROUPINVITE, REQUEST_ALLOW, "");
	//}

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}

/*
* �˵������� .json �ļ������ò˵���Ŀ��������
* �����ʹ�ò˵������� .json ���˴�ɾ�����ò˵�
*/
CQEVENT(int32_t, __menuA, 0)() {
	MessageBoxA(NULL, "����menuA�����������봰�ڣ����߽�������������", "" ,0);
	return 0;
}

CQEVENT(int32_t, __menuB, 0)() {
	MessageBoxA(NULL, "����menuB�����������봰�ڣ����߽�������������", "" ,0);
	return 0;
}
