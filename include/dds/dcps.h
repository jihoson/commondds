#ifndef __DDS_DSCP_H__
#define __DDS_DSCP_H__

#include <stdint.h>
#include <malloc.h>
#include <iostream>

#define DOMAINID_TYPE_NATIVE		int32_t
#define HANDLE_TYPE_NATIVE		int32_t
#define HANDLE_NIL_NATIVE		0
#define BUILTIN_TOPIC_KEY_TYPE_NATIVE	int32_t

#define TheParticipantFactory
#define PARTICIPANT_QOS_DEFAULT
#define TOPIC_QOS_DEFAULT
#define PUBLISHER_QOS_DEFAULT
#define SUBSCRIBER_QOS_DEFAULT
#define DATAWRITER_QOS_DEFAULT
#define DATAREADER_QOS_DEFAULT
#define DATAWRITER_QOS_USE_TOPIC_QOS
#define DATAREADER_QOS_USE_TOPIC_QOS

namespace dds {
	// IDL
	template<typename T>
	struct sequence {
		uint32_t maximum;
		uint32_t length;
		
		T* buffer;
		
		sequence() {
			maximum = 0;
			length = 0;
			buffer = NULL;
		}
		
		sequence(uint32_t size) {
			maximum = size;
			length = 0;
			buffer = (T*)malloc(sizeof(T) * size);
		}
		
		sequence(T* array, uint32_t size) {
			maximum = size;
			length = size;
			buffer = (T*)malloc(sizeof(T) * size);
			memcpy(buffer, array, sizeof(T) * size);
		}
		
		~sequence() {
			free(buffer);
		}
		
		bool add(T value) {
			if(length < maximum) {
				buffer[length++] = value;
				return true;
			} else {
				return false;
			}
		}
		
		T& operator[](uint32_t index) {
			return buffer[index];
		}
		
		const T& operator[](uint32_t index) const {
			return buffer[index];
		}
		
		friend std::ostream& operator<<(std::ostream& os, const sequence<T>& seq) {
			os << &seq;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const sequence<T>* seq) {
			os << "sequence[maximum=" << seq->maximum << ", length=" << seq->length << "]";
		}
	};
	
	typedef DOMAINID_TYPE_NATIVE DomainId_t;
	typedef HANDLE_TYPE_NATIVE InstanceHandle_t;
	 
	struct BuiltinTopicKey_t {
		BUILTIN_TOPIC_KEY_TYPE_NATIVE value[3];
		
		BuiltinTopicKey_t();
		BuiltinTopicKey_t(BUILTIN_TOPIC_KEY_TYPE_NATIVE value[3]);
		~BuiltinTopicKey_t();
	};
	
	typedef sequence<InstanceHandle_t> InstanceHandleSeq;
	
	typedef int32_t ReturnCode_t;
	typedef int32_t QosPolicyId_t;
	typedef sequence<char*> StringSeq;
	
	struct Duration_t {
		int32_t sec;
		uint32_t nanosec;
		
		Duration_t();
		Duration_t(int32_t sec, uint32_t nanosec);
		~Duration_t();
	};
	
	struct Time_t {
		int32_t sec;
		uint32_t nanosec;
		
		Time_t();
		Time_t(int32_t sec, uint32_t nanosec);
		~Time_t();
	};
	
	// ----------------------------------------------------------------------
	// Pre-defined values
	// ----------------------------------------------------------------------
	const InstanceHandle_t HANDLE_NIL = HANDLE_NIL_NATIVE;
	
	const int32_t LENGTH_UNLIMITED = -1;
	
	const int32_t DURATION_INFINITE_SEC		= 0x7fffffff;
	const uint32_t DURATION_INFINITE_NSEC		= 0x7fffffff;
	
	const int32_t DURATION_ZERO_SEC			= 0;
	const uint32_t DURATION_ZERO_NSEC		= 0;
	
	const int32_t TIME_INVALID_SEC			= -1;
	const uint32_t TIME_INVALID_NSEC		= 0xffffffff;
	
	// ----------------------------------------------------------------------
	// Return codes
	// ----------------------------------------------------------------------
	const ReturnCode_t RETCODE_OK			= 0;
	const ReturnCode_t RETCODE_ERROR		= 1;
	const ReturnCode_t RETCODE_UNSUPPORTED		= 2;
	const ReturnCode_t RETCODE_BAD_PARAMETER	= 3;
	const ReturnCode_t RETCODE_PRECONDITION_NOT_MET	= 4;
	const ReturnCode_t RETCODE_OUT_OF_RESOURCES	= 5;
	const ReturnCode_t RETCODE_NOT_ENABLED		= 6;
	const ReturnCode_t RETCODE_IMMUTABLE_POLICY	= 7;
	const ReturnCode_t RETCODE_INCONSISTENT_POLICY	= 8;
	const ReturnCode_t RETCODE_ALREADY_DELETED	= 9;
	const ReturnCode_t RETCODE_TIMEOUT		= 10;
	const ReturnCode_t RETCODE_NO_DATA		= 11;
	const ReturnCode_t RETCODE_ILLEGAL_OPERATION	= 12;
	
	// ----------------------------------------------------------------------
	// Status to support listeners and conditions
	// ----------------------------------------------------------------------
	
	typedef uint32_t StatusKind;
	typedef uint32_t StatusMask;	// bit-mask StatusKind
	
	const StatusKind INCONSISTENT_TOPIC_STATUS		= 0x0001 << 0;
	const StatusKind OFFERED_DEADLINE_MISSED_STATUS		= 0x0001 << 1;
	const StatusKind REQUESTED_DEADLINE_MISSED_STATUS	= 0x0001 << 2;
	const StatusKind OFFERED_INCOMPATIBLE_QOS_STATUS	= 0x0001 << 5;
	const StatusKind REQUESTED_INCOMPATIBLE_QOS_STATUS	= 0x0001 << 6;
	const StatusKind SAMPLE_LOST_STATUS			= 0x0001 << 7;
	const StatusKind SAMPLE_REJECTED_STATUS			= 0x0001 << 8;
	const StatusKind DATA_ON_READERS_STATUS			= 0x0001 << 9;
	const StatusKind DATA_AVAILABLE_STATUS			= 0x0001 << 10;
	const StatusKind LIVELINESS_LOST_STATUS			= 0x0001 << 11;
	const StatusKind LIVELINESS_CHANGED_STATUS		= 0x0001 << 12;
	const StatusKind PUBLICATION_MATCHED_STATUS		= 0x0001 << 13;
	const StatusKind SUBSCRIPTION_MATCHED_STATUS		= 0x0001 << 14;
	
	struct InconsistentTopicStatus {
		int32_t total_count;
		int32_t total_count_change;
		
		InconsistentTopicStatus();
		InconsistentTopicStatus(int32_t total_count, int32_t total_count_change);
		~InconsistentTopicStatus();
	};
	
	struct SampleLostStatus {
		int32_t total_count;
		int32_t total_count_change;
		
		SampleLostStatus();
		SampleLostStatus(int32_t total_count, int32_t total_count_change);
		~SampleLostStatus();
	};
	
