/*
이 파일은 OMG-DDS-07-0101.pdf 파일을 참고하여, 만든 헤더 파일이며,
문서의 7.2.3 DCPS PSM : IDL에 나와 있는 내용을 바탕으로 작성되었다.

작성자 :

이력...
2010-07-22 : 시작
2010-07-23 : FooData 이전까지 선언 완료.

*/

#if !defined(__CPSDCPS_H)
#define __CPSDCPS_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


static Duration_t TIME_ZERO = { 0, 0 };
static Duration_t TIME_INVALID = { -1, 0xffffffff };
static Duration_t TIME_INFINITE = { 0x7fffffff, 0xffffffff };


#define in_mds
#define inout_mds
typedef  char* string_mds;


#ifndef __cplusplus
typedef int SampleRejectedStatusKind;
typedef int DurabilityQosPolicyKind;
typedef int PresentationQosPolicyAccessScopeKind;
typedef int OwnershipQosPolicyKind;
typedef int LivelinessQosPolicyKind;
typedef int ReliabilityQosPolicyKind;
typedef int DestinationOrderQosPolicyKind;
typedef int HistoryQosPolicyKind;
#endif


#ifndef TIME_STRUCT_T
#define TIME_STRUCT_T
typedef struct Time_t Time_t;
struct Time_t {
	long sec;
	unsigned long nanosec;
};
typedef struct Duration_t {
	long sec;
	unsigned long nanosec;
}Duration_t;
#endif

typedef struct BuiltinTopicKey_t BuiltinTopicKey_t;
typedef struct QosPolicyCount QosPolicyCount;

#ifndef ENTITY_DEFINE
#define ENTITY_DEFINE 1
typedef struct Entity Entity;
#endif
#ifndef TOPIC_DEFINE
#define TOPIC_DEFINE 1
typedef struct Topic Topic;
#endif

#ifndef PUBLISHER_DEFINE
#	define PUBLISHER_DEFINE 1
typedef struct Publisher Publisher;
#endif

#ifndef DOMAINPARTICIPANT_DEFINE
#define DOMAINPARTICIPANT_DEFINE 1
typedef struct DomainParticipant DomainParticipant;
#endif
typedef struct DomainParticipantFactory DomainParticipantFactory;
#ifndef DATAREADER_DEFINE
#define DATAREADER_DEFINE 1
typedef struct DataReader DataReader;
#endif
#ifndef DATAWRITER_DEFINE
#define DATAWRITER_DEFINE 1
typedef struct DataWriter DataWriter;
#endif

#ifndef SUBSCRIBER_DEFINE
#	define SUBSCRIBER_DEFINE 1
typedef struct Subscriber Subscriber;
#endif

typedef struct TopicDescription TopicDescription;
typedef struct ContentFilteredTopic ContentFilteredTopic;
typedef struct MultiTopic MultiTopic;
typedef struct ParticipantBuiltinTopicData ParticipantBuiltinTopicData;
typedef struct TopicBuiltinTopicData TopicBuiltinTopicData;
typedef struct SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData;
typedef struct PublicationBuiltinTopicData PublicationBuiltinTopicData;

#ifndef SAMPLEINFO_DEFINE
typedef struct SampleInfo SampleInfo;
#	define SAMPLEINFO_DEFINE 1
#endif

typedef struct Foo Foo;

typedef struct InconsistentTopicStatus InconsistentTopicStatus;
typedef struct LivelinessChangedStatus LivelinessChangedStatus;
typedef struct LivelinessLostStatus LivelinessLostStatus;
typedef struct OfferedDeadlineMissedStatus OfferedDeadlineMissedStatus;
typedef struct OfferedIncompatibleQosStatus OfferedIncompatibleQosStatus;
typedef struct PublicationMatchedStatus PublicationMatchedStatus;
typedef struct RequestedDeadlineMissedStatus RequestedDeadlineMissedStatus;
typedef struct RequestedIncompatibleQosStatus RequestedIncompatibleQosStatus;
typedef struct SampleRejectedStatus SampleRejectedStatus;
typedef struct SubscriptionMatchedStatus SubscriptionMatchedStatus;
typedef struct SampleLostStatus	SampleLostStatus;

typedef struct Condition Condition;
typedef struct GuardCondition GuardCondition;
typedef struct StatusCondition StatusCondition;
typedef struct ReadCondition ReadCondition;
typedef struct QueryCondition QueryCondition;

#ifndef WAITSET_DEFINE
#define WAITSET_DEFINE 1
typedef struct WaitSet WaitSet;
#endif

typedef struct EntityFactoryQosPolicy EntityFactoryQosPolicy;
typedef struct UserDataQosPolicy UserDataQosPolicy;
typedef struct TopicDataQosPolicy TopicDataQosPolicy;
typedef struct GroupDataQosPolicy GroupDataQosPolicy;
typedef struct TransportPriorityQosPolicy TransportPriorityQosPolicy;
typedef struct LifespanQosPolicy LifespanQosPolicy;
typedef struct DurabilityQosPolicy DurabilityQosPolicy;
typedef struct ReaderDataLifecycleQosPolicy ReaderDataLifecycleQosPolicy;
typedef struct DurabilityServiceQosPolicy DurabilityServiceQosPolicy;
typedef struct DeadlineQosPolicy DeadlineQosPolicy;
typedef struct LatencyBudgetQosPolicy LatencyBudgetQosPolicy;
typedef struct LivelinessQosPolicy LivelinessQosPolicy;
typedef struct ReliabilityQosPolicy ReliabilityQosPolicy;
typedef struct DestinationOrderQosPolicy DestinationOrderQosPolicy;
typedef struct HistoryQosPolicy HistoryQosPolicy;
typedef struct ResourceLimitsQosPolicy ResourceLimitsQosPolicy;
typedef struct OwnershipQosPolicy OwnershipQosPolicy;
typedef struct OwnershipStrengthQosPolicy OwnershipStrengthQosPolicy;
typedef struct WriterDataLifecycleQosPolicy WriterDataLifecycleQosPolicy;
typedef struct PresentationQosPolicy PresentationQosPolicy;
typedef struct PartitionQosPolicy PartitionQosPolicy;
typedef struct TimeBasedFilterQosPolicy TimeBasedFilterQosPolicy;

typedef struct PublisherQos PublisherQos;
typedef struct SubscriberQos SubscriberQos;
typedef struct TopicQos TopicQos;
typedef struct DomainParticipantQos DomainParticipantQos;
typedef struct DomainParticipantFactoryQos DomainParticipantFactoryQos;
typedef struct DataWriterQos DataWriterQos;
typedef struct DataReaderQos DataReaderQos;

typedef struct RxOQos RxOQos;
typedef struct SubscriberListener SubscriberListener;
typedef struct TopicListener TopicListener;
typedef struct DomainParticipantListener DomainParticipantListener;
typedef struct DataWriterListener DataWriterListener;
typedef struct DataReaderListener DataReaderListener;

typedef struct TopicStatus TopicStatus;
typedef struct DataWriterStatus DataWriterStatus;
typedef struct DataReaderStatus DataReaderStatus;

typedef struct SubscriberListenerStatusChangedFlag SubscriberListenerStatusChangedFlag;
typedef struct TopicListenerStatusChangedFlag TopicListenerStatusChangedFlag;
typedef struct DataWriterListenerStatusChangedFlag DataWriterListenerStatusChangedFlag;
typedef struct DataReaderListenerStatusChangedFlag DataReaderListenerStatusChangedFlag;

/////////////////// DCPS PSM : IDL  //////////////////////////////////

#define DOMAINID_TYPE_NATIVE int32_t

