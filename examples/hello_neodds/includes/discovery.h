/*
	��Ŀ���� ���� ���
	�ۼ��� : 
	�̷�
	2010-09-27 : ����

*/

#if !defined(__DISCOVERY_H)
#define __DISCOVERY_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


typedef struct discovery_sys_t discovery_sys_t;

struct discovery_t
{
    MODULE_COMMON_FIELD

	moduleload_t*	p_moduleload;

	discovery_sys_t*	p_sys;
};


#ifdef __cplusplus
extern "C" {
#endif
	// domainID�� ���� ��Ī�ϵ��� ����
	DDS_DLL_API	int launch_discovery_module(module_object_t* p_this, int32_t domain_id);
#ifdef __cplusplus
}
#endif

#endif