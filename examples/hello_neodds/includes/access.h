/*
	access관련 헤더
	작성자 : 
	이력
	2010-08-08 : 시작

*/


#if !defined(__ACCESS_H)
#define __ACCESS_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif

typedef struct access_sys_t access_sys_t;

struct access_t
{
	MODULE_COMMON_FIELD
	moduleload_t* p_moduleload;

	char*			psz_access;
	char*			psz_path;
	access_sys_t*	p_sys;
	int				fd;
	data_t*			(*pf_data)(access_t *);
	data_t*			(*pf_data_for_service)(service_t *, access_t *p_access, int spdp_fd, int sedp_fd, int data_fd);
	int				(*pf_getBind)(access_t *);
};

typedef struct access_out_sys_t access_out_sys_t;

struct access_out_t
{
	MODULE_COMMON_FIELD
	moduleload_t*		p_moduleload;
	char*				p_name;
	int					(*pf_write)( access_out_t *, data_t * );
	int					fd;
	int					mtu;
	access_out_sys_t*	p_sys;
};


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	access_t* access_new(module_object_t* p_obj, char* psz_access, char* psz_path);
	DDS_DLL_API	void access_delete(access_t* p_access);
	DDS_DLL_API	access_out_t* access_out_new(module_object_t* p_this, char* psz_access, char* p_name, int fd);
	DDS_DLL_API	void access_out_delete(access_out_t* p_access);
#ifdef __cplusplus
}
#endif

#endif