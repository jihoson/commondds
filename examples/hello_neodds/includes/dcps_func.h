/*
dcps에서 사용되는 함수들 등록...
작성자 :
이력
2010-07-18 : 시작
*/

#if !defined(__DCPS_FUNC_H)
#define __DCPS_FUNC_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif

#define WHERE_TOPICDESCRIPTION(x) (TopicDescription *)(((char*)x)+(int32_t)&x->get_type_name - (int32_t)&x->enable)

#define REMOVE_STRING_SEQ(x)						\
while (x.i_string)									\
	{												\
	FREE(x.pp_string[0]);							\
	REMOVE_ELEM(x.pp_string, x.i_string, 0);		\
	}												\
	x.i_string = 0;									\
	FREE(x.pp_string);

#define BUILTIN_PARTICIPANT_DOMAIN_ID -999


static const Duration_t DURATIOIN_ZERO = { 0, 0 };


#define PARTICIPANTINFO_NAME	"DCPSParticipant"
#define TOPICINFO_NAME			"DCPSTopic"
#define PUBLICATIONINFO_NAME	"DCPSPublication"
#define SUBSCRIPTIONINFO_NAME	"DCPSSubscription"
#define LIVELINESSP2P_NAME		"DCPSLivenessP2P"

#define PARTICIPANTINFO_TYPE   "participantInfoType"
#define TOPICINFO_TYPE         "topicInfoType"
#define PUBLICATIONINFO_TYPE   "publicationInfoType"
#define SUBSCRIPTIONINFO_TYPE  "subscriptionInfoType"
#define LIVELINESSP2PINFO_TYPE "livenessp2pInfoType"

#define BUILTIN_PUBLISHER_PARTITION_QOS "builtin_partition"


enum BUILTIN_TOPIC_ID
{
	PARTICIPANTINFO_ID,
	TOPICINFO_ID,
	PUBLICATIONINFO_ID,
	SUBSCRIPTIONINFO_ID
};

enum _CONDITION_TYPE
{
	NORMAL_CONDITION,
	STATUS_CONDITION,
	QUERY_CONDITION,
	READ_CONDITION,
	GUARD_CONDITION
};

enum ENTITY_TYPE
{
	ENTITY_ENTITY,
	DOMAINPARTICIPANT_ENTITY,
	PUBLISHER_ENTITY,
	SUBSCRIBER_ENTITY,
	TOPIC_ENTITY,
	DATAREADER_ENTITY,
	DATAWRITER_ENTITY
};


struct dds_string
{
	int32_t size;
	char value[256];
};

struct dds_longdouble 
{
	char dds_longdouble_value[16];
};

typedef struct dds_string2
{
	int32_t size;
	char* p_dummy;
}dds_string2;