	enum SampleRejectedStatusKind {
		NOT_REJECTED,
		REJECTED_BY_INSTANCES_LIMIT,
		REJECTED_BY_SAMPLES_LIMIT,
		REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
	};
	
	struct SampleRejectedStatus {
		int32_t				total_count;
		int32_t				total_count_change;
		SampleRejectedStatusKind	last_reason;
		InstanceHandle_t		last_instance_handle;
		
		SampleRejectedStatus();
		SampleRejectedStatus(
			int32_t total_count, 
			int32_t total_count_change, 
			SampleRejectedStatusKind last_reason, 
			InstanceHandle_t last_instance_handle);
		~SampleRejectedStatus();
	};
	
	struct LivelinessLostStatus {
		int32_t	total_count;
		int32_t	total_count_change;
		
		LivelinessLostStatus();
		LivelinessLostStatus(int32_t total_count, int32_t total_count_change);
		~LivelinessLostStatus();
	};
	
	struct LivelinessChangedStatus {
		int32_t			alive_count;
		int32_t			not_alive_count;
		int32_t			alive_count_change;
		int32_t			not_alive_count_change;
		InstanceHandle_t	last_publication_handle;
		
		LivelinessChangedStatus();
		LivelinessChangedStatus(
			int32_t alive_count, 
			int32_t not_alive_count, 
			int32_t alive_count_change, 
			int32_t not_alive_count_change, 
			InstanceHandle_t last_publication_handle);
		~LivelinessChangedStatus();
	};
	
	struct OfferedDeadlineMissedStatus {
		int32_t			total_count;
		int32_t			total_count_change;
		InstanceHandle_t	last_instance_handle;
		
	 	OfferedDeadlineMissedStatus();
	 	OfferedDeadlineMissedStatus(
			int32_t total_count,
			int32_t total_count_change,
			InstanceHandle_t last_instance_handle);
	 	~OfferedDeadlineMissedStatus();
	};
	
	struct RequestedDeadlineMissedStatus {
		int32_t			total_count;
		int32_t			total_count_change;
		InstanceHandle_t	last_instance_handle;
		
		RequestedDeadlineMissedStatus();
		RequestedDeadlineMissedStatus(
			int32_t total_count,
			int32_t total_count_change,
			InstanceHandle_t last_instance_handle);
		~RequestedDeadlineMissedStatus();
	};
	
	struct QosPolicyCount {
		QosPolicyId_t		policy_id;
		int32_t			count;
		
		QosPolicyCount();
		QosPolicyCount(
			QosPolicyId_t policy_id,
			int32_t count);
		~QosPolicyCount();
	};
	
	typedef sequence<QosPolicyCount> QosPolicyCountSeq;
	
	struct OfferedIncompatibleQosStatus {
		int32_t			total_count;
		int32_t			total_count_change;
		QosPolicyId_t		last_policy_id;
		QosPolicyCountSeq	policies;
		
		OfferedIncompatibleQosStatus();
		OfferedIncompatibleQosStatus(
			int32_t total_count,
			int32_t total_count_change,
			QosPolicyId_t last_policy_id,
			QosPolicyCountSeq policies);
		~OfferedIncompatibleQosStatus();
	};
	
	struct RequestedIncompatibleQosStatus {
		int32_t			total_count;
		int32_t			total_count_change;
		QosPolicyId_t		last_policy_id;
		QosPolicyCountSeq	policies;
		
		RequestedIncompatibleQosStatus();
		RequestedIncompatibleQosStatus(
			int32_t total_count,
			int32_t total_count_change,
			QosPolicyId_t last_policy_id,
			QosPolicyCountSeq policies);
		~RequestedIncompatibleQosStatus();
	};
	
	struct PublicationMatchedStatus {
		int32_t			total_count;
		int32_t			total_count_change;
		int32_t			current_count;
		int32_t			current_count_change;
		InstanceHandle_t	last_subscription_handle;
		
		PublicationMatchedStatus();
		PublicationMatchedStatus(
			int32_t total_count,
			int32_t total_count_change,
			int32_t current_count,
			int32_t current_count_change,
			InstanceHandle_t last_subscription_handle);
		~PublicationMatchedStatus();
	};
	
	struct SubscriptionMatchedStatus {
		int32_t			total_count;
		int32_t			total_count_change;
		int32_t			current_count;
		int32_t			current_count_change;
		InstanceHandle_t	last_publication_handle;
		
		SubscriptionMatchedStatus();
		SubscriptionMatchedStatus(
			int32_t total_count,
			int32_t total_count_change,
			int32_t current_count,
			int32_t current_count_change,
			InstanceHandle_t last_publication_handle);
		~SubscriptionMatchedStatus();
	};
	
	// ----------------------------------------------------------------------
	// Listeners
	// ----------------------------------------------------------------------
	
	class Listener;
	class Entity;
	class TopicDescription;
	class Topic;
	class ContentFilteredTopic;
	class MultiTopic;
	class DataWriter;
	class DataReader;
	class Subscriber;
	class Publisher;
	
	typedef sequence<DataReader> DataReaderSeq;
	
	class Listener {};
	
	class TopicListener : Listener {
	public:
		TopicListener();
		virtual ~TopicListener();
		
		void on_inconsistent_topic(const Topic* the_topic, 
			const InconsistentTopicStatus* status);
	};
	
	class DataWriterListener : Listener {
	public:
		DataWriterListener();
		virtual ~DataWriterListener();
		
		void on_offered_deadline_missed(
			const DataWriter* writer, 
			const OfferedDeadlineMissedStatus* status);
		void on_offered_incompatible_qos(
			const DataWriter* writer, 
			const OfferedIncompatibleQosStatus* status);
		void on_liveliness_lost(
			const DataWriter* writer, 
			const LivelinessLostStatus* status);
		void on_publication_matched(
			const DataWriter* writer, 
			const PublicationMatchedStatus* status);
	};
	
	class PublisherListener : DataWriterListener {
	};
	
	class DataReaderListener : Listener {
	public:
		DataReaderListener();
		virtual ~DataReaderListener();
		
		void on_requested_deadline_missed(
			const DataReader* the_reader, 
			const RequestedDeadlineMissedStatus* status);
		void on_requested_incompatible_qos(
			const DataReader* the_reader, 
			const RequestedIncompatibleQosStatus* status);
		void on_sample_rejected(
			const DataReader* the_reader,
			const SampleRejectedStatus* status);
		void on_liveliness_changed(
			const DataReader* the_reader,
			const LivelinessChangedStatus* status);
		void on_data_available(
			const DataReader* the_reader);
		void on_subscription_matched(
			const DataReader* the_reader,
			const SubscriptionMatchedStatus* status);
		void on_sample_lost(
			const DataReader* the_reader,
			const SampleLostStatus* status);
	};
	
	class SubscriberListener : DataReaderListener {
	public:
		SubscriberListener();
		virtual ~SubscriberListener();
		
		void on_data_on_readers(
			const Subscriber* the_subscriber);
	};
	
	class DomainParticipantListener : TopicListener,
					PublisherListener,
					SubscriberListener {
	public:
		DomainParticipantListener();
		virtual ~DomainParticipantListener();
	};
	
