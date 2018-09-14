//연락처 DataBase	
#if 01
#include <iostream>
using namespace std;

#define HASH_SIZE (40000)
typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

struct HASHNODE
{
	char str[5][20];
	HASHNODE * prev[5];
	HASHNODE * next[5];
	HASHNODE() {
		for (int i = 0; i < 5; ++i){
			str[i][0] = 0;
			prev[i] = this;
			next[i] = this;
		}
	}
};

HASHNODE * Htb[5][HASH_SIZE];

void Mstrcpy(char * dest, const char * src)
{
	unsigned int i;
	for (i = 0; src[i] != 0; ++i){
		dest[i] = src[i];
	}
	dest[i] = src[i];
}
int Mstrcmp(const char * a, const char * b)
{
	unsigned int i;
	for (i = 0; a[i] != 0 && b[i] != 0; ++i){
		if (a[i] != b[i]) return a[i] - b[i];
	}
	return 0;
}

//처음 배울 때는 소수 1개만 쓰게 배우지만 //이론적으로 소수 갯수가 많아질수록 해쉬가 고르게 퍼짐
int prime[3] = { 17, 31, 111 };		
unsigned int getHashKey(char * str)
{
	unsigned int mux, result;
	mux = 1; result = 0;
	for (register int i = 0; str[i] != 0; ++i){
		mux *= prime[result % 3];
		result += (mux*str[i]);
	}
	return result % HASH_SIZE;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void InitDB()
{
	for (register int i = 0; i < 5; ++i){
		for (register int j = 0; j < HASH_SIZE; ++j){
			Htb[i][j] = new HASHNODE();
		}
	}
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	HASHNODE * newNode = new HASHNODE();

	Mstrcpy(newNode->str[NAME], name);
	Mstrcpy(newNode->str[NUMBER], number);
	Mstrcpy(newNode->str[BIRTHDAY], birthday);
	Mstrcpy(newNode->str[EMAIL], email);
	Mstrcpy(newNode->str[MEMO], memo);
	
	int key;

	for (register int i = 0; i < 5; ++i){
		key = getHashKey(newNode->str[i]);
		newNode->prev[i] = Htb[i][key];
		newNode->next[i] = Htb[i][key]->next[i];
		newNode->prev[i]->next[i] = newNode;
		newNode->next[i]->prev[i] = newNode;
	}
}

int Delete(FIELD field, char* str)
{
	HASHNODE * p;
	int key = getHashKey(str);
	int count;

	count = 0;
	p = Htb[field][key]->next[field];
	while (p != Htb[field][key]){	
		if (Mstrcmp(p->str[field], str) == 0){
			//삭제
			for (int i = 0; i < 5; ++i){
				p->prev[i]->next[i] = p->next[i];
				p->next[i]->prev[i] = p->prev[i];
			}			
			//delete p;	//이거 지우니까 돌아가긴 하네?
			++count;
		}
		p = p->next[field];	
	}
	return count;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{	
	HASHNODE * p;
	int key = getHashKey(str);
	int key2 = getHashKey(changestr);
	int count;

	count = 0;
	p = Htb[field][key]->next[field];
	while (p != Htb[field][key]) {		
		if (Mstrcmp(p->str[field], str) == 0) {
			//수정
			Mstrcpy(p->str[changefield], changestr);
			//기존노드에서 분리
			for (int i = 0; i < 5; ++i){
				p->prev[i]->next[i] = p->next[i];
				p->next[i]->prev[i] = p->prev[i];
			}
			//새롭게 붙임
			Add(p->str[0], p->str[1], p->str[2], p->str[3], p->str[4]);

			++count;
		}
		p = p->next[field];
	}
	return count;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	HASHNODE * p;
	int key = getHashKey(str);

	result.count = 0;	
	p = Htb[field][key]->next[field];
	while (p != Htb[field][key]) {
		if (Mstrcmp(p->str[field], str) == 0) {
			++result.count;
			Mstrcpy(result.str, p->str[ret_field]);
		}		
		p = p->next[field];
	}
	return result;
}

#endif