#define HANDLE_NIL_NATIVE 0
#define BUILTIN_TOPIC_KEY_TYPE_NATIVE int32_t
#define TheParticipantFactory
#define PARTICIPANT_QOS_DEFAULT
#define TOPIC_QOS_DEFAULT
#define PUBLISHER_QOS_DEFAULT
#define SUBSCRIBER_QOS_DEFAULT
#define DATAWRITER_QOS_DEFAULT
#define DATAREADER_QOS_DEFAULT
#define DATAWRITER_QOS_USE_TOPIC_QOS
#define DATAREADER_QOS_USE_TOPIC_QOS

//////////////////  modules DDS ////////////////////////////////////

typedef DOMAINID_TYPE_NATIVE DomainId_t;

// Linux에서는 64bit/32bit 모두 long값이 pointer 크기(8)과 같다.
typedef long InstanceHandle_t;


struct BuiltinTopicKey_t
{	
	BUILTIN_TOPIC_KEY_TYPE_NATIVE value[4];
};


typedef struct InstanceHandleSeq
{
	int32_t i_seq;
	InstanceHandle_t **pp_instancehandle;
} InstanceHandleSeq;


static InstanceHandleSeq INIT_INSTANCESEQ = { 0, NULL };

typedef int32_t ReturnCode_t;
typedef int32_t QosPolicyId_t;

typedef struct StringSeq StringSeq;


struct StringSeq
{
	int32_t i_string;
	string_mds* pp_string;
};


static const InstanceHandle_t HANDLE_NIL = HANDLE_NIL_NATIVE;

static const int32_t LENGTH_UNLIMITED_RELIABLE = 256;

static const int32_t LENGTH_UNLIMITED = -1;
static const int32_t DURATION_INFINITE_SEC = 0x7fffffff;
static const uint32_t DURATION_INFINITE_NSEC = 0x7fffffff;
static const int32_t DURATION_ZERO_SEC = 0;
static const uint32_t DURATION_ZERO_NSEC = 0;
static const int32_t TIME_INVALID_SEC = -1;
static const uint32_t TIME_INVALID_NSEC = 0xffffffff;

// ----------------------------------------------------------------------
// Return codes
// ----------------------------------------------------------------------
static const ReturnCode_t RETCODE_OK = 0;
static const ReturnCode_t RETCODE_ERROR = 1;
static const ReturnCode_t RETCODE_UNSUPPORTED = 2;
static const ReturnCode_t RETCODE_BAD_PARAMETER = 3;
static const ReturnCode_t RETCODE_PRECONDITION_NOT_MET = 4;
static const ReturnCode_t RETCODE_OUT_OF_RESOURCES = 5;
static const ReturnCode_t RETCODE_NOT_ENABLED = 6;
static const ReturnCode_t RETCODE_IMMUTABLE_POLICY = 7;
static const ReturnCode_t RETCODE_INCONSISTENT_POLICY = 8;
static const ReturnCode_t RETCODE_ALREADY_DELETED = 9;
static const ReturnCode_t RETCODE_TIMEOUT = 10;
static const ReturnCode_t RETCODE_NO_DATA = 11;
static const ReturnCode_t RETCODE_ILLEGAL_OPERATION = 12;

// ----------------------------------------------------------------------
// Status to support listeners and conditions
// ----------------------------------------------------------------------

typedef uint32_t StatusKind;
typedef uint32_t StatusMask; // bit-mask StatusKind
static const StatusKind INCONSISTENT_TOPIC_STATUS = 0x0001 << 0;
static const StatusKind OFFERED_DEADLINE_MISSED_STATUS = 0x0001 << 1;
static const StatusKind REQUESTED_DEADLINE_MISSED_STATUS = 0x0001 << 2;
static const StatusKind OFFERED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 5;
static const StatusKind REQUESTED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 6;
static const StatusKind SAMPLE_LOST_STATUS = 0x0001 << 7;
static const StatusKind SAMPLE_REJECTED_STATUS = 0x0001 << 8;
static const StatusKind DATA_ON_READERS_STATUS = 0x0001 << 9;
static const StatusKind DATA_AVAILABLE_STATUS = 0x0001 << 10;
static const StatusKind LIVELINESS_LOST_STATUS = 0x0001 << 11;
static const StatusKind LIVELINESS_CHANGED_STATUS = 0x0001 << 12;
static const StatusKind PUBLICATION_MATCHED_STATUS = 0x0001 << 13;
static const StatusKind SUBSCRIPTION_MATCHED_STATUS = 0x0001 << 14;
static const StatusKind ALL_ENABLE_STATUS = 0xFFFF;

struct InconsistentTopicStatus
{
	int32_t total_count;
	int32_t total_count_change;
};

struct SampleLostStatus
{
	int32_t total_count;
	int32_t total_count_change;
};

enum SampleRejectedStatusKind
{
	NOT_REJECTED,
	REJECTED_BY_INSTANCES_LIMIT,
	REJECTED_BY_SAMPLES_LIMIT,
	REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
};

struct SampleRejectedStatus
{
	int32_t total_count;
	int32_t total_count_change;
	SampleRejectedStatusKind last_reason;
	InstanceHandle_t last_instance_handle;
};

struct LivelinessLostStatus
{
	int32_t total_count;
	int32_t total_count_change;
};


struct LivelinessChangedStatus
{
	int32_t alive_count;
	int32_t not_alive_count;
	int32_t alive_count_change;
	int32_t not_alive_count_change;
	InstanceHandle_t last_publication_handle;
};

struct OfferedDeadlineMissedStatus
{
	int32_t total_count;
	int32_t total_count_change;
	InstanceHandle_t last_instance_handle;
};

struct RequestedDeadlineMissedStatus
{
	int32_t total_count;
	int32_t total_count_change;
	InstanceHandle_t last_instance_handle;
};

struct QosPolicyCount
{
	QosPolicyId_t policy_id;
	int32_t count;
};

typedef QosPolicyCount* QosPolicyCountSeq;

struct OfferedIncompatibleQosStatus
{
	int32_t total_count;
	int32_t total_count_change;
	QosPolicyId_t last_policy_id;
	QosPolicyCountSeq policies;
};

struct RequestedIncompatibleQosStatus
{
	int32_t total_count;
	int32_t total_count_change;
	QosPolicyId_t last_policy_id;
	QosPolicyCountSeq policies;
};

struct PublicationMatchedStatus
{
	int32_t total_count;
	int32_t total_count_change;
	int32_t current_count;
	int32_t current_count_change;
	InstanceHandle_t last_subscription_handle;
};


struct SubscriptionMatchedStatus
{
	int32_t total_count;
	int32_t total_count_change;
	int32_t current_count;
	int32_t current_count_change;
	InstanceHandle_t last_publication_handle;
};

// ----------------------------------------------------------------------
// Listeners
// ----------------------------------------------------------------------

typedef struct DataReaderSeq
{
	int i_seq;
	DataReader** pp_datareaders;
} DataReaderSeq;


#define LISTENER_BODY \
	int	not_used;

struct Listener
{
	LISTENER_BODY
};


#define TOPICLISTENER_BODY \
	void(*on_inconsistent_topic)(in_mds Topic *the_topic, in_mds InconsistentTopicStatus *status);

struct TopicListener
{
	LISTENER_BODY
	TOPICLISTENER_BODY
};

struct TopicStatus
{
	InconsistentTopicStatus inconsistent_topic;
};

struct TopicListenerStatusChangedFlag
{
	bool b_inconsistent_topic_status_changed_flag;
};


#define DATAWRITERLISTENER_BODY\
	void(*on_offered_deadline_missed)(in_mds DataWriter *writer, in_mds OfferedDeadlineMissedStatus *status); \
	void(*on_offered_incompatible_qos)(in_mds DataWriter *writer, in_mds OfferedIncompatibleQosStatus *status); \
	void(*on_liveliness_lost)(in_mds DataWriter *writer, in_mds LivelinessLostStatus *status); \
	void(*on_publication_matched)(in_mds DataWriter *writer, in_mds PublicationMatchedStatus *status);