enum THREAD_TYPE
{
	READER_THREAD,
	WRITER_THREAD
};


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	DomainParticipantFactory* DomainParticipantFactory_get_instance();
	
	DDS_DLL_API	void init_entity(Entity* p_entity);
	DDS_DLL_API	void init_publisher(Publisher* p_publisher);
	DDS_DLL_API	void init_topic(Topic* p_topic);
	DDS_DLL_API	void init_topic_description(TopicDescription* p_topic_description);
	DDS_DLL_API	void init_domain_paticipant(DomainParticipant* p_domain_participant);
	DDS_DLL_API	void init_datawriter(DataWriter* p_datawriter);
	DDS_DLL_API	void init_subscriber(Subscriber* p_subscriber);
	DDS_DLL_API	void init_content_filtered_topic(ContentFilteredTopic* p_topic_init_topic_description);
	DDS_DLL_API	void init_multi_topic(MultiTopic* p_multi_topic);
	DDS_DLL_API	void init_datareader(DataReader* p_datareader);
	DDS_DLL_API	void init_read_condition(ReadCondition* p_read_condition);
	DDS_DLL_API	void init_condition(Condition* p_condition);
	DDS_DLL_API	void init_query_condition(QueryCondition* p_query_condition);
	DDS_DLL_API	void init_status_condition(StatusCondition* p_status_condition);
	DDS_DLL_API	void init_waitset(WaitSet* p_waitset);
	
	DDS_DLL_API	void destroy_entity(Entity* p_entity);
	DDS_DLL_API	void destroy_domain_participant(DomainParticipant* p_domain_participant, bool b_except_domain_paticipant);
	DDS_DLL_API	void destroy_publisher(Publisher* p_publisher);
	DDS_DLL_API	void destroy_subscriber(Subscriber* p_subscriber);
	DDS_DLL_API	void destroy_topic(Topic* p_topic);
	DDS_DLL_API	void destroy_domain_participant_factory(DomainParticipantFactory* p_domain_participant_factory);
	DDS_DLL_API	void destroy_topic_description(TopicDescription* p_topic_description);
	DDS_DLL_API	void destroy_content_filtered_topic(ContentFilteredTopic* p_topic_init_topic_description);
	DDS_DLL_API	void destroy_multi_topic(MultiTopic* p_multi_topic);
	DDS_DLL_API	void destroy_datawriter(DataWriter* p_datawriter);
	DDS_DLL_API	void destroy_datareader(DataReader* p_datareader);
	DDS_DLL_API	void destroy_read_condition(ReadCondition* p_read_condition);
	DDS_DLL_API	void destroy_condition(Condition* p_condition);
	DDS_DLL_API	void destroy_query_condition(QueryCondition* p_query_condition);
	DDS_DLL_API	void destroy_read_condition_except_read_condition(ReadCondition* p_read_condition);
	DDS_DLL_API	void destroy_status_condition(StatusCondition* p_status_condition);
	DDS_DLL_API	void destroy_waitset(WaitSet* p_waitset);

	DDS_DLL_API	ReturnCode_t static_set_default_participant_qos(in_mds DomainParticipantQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_get_default_participant_qos(inout_mds DomainParticipantQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_set_default_publisher_qos(in_mds PublisherQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_get_default_publisher_qos(inout_mds PublisherQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_set_default_subscriber_qos(in_mds SubscriberQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_get_default_subscriber_qos(inout_mds SubscriberQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_set_default_topic_qos(in_mds TopicQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_get_default_topic_qos(inout_mds TopicQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_set_default_datawriter_qos(in_mds DataWriterQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_get_default_datawriter_qos(inout_mds DataWriterQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_set_default_datareader_qos(in_mds DataReaderQos *p_qos);
	DDS_DLL_API	ReturnCode_t static_get_default_datareader_qos(inout_mds DataReaderQos *p_qos);

	DDS_DLL_API	int get_domain_participant_factory_module_id();
	DDS_DLL_API	WaitSet* waitset_new();

	DDS_DLL_API	void dds_quit();
	DDS_DLL_API	bool is_dds_quit();
	DDS_DLL_API	bool is_dds_terminated();
	DDS_DLL_API	void quit();			// BACKWARD_COMPATIBILITY를 위해 유지
	DDS_DLL_API	bool is_quit();			// BACKWARD_COMPATIBILITY를 위해 유지
	DDS_DLL_API	bool is_terminated();		// BACKWARD_COMPATIBILITY를 위해 유지

	// 개체 삭제 전 종료메시지 처리하고 스레드 종료시키는 함수 추가
	DDS_DLL_API	void SendTerminatedMessageAndSetThreadEndFlag(module_t* pFactory);

	DDS_DLL_API	char *get_string(char *p_chars, int *p_size);
	
	DDS_DLL_API	expression_t *expression_parse(const char *expression);
	DDS_DLL_API	void expression_check_field(expression_t *p_expr, FooTypeSupport *p_footypesupport);
	DDS_DLL_API	int set_string_rtps_to_type_support(dds_string2* p_string, char* p_data, int i_parameter_string_size, int packet_size, long offset);
	DDS_DLL_API	long caculate_message_data_type_support_to_rtps(message_t *p_message, FooTypeSupport* p_type_support, char* p_send_value, int i_type_support_size, char* p_value);

	DDS_DLL_API	instanceset_t *instaceset_new(message_t *p_message, uint32_t depth, uint32_t max_samples_per_instance);
	DDS_DLL_API	void insert_instanceset_datareader(DataReader *p_datareader, rtps_cachechange_t *p_rtps_cachechange, message_t *p_message);
	DDS_DLL_API	void insert_instanceset_datawriter(DataWriter *p_datawriter, rtps_cachechange_t *p_rtps_cachechange, message_t *p_message);
	DDS_DLL_API	void instanceset_remove(Entity *p_entity, instanceset_t *p_instaceset);
	DDS_DLL_API	void remove_in_order(Entity* p_entity, message_t* p_message);
	DDS_DLL_API	void remove_in_instanceset(message_t *p_message);

	DDS_DLL_API	ReturnCode_t status_condition_plain_status_set(Entity* p_entity, StatusKind kind);
	DDS_DLL_API	ReturnCode_t data_on_readers_statuscondition(Entity * subscriber_entity);
	DDS_DLL_API	ReturnCode_t data_available_statuscondition(Entity * reader_entity);
	DDS_DLL_API	ReturnCode_t change_DataOnReaders_DataAvailable_status(DataReader* p_datareader);
	DDS_DLL_API	ReturnCode_t change_RequestedDeadlineMissed_status(DataReader* p_datareader, InstanceHandle_t handle);
	DDS_DLL_API	ReturnCode_t change_RequestedIncompatibleQoS_status(DataReader* p_datareader, QosPolicyId_t id);
	DDS_DLL_API	ReturnCode_t change_OfferedIncompatibleQoS_status(DataWriter* p_datawriter, QosPolicyId_t id);
	DDS_DLL_API	ReturnCode_t change_SubscriberMathed_status(DataReader* p_datareader, int current_count, InstanceHandle_t handle);
	DDS_DLL_API	ReturnCode_t change_SubscriberMathed_CurrentCount_status(DataReader* p_datareader, int current_count);
	DDS_DLL_API	ReturnCode_t change_PublicationMathced_status(DataWriter* p_datawriter, int current_count, InstanceHandle_t handle);
	DDS_DLL_API	ReturnCode_t change_publication_mathced_current_count_status(DataWriter* p_datawriter, int current_count);
	DDS_DLL_API	ReturnCode_t change_OfferedDeadlineMissed_status(DataWriter * p_datawriter, InstanceHandle_t handle);
	DDS_DLL_API	ReturnCode_t change_SampleRejected_status(DataReader * p_datareader, SampleRejectedStatusKind reason, InstanceHandle_t handle);
	DDS_DLL_API	ReturnCode_t change_sample_lost_status(DataReader* p_datareader);
	DDS_DLL_API	ReturnCode_t change_topic_status(Topic* p_topic);
	DDS_DLL_API	void init_subscriber_status(Subscriber* p_subscriber);
	DDS_DLL_API	void init_topic_status(Topic* p_topic);
	DDS_DLL_API	void get_key_guid(message_t* p_message, uint8_t* p_data, int size);

	// 각 builtin reader를 domainID로 가져오도록 수정	
	DDS_DLL_API	DataReader* get_builtin_participant_reader(DomainId_t domainID);
	DDS_DLL_API	DataReader* get_builtin_topic_reader(DomainId_t domainID);
	DDS_DLL_API	DataReader* get_builtin_publisher_reader(DomainId_t domainID);
	DDS_DLL_API	DataReader* get_builtin_subscriber_reader(DomainId_t domainID);

	DDS_DLL_API	void get_builtin_participant_data(ParticipantBuiltinTopicData* p_participant_data, void* p_cache);
	DDS_DLL_API	void get_publication_builtin_topic_data(PublicationBuiltinTopicData* p_publication_data, void* p_cache);
	DDS_DLL_API	bool is_matched_remote_publisher(char* p_topic_name, char* p_type_name, void* p_cache);
	DDS_DLL_API	bool is_matched_remote_subscriber(char* p_topic_name, char* p_type_name, void* p_cache);
	DDS_DLL_API	void get_subscription_builtin_topic_data(SubscriptionBuiltinTopicData* p_subscription_data, void* p_cache);
	DDS_DLL_API	void get_builtin_topic_data(TopicBuiltinTopicData* p_topic_data, void* p_cache);
	
	// typecode 개념 추가에 따른 함수 추가
	// TopicBuiltinTopicData 에 topic 의 멤버변수를 저장하는 구조체 추가
	// DIDE-1	
	DDS_DLL_API	void get_builtin_topic_typecode(void* p_topic_typecode, void* p_cache);
	// get_builtin_topic_typecode에 의해 생성된 메모리 삭제하기 위한 함수 추가
	DDS_DLL_API	void release_topic_typecode(BuiltinTopicDataTypeCode * pTopicDataTypeCode);

	DDS_DLL_API	void ignore_writerproxy(void* v_reader, void* v_key);
	DDS_DLL_API	void ignore_writerproxy_guid_prefix(void* v_reader, void* v_key);
	DDS_DLL_API	void ignore_readerproxy(void* v_writer, void* v_key);
	DDS_DLL_API	void ignore_readerproxy_guid_prefix(void* v_writer, void* v_key);

	DDS_DLL_API	void check_new_data_sample_status(Entity* p_entity, instanceset_t* p_instanceset, message_t* p_message);
	DDS_DLL_API	void check_new_data_instance_stautus(Entity* p_entity, instanceset_t* p_instanceset, message_t* p_message);
	DDS_DLL_API	void check_newData_viewStautus(Entity * p_entity, instanceset_t * p_instanceset, message_t *p_message);
	DDS_DLL_API	void check_instanceStatus_disposed(Entity *p_entity, instanceset_t *p_instanceset);
	DDS_DLL_API	void check_instanceStatus_unregister(Entity * p_entity, instanceset_t * p_instanceset);
	DDS_DLL_API	void read_instance_change_sample_status(DataReader* p_datareader, instanceset_t* p_instanceset);
	DDS_DLL_API	void read_instance_change_instance_status(DataReader* p_datareader, instanceset_t* p_instanceset);
	DDS_DLL_API	void read_change_sample_status(DataReader* p_datareader, int i);
	DDS_DLL_API	void read_change_instance_status(DataReader* p_datareader, int i);
	DDS_DLL_API	void take_remove_instance(DataReader * p_datareader, instanceset_t * p_instanceset);
	DDS_DLL_API	void take_instance_change_instance_status(DataReader* p_datareader, instanceset_t* p_instanceset);
	DDS_DLL_API	void take_change_instance_status(DataReader* p_datareader, int i);
	DDS_DLL_API	ReturnCode_t read_condition_set(DataReader* p_datareader, instanceset_t* p_instanceset);
	DDS_DLL_API	ReturnCode_t read_condition_set_from_add_instanceset(DataReader* p_datareader, instanceset_t* p_instanceset, message_t *p_message);
	DDS_DLL_API	ReturnCode_t check_all_samples_sample_status(instanceset_t* p_instanceset);
	DDS_DLL_API	void qosim_dcps_message_ordering_change(DataReader *p_datareader);
		
	DDS_DLL_API	void take_change_instance_status_querycondition(DataReader* p_datareader, message_t *p_message, int i);

	DDS_DLL_API	void set_global_domain_id(const DomainId_t domain_id);
	DDS_DLL_API	DomainId_t get_global_domain_id(void);

	//20161102
	DDS_DLL_API void set_md5_enable(bool bMD5);
	DDS_DLL_API void set_rc4_enable(bool bRC4);

	DDS_DLL_API	int32_t setAvailablePort(int32_t portNum);

	// 다수의 APP이 동시에 실행될 때 Port번호가 중복되는 현상 처리
	DDS_DLL_API	int32_t CheckAvailablePort(int32_t nMaxPortNo, int32_t portNum);	// portNum ~ nMaxPortNo 내의 사용가능한 제일 작은 portNo 반환, -1일경우 가능한 포트 없음.
	DDS_DLL_API	int32_t setAvailablePort2(int32_t nMaxPortNo, int32_t portNum);		// 기존 setAvailablePort() 함수 랩핑, portNum ~ nMaxPortNo 내의 사용가능한 제일 작은 portNo 반환, 가능 포트 없을 경우 종료함.

	DDS_DLL_API void enable_mornitoring(bool isenable);
#ifdef __cplusplus
}
#endif

#endif