	// ----------------------------------------------------------------------
	// Conditions
	// ----------------------------------------------------------------------
	
	class Condition {
	public:
		Condition();
		virtual ~Condition();
		
		bool get_trigger_value();
	};
	
	typedef sequence<Condition> ConditionSeq;
	
	class WaitSet {
	public:
		WaitSet();
		virtual ~WaitSet();
		
		ReturnCode_t wait(
			ConditionSeq* active_conditions,
			const Duration_t* timeout);
		ReturnCode_t attach_condition(
			const Condition* cond);
		ReturnCode_t detach_condition(
			const Condition* cond);
		ReturnCode_t get_conditions(
			ConditionSeq* attached_conditions);
	};
	
	class GuardCondition : Condition {
	public:
		GuardCondition();
		virtual ~GuardCondition();
		
		ReturnCode_t set_trigger_value(
			bool value);
	};
	
	class StatusCondition : Condition {
	public:
		StatusCondition();
		virtual ~StatusCondition();
		
		StatusMask* get_enabled_statuses();
		ReturnCode_t set_enabled_statuses(
			const StatusMask* mask);
		Entity* get_entity();
	};
	
	// Sample states to support reads
	typedef uint32_t SampleStateKind;
	const SampleStateKind READ_SAMPLE_STATE				= 0x0001 << 0;
	const SampleStateKind NOT_READ_SAMPLE_STATE			= 0x0001 << 1;
	
	// This is a bit-mask SampleStateKind
	typedef uint32_t SampleStateMask;
	const SampleStateMask ANY_SAMPLE_STATE				= 0xffff;
	
	// View states to support reads
	typedef uint32_t ViewStateKind;
	const ViewStateKind NEW_VIEW_STATE				= 0x0001 << 0;
	const ViewStateKind NOT_NEW_VIEW_STATE				= 0x0001 << 1;
	
	// This is a bit-mask ViewStateKind
	typedef uint32_t ViewStateMask;
	const ViewStateMask ANY_VIEW_STATE				= 0xffff;
	
	// Instance states to support reads
	typedef uint32_t InstanceStateKind;
	const InstanceStateKind ALIVE_INSTANCE_STATE			= 0x0001 << 0;
	const InstanceStateKind NOT_ALIVE_DISPOSED_INSTANCE_STATE	= 0x0001 << 1;
	const InstanceStateKind NOT_ALIVE_NO_WRITERS_INSTANCE_STATE	= 0x0001 << 2;
	
	// This is a bit-mask InstanceStateKind
	typedef uint32_t InstanceStateMask;
	const InstanceStateMask ANY_INSTANCE_STATE			= 0xffff;
	const InstanceStateMask NOT_ALIVE_INSTANCE_STATE		= 0x006;
	
	class ReadCondition : Condition {
	public:
		ReadCondition();
		virtual ~ReadCondition();
		
		SampleStateMask* get_sample_state_mask();
		ViewStateMask* get_view_state_mask();
		InstanceStateMask* get_instance_state_mask();
		DataReader* get_datareader();
	};
	
	class QueryCondition : ReadCondition {
	public:
		QueryCondition();
		virtual ~QueryCondition();
		
		char* get_query_expression();
		ReturnCode_t get_query_parameters(
			StringSeq* query_parameters);
		ReturnCode_t set_query_parameters(
			const StringSeq* query_parameters);
	};
	
	// ----------------------------------------------------------------------
	// Qos
	// ----------------------------------------------------------------------
	extern const char* USERDATA_QOS_POLICY_NAME			;//= "UserData";
	extern const char* DURABILITY_QOS_POLICY_NAME			;//= "Durability";
	extern const char* PRESENTATION_QOS_POLICY_NAME			;//= "Presentation";
	extern const char* DEADLINE_QOS_POLICY_NAME			;//= "Deadline";
	extern const char* LATENCYBUDGET_QOS_POLICY_NAME		;//= "LatencyBudget";
	extern const char* OWNERSHIP_QOS_POLICY_NAME			;//= "Ownership";
	extern const char* OWNERSHIPSTRENGTH_QOS_POLICY_NAME		;//= "OwnershipStrength";
	extern const char* LIVELINESS_QOS_POLICY_NAME			;//= "Liveliness";
	extern const char* TIMEBASEDFILTER_QOS_POLICY_NAME		;//= "TimeBasedFilter";
	extern const char* PARTITION_QOS_POLICY_NAME			;//= "Partition";
	extern const char* RELIABILITY_QOS_POLICY_NAME			;//= "Reliability";
	extern const char* DESTINATIONORDER_QOS_POLICY_NAME		;//= "DestinationOrder";
	extern const char* HISTORY_QOS_POLICY_NAME			;//= "History";
	extern const char* RESOURCELIMITS_QOS_POLICY_NAME		;//= "ResourceLimits";
	extern const char* ENTITYFACTORY_QOS_POLICY_NAME		;//= "EntityFactory";
	extern const char* WRITERDATALIFECYCLE_QOS_POLICY_NAME		;//= "WriterDataLifecycle";
	extern const char* READERDATALIFECYCLE_QOS_POLICY_NAME		;//= "ReaderDataLifecycle";
	extern const char* TOPICDATA_QOS_POLICY_NAME			;//= "TopicData";
	extern const char* GROUPDATA_QOS_POLICY_NAME			;//= "TransportPriority";
	extern const char* LIFESPAN_QOS_POLICY_NAME			;//= "Lifespan";
	extern const char* DURABILITYSERVICE_POLICY_NAME		;//= "DurabilityService";
	const QosPolicyId_t INVALID_QOS_POLICY_ID		= 0;
	const QosPolicyId_t USERDATA_QOS_POLICY_ID		= 1;
	const QosPolicyId_t DURABILITY_QOS_POLICY_ID		= 2;
	const QosPolicyId_t PRESENTATION_QOS_POLICY_ID		= 3;
	const QosPolicyId_t DEADLINE_QOS_POLICY_ID		= 4;
	const QosPolicyId_t LATENCYBUDGET_QOS_POLICY_ID		= 5;
	const QosPolicyId_t OWNERSHIP_QOS_POLICY_ID		= 6;
	const QosPolicyId_t OWNERSHIPSTRENGTH_QOS_POLICY_ID	= 7;
	const QosPolicyId_t LIVELINESS_QOS_POLICY_ID		= 8;
	const QosPolicyId_t TIMEBASEDFILTER_QOS_POLICY_ID	= 9;
	const QosPolicyId_t PARTITION_QOS_POLICY_ID		= 10;
	const QosPolicyId_t RELIABILITY_QOS_POLICY_ID		= 11;
	const QosPolicyId_t DESTINATIONORDER_QOS_POLICY_ID	= 12;
	const QosPolicyId_t HISTORY_QOS_POLICY_ID		= 13;
	const QosPolicyId_t RESOURCELIMITS_QOS_POLICY_ID	= 14;
	const QosPolicyId_t ENTITYFACTORY_QOS_POLICY_ID		= 15;
	const QosPolicyId_t WRITERDATALIFECYCLE_QOS_POLICY_ID	= 16;
	const QosPolicyId_t READERDATALIFECYCLE_QOS_POLICY_ID	= 17;
	const QosPolicyId_t TOPICDATA_QOS_POLICY_ID		= 18;
	const QosPolicyId_t GROUPDATA_QOS_POLICY_ID		= 19;
	const QosPolicyId_t TRANSPORTPRIORITY_QOS_POLICY_ID	= 20;
	const QosPolicyId_t LIFESPAN_QOS_POLICY_ID		= 21;
	const QosPolicyId_t DURABILITYSERVICE_QOS_POLICY_ID	= 22;
	