struct DataWriterListener
{
	LISTENER_BODY
	DATAWRITERLISTENER_BODY
};

struct DataWriterStatus
{
	OfferedDeadlineMissedStatus offered_deadline_missed;
	OfferedIncompatibleQosStatus offered_incompatible_qos;
	LivelinessLostStatus liveliness_lost;
	PublicationMatchedStatus publication_matched;

};

struct DataWriterListenerStatusChangedFlag
{
	bool b_liveliness_lost_status_changed_flag; \
	bool b_offered_deadline_missed_status_changed_flag; \
	bool b_offered_incompatible_qos_status_changed_flag; \
	bool b_publication_matched_status_changed_flag; \
};

typedef struct DataWriterListener PublisherListener;


#define DATAREADERLISTENER_BODY \
	void(*on_requested_deadline_missed)(in_mds DataReader *the_reader, in_mds RequestedDeadlineMissedStatus *status); \
	void(*on_requested_incompatible_qos)(in_mds DataReader *the_reader, in_mds RequestedIncompatibleQosStatus *status); \
	void(*on_sample_rejected)(in_mds DataReader *the_reader, in_mds SampleRejectedStatus *status); \
	void(*on_liveliness_changed)(in_mds DataReader *the_reader, in_mds LivelinessChangedStatus *status); \
	void(*on_data_available)(in_mds DataReader *p_reader); \
	void(*on_subscription_matched)(in_mds DataReader *the_reader, in_mds SubscriptionMatchedStatus *status); \
	void(*on_sample_lost)(in_mds DataReader *the_reader, in_mds SampleLostStatus *status);


typedef void(*CALLBACK_FUNC)(void*);
//typedef void(*CALLBACK_FUNC)(LPCTSTR lpTopicName, UINT nTopicSize, void* pData);


struct DataReaderListener
{
	LISTENER_BODY\
	DATAREADERLISTENER_BODY
	CALLBACK_FUNC m_CallBack;
};

struct DataReaderStatus
{
	RequestedDeadlineMissedStatus requested_deadline_missed;
	RequestedIncompatibleQosStatus requested_incompatible_qos;
	SampleRejectedStatus sample_rejected;
	LivelinessChangedStatus liveliness_changed;
	SubscriptionMatchedStatus subscriber_matched;
	SampleLostStatus sample_lost;
};

struct DataReaderListenerStatusChangedFlag
{
	bool	b_sample_rejected_status_changed_flag; \
	bool	b_liveliness_changed_status_changed_flag; \
	bool	b_requested_deadline_missed_status_changed_flag; \
	bool	b_requested_incompatible_qos_status_changed_flag; \
	bool	b_data_available_status_changed_flag; \
	bool	b_sample_lost_status_changed_flag; \
	bool	b_subscription_matched_status_changed_flag; \
};


#define SUBSCRIBERLISTENER_BODY \
	DATAREADERLISTENER_BODY\
	void(*on_data_on_readers)(in_mds Subscriber *p_subscriber); \

struct SubscriberListener
{
	LISTENER_BODY\
	SUBSCRIBERLISTENER_BODY
};

struct SubscriberListenerStatusChangedFlag
{
	bool b_data_on_readers_status_changed_flag;
};

struct DomainParticipantListener
{
	LISTENER_BODY
	TOPICLISTENER_BODY
	DATAWRITERLISTENER_BODY
	SUBSCRIBERLISTENER_BODY
};

// ----------------------------------------------------------------------
// Conditions
// ----------------------------------------------------------------------

#define CONDITION_BODY\
	bool(*get_trigger_value)(); \
	bool	b_trigger_value;		\
	uint32_t		condition_type; \
	WaitSet	*p_waitset;

struct Condition
{
	CONDITION_BODY
};

typedef struct ConditionSeq
{
	int32_t i_seq;
	Condition** pp_conditions;
} ConditionSeq;

static ConditionSeq INIT_CONDITIONSEQ = { 0, NULL };

struct WaitSet
{
	ReturnCode_t(*wait)(WaitSet* p_waitSet, inout_mds ConditionSeq *p_active_conditions, in_mds Duration_t timeout);
	ReturnCode_t(*attach_condition)(WaitSet* p_waitSet, in_mds Condition *p_cond);
	ReturnCode_t(*detach_condition)(WaitSet* p_waitSet, in_mds Condition *p_cond);
	ReturnCode_t(*get_conditions)(WaitSet* p_waitSet, inout_mds ConditionSeq *p_attached_conditions);
	mutex_t		waitset_lock;
	int32_t		i_conditions;
	Condition** pp_conditions;
	cond_t	 	waitset_wait;
};

struct GuardCondition
{
	CONDITION_BODY
	ReturnCode_t(*set_trigger_value)(GuardCondition *p_guardcondition, in_mds bool value);
};

struct StatusCondition
{
	CONDITION_BODY
	StatusMask(*get_enabled_statuses)(StatusCondition* p_status_condition);
	ReturnCode_t(*set_enabled_statuses)(StatusCondition* p_status_condition, in_mds StatusMask mask);
	Entity* (*get_entity)(StatusCondition* p_status_condition);
	
	StatusMask enabled_statuses;
	Entity* p_entity;
};


#define READCONDITION_BODY\
	CONDITION_BODY\
	SampleStateMask(*get_sample_state_mask)(ReadCondition* p_readcondition);		\
	ViewStateMask(*get_view_state_mask)(ReadCondition* p_readcondition);			\
	InstanceStateMask(*get_instance_state_mask)(ReadCondition* p_readcondition);	\
	DataReader *(*get_datareader)(ReadCondition* p_readcondition);					\
	SampleStateMask	l_sampleStateMask;												\
	ViewStateMask	l_viewStateMask;												\
	InstanceStateMask	l_instanceStateMask;										\
	DataReader	*p_datareader;

struct ReadCondition
{
	READCONDITION_BODY
};

typedef struct expression_t expression_t;

struct QueryCondition
{
	READCONDITION_BODY
	string_mds(*get_query_expression)(QueryCondition* p_queryCondition);
	ReturnCode_t(*get_query_parameters)(QueryCondition* p_queryCondition, inout_mds StringSeq *p_query_parameters);
	ReturnCode_t(*set_query_parameters)(QueryCondition* p_queryCondition, in_mds StringSeq *p_query_parameters);

	string_mds query_expression;
	StringSeq query_parameters;
	expression_t *p_expr;
	FooTypeSupport *p_typeSupport;
};

