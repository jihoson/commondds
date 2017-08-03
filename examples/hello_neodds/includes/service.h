/*
	서비스 관련 헤더
	작성자 : 
	이력
	2010-07-24 : 시작 일단 윈도우만 우선 선언 어느 정도 되면 다른 플랫폼 추가

*/

#if !defined(__SERVICE_H)
#define __SERVICE_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


typedef struct service_sys_t service_sys_t;


#ifndef ENTITY_DEFINE
        #define ENTITY_DEFINE 1
        typedef struct Entity Entity;
#endif

#ifndef DOMAINPARTICIPANT_DEFINE
        #define DOMAINPARTICIPANT_DEFINE 1
        typedef struct DomainParticipant DomainParticipant;
#endif

#ifndef RTPS_WRITER_T_DEFINE
        #define RTPS_WRITER_T_DEFINE 1
        typedef struct rtps_writer_t rtps_writer_t;
#endif

		
typedef long InstanceHandle_t;		// Linux에서는 64bit/32bit 모두 long값이 pointer 크기(8)과 같다.


#ifndef DATAREADER_DEFINE
	#define DATAREADER_DEFINE 1
	typedef struct DataReader DataReader;
#endif

#ifndef TIME_STRUCT_T
	#define TIME_STRUCT_T
	typedef struct Time_t Time_t;
	struct Time_t 
	{
		int32_t sec;
		uint32_t nanosec;
	};

	typedef struct Duration_t 
	{
		int32_t sec;
		uint32_t nanosec;
	}Duration_t;
#endif


enum SERVICE_ACCESS_OUT_TYPE
{
	SPDP_OUT_TYPE,
	SEDP_OUT_TYPE,
	DEFAULT_OUT_TYPE
};


#ifndef DCPS_STATE_DEFINE
#define DCPS_STATE_DEFINE 1

// Application에서 참조하는 header 파일에서 VS2013_x64 적용해야함.
typedef uint32_t		SampleStateKind;
typedef uint32_t		SampleStateMask;
typedef uint32_t		ViewStateKind;
typedef uint32_t		ViewStateMask;
typedef uint32_t		InstanceStateKind;
typedef uint32_t		InstanceStateMask;

// Sample states to support reads
static const SampleStateKind READ_SAMPLE_STATE = 0x0001 << 0;
static const SampleStateKind NOT_READ_SAMPLE_STATE = 0x0001 << 1;
static const SampleStateMask ANY_SAMPLE_STATE = 0xffff;

// View states to support reads
static const ViewStateKind NEW_VIEW_STATE = 0x0001 << 0;
static const ViewStateKind NOT_NEW_VIEW_STATE = 0x0001 << 1;
static const ViewStateMask ANY_VIEW_STATE = 0xffff;

// Instance states to support reads
static const InstanceStateKind ALIVE_INSTANCE_STATE = 0x0001 << 0;
static const InstanceStateKind NOT_ALIVE_DISPOSED_INSTANCE_STATE = 0x0001 << 1;
static const InstanceStateKind NOT_ALIVE_NO_WRITERS_INSTANCE_STATE = 0x0001 << 2;
static const InstanceStateMask ANY_INSTANCE_STATE = 0xffff;
static const InstanceStateMask NOT_ALIVE_INSTANCE_STATE = 0x006;

#endif


struct service_t
{
    MODULE_COMMON_FIELD

	moduleload_t*	p_moduleload;
	