	struct UserDataQosPolicy {
		sequence<uint8_t> value;
		
		UserDataQosPolicy();
		UserDataQosPolicy(sequence<uint8_t>* value);
		UserDataQosPolicy(uint8_t* array, uint32_t size);
		virtual ~UserDataQosPolicy();
	};
	
	struct TopicDataQosPolicy {
		sequence<uint8_t> value;
		
		TopicDataQosPolicy();
		TopicDataQosPolicy(sequence<uint8_t>* value);
		TopicDataQosPolicy(uint8_t* array, uint32_t size);
		virtual ~TopicDataQosPolicy();
	};
	
	struct GroupDataQosPolicy {
		sequence<uint8_t> value;
		
		GroupDataQosPolicy();
		GroupDataQosPolicy(sequence<uint8_t>* value);
		GroupDataQosPolicy(uint8_t* array, uint32_t size);
		virtual ~GroupDataQosPolicy();
	};
	
	struct TransportPriorityQosPolicy {
		int32_t value;
		
		TransportPriorityQosPolicy();
		TransportPriorityQosPolicy(int32_t value);
		virtual ~TransportPriorityQosPolicy();
	};
	
	struct LifespanQosPolicy {
		Duration_t duration;
		
		LifespanQosPolicy();
		LifespanQosPolicy(Duration_t* duration);
		virtual ~LifespanQosPolicy();
	};
	
	enum DurabilityQosPolicyKind {
		VOLATILE_DURABILITY_QOS,
		TRANSIENT_LOCAL_DURABILITY_QOS,
		TRANSIENT_DURABILITY_QOS,
		PERSISTENT_DURABILITY_QOS
	};
	
	struct DurabilityQosPolicy {
		DurabilityQosPolicyKind kind;
		
		DurabilityQosPolicy();
		DurabilityQosPolicy(DurabilityQosPolicyKind* kind);
		virtual ~DurabilityQosPolicy();
	};
	
	enum PresentationQosPolicyAccessScopeKind {
		INSTANCE_PRESENTATION_QOS,
		TOPIC_PRESENTATION_QOS,
		GROUP_PRESENTATION_QOS
	};
	
	struct PresentationQosPolicy {
		PresentationQosPolicyAccessScopeKind access_scope;
		bool coherent_access;
		bool ordered_access;
		
		PresentationQosPolicy();
		PresentationQosPolicy(
			PresentationQosPolicyAccessScopeKind* access_scope,
			bool coherent_access,
			bool ordered_access);
		virtual ~PresentationQosPolicy();
	};
	
	struct DeadlineQosPolicy {
		Duration_t period;
		
		DeadlineQosPolicy();
		DeadlineQosPolicy(Duration_t* period);
		virtual ~DeadlineQosPolicy();
	};
	
	struct LatencyBudgetQosPolicy {
		Duration_t duration;
		
		LatencyBudgetQosPolicy();
		LatencyBudgetQosPolicy(Duration_t* duration);
		virtual ~LatencyBudgetQosPolicy();
	};
	
	enum OwnershipQosPolicyKind {
		SHARED_OWNERSHIP_QOS,
		EXCLUSIVE_OWNERSHIP_QOS
	};
	
	struct OwnershipQosPolicy {
		OwnershipQosPolicyKind kind;
		
		OwnershipQosPolicy();
		OwnershipQosPolicy(OwnershipQosPolicyKind* kind);
		virtual ~OwnershipQosPolicy();
	};
	
	struct OwnershipStrengthQosPolicy {
		int32_t value;
		
		OwnershipStrengthQosPolicy();
		OwnershipStrengthQosPolicy(int32_t value);
		virtual ~OwnershipStrengthQosPolicy();
	};
	
	enum LivelinessQosPolicyKind {
		AUTOMATIC_LIVELINESS_QOS,
		MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
		MANUAL_BY_TOPIC_LIVELINESS_QOS
	};
	
	struct LivelinessQosPolicy {
		LivelinessQosPolicyKind kind;
		Duration_t lease_duration;
		
		LivelinessQosPolicy();
		LivelinessQosPolicy(
			LivelinessQosPolicyKind* kind,
			Duration_t* lease_duration);
		virtual ~LivelinessQosPolicy();
	};
	
	struct TimeBasedFilterQosPolicy {
		Duration_t minimum_separation;
		
		TimeBasedFilterQosPolicy();
		TimeBasedFilterQosPolicy(Duration_t* minimum_separation);
		virtual ~TimeBasedFilterQosPolicy();
	};
	
	struct PartitionQosPolicy {
		StringSeq name;
		
		PartitionQosPolicy();
		PartitionQosPolicy(StringSeq* name);
		virtual ~PartitionQosPolicy();
	};
	
	enum ReliabilityQosPolicyKind {
		BEST_EFFORT_RELIABILITY_QOS,
		RELIABLE_RELIABILITY_QOS
	};
	
	struct ReliabilityQosPolicy {
		ReliabilityQosPolicyKind kind;
		Duration_t max_blocking_time;
		
		ReliabilityQosPolicy();
		ReliabilityQosPolicy(
			ReliabilityQosPolicyKind* kind,
			Duration_t* max_blocking_time);
		virtual ~ReliabilityQosPolicy();
	};
	
	enum DestinationOrderQosPolicyKind {
		BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
		BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
	};
	
	struct DestinationOrderQosPolicy {
		DestinationOrderQosPolicyKind kind;
		
		DestinationOrderQosPolicy();
		DestinationOrderQosPolicy(DestinationOrderQosPolicyKind* kind);
		virtual ~DestinationOrderQosPolicy();
	};
	
	enum HistoryQosPolicyKind {
		KEEP_LAST_HISTORY_QOS,
		KEEP_ALL_HISTORY_QOS
	};
	 
	struct HistoryQosPolicy {
		HistoryQosPolicyKind kind;
		int32_t depth;
		
		HistoryQosPolicy();
		HistoryQosPolicy(
			HistoryQosPolicyKind* kind,
			int32_t depth);
		virtual ~HistoryQosPolicy();
	};
	
	struct ResourceLimitsQosPolicy {
		int32_t max_samples;
		int32_t max_instances;
		int32_t max_samples_per_instance;
		
		ResourceLimitsQosPolicy();
		ResourceLimitsQosPolicy(
			int32_t max_samples,
			int32_t max_instances,
			int32_t max_samples_per_instance);
		virtual ~ResourceLimitsQosPolicy();
	};
	