// ----------------------------------------------------------------------
// Qos
// ----------------------------------------------------------------------
static const string_mds USERDATA_QOS_POLICY_NAME = (const string_mds)"UserData";
static const string_mds DURABILITY_QOS_POLICY_NAME = (const string_mds)"Durability";
static const string_mds PRESENTATION_QOS_POLICY_NAME = (const string_mds)"Presentation";
static const string_mds DEADLINE_QOS_POLICY_NAME = (const string_mds)"Deadline";
static const string_mds LATENCYBUDGET_QOS_POLICY_NAME = (const string_mds)"LatencyBudget";
static const string_mds OWNERSHIP_QOS_POLICY_NAME = (const string_mds)"Ownership";
static const string_mds OWNERSHIPSTRENGTH_QOS_POLICY_NAME = (const string_mds)"OwnershipStrength";
static const string_mds LIVELINESS_QOS_POLICY_NAME = (const string_mds)"Liveliness";
static const string_mds TIMEBASEDFILTER_QOS_POLICY_NAME = (const string_mds)"TimeBasedFilter";
static const string_mds PARTITION_QOS_POLICY_NAME = (const string_mds)"Partition";
static const string_mds RELIABILITY_QOS_POLICY_NAME = (const string_mds)"Reliability";
static const string_mds DESTINATIONORDER_QOS_POLICY_NAME = (const string_mds)"DestinationOrder";
static const string_mds HISTORY_QOS_POLICY_NAME = (const string_mds)"History";
static const string_mds RESOURCELIMITS_QOS_POLICY_NAME = (const string_mds)"ResourceLimits";
static const string_mds ENTITYFACTORY_QOS_POLICY_NAME = (const string_mds)"EntityFactory";
static const string_mds WRITERDATALIFECYCLE_QOS_POLICY_NAME = (const string_mds)"WriterDataLifecycle";
static const string_mds READERDATALIFECYCLE_QOS_POLICY_NAME = (const string_mds)"ReaderDataLifecycle";
static const string_mds TOPICDATA_QOS_POLICY_NAME = (const string_mds)"TopicData";
static const string_mds GROUPDATA_QOS_POLICY_NAME = (const string_mds)"TransportPriority";
static const string_mds LIFESPAN_QOS_POLICY_NAME = (const string_mds)"Lifespan";
static const string_mds DURABILITYSERVICE_POLICY_NAME = (const string_mds)"DurabilityService";

static const QosPolicyId_t INVALID_QOS_POLICY_ID = 0;
static const QosPolicyId_t USERDATA_QOS_POLICY_ID = 1;
static const QosPolicyId_t DURABILITY_QOS_POLICY_ID = 2;
static const QosPolicyId_t PRESENTATION_QOS_POLICY_ID = 3;
static const QosPolicyId_t DEADLINE_QOS_POLICY_ID = 4;
static const QosPolicyId_t LATENCYBUDGET_QOS_POLICY_ID = 5;
static const QosPolicyId_t OWNERSHIP_QOS_POLICY_ID = 6;
static const QosPolicyId_t OWNERSHIPSTRENGTH_QOS_POLICY_ID = 7;
static const QosPolicyId_t LIVELINESS_QOS_POLICY_ID = 8;
static const QosPolicyId_t TIMEBASEDFILTER_QOS_POLICY_ID = 9;
static const QosPolicyId_t PARTITION_QOS_POLICY_ID = 10;
static const QosPolicyId_t RELIABILITY_QOS_POLICY_ID = 11;
static const QosPolicyId_t DESTINATIONORDER_QOS_POLICY_ID = 12;
static const QosPolicyId_t HISTORY_QOS_POLICY_ID = 13;
static const QosPolicyId_t RESOURCELIMITS_QOS_POLICY_ID = 14;
static const QosPolicyId_t ENTITYFACTORY_QOS_POLICY_ID = 15;
static const QosPolicyId_t WRITERDATALIFECYCLE_QOS_POLICY_ID = 16;
static const QosPolicyId_t READERDATALIFECYCLE_QOS_POLICY_ID = 17;
static const QosPolicyId_t TOPICDATA_QOS_POLICY_ID = 18;
static const QosPolicyId_t GROUPDATA_QOS_POLICY_ID = 19;
static const QosPolicyId_t TRANSPORTPRIORITY_QOS_POLICY_ID = 20;
static const QosPolicyId_t LIFESPAN_QOS_POLICY_ID = 21;
static const QosPolicyId_t DURABILITYSERVICE_QOS_POLICY_ID = 22;

struct UserDataQosPolicy
{	
	StringSeq value;
};

struct TopicDataQosPolicy
{	
	StringSeq value;
};

struct GroupDataQosPolicy
{	
	StringSeq value;
};

struct TransportPriorityQosPolicy
{
	long value;
};

struct LifespanQosPolicy
{
	Duration_t duration;
};

enum DurabilityQosPolicyKind
{
	VOLATILE_DURABILITY_QOS,
	TRANSIENT_LOCAL_DURABILITY_QOS,
	TRANSIENT_DURABILITY_QOS,
	PERSISTENT_DURABILITY_QOS
};

struct DurabilityQosPolicy
{
	DurabilityQosPolicyKind kind;
};

enum PresentationQosPolicyAccessScopeKind
{
	INSTANCE_PRESENTATION_QOS,
	TOPIC_PRESENTATION_QOS,
	GROUP_PRESENTATION_QOS
};


struct PresentationQosPolicy
{
	PresentationQosPolicyAccessScopeKind access_scope;
	bool coherent_access;
	bool ordered_access;
};


struct DeadlineQosPolicy
{
	Duration_t period;
};

struct LatencyBudgetQosPolicy
{
	Duration_t duration;
};

enum OwnershipQosPolicyKind
{
	SHARED_OWNERSHIP_QOS,
	EXCLUSIVE_OWNERSHIP_QOS
};

struct OwnershipQosPolicy
{
	OwnershipQosPolicyKind kind;
};

struct OwnershipStrengthQosPolicy
{
	int32_t value;
};

enum LivelinessQosPolicyKind
{
	AUTOMATIC_LIVELINESS_QOS,
	MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
	MANUAL_BY_TOPIC_LIVELINESS_QOS
};


struct LivelinessQosPolicy
{
	LivelinessQosPolicyKind kind;
	Duration_t lease_duration;
};

struct TimeBasedFilterQosPolicy
{
	Duration_t minimum_separation;
};

struct PartitionQosPolicy
{
	StringSeq name;
};

enum ReliabilityQosPolicyKind
{
	BEST_EFFORT_RELIABILITY_QOS = 1,
	RELIABLE_RELIABILITY_QOS
};

struct ReliabilityQosPolicy
{
	ReliabilityQosPolicyKind kind;
	Duration_t max_blocking_time;
};

enum DestinationOrderQosPolicyKind
{
	BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
	BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
};

struct DestinationOrderQosPolicy
{
	DestinationOrderQosPolicyKind kind;
};

enum HistoryQosPolicyKind
{
	KEEP_LAST_HISTORY_QOS,
	KEEP_ALL_HISTORY_QOS
};

struct HistoryQosPolicy
{
	HistoryQosPolicyKind kind;
	int32_t depth;
};

struct ResourceLimitsQosPolicy
{
	int32_t max_samples;
	int32_t max_instances;
	int32_t max_samples_per_instance;
};

struct EntityFactoryQosPolicy
{
	bool autoenable_created_entities;
};

struct WriterDataLifecycleQosPolicy
{
	bool autodispose_unregistered_instances;
};

struct ReaderDataLifecycleQosPolicy
{
	Duration_t autopurge_nowriter_samples_delay;
	Duration_t autopurge_disposed_samples_delay;
};

struct DurabilityServiceQosPolicy
{
	Duration_t service_cleanup_delay;
	HistoryQosPolicyKind history_kind;
	int32_t history_depth;
	int32_t max_samples;
	int32_t max_instances;
	int32_t max_samples_per_instance;
};

struct DomainParticipantFactoryQos
{
	EntityFactoryQosPolicy entity_factory;
};

struct DomainParticipantQos
{
	UserDataQosPolicy user_data;
	EntityFactoryQosPolicy entity_factory;
};

struct TopicQos
{
	TopicDataQosPolicy topic_data;
	DurabilityQosPolicy durability;
	DurabilityServiceQosPolicy durability_service;
	DeadlineQosPolicy deadline;
	LatencyBudgetQosPolicy latency_budget;
	LivelinessQosPolicy liveliness;
	ReliabilityQosPolicy reliability;
	DestinationOrderQosPolicy destination_order;
	HistoryQosPolicy history;
	ResourceLimitsQosPolicy resource_limits;
	TransportPriorityQosPolicy transport_priority;
	LifespanQosPolicy lifespan;

	OwnershipQosPolicy ownership;
};

