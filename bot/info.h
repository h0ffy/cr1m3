#ifndef __INFO_H_FILE
#define __INFO_H_FILE


struct info_struct {
	char *volume_serial;
	char *user_name;
	char *computer_name;
	char *os_version;
};

typedef struct info_struct info;



//public
int __get_info(info *s_info);

//private
int __get_volume_serial(info *s_info);
int __get_user_name(info *s_info);
int __get_computer_name(info *s_info);
int __get_windows_version(info *s_info);


#endif __INFO_H_FILE