	struct EntityFactoryQosPolicy {
		bool autoenable_created_entities;
		
		EntityFactoryQosPolicy();
		EntityFactoryQosPolicy(bool autoenable_created_entities);
		virtual ~EntityFactoryQosPolicy();
	};
	
	struct WriterDataLifecycleQosPolicy {
		bool autodispose_unregistered_instances;
		
		WriterDataLifecycleQosPolicy();
		WriterDataLifecycleQosPolicy(bool autodispose_unregistered_instances);
		virtual ~WriterDataLifecycleQosPolicy();
	};
	
	struct ReaderDataLifecycleQosPolicy {
		Duration_t autopurge_nowriter_samples_delay;
		Duration_t autopurge_disposed_samples_delay;
		
		ReaderDataLifecycleQosPolicy();
		ReaderDataLifecycleQosPolicy(
			Duration_t* autopurge_nowriter_samples_delay,
			Duration_t* autopurge_disposed_samples_delay);
		virtual ~ReaderDataLifecycleQosPolicy();
	};
	
	struct DurabilityServiceQosPolicy {
		Duration_t		service_cleanup_delay;
		HistoryQosPolicyKind	history_kind;
		int32_t			history_depth;
		int32_t			max_samples;
		int32_t			max_instances;
		int32_t			max_samples_per_instance;
		
		DurabilityServiceQosPolicy();
		DurabilityServiceQosPolicy(
			Duration_t* service_cleanup_delay,
			HistoryQosPolicyKind* history_kind,
			int32_t history_depth,
			int32_t max_samples,
			int32_t max_instances,
			int32_t max_samples_per_instance);
		virtual ~DurabilityServiceQosPolicy();
	};
	
	struct DomainParticipantFactoryQos {
		EntityFactoryQosPolicy	entity_factory;
		
		DomainParticipantFactoryQos();
		DomainParticipantFactoryQos(EntityFactoryQosPolicy* entity_factory);
		virtual ~DomainParticipantFactoryQos();
	};
	
	struct DomainParticipantQos {
		UserDataQosPolicy	user_data;
		EntityFactoryQosPolicy	entity_factory;
		
		DomainParticipantQos();
		DomainParticipantQos(
			UserDataQosPolicy* user_data,
			EntityFactoryQosPolicy* entity_factory);
		virtual ~DomainParticipantQos();
	};
	
	struct TopicQos {
		TopicDataQosPolicy		topic_data;
		DurabilityQosPolicy		durability;
		DurabilityServiceQosPolicy	durability_service;
		DeadlineQosPolicy		deadline;
		LatencyBudgetQosPolicy		latency_budget;
		LivelinessQosPolicy		liveliness;
		ReliabilityQosPolicy		reliability;
		DestinationOrderQosPolicy	destination_order;
		HistoryQosPolicy		history;
		ResourceLimitsQosPolicy		resource_limits;
		TransportPriorityQosPolicy	transport_priority;
		LifespanQosPolicy		lifespan;
		OwnershipQosPolicy		ownership;
		
		TopicQos();
		TopicQos(
			TopicDataQosPolicy* topic_data,
			DurabilityQosPolicy* durability,
			DurabilityServiceQosPolicy* durability_service,
			DeadlineQosPolicy* deadline,
			LatencyBudgetQosPolicy* latency_budget,
			LivelinessQosPolicy* liveliness,
			ReliabilityQosPolicy* reliability,
			DestinationOrderQosPolicy* destination_order,
			HistoryQosPolicy* history,
			ResourceLimitsQosPolicy* resource_limits,
			TransportPriorityQosPolicy* transport_priority,
			LifespanQosPolicy* lifespan,
			OwnershipQosPolicy* ownership);
		virtual ~TopicQos();
	};
	
	struct DataWriterQos {
		DurabilityQosPolicy		durability;
		DurabilityServiceQosPolicy	durability_service;
		DeadlineQosPolicy		deadline;
		LatencyBudgetQosPolicy		latency_budget;
		LivelinessQosPolicy		liveliness;
		ReliabilityQosPolicy		reliability;
		DestinationOrderQosPolicy	destination_order;
		HistoryQosPolicy		history;
		ResourceLimitsQosPolicy		resource_limits;
		TransportPriorityQosPolicy	transport_priority;
		LifespanQosPolicy		lifespan;
		UserDataQosPolicy		user_data;
		OwnershipQosPolicy		ownership;
		OwnershipStrengthQosPolicy	ownership_strength;
		WriterDataLifecycleQosPolicy	writer_data_lifecycle;
		
		DataWriterQos();
		DataWriterQos(
			DurabilityQosPolicy* durability,
			DurabilityServiceQosPolicy* durability_service,
			DeadlineQosPolicy* deadline,
			LatencyBudgetQosPolicy* latency_budget,
			LivelinessQosPolicy* liveliness,
			ReliabilityQosPolicy* reliability,
			DestinationOrderQosPolicy* destination_order,
			HistoryQosPolicy* history,
			ResourceLimitsQosPolicy* resource_limits,
			TransportPriorityQosPolicy* transport_priority,
			LifespanQosPolicy* lifespan,
			UserDataQosPolicy* user_data,
			OwnershipQosPolicy* ownership,
			OwnershipStrengthQosPolicy* ownership_strength,
			WriterDataLifecycleQosPolicy* writer_data_lifecycle);
		virtual ~DataWriterQos();
	};
	
	struct PublisherQos {
		PresentationQosPolicy		presentation;
		PartitionQosPolicy		partition;
		GroupDataQosPolicy		group_data;
		EntityFactoryQosPolicy		entity_factory;
		
		PublisherQos();
		PublisherQos(
			PresentationQosPolicy* presentation,
			PartitionQosPolicy* partition,
			GroupDataQosPolicy* group_data,
			EntityFactoryQosPolicy* entity_factory);
		virtual ~PublisherQos();
	};
	
	struct DataReaderQos {
		DurabilityQosPolicy		durability;
		DeadlineQosPolicy		deadline;
		LatencyBudgetQosPolicy		latency_budget;
		LivelinessQosPolicy		liveliness;
		ReliabilityQosPolicy		reliability;
		DestinationOrderQosPolicy	destination_order;
		HistoryQosPolicy		history;
		ResourceLimitsQosPolicy		resource_limits;
		UserDataQosPolicy		user_data;
		OwnershipQosPolicy		ownership;
		TimeBasedFilterQosPolicy	time_based_filter;
		ReaderDataLifecycleQosPolicy	reader_data_lifecycle;
		
		DataReaderQos();
		DataReaderQos(
			DurabilityQosPolicy* durability,
			DeadlineQosPolicy* deadline,
			LatencyBudgetQosPolicy* latency_budget,
			LivelinessQosPolicy* liveliness,
			ReliabilityQosPolicy* reliability,
			DestinationOrderQosPolicy* destination_order,
			HistoryQosPolicy* history,
			ResourceLimitsQosPolicy* resource_limits,
			UserDataQosPolicy* user_data,
			OwnershipQosPolicy* ownership,
			TimeBasedFilterQosPolicy* time_based_filter,
			ReaderDataLifecycleQosPolicy* reader_data_lifecycle);
		virtual ~DataReaderQos();
	};
	