struct DataWriterQos
{
	DurabilityQosPolicy durability;
	DurabilityServiceQosPolicy durability_service;
	DeadlineQosPolicy deadline;
	LatencyBudgetQosPolicy latency_budget;
	LivelinessQosPolicy liveliness;
	ReliabilityQosPolicy reliability;
	DestinationOrderQosPolicy destination_order;
	HistoryQosPolicy history;
	ResourceLimitsQosPolicy resource_limits;
	TransportPriorityQosPolicy transport_priority;
	LifespanQosPolicy lifespan;
	UserDataQosPolicy user_data;
	OwnershipQosPolicy ownership;
	OwnershipStrengthQosPolicy ownership_strength;
	WriterDataLifecycleQosPolicy writer_data_lifecycle;
};

struct PublisherQos
{
	PresentationQosPolicy presentation;
	PartitionQosPolicy partition;
	GroupDataQosPolicy group_data;
	EntityFactoryQosPolicy entity_factory;
};

struct DataReaderQos
{
	DurabilityQosPolicy durability;
	DeadlineQosPolicy deadline;
	LatencyBudgetQosPolicy latency_budget;
	LivelinessQosPolicy liveliness;
	ReliabilityQosPolicy reliability;
	DestinationOrderQosPolicy destination_order;
	HistoryQosPolicy history;
	ResourceLimitsQosPolicy resource_limits;
	UserDataQosPolicy user_data;
	OwnershipQosPolicy ownership;
	TimeBasedFilterQosPolicy time_based_filter;
	ReaderDataLifecycleQosPolicy reader_data_lifecycle;
};

struct SubscriberQos
{
	PresentationQosPolicy presentation;
	PartitionQosPolicy partition;
	GroupDataQosPolicy group_data;
	EntityFactoryQosPolicy entity_factory;
};

struct RxOQos
{
	DurabilityQosPolicy durability;
	DeadlineQosPolicy deadline;
	LatencyBudgetQosPolicy latency_budget;
	LivelinessQosPolicy liveliness;
	ReliabilityQosPolicy reliability;
	OwnershipQosPolicy ownership;
	DestinationOrderQosPolicy destination_order;
	PresentationQosPolicy presentation;
		
	rtps_reader_t * p_rtps_reader;
	rtps_writer_t * p_rtps_writer;
};

struct ParticipantBuiltinTopicData
{
	BuiltinTopicKey_t key;
	UserDataQosPolicy user_data;
};

struct TopicBuiltinTopicData
{
	BuiltinTopicKey_t key;
	string_mds name;
	string_mds type_name;
	DurabilityQosPolicy durability;
	DurabilityServiceQosPolicy durability_service;
	DeadlineQosPolicy deadline;
	LatencyBudgetQosPolicy latency_budget;
	LivelinessQosPolicy liveliness;
	ReliabilityQosPolicy reliability;
	TransportPriorityQosPolicy transport_priority;
	LifespanQosPolicy lifespan;
	DestinationOrderQosPolicy destination_order;
	HistoryQosPolicy history;
	ResourceLimitsQosPolicy resource_limits;
	OwnershipQosPolicy ownership;
	TopicDataQosPolicy topic_data;
};

struct PublicationBuiltinTopicData
{
	BuiltinTopicKey_t key;
	BuiltinTopicKey_t participant_key;
	string_mds topic_name;
	string_mds type_name;
	DurabilityQosPolicy durability;
	DurabilityServiceQosPolicy durability_service;
	DeadlineQosPolicy deadline;
	LatencyBudgetQosPolicy latency_budget;
	LivelinessQosPolicy liveliness;
	ReliabilityQosPolicy reliability;
	LifespanQosPolicy lifespan;
	UserDataQosPolicy user_data;
	OwnershipQosPolicy ownership;
	OwnershipStrengthQosPolicy ownership_strength;
	DestinationOrderQosPolicy destination_order;
	PresentationQosPolicy presentation;
	PartitionQosPolicy partition;
	TopicDataQosPolicy topic_data;
	GroupDataQosPolicy group_data;
};

struct SubscriptionBuiltinTopicData
{
	BuiltinTopicKey_t key;
	BuiltinTopicKey_t participant_key;
	string_mds topic_name;
	string_mds type_name;
	DurabilityQosPolicy durability;
	DeadlineQosPolicy deadline;
	LatencyBudgetQosPolicy latency_budget;
	LivelinessQosPolicy liveliness;
	ReliabilityQosPolicy reliability;
	OwnershipQosPolicy ownership;
	DestinationOrderQosPolicy destination_order;
	UserDataQosPolicy user_data;
	TimeBasedFilterQosPolicy time_based_filter;
	PresentationQosPolicy presentation;
	PartitionQosPolicy partition;
	TopicDataQosPolicy topic_data;
	GroupDataQosPolicy group_data;
};


// MultiDomain 지원을 위해 domain_id_for_entity 추가
#define ENTITY_BODY \
	ReturnCode_t(*enable)(Entity *p_entity);					\
	StatusCondition *(*get_statuscondition)(Entity *p_entity);	\
	StatusMask(*get_status_changes)(Entity *p_entity);			\
	InstanceHandle_t(*get_instance_handle)(Entity *p_entity);	\
	int32_t		i_entity_type;									\
	bool	b_enable;											\
	StatusCondition* p_status_condition;						\
	StatusMask		l_status_mask;								\
	StatusMask		l_status_changes;							\
	mutex_t			entity_lock;								\
	cond_t			entity_wait;								\
	int32_t			last_sequencenum;							\
	int32_t			test_for_reliablity_division;				\
	int32_t			test_for_reliablity_bulk_start;				\
	int32_t			test_for_reliablity_bulk_last;				\
	int32_t			id;											\
	DomainId_t		domain_id_for_entity;


struct Entity
{
	ENTITY_BODY
};

#ifndef RTPS_PARTICIPANT_T_DEFINE
#	define RTPS_PARTICIPANT_T_DEFINE 1
typedef struct rtps_participant_t rtps_participant_t;
#endif

struct DomainParticipant
{
	ENTITY_BODY
	Publisher *(*create_publisher)(DomainParticipant *p_domainparticipant, in_mds PublisherQos *p_qos, in_mds PublisherListener *p_listener, in_mds StatusMask mask);
	ReturnCode_t(*delete_publisher)(DomainParticipant *p_domainparticipant, in_mds Publisher *p_publisher);
	Subscriber *(*create_subscriber)(DomainParticipant *p_domainparticipant, in_mds SubscriberQos *p_qos, in_mds SubscriberListener *p_listener, in_mds StatusMask mask);
	ReturnCode_t(*delete_subscriber)(DomainParticipant *p_domainparticipant, in_mds Subscriber *p_subscriber);
	Subscriber *(*get_builtin_subscriber)(DomainParticipant *p_domainparticipant);
	Topic *(*create_topic)(DomainParticipant *p_domainparticipant, in_mds string_mds topic_name, in_mds string_mds type_name, in_mds TopicQos *p_qos, in_mds TopicListener *p_listener, in_mds StatusMask mask);
	ReturnCode_t(*delete_topic)(DomainParticipant *p_domainparticipant, in_mds Topic *p_topic);

