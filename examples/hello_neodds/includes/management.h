/*
	Management 관련 헤더
	작성자 : 
	이력
	2010-08-8 : 시작

*/

#if !defined(__MANAGEMENT_H)
#define __MANAGEMENT_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


typedef struct management_sys_t management_sys_t;


#ifndef DATAREADER_DEFINE
	#define DATAREADER_DEFINE 1
	typedef struct DataReader DataReader;
#endif


struct management_t
{
	MODULE_COMMON_FIELD
	moduleload_t* p_moduleload;
	void (*message_write)(management_t* p_management, message_t* p_message);
	message_t** (*message_read)(management_t* p_management, DataReader* p_datareader, int* p_size);

	management_sys_t*	p_sys;
};


#ifdef __cplusplus
extern "C" {
#endif
	// management module을 domainID에 따라 런칭할 수 있도록 수정
	DDS_DLL_API	int launch_management_module(module_object_t* p_this, int32_t domainID);
	
	DDS_DLL_API	void message_write(message_t* p_message);
	DDS_DLL_API	message_t** message_read(DataReader* p_datareader, int* p_count);
#ifdef __cplusplus
}
#endif

#endif
