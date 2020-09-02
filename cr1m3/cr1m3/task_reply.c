#include "task_reply.h"
#include "api.h"


TASK_REPLY task_001[MAX_TASK_REPLY];
int last_task=0;
int last_push=0;


/**
 * @brief push reply in task
 * @param reply string with reply
 * @returns next task id
**/
int __push_reply(char *reply, int option) {

	while(last_task>=MAX_TASK_REPLY) {
		_Sleep(2000);
	}

	task_001[last_task].buff = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 1030);
	task_001[last_task].token = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000008, 35);

	_lstrcpynA(task_001[last_task].buff, reply, _lstrlenA(reply)+1); 
	task_001[last_task].buff_len = _lstrlenA(reply)+1;
	task_001[last_task].status = 1;
	task_001[last_task].opt = option;	
	
	last_task++;

	return(last_task);
}

/**
 * @brief pop reply in task
 * @param reply out put string with reply
 * @returns next push id
**/
int __pop_reply(char *reply) {
	int option;
	
	if(last_task<=last_push) {
		last_push=0;
		last_task=0;
		return -1;
	}	
	
	_lstrcpynA(reply, task_001[last_push].buff, task_001[last_push].buff_len);
	//_lstrcpynA(token, task_001[last_push].token, 32);
	option = task_001[last_push].opt;
	_HeapFree(_GetProcessHeap(), 0x00000001, task_001[last_push].buff);
	_HeapFree(_GetProcessHeap(), 0x00000001, task_001[last_push].token);
	task_001[last_push].status=0;
	task_001[last_push].opt=0;


	last_push++;
	return(0);
}