	Topic *(*find_topic)(DomainParticipant *p_domainparticipant, in_mds string_mds topic_name, in_mds Duration_t timeout);
	TopicDescription *(*lookup_topicdescription)(DomainParticipant *p_domainparticipant, in_mds string_mds name);
	ContentFilteredTopic *(*create_contentfilteredtopic)(DomainParticipant *p_domainparticipant, in_mds string_mds name, in_mds Topic *p_related_topic, in_mds string_mds filter_expression, in_mds StringSeq expression_parameters);
	ReturnCode_t(*delete_contentfilteredtopic)(DomainParticipant *p_domainparticipant, in_mds ContentFilteredTopic *p_contentfilteredtopic);
	MultiTopic *(*create_multitopic)(DomainParticipant *p_domainparticipant, in_mds string_mds name, in_mds string_mds type_name, in_mds string_mds subscription_expression, in_mds StringSeq expression_parameters);
	ReturnCode_t(*delete_multitopic)(DomainParticipant *p_domainparticipant, in_mds MultiTopic *p_multitopic);
	ReturnCode_t(*delete_contained_entities)(DomainParticipant *p_domainparticipant);
	ReturnCode_t(*set_qos)(DomainParticipant *p_domainparticipant, in_mds DomainParticipantQos *p_qos);
	ReturnCode_t(*get_qos)(DomainParticipant *p_domainparticipant, inout_mds DomainParticipantQos *p_qos);
	ReturnCode_t(*set_listener)(DomainParticipant *p_domainparticipant, in_mds DomainParticipantListener *p_listener, in_mds StatusMask mask);
	DomainParticipantListener *(*get_listener)(DomainParticipant *p_domainparticipant);
	ReturnCode_t(*ignore_participant)(DomainParticipant *p_domainparticipant, in_mds InstanceHandle_t handle);
	ReturnCode_t(*ignore_topic)(DomainParticipant *p_domainparticipant, in_mds InstanceHandle_t handle);
	ReturnCode_t(*ignore_publication)(DomainParticipant *p_domainparticipant, in_mds InstanceHandle_t handle);
	ReturnCode_t(*ignore_subscription)(DomainParticipant *p_domainparticipant, in_mds InstanceHandle_t handle);
	DomainId_t(*get_domain_id)(DomainParticipant *p_domainparticipant);
	ReturnCode_t(*assert_liveliness)(DomainParticipant *p_domainparticipant);
	ReturnCode_t(*set_default_publisher_qos)(in_mds PublisherQos *p_qos);
	ReturnCode_t(*get_default_publisher_qos)(inout_mds PublisherQos *p_qos);
	ReturnCode_t(*set_default_subscriber_qos)(in_mds SubscriberQos *p_qos);
	ReturnCode_t(*get_default_subscriber_qos)(inout_mds SubscriberQos *p_qos);
	ReturnCode_t(*set_default_topic_qos)(in_mds TopicQos *p_qos);
	ReturnCode_t(*get_default_topic_qos)(inout_mds TopicQos *p_qos);

	ReturnCode_t(*get_discovered_participants)(DomainParticipant *p_domainparticipant, inout_mds InstanceHandleSeq *participant_handles);
	ReturnCode_t(*get_discovered_participant_data)(DomainParticipant *p_domainparticipant, inout_mds ParticipantBuiltinTopicData *p_participant_data, in_mds InstanceHandle_t participant_handle);
	ReturnCode_t(*get_discovered_topics)(DomainParticipant *p_domainparticipant, inout_mds InstanceHandleSeq *topic_handles);
	ReturnCode_t(*get_discovered_topic_data)(DomainParticipant *p_domainparticipant, inout_mds TopicBuiltinTopicData *p_topic_data, in_mds InstanceHandle_t topic_handle);
	ReturnCode_t(*get_discovered_topic_typecode_data)(DomainParticipant *p_domainparticipant, inout_mds void *p_topic_typecode, in_mds InstanceHandle_t topic_handle);
	bool(*contains_entity)(DomainParticipant *p_domainparticipant, in_mds InstanceHandle_t a_handle);
	ReturnCode_t(*get_current_time)(DomainParticipant *p_domainparticipant, inout_mds Time_t *p_current_time);

	DomainId_t domain_id;
	int32_t	i_publisher;
	Publisher** pp_publisher;
	int32_t i_subscriber;
	Subscriber** pp_subscriber;
	int32_t i_topic;
	Topic** pp_topic;
	int32_t i_content_filtered_topics;
	ContentFilteredTopic** pp_content_filtered_topics;
	int32_t i_multi_topics;
	MultiTopic** pp_multi_topics;

	DomainParticipantQos qos;
	DomainParticipantListener* p_domain_participant_listener;

	int32_t				i_builtin_topics;
	Topic**				pp_builtin_topics;
	Publisher*			p_builtin_publisher;
	int32_t				i_waitsets;
	WaitSet**			pp_waitsets;
	rtps_participant_t* p_rtps_participant;
		
	// reader thread 제어하기 위한 변수
	data_fifo_t* p_reader_thread_fifo;
	module_thread_t thread_id;
	bool						b_end;
	
	//writer thread 제어하기 위한 변수들 
	data_fifo_t* p_writer_thread_fifo;
	module_thread_t thread_id2;
	bool						b_end2;
	
	//Writer_Thread2에 이벤트를 전달하기 위한 변수
	cond_t			writer_thread_wait;
	mutex_t 		writer_thread_lock;
	// Reader와 Writer Thread 생성시 구분하기 위한 변수
	int					i_flag_reader_writer_thread;
};

struct DomainParticipantFactory
{
	DomainParticipant *(*create_participant)(in_mds DomainId_t domain_id, in_mds DomainParticipantQos *p_qos, in_mds DomainParticipantListener *p_listener, in_mds StatusMask mask);
	ReturnCode_t(*delete_participant)(in_mds DomainParticipant *p_participant);
	DomainParticipant *(*lookup_participant)(in_mds DomainId_t domain_id);
	ReturnCode_t(*set_default_participant_qos)(in_mds DomainParticipantQos *p_qos);
	ReturnCode_t(*get_default_participant_qos)(inout_mds DomainParticipantQos *p_qos);
	ReturnCode_t(*set_qos)(in_mds DomainParticipantFactoryQos *p_qos);
	ReturnCode_t(*get_qos)(inout_mds DomainParticipantFactoryQos *p_qos);
	//20161102
	ReturnCode_t(*set_md5_rc4_enable)(in_mds bool md5, in_mds bool rc4);

	int32_t		module_id;
};


typedef struct dds_parameter_t dds_parameter_t;


#define TYPESUPPORT_BODY	\
	int32_t		i_size;			\
	int32_t		i_parameters;	\
	dds_parameter_t** pp_parameters; \
	int32_t		offsetcount;			\


struct TypeSupport
{
	TYPESUPPORT_BODY
};


typedef enum TOPIC_TYPE
{
	DEFAULT_TOPIC_TYPE,
	CONTENTFILTER_TOPIC_TYPE,
	MULTITOPIC_TYPE
} TOPIC_TYPE;


#define TOPICDESCRIPTION_BODY								\
	string_mds(*get_type_name)(Topic *p_topic);				\
	string_mds(*get_name)(Topic *p_topic);					\
	DomainParticipant *(*get_participant)(Topic *p_topic);	\
	string_mds		topic_name;								\
	string_mds		type_name;								\
	DomainParticipant* p_domain_participant;				\
	TOPIC_TYPE			topic_type;							\


struct TopicDescription
{
	TOPICDESCRIPTION_BODY
};

struct Topic
{
	ENTITY_BODY
	TOPICDESCRIPTION_BODY
	ReturnCode_t(*set_qos)(Topic* p_topic, in_mds TopicQos *p_qos);
	ReturnCode_t(*get_qos)(Topic* p_topic, inout_mds TopicQos *p_qos);
	ReturnCode_t(*set_listener)(Topic* p_topic, in_mds TopicListener *p_listener, in_mds StatusMask mask);
	TopicListener *(*get_listener)(Topic* p_topic);
	// Access the status
	ReturnCode_t(*get_inconsistent_topic_status)(Topic* p_topic, inout_mds InconsistentTopicStatus *a_status);
	TopicQos topic_qos;
	TopicListener* p_topic_listener;
	TopicStatus status;
	TopicListenerStatusChangedFlag status_changed_flag;
	void*	p_rtps_topic;
};

