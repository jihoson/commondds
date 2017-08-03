/*
	UTIL 관련 헤더파일

	작성자 : 
	이력
	2010-08-5: 시작
*/

#if !defined(__UTIL_H)
#define __UTIL_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	FILE* open_file(const char* psz_file_path, const char* psz_mode);
	DDS_DLL_API	int close_file(FILE* p_file);

	DDS_DLL_API	size_t strlcpy(char *tgt, const char *src, size_t bufsize);
	DDS_DLL_API	int vasprintf(char **strp, const char *fmt, va_list ap);
	DDS_DLL_API	int asprintf(char **strp, const char *fmt, ...);

	DDS_DLL_API	char* get_default_local_address();
	DDS_DLL_API	bool get_allowed_nic_list();	//youngjin.150120
	
	DDS_DLL_API	void set_string(dds_string* p_string, char* p_value);
	DDS_DLL_API	char* get__string(dds_string* p_string);

	DDS_DLL_API	void free_ip_string();
#ifdef __cplusplus
}
#endif

#endif