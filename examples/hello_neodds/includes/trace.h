/*
	TRACE ���� ���
	�ۼ��� : 
	�̷�
	2010-08-8 : ����

*/

#if !defined(__TRACE_H)
#define __TRACE_H
#endif

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


struct trace_t
{
    MODULE_COMMON_FIELD

	moduleload_t	*p_moduleload;
	void ( *pf_trace ) (trace_t *p_trace, int mode, char *p_str);

	trace_sys_t		*p_sys;
};


#ifdef __cplusplus
extern "C" {
#endif
	// Trace����� domainID�� ���� ��Ī�� �� �ֵ��� ����
	DDS_DLL_API	int	launchTraceModule(module_object_t *p_this, int32_t domainID);
#ifdef __cplusplus
}
#endif