	struct SubscriberQos {
		PresentationQosPolicy		presentation;
		PartitionQosPolicy		partition;
		GroupDataQosPolicy		group_data;
		EntityFactoryQosPolicy		entity_factory;
		
		SubscriberQos();
		SubscriberQos(
			PresentationQosPolicy* presentation,
			PartitionQosPolicy* partition,
			GroupDataQosPolicy* group_data,
			EntityFactoryQosPolicy* entity_factory);
		virtual ~SubscriberQos();
	};
	
	// ----------------------------------------------------------------------
	struct ParticipantBuiltinTopicData {
		BuiltinTopicKey_t		key;
		UserDataQosPolicy		user_data;
		
		ParticipantBuiltinTopicData();
		ParticipantBuiltinTopicData(
			BuiltinTopicKey_t key,
			UserDataQosPolicy* user_data);
		virtual ~ParticipantBuiltinTopicData();
	};
	
	struct TopicBuiltinTopicData {
		BuiltinTopicKey_t		key;
		char*				name;
		char*				type_name;
		DurabilityQosPolicy		durability;
		DurabilityServiceQosPolicy	durability_service;
		DeadlineQosPolicy		deadline;
		LatencyBudgetQosPolicy		latency_budget;
		LivelinessQosPolicy		liveliness;
		ReliabilityQosPolicy		reliability;
		TransportPriorityQosPolicy	transport_priority;
		LifespanQosPolicy		lifespan;
		DestinationOrderQosPolicy	destination_order;
		HistoryQosPolicy		history;
		ResourceLimitsQosPolicy		resource_limits;
		OwnershipQosPolicy		ownership;
		TopicDataQosPolicy		topic_data;
		
		TopicBuiltinTopicData();
		TopicBuiltinTopicData(
			BuiltinTopicKey_t key,
			char* name,
			char* type_name,
			DurabilityQosPolicy* durability,
			DurabilityServiceQosPolicy* durability_service,
			DeadlineQosPolicy* deadline,
			LatencyBudgetQosPolicy* latency_budget,
			LivelinessQosPolicy* liveliness,
			ReliabilityQosPolicy* reliability,
			TransportPriorityQosPolicy* transport_priority,
			LifespanQosPolicy* lifespan,
			DestinationOrderQosPolicy* destination_order,
			HistoryQosPolicy* history,
			ResourceLimitsQosPolicy* resource_limits,
			OwnershipQosPolicy* ownership,
			TopicDataQosPolicy* topic_data);
		virtual ~TopicBuiltinTopicData();
	};
	
	struct PublicationBuiltinTopicData {
		BuiltinTopicKey_t		key;
		BuiltinTopicKey_t		participant_key;
		char*				topic_name;
		char*				type_name;
		DurabilityQosPolicy		durability;
		DurabilityServiceQosPolicy	durability_service;
		DeadlineQosPolicy		deadline;
		LatencyBudgetQosPolicy		latency_budget;
		LivelinessQosPolicy		liveliness;
		ReliabilityQosPolicy		reliability;
		LifespanQosPolicy		lifespan;
		UserDataQosPolicy		user_data;
		OwnershipQosPolicy		ownership;
		OwnershipStrengthQosPolicy	ownership_strength;
		DestinationOrderQosPolicy	destination_order;
		PresentationQosPolicy		presentation;
		PartitionQosPolicy		partition;
		TopicDataQosPolicy		topic_data;
		GroupDataQosPolicy		group_data;
		
		PublicationBuiltinTopicData();
		PublicationBuiltinTopicData(
			BuiltinTopicKey_t key,
			BuiltinTopicKey_t participant_key,
			char* topic_name,
			char* type_name,
			DurabilityQosPolicy* durability,
			DurabilityServiceQosPolicy* durability_service,
			DeadlineQosPolicy* deadline,
			LatencyBudgetQosPolicy* latency_budget,
			LivelinessQosPolicy* liveliness,
			ReliabilityQosPolicy* reliability,
			LifespanQosPolicy* lifespan,
			UserDataQosPolicy* user_data,
			OwnershipQosPolicy* ownership,
			OwnershipStrengthQosPolicy* ownership_strength,
			DestinationOrderQosPolicy* destination_order,
			PresentationQosPolicy* presentation,
			PartitionQosPolicy* partition,
			TopicDataQosPolicy* topic_data,
			GroupDataQosPolicy* group_data);
		virtual ~PublicationBuiltinTopicData();
	};
	
	struct SubscriptionBuiltinTopicData {
		BuiltinTopicKey_t		key;
		BuiltinTopicKey_t		participant_key;
		char*				topic_name;
		char*				type_name;
		DurabilityQosPolicy		durability;
		DeadlineQosPolicy		deadline;
		LatencyBudgetQosPolicy		latency_budget;
		LivelinessQosPolicy		liveliness;
		ReliabilityQosPolicy		reliability;
		OwnershipQosPolicy		ownership;
		DestinationOrderQosPolicy	destination_order;
		UserDataQosPolicy		user_data;
		TimeBasedFilterQosPolicy	time_based_filter;
		PresentationQosPolicy		presentation;
		PartitionQosPolicy		partition;
		TopicDataQosPolicy		topic_data;
		GroupDataQosPolicy		group_data;
		
		SubscriptionBuiltinTopicData();
		SubscriptionBuiltinTopicData(
			BuiltinTopicKey_t key,
			BuiltinTopicKey_t participant_key,
			char* topic_name,
			char* type_name,
			DurabilityQosPolicy* durability,
			DeadlineQosPolicy* deadline,
			LatencyBudgetQosPolicy* latency_budget,
			LivelinessQosPolicy* liveliness,
			ReliabilityQosPolicy* reliability,
			OwnershipQosPolicy* ownership,
			DestinationOrderQosPolicy* destination_order,
			UserDataQosPolicy* user_data,
			TimeBasedFilterQosPolicy* time_based_filter,
			PresentationQosPolicy* presentation,
			PartitionQosPolicy* partition,
			TopicDataQosPolicy* topic_data,
			GroupDataQosPolicy* group_data);
		virtual ~SubscriptionBuiltinTopicData();
	};
	
	// ----------------------------------------------------------------------
	class Entity {
	public:
		Entity();
		virtual ~Entity();
		
		// abstract ReturnCode_t set_qos(
		// 	const EntityQos* qos);
		// abstract ReturnCode_t get_qos(
		// 	EntityQos* qos);
		// abstract ReturnCode_t set_listener(
		// 	const Listener* l,
		// 	const StatusMask* mask);
		// abstract Listener* get_listener();
		
		ReturnCode_t enable();
		StatusCondition* get_statuscondition();
		StatusMask* get_status_changes();
		InstanceHandle_t get_instance_handle();
	};
	
	// ----------------------------------------------------------------------
	class DomainParticipant : Entity {
	public:
		DomainParticipant();
		virtual ~DomainParticipant();
		