struct ContentFilteredTopic
{
	ENTITY_BODY
	TOPICDESCRIPTION_BODY
	string_mds(*get_filter_expression)(ContentFilteredTopic* p_topicinitTopicDescription);
	ReturnCode_t(*get_expression_parameters)(ContentFilteredTopic* p_topicinitTopicDescription, inout_mds StringSeq *p_expression_parameters);
	ReturnCode_t(*set_expression_parameters)(ContentFilteredTopic* p_topicinitTopicDescription, in_mds StringSeq *p_expression_parameters);
	Topic *(*get_related_topic)(ContentFilteredTopic* p_topicinitTopicDescription);
	
	Topic *p_related_topic;
	string_mds filter_expression;
	StringSeq expression_parameters;
	expression_t *p_expr;
};

struct MultiTopic
{
	ENTITY_BODY
	TOPICDESCRIPTION_BODY
	string_mds(*get_subscription_expression)(MultiTopic* p_multiTopic);
	ReturnCode_t(*get_expression_parameters)(MultiTopic* p_multiTopic, inout_mds StringSeq *p_expression_parameters);
	ReturnCode_t(*set_expression_parameters)(MultiTopic* p_multiTopic, in_mds StringSeq *p_expression_parameters);
	
	string_mds subscription_expression;
	StringSeq expression_parameters;
};

struct Publisher
{
	ENTITY_BODY
	DataWriter *(*create_datawriter)(Publisher *p_publisher, in_mds Topic *p_topic, in_mds DataWriterQos *p_qos, in_mds DataWriterListener *p_listener, in_mds StatusMask mask);
	ReturnCode_t(*delete_datawriter)(Publisher *p_publisher, in_mds DataWriter *p_datawriter);
	DataWriter *(*lookup_datawriter)(Publisher *p_publisher, in_mds string_mds topic_name);
	ReturnCode_t(*delete_contained_entities)(Publisher *p_publisher);
	ReturnCode_t(*set_qos)(Publisher *p_publisher, in_mds PublisherQos *p_qos);
	ReturnCode_t(*get_qos)(Publisher *p_publisher, inout_mds PublisherQos *p_qos);
	ReturnCode_t(*set_listener)(Publisher *p_publisher, in_mds PublisherListener *p_listener, in_mds StatusMask mask);
	PublisherListener *(*get_listener)(Publisher *p_publisher);
	ReturnCode_t(*suspend_publications)(Publisher *p_publisher);
	ReturnCode_t(*resume_publications)(Publisher *p_publisher);
	ReturnCode_t(*begin_coherent_changes)(Publisher *p_publisher);
	ReturnCode_t(*end_coherent_changes)(Publisher *p_publisher);
	ReturnCode_t(*wait_for_acknowledgments)(Publisher *p_publisher, in_mds Duration_t max_wait);
	DomainParticipant *(*get_participant)(Publisher *p_publisher);
	ReturnCode_t(*set_default_datawriter_qos)(in_mds DataWriterQos *p_qos);
	ReturnCode_t(*get_default_datawriter_qos)(inout_mds DataWriterQos *p_qos);
	ReturnCode_t(*copy_from_topic_qos)(inout_mds DataWriterQos *p_datawriter_qos, in_mds TopicQos *p_topic_qos);
	PublisherQos publisher_qos;
	int	i_datawriters;
	DataWriter** pp_datawriters;
	PublisherListener* p_publisher_listener;
	DomainParticipant* p_domain_participant;
	bool		is_suspend;
	bool		begin_coherent;
};


#ifndef RTPS_CACHECHANGE_T_DEFINE
#define RTPS_CACHECHANGE_T_DEFINE 1
typedef struct rtps_cachechange_t rtps_cachechange_t;
#endif

#define MAX_KEY_NUM 10


typedef struct cpskey_t
{
	long		id;
	uint32_t	offset;
	uint32_t	len;
	void*		p_value;
}cpskey_t;

typedef struct key_guid_t
{
	uint8_t		key[16];
}key_guid_t;

typedef struct instanceset_t
{
	uint32_t				i_key;
	cpskey_t				keylist[MAX_KEY_NUM];
	int32_t					max_samples_per_instance;
	int32_t					i_history_depth;
	int32_t					i_messages;
	message_t**				pp_messages;
	int32_t					i_key_guid;
	key_guid_t**			pp_key_guid;

	InstanceStateKind		instance_state;
	SampleStateKind 		sample_state;
	ViewStateKind 			view_state;
	
	bool					register_instance_timestamp_set;
	Time_t					register_instance_timestamp_value;
} instanceset_t;


#define DATAWRITER_BODY \
	ENTITY_BODY\
	ReturnCode_t(*set_qos)(DataWriter* p_datawriter, in_mds DataWriterQos *p_qos); \
	ReturnCode_t(*get_qos)(DataWriter* p_datawriter, inout_mds DataWriterQos *p_qos); \
	ReturnCode_t(*set_listener)(DataWriter* p_datawriter, in_mds DataWriterListener *p_listener, in_mds StatusMask mask); \
	DataWriterListener *(*get_listener)(DataWriter* p_datawriter); \
	Topic *(*get_topic)(DataWriter* p_datawriter); \
	Publisher *(*get_publisher)(DataWriter* p_datawriter); \
	ReturnCode_t(*wait_for_acknowledgments)(DataWriter* p_datawriter, in_mds Duration_t max_wait); \
	ReturnCode_t(*get_liveliness_lost_status)(DataWriter* p_datawriter, inout_mds LivelinessLostStatus *status); \
	ReturnCode_t(*get_offered_deadline_missed_status)(DataWriter* p_datawriter, inout_mds OfferedDeadlineMissedStatus *status); \
	ReturnCode_t(*get_offered_incompatible_qos_status)(DataWriter* p_datawriter, inout_mds OfferedIncompatibleQosStatus *status); \
	ReturnCode_t(*get_publication_matched_status)(DataWriter* p_datawriter, inout_mds PublicationMatchedStatus *status); \
	ReturnCode_t(*assert_liveliness)(DataWriter* p_datawriter); \
	ReturnCode_t(*get_matched_subscriptions)(DataWriter* p_datawriter, inout_mds InstanceHandleSeq *subscription_handles); \
	ReturnCode_t(*get_matched_subscription_data)(DataWriter* p_datawriter, inout_mds SubscriptionBuiltinTopicData *subscription_data, in_mds InstanceHandle_t subscription_handle); \
	DataWriterQos datawriter_qos; \
	DataWriterListener* p_datawriter_listener; \
	Topic* p_topic; \
	Publisher* p_publisher; \
	void*	p_related_rtps_writer; \
	bool	begin_coherent; \
	DataWriterStatus status; \
	DataWriterListenerStatusChangedFlag status_changed_flag; \
	int32_t		i_instanceset; \
	instanceset_t**	pp_instanceset; \
	int32_t					i_message_order; \
	message_t**				pp_message_order; \


struct DataWriter
{
	DATAWRITER_BODY
};