	int				(*add_entity)(module_object_t* p_this, Entity* p_entity);
	int				(*remove_entity)(module_object_t* p_this, Entity* p_entity);
	void*			(*write)(module_object_t * p_this, rtps_writer_t *p_writer, message_t *p_message);
	void*			(*dispose)(module_object_t * p_this, rtps_writer_t *p_writer, void *v_data, InstanceHandle_t handle);
	void*			(*unregister)(module_object_t * p_this, rtps_writer_t *p_writer, void *v_data, InstanceHandle_t handle, bool b_dispose);
	access_out_t*	(*getaccessout)(module_object_t * p_this, int type);
	message_t**		(*read)(module_object_t * p_this, DataReader *p_datareader, int32_t max_samples, int *p_size, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);
	message_t**		(*take)(module_object_t * p_this, DataReader *p_datareader, int32_t max_samples, int *p_size, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);
	message_t**		(*read_instance)(module_object_t * p_this, DataReader *p_datareader, InstanceHandle_t handle, int32_t max_samples, int *p_size, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);
	message_t**		(*take_instance)(module_object_t * p_this, DataReader *p_datareader, InstanceHandle_t handle, int32_t max_samples, int *p_size, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);
	void*			(*write_timestamp)(module_object_t * p_this, rtps_writer_t *p_writer, message_t *p_message, Time_t source_timestamp);
	void*			(*dispose_timestamp)(module_object_t * p_this, rtps_writer_t *p_writer, void *v_data, InstanceHandle_t handle, Time_t source_timestamp);
	void*			(*unregister_timestamp)(module_object_t * p_this, rtps_writer_t *p_writer, void *v_data, InstanceHandle_t handle, Time_t source_timestamp);
	
	int				(*add_thread)(module_object_t* p_this, Entity* p_entity);

	data_fifo_t*	p_network_fifo;
	service_sys_t*	p_sys;
	
	// Read관련인 NetworkThread만 종료시 기존 b_end 사용시 ThreadWrite2도 중지되어 종료 메시지를 못보내기 때문에 NetworkThread만 먼저 죽이기 위해 별도로 구성
	bool b_end_for_NetworkThread;
};


#ifdef __cplusplus
extern "C" {
#endif
// Service 모듈을 domainID에 따라 런칭할 수 있도록 수정
	DDS_DLL_API	int launch_service_module(module_object_t* p_this, int32_t domainID);
	
	DDS_DLL_API	void add_entity_to_service(Entity* p_entity);
	DDS_DLL_API	void remove_entity_to_service(Entity* p_entity);
	
	// 각 서비스모듈 함수에 DomainID로 처리할 수 있도록 수정
	DDS_DLL_API	void write_to_service(rtps_writer_t* p_rtps_writer, message_t* p_message, int32_t domainID);
	DDS_DLL_API	void dispose_to_service(rtps_writer_t* p_rtps_writer, void* v_data, InstanceHandle_t handle, int32_t domainID);
	DDS_DLL_API	void dispose_to_service_timestamp(rtps_writer_t* p_rtps_writer, void* v_data, InstanceHandle_t handle, Time_t source_timestamp, int32_t domainID);
	DDS_DLL_API	void unregister_to_service(rtps_writer_t* p_rtps_writer, void* v_data, InstanceHandle_t handle, bool b_dispose, int32_t domainID);
	DDS_DLL_API	void unregister_to_service_timestamp(rtps_writer_t* p_rtps_writer, void* v_data, InstanceHandle_t handle, Time_t source_timestamp, int32_t domainID);

	// domainID로 서비스 모듈을 얻어올 수 있도록 함수 추가
	DDS_DLL_API	service_t * getServiseModule(int32_t domainID);
	
	DDS_DLL_API	message_t** message_read_from_service(DataReader* p_datareader, int32_t max_samples, int* p_count, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);
	DDS_DLL_API	message_t** message_take_from_service(DataReader* p_datareader, int32_t max_samples, int* p_count, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);
	DDS_DLL_API	message_t** message_read_instance_from_service(DataReader* p_datareader, InstanceHandle_t handle, int32_t max_samples, int* p_count, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);
	DDS_DLL_API	message_t** message_take_instance_from_service(DataReader* p_datareader, InstanceHandle_t handle, int32_t max_samples, int* p_count, SampleStateMask sample_states, ViewStateMask view_states, InstanceStateMask instance_states);

	DDS_DLL_API	void add_thread_to_service(Entity* p_entity);
#ifdef __cplusplus
}
#endif

// Data Frag 기준 변경. 기존(30000bytes) -> 현재(63K, 64512bytes).
#define DEFAULT_MTU 64512

#endif