		// Factory interfaces
		Publisher* create_publisher(
			const PublisherQos* qos,
			const PublisherListener* a_listener,
			const StatusMask* mask);
		ReturnCode_t delete_publisher(
			const Publisher* p);
		Subscriber* create_subscriber(
			const SubscriberQos* qos,
			const SubscriberListener* a_listener,
			const StatusMask* mask);
		ReturnCode_t delete_subscriber(
			const Subscriber* s);
		Subscriber* get_builtin_subscriber();
		Topic* create_topic(
			const char* topic_name,
			const char* type_name,
			const TopicQos* qos,
			const TopicListener* a_listener,
			const StatusMask* mask);
		ReturnCode_t delete_topic(
			const Topic* a_topic);
		Topic* find_topic(
			const char* topic_name,
			const Duration_t* timeout);
		TopicDescription* lookup_topicdescription(
			const char* name);
		ContentFilteredTopic* create_contentfilteredtopic(
			const char* name,
			const Topic* related_topic,
			const char* filter_expression,
			const StringSeq* expression_parameters);
		ReturnCode_t delete_contentfilteredtopic(
			const ContentFilteredTopic* a_contentfilteredtopic);
		MultiTopic* create_multitopic(
			const char* name,
			const char* type_name,
			const char* subscription_expression,
			const StringSeq* expression_parameters);
		ReturnCode_t delete_multitopic(
			const MultiTopic* a_multitopic);
		ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			const DomainParticipantQos* qos);
		ReturnCode_t get_qos(
			DomainParticipantQos* qos);
		ReturnCode_t set_listener(
			const DomainParticipantListener* a_listener,
			const StatusMask* mask);
		DomainParticipantListener* get_listener();
		ReturnCode_t ignore_participant(
			InstanceHandle_t handle);
		ReturnCode_t ignore_topic(
			InstanceHandle_t handle);
		ReturnCode_t ignore_publication(
			InstanceHandle_t handle);
		ReturnCode_t ignore_subscription(
			InstanceHandle_t handle);
		DomainId_t get_domain_id();
		ReturnCode_t assert_liveliness();
		ReturnCode_t set_default_publisher_qos(
			const PublisherQos* qos);
		ReturnCode_t get_default_publisher_qos(
			PublisherQos* qos);
		ReturnCode_t set_default_subscriber_qos(
			const SubscriberQos* qos);
		ReturnCode_t get_default_subscriber_qos(
			SubscriberQos* qos);
		ReturnCode_t set_default_topic_qos(
			const TopicQos* qos);
		ReturnCode_t get_default_topic_qos(
			TopicQos* qos);
		ReturnCode_t get_discovered_participants(
			InstanceHandleSeq* participant_handles);
		ReturnCode_t get_discovered_participant_data(
			ParticipantBuiltinTopicData* participant_data,
			InstanceHandle_t participant_handle);
		ReturnCode_t get_discovered_topics(
			InstanceHandleSeq* topic_handles);
		ReturnCode_t get_discovered_topic_data(
			TopicBuiltinTopicData* topic_data,
			InstanceHandle_t topic_handle);
		bool contains_entity(
			InstanceHandle_t a_handle);
		ReturnCode_t get_current_time(
			Time_t* current_time);
	};
	
	class DomainParticipantFactory {
	public:
		DomainParticipantFactory();
		virtual ~DomainParticipantFactory();
		
		DomainParticipant* create_participant(
			DomainId_t domain_id,
			const DomainParticipantQos* qos,
			const DomainParticipantListener* a_listener,
			const StatusMask* mask);
		ReturnCode_t delete_participant(
			const DomainParticipant* a_participant);
		DomainParticipant* lookup_participant(
			DomainId_t domain_id);
		ReturnCode_t set_default_participant_qos(
			const DomainParticipantQos* qos);
		ReturnCode_t get_default_participant_qos(
			DomainParticipantQos* qos);
		ReturnCode_t set_qos(
			const DomainParticipantFactoryQos* qos);
		ReturnCode_t get_qos(
			DomainParticipantFactoryQos* qos);
	};
	
	class TypeSupport {
	public:
		TypeSupport();
		virtual ~TypeSupport();
		
		// abstract ReturnCode_t register_type(
		// 	const DomainParticipant* domain,
		// 	const char* type_name);
		// abstract char* get_type_name();
	};
	
	// ----------------------------------------------------------------------
	class TopicDescription {
	public:
		TopicDescription();
		virtual ~TopicDescription();
		
		char* get_type_name();
		char* get_name();
		DomainParticipant* get_participant();
	};
	
	class Topic : Entity, TopicDescription {
	public:
		Topic();
		virtual ~Topic();
		
		ReturnCode_t set_qos(
			const TopicQos* qos);
		ReturnCode_t get_qos(
			TopicQos* qos);
		ReturnCode_t set_listener(
			const TopicListener* a_listener,
			const StatusMask* mask);
		TopicListener* get_listener();
		
		// Access the status
		ReturnCode_t get_inconsistent_topic_status(
			InconsistentTopicStatus* a_status);
	};
	
	class ContentFilteredTopic : TopicDescription {
	public:
		ContentFilteredTopic();
		virtual ~ContentFilteredTopic();
		
		char* get_filter_expression();
		
		ReturnCode_t get_expression_parameters(
			StringSeq* expression_parameters);
		
		ReturnCode_t set_expression_parameters(
			const StringSeq* expression_parameters);
		
		Topic* get_related_topic();
	};
	
	class MultiTopic : TopicDescription {
	public:
		MultiTopic();
		virtual ~MultiTopic();
		
		char* get_subscription_expression();
		
		ReturnCode_t get_expression_parameters(
			StringSeq* expression_parameters);
		
		ReturnCode_t set_expression_parameters(
			const StringSeq* expression_parameters);
	};
	
	// ----------------------------------------------------------------------
	class Publisher : Entity {
	public:
		Publisher();
		virtual ~Publisher();
		
		DataWriter* create_datawriter(
			const Topic* a_topic,
			const DataWriterQos* qos,
			const DataWriterListener* a_listener,
			const StatusMask* mask);
		ReturnCode_t delete_datawriter(
			const DataWriter* a_datawriter);
		DataWriter* lookup_datawriter(
			const char* topic_name);
		ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			const PublisherQos* qos);
		ReturnCode_t get_qos(
			PublisherQos* qos);
		ReturnCode_t set_listener(
			const PublisherListener* a_listener,
			const StatusMask* mask);
		PublisherListener* get_listener();
		ReturnCode_t suspend_publications();
		ReturnCode_t resume_publications();
		ReturnCode_t begin_coherent_changes();
		ReturnCode_t end_coherent_changes();
		ReturnCode_t wait_for_acknowledgments(
			const Duration_t* max_wait);
		DomainParticipant* get_participant();
		ReturnCode_t set_default_datawriter_qos(
			const DataWriterQos* qos);
		ReturnCode_t get_default_datawriter_qos(
			DataWriterQos* qos);
		ReturnCode_t copy_from_topic_qos(
			DataWriterQos* a_datawriter_qos,
			const TopicQos* a_topic_qos);
	};
	
	class DataWriter : Entity {
	public:
		DataWriter();
		virtual ~DataWriter();
		
		// abstract InstanceHandle_t register_instance(
		// 	const Data* instance_data);
		// abstract InstanceHandle_t register_instance_w_timestamp(
		// 	const Data* instance_data,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t unregister_instance(
		// 	const Data* instance_data,
		// 	InstanceHandle_t handle);
		// abstract ReturnCode_t unregister_instance_w_timestamp(
		// 	const Data* instance_data,
		// 	InstanceHandle_t handle,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t write(
		// 	const Data* instance_data,
		// 	InstanceHandle_t handle);
		// abstract ReturnCode_t write_w_timestamp(
		// 	const Data* instance_data,
		// 	InstanceHandle_t handle,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t dispose(
		// 	const Data* instance_data,
		// 	InstanceHandle_t instance_handle);
		// abstract ReturnCode_t dispose_w_timestamp(
		// 	const Data* instance_data,
		// 	InstanceHandle_t instance_handle,
		// 	const Time_t* source_timestamp);
		// abstract ReturnCode_t get_key_value(
		// 	Data* key_holder,
		// 	InstanceHandle_t handle);
		// abstract InstanceHandle_t lookup_instance(
		// 	const Data* instance_data);
		
		ReturnCode_t set_qos(
			const DataWriterQos* qos);
		ReturnCode_t get_qos(
			DataWriterQos* qos);
		ReturnCode_t set_listener(
			const DataWriterListener* a_listener,
			const StatusMask* mask);
		DataWriterListener* get_listener();
		Topic* get_topic();
		Publisher* get_publisher();
		ReturnCode_t wait_for_acknowledgments(
			const Duration_t* max_wait);
		// Access the status
		ReturnCode_t get_liveliness_lost_status(
			LivelinessLostStatus* status);
		ReturnCode_t get_offered_deadline_missed_status(
			OfferedDeadlineMissedStatus* status);
		ReturnCode_t get_offered_incompatible_qos_status(
			OfferedIncompatibleQosStatus* status);
		ReturnCode_t get_publication_matched_status(
			PublicationMatchedStatus* status);
		ReturnCode_t assert_liveliness();
		ReturnCode_t get_matched_subscriptions(
			InstanceHandleSeq* subscription_handles);
		ReturnCode_t get_matched_subscription_data(
			SubscriptionBuiltinTopicData* subscription_data,
			InstanceHandle_t subscription_handle);
	};
	
	// ----------------------------------------------------------------------
	class Subscriber : Entity {
	public:
		Subscriber();
		virtual ~Subscriber();
		
		DataReader* create_datareader(
			const TopicDescription* a_topic,
			const DataReaderQos* qos,
			const DataReaderListener* a_listener,
			const StatusMask* mask);
		ReturnCode_t delete_datareader(
			const DataReader* a_datareader);
		ReturnCode_t delete_contained_entities();
		DataReader* lookup_datareader(
			const char* topic_name);
		ReturnCode_t get_datareaders(
			DataReaderSeq* readers,
			const SampleStateMask* sample_states,
			const ViewStateMask* view_states,
			const InstanceStateMask* instance_states);
		ReturnCode_t notify_datareaders();
		ReturnCode_t set_qos(
			const SubscriberQos* qos);
		ReturnCode_t get_qos(
			SubscriberQos* qos);
		ReturnCode_t set_listener(
			const SubscriberListener* a_listener,
			const StatusMask* mask);
		SubscriberListener* get_listener();
		ReturnCode_t begin_access();
		ReturnCode_t end_access();
		DomainParticipant* get_participant();
		ReturnCode_t set_default_datareader_qos(
			const DataReaderQos* qos);
		ReturnCode_t get_default_datareader_qos(
			DataReaderQos* qos);
		ReturnCode_t copy_from_topic_qos(
			DataReaderQos* a_datareader_qos,
			const TopicQos* a_topic_qos);
	};
	
	class DataReader : Entity {
	public:
		DataReader();
		virtual ~DataReader();
		
		// abstract ReturnCode_t read(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t take(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t read_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t take_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t read_next_sample(
		// 	Data* data_values,
		// 	SampleInfo* sample_info);
		// abstract ReturnCode_t take_next_sample(
		// 	Data* data_values,
		// 	SampleInfo* sample_info);
		// abstract ReturnCode_t read_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t a_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t take_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t a_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t read_next_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t take_next_instance(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const SampleStateMask* sample_states,
		// 	const ViewStateMask* view_states,
		// 	const InstanceStateMask* instance_states);
		// abstract ReturnCode_t read_next_instance_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t take_next_instance_w_condition(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos,
		// 	const int32_t* max_samples,
		// 	InstanceHandle_t previous_handle,
		// 	const ReadCondition* a_condition);
		// abstract ReturnCode_t return_loan(
		// 	DataSeq* data_values,
		// 	SampleInfoSeq* sample_infos);
		// abstract ReturnCode_t get_key_value(
		// 	Data* key_holder,
		// 	InstanceHandle_t handle);
		// abstract InstanceHandle_t lookup_instance(
		// 	const Data* instance_data);
		
		ReadCondition* create_readcondition(
			const SampleStateMask* sample_states,
			const ViewStateMask* view_states,
			const InstanceStateMask* instance_states);
		QueryCondition* create_querycondition(
			const SampleStateMask* sample_states,
			const ViewStateMask* view_states,
			const InstanceStateMask* instance_states,
			const char* query_expression,
			const StringSeq* query_parameters);
		ReturnCode_t delete_readcondition(
			const ReadCondition* a_condition);
		ReturnCode_t delete_contained_entities();
		ReturnCode_t set_qos(
			const DataReaderQos* qos);
		ReturnCode_t get_qos(
			DataReaderQos* qos);
		ReturnCode_t set_listener(
			const DataReaderListener* a_listener,
			const StatusMask* mask);
		DataReaderListener* get_listener();
		TopicDescription* get_topicdescription();
		Subscriber* get_subscriber();
		ReturnCode_t get_sample_rejected_status(
			SampleRejectedStatus* status);
		ReturnCode_t get_liveliness_changed_status(
			LivelinessChangedStatus* status);
		ReturnCode_t get_requested_deadline_missed_status(
			RequestedDeadlineMissedStatus* status);
		ReturnCode_t get_requested_incompatible_qos_status(
			RequestedIncompatibleQosStatus* status);
		ReturnCode_t get_subscription_matched_status(
			SubscriptionMatchedStatus* status);
		ReturnCode_t get_sample_lost_status(
			SampleLostStatus* status);
		ReturnCode_t wait_for_historical_data(
			const Duration_t* max_wait);
		ReturnCode_t get_matched_publications(
			InstanceHandleSeq* publication_handles);
		ReturnCode_t get_matched_publication_data(
			PublicationBuiltinTopicData* publication_data,
			InstanceHandle_t publication_handle);
	};
	
	struct SampleInfo {
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
		
		SampleInfo();
		virtual ~SampleInfo();
	};
	
	typedef sequence<SampleInfo> SampleInfoSeq;
};

#endif /* __DDS_DSCP_H__ */