struct Subscriber 
{
	ENTITY_BODY
	DataReader *(*create_datareader)(Subscriber *p_subscriber, in_mds Topic *p_topic, in_mds DataReaderQos *p_qos, in_mds DataReaderListener *p_listener, in_mds StatusMask mask);
	ReturnCode_t(*delete_datareader)(Subscriber *p_subscriber, in_mds DataReader *p_datareader);
	ReturnCode_t(*delete_contained_entities)(Subscriber *p_subscriber);
	DataReader *(*lookup_datareader)(Subscriber *p_subscriber, in_mds string_mds topic_name);
	ReturnCode_t(*get_datareaders)(Subscriber *p_subscriber, inout_mds DataReaderSeq *p_readers, in_mds SampleStateMask sample_states, in_mds ViewStateMask view_states, in_mds InstanceStateMask instance_states);
	ReturnCode_t(*notify_datareaders)(Subscriber *p_subscriber);
	ReturnCode_t(*set_qos)(Subscriber *p_subscriber, in_mds SubscriberQos *p_qos);
	ReturnCode_t(*get_qos)(Subscriber *p_subscriber, inout_mds SubscriberQos *p_qos);
	ReturnCode_t(*set_listener)(Subscriber *p_subscriber, in_mds SubscriberListener *p_listener, in_mds StatusMask mask);
	SubscriberListener *(*get_listener)(Subscriber *p_subscriber);
	ReturnCode_t(*begin_access)(Subscriber *p_subscriber);
	ReturnCode_t(*end_access)(Subscriber *p_subscriber);
	DomainParticipant *(*get_participant)(Subscriber *p_subscriber);
	ReturnCode_t(*set_default_datareader_qos)(in_mds DataReaderQos *p_qos);
	ReturnCode_t(*get_default_datareader_qos)(inout_mds DataReaderQos *p_qos);
	ReturnCode_t(*copy_from_topic_qos)(inout_mds DataReaderQos *p_datareader_qos, in_mds TopicQos *p_topic_qos);

	SubscriberQos subscriber_qos;
	int i_datareaders;
	DataReader** pp_datareaders;
	SubscriberListener* p_subscriber_listener;
	DomainParticipant* p_domain_participant;

	SubscriberListenerStatusChangedFlag status_changed_flag;
};


#define DATAREADER_BODY \
	ENTITY_BODY\
	ReadCondition *(*create_readcondition)(DataReader* p_datareader, in_mds SampleStateMask sample_states, in_mds ViewStateMask view_states, in_mds InstanceStateMask instance_states); \
	QueryCondition *(*create_querycondition)(DataReader* p_datareader, in_mds SampleStateMask sample_states, in_mds ViewStateMask view_states, in_mds InstanceStateMask instance_states, in_mds string_mds query_expression, in_mds StringSeq *p_query_parameters); \
	ReturnCode_t(*delete_readcondition)(DataReader* p_datareader, in_mds ReadCondition *p_condition); \
	ReturnCode_t(*delete_contained_entities)(DataReader* p_datareader); \
	ReturnCode_t(*set_qos)(DataReader* p_datareader, in_mds DataReaderQos *p_qos); \
	ReturnCode_t(*get_qos)(DataReader* p_datareader, inout_mds DataReaderQos *p_qos); \
	ReturnCode_t(*set_listener)(DataReader* p_datareader, in_mds DataReaderListener *p_listener, in_mds StatusMask mask); \
	DataReaderListener *(*get_listener)(DataReader* p_datareader); \
	TopicDescription *(*get_topicdescription)(DataReader* p_datareader); \
	Subscriber *(*get_subscriber)(DataReader* p_datareader); \
	ReturnCode_t(*get_sample_rejected_status)(DataReader* p_datareader, inout_mds SampleRejectedStatus *status); \
	ReturnCode_t(*get_liveliness_changed_status)(DataReader* p_datareader, inout_mds LivelinessChangedStatus *status); \
	ReturnCode_t(*get_requested_deadline_missed_status)(DataReader* p_datareader, inout_mds RequestedDeadlineMissedStatus *status); \
	ReturnCode_t(*get_requested_incompatible_qos_status)(DataReader* p_datareader, inout_mds RequestedIncompatibleQosStatus *status); \
	ReturnCode_t(*get_subscription_matched_status)(DataReader* p_datareader, inout_mds SubscriptionMatchedStatus *status); \
	ReturnCode_t(*get_sample_lost_status)(DataReader* p_datareader, inout_mds SampleLostStatus *status); \
	ReturnCode_t(*wait_for_historical_data)(DataReader* p_datareader, in_mds Duration_t max_wait); \
	ReturnCode_t(*get_matched_publications)(DataReader* p_datareader, inout_mds InstanceHandleSeq *publication_handles); \
	ReturnCode_t(*get_matched_publication_data)(DataReader* p_datareader, inout_mds PublicationBuiltinTopicData *publication_data, in_mds InstanceHandle_t publication_handle); \
	DataReaderQos datareader_qos; \
	Subscriber* p_subscriber; \
	Topic* p_topic; \
	int32_t	i_read_conditions; \
	ReadCondition** pp_read_conditions; \
	int32_t	i_query_conditions; \
	QueryCondition** pp_query_conditions; \
	DataReaderListener* p_datareader_listener; \
	void*				p_related_rtps_reader; \
	int32_t first_coh_number; \
	int32_t last_coh_number; \
	DataReaderStatus status; \
	DataReaderListenerStatusChangedFlag status_changed_flag; \
	int32_t			i_instanceset; \
	instanceset_t**	pp_instanceset; \
	int32_t					i_message_order; \
	message_t**				pp_message_order; \
	int32_t			len; \
	int32_t			max_len; \
	bool			owned; \


struct DataReader
{
	DATAREADER_BODY
};

struct SampleInfo
{
	SampleStateKind sample_state;
	ViewStateKind view_state;
	InstanceStateKind instance_state;
	Time_t source_timestamp;
	InstanceHandle_t instance_handle;
	InstanceHandle_t publication_handle;
	int32_t disposed_generation_count;
	int32_t no_writers_generation_count;
	int32_t sample_rank;
	int32_t generation_rank;
	int32_t absolute_generation_rank;
	bool valid_data;
	Time_t disposed_timestamp; // reader data lifecycle
};

typedef struct SampleInfoSeq
{
	int32_t i_seq;
	SampleInfo** pp_sample_infos;
} SampleInfoSeq;


static SampleInfoSeq INIT_SAMPLEINFOSEQ = { 0, NULL };


#include <foo.h>


typedef struct Foo SampleData;

typedef struct DataSample
{
	SampleData data;
	SampleInfo sample_info;
} DataSample;


typedef enum BEHAVIOR_KIND
{
	DEFAULT_TYPE,
	STATELESS_TYPE,
	STATEFUL_TYPE
} BEHAVIOR_KIND;


unsigned long _get_init_time(void);


// Application 에서 지정한 IP 설정 지원 기능
typedef struct DDS_transport_property
{
	int		list_length;
	char**	ip_list;
}DDS_transport_property;

typedef struct DDS_transport_property_multinic
{
	int		list_length;
	char**	ip_list;
	unsigned int	a_list[10][4];
}DDS_transport_property_multinic;

#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	bool DDS_transport_property_ipcnt(int cnt);		/* DDS Aceess IP counts From Application */
	DDS_DLL_API	bool DDS_transport_property_ipaddr(const char* addr);	/* DDS Aceess IP address From Application */
	DDS_DLL_API	void DDS_transport_property_Free();
	DDS_DLL_API	bool DDS_transport_property_restrict_ipaddr();
	DDS_DLL_API	void DDS_transport_property_Free_AllowedIpAddress();
	DDS_DLL_API	bool DDS_transport_property_ipaddr_search();		//LDDS_SETIP()에서 지정한 특정 NIC ipaddress 대역에 해당하는 nic ip를 list에 저장하는 함수를 호출하는 API
	
	// Reliable Multicast 지원을 위한 multicast IP address 설정 (DR 설정)
	DDS_DLL_API	void DDS_set_reliable_multicast(bool enable);
#ifdef __cplusplus
}
#endif

#if (EJ_CDR == 1)

#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API unsigned char	DDS_get_target_CDR();
	DDS_DLL_API void DDS_set_target_CDR(unsigned char val);
#ifdef __cplusplus
}
#endif

#endif // (EF_CDR == 1)
#include <expression.h>
#include <message.h>

#endif
