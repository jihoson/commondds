// DIDE-2

#if !defined(__RTPS_DISCOVERED_H)
#define __RTPS_DISCOVERED_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


#include <core.h>
#include <cpsdcps.h>
#include <dcps_func.h>


typedef uint8_t	octet;

typedef struct GUID_t GUID_t;

typedef struct GuidPrefix_t GuidPrefix_t;

typedef struct EntityId_t EntityId_t;

typedef struct SequenceNumber_t SequenceNumber_t;

typedef struct Locator_t Locator_t;

typedef int32_t TopicKind_t;

typedef int32_t ChangeKind_t;

typedef int32_t ReliabilityKind_t;

typedef struct ProtocolVersion_t ProtocolVersion_t;

typedef struct VendorId_t VendorId_t;

struct VendorId_t
{
	octet vendor_id[2];
};


static VendorId_t VENDORID_UNKNOWN = {0,0};

static VendorId_t VENDORID_ETRI = {1,17};


#define SEQUENCENUMBER_UNKNOWN {-1,0}

#define LOCATOR_INVALID {LOCATOR_KIND_INVALID, LOCATOR_PORT_INVALID, LOCATOR_ADDRESS_INVALID}
#define LOCATOR_KIND_INVALID -1
#define LOCATOR_ADDRESS_INVALID {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define LOCATOR_PORT_INVALID 0
#define LOCATOR_KIND_RESERVED 0
#define LOCATOR_KIND_UDPv4 1
#define LOCATOR_KIND_UDPv6 2

#define NO_KEY		1
#define WITH_KEY	2

#define BEST_EFFORT 1
#define RELIABLE	3

#define PROTOCOLVERSION_1_0 {1,0}
#define PROTOCOLVERSION_1_1 {1,1}
#define PROTOCOLVERSION_2_0 {2,0}
#define PROTOCOLVERSION_2_1 {2,1}
#define PROTOCOLVERSION		PROTOCOLVERSION_2_1

#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_ANNOUNCER 0x00000001			<< 0
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_DETECTOR 0x00000001			<< 1
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_ANNOUNCER 0x00000001			<< 2
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_DETECTOR 0x00000001			<< 3
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_ANNOUNCER 0x00000001			<< 4
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_DETECTOR 0x00000001			<< 5
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_ANNOUNCER 0x00000001	<< 6
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_DETECTOR 0x00000001		<< 7
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_ANNOUNCER 0x00000001	<< 8
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_DETECTOR 0x00000001		<< 9;
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_WRITER 0x00000001		<< 10
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_READER 0x00000001		<< 11

#define LOCATORUDPv4_INVALID {0, 0}

static char PARTICIPANT_MESSAGE_DATA_KIND_UNKNOWN[] = {0x00, 0x00, 0x00, 0x00};
static char PARTICIPANT_MESSAGE_DATA_KIND_AUTOMATIC_LIVELINESS_UPDATE[] = {0x00, 0x00, 0x00, 0x01};
static char PARTICIPANT_MESSAGE_DATA_KIND_AUTOMATIC_LIVELINESS_UPDATE_FOR_TEST[] = {0x01, 0x00, 0x00, 0x00};
static char PARTICIPANT_MESSAGE_DATA_KIND_MANUAL_LIVELINESS_UPDATE[] = {0x00, 0x00, 0x00, 0x02};


#define PID_PAD								0x0000
#define PID_SENTINEL						0x0001
#define PID_USER_DATA						0x002c	// UserDataQosPolicy
#define PID_TOPIC_NAME						0x0005	// string_mds<256>
#define PID_TYPE_NAME						0x0007	// string_mds<256>
#define PID_GROUP_DATA						0x002d
#define PID_TOPIC_DATA						0x002e
#define PID_DURABILITY						0x001d
#define PID_DURABILITY_SERVICE				0x001e
#define PID_DEADINE							0x0023
#define PID_LATENCY_BUDGET					0x0027
#define PID_LIVELINESS						0x001b
#define PID_RELIABILITY						0x001a
#define PID_LIFESPAN						0x002b
#define PID_DESTINATION_ORDER				0x0025
#define PID_HISTORY							0x0040
#define PID_RESOURCE_LIMITS					0x0041
#define PID_OWNERSHIP						0x001f
#define PID_OWNERSHIP_STRENGTH				0x0006
#define PID_PRESENTATION					0x0021
#define PID_PARTITION						0x0029
#define PID_TIME_BASED_FILTER				0x0004
#define PID_TRANSPORT_PRIORITY				0x0049
#define PID_PROTOCOL_VERSION				0x0015
#define PID_VENDORID						0x0016
#define PID_UNICAST_LOCATOR					0x002f
#define PID_MULTICAST_LOCATOR				0x0030
#define PID_MULTICAST_IPADDRESS				0x0011
#define PID_DEFAULT_UNICAST_LOCATOR			0x0031
#define PID_DEFAULT_MULTICAST_LOCATOR		0x0048
#define PID_METATRAFFIC_UNICAST_LOCATOR		0x0032
#define PID_METATRAFFIC_MULTICAST_LOCATOR	0x0033
#define PID_DEFAULT_UNICAST_IPADDRESS		0x000c
#define PID_DEFAULT_UNICAST_PORT			0x000e
#define PID_METATRAFFIC_UNICAST_IPADDRESS	0x0045
#define PID_METATRAFFIC_UNICAST_PORT		0x000d
#define PID_METATRAFFIC_MULTICAST_IPADDRESS	0x000b
#define PID_METATRAFFIC_MULTICAST_PORT		0x0046
#define PID_EXPECTS_INLINE_QOS				0x0043
#define PID_PARTICIPANT_MANUAL_LIVENESS_COUNT	0x0034
#define PID_PARTICIPANT_BUILTIN_ENDPOINTS	0x0044
#define PID_PARTICIPANT_LEASE_DURATION		0x0002
#define PID_CONTENT_FILTER_PROPERTY			0x0035
#define PID_PARTICIPANT_GUID				0x0050
#define PID_PARTICIPANT_ENTITYID			0x0051
#define PID_GROUP_GUID						0x0052
#define PID_GROUP_ENTITYID					0x0053
#define PID_COHERENT_SET					0x0056	// Presetation QoS
#define PID_BUILTIN_ENDPOINT_SET			0x0058
#define PID_PROPERTY_LIST					0x0059
#define PID_TYPE_MAX_SIZE_SERIALIZED		0x0060
#define PID_ENTITY_NAME						0x0062
#define PID_KEY_HASH						0x0070
#define PID_STATUS_INFO						0x0071

#define PID_PERSISTENCE						0x0003
#define PID_TYPE_CHECKSUM					0x0008
#define PID_TYPE2_NAME						0x0009
#define PID_TYPE2_CHECKSUM					0x000a
#define PID_EXPECTS_ACK						0x0010
#define PID_MANAGER_KEY						0x0012
#define PID_SEND_QUEUE_SIZE					0x0013
#define PID_RELIABILITY_ENABLED				0x0014
#define PID_VARGAPPS_SEQUENCE_NUMBER_LIST	0x0017
#define PID_RECV_QUEUE_SIZE					0x0018
#define PID_RELIABILITY_OFFERED				0x0019

#define PID_PRODUCT_VERSION					0x8000
#define PID_ENDPOINT_GUID					0x005a

#define CDR_BE		0x0000		// Big Endian
#define CDR_LE		0x0001		// Little Endian
#define PL_CDR_BE	0x0002		// Both the parameter list and its parameters are encapsulated using OMG CDR Big Endian.
#define PL_CDR_LE	0x0003		// Both the parameter list and its parameters are encapsulated using OMG CDR Little Endian.

#define	KIND_OF_ENTITY_UNKNOWN_USER_DEFINED			0x00
#define	KIND_OF_ENTITY_WRITER_WITH_KEY_USER_DEFINED	0x02
#define	KIND_OF_ENTITY_WRITER_NO_KEY_USER_DEFINED	0x03
#define	KIND_OF_ENTITY_READER_WITH_KEY_USER_DEFINED	0x07
#define	KIND_OF_ENTITY_READER_NO_KEY_USER_DEFINED	0x04

#define	KIND_OF_ENTITY_UNKNOWN_BUILTIN				0xc0
#define	KIND_OF_ENTITY_PARTICIPANT_BUILTIN			0xc1
#define	KIND_OF_ENTITY_WRITER_WITH_KEY_BUILTIN		0xc2
#define	KIND_OF_ENTITY_WRITER_NO_KEY_BUILTIN		0xc3
#define	KIND_OF_ENTITY_READER_WITH_KEY_BUILTIN		0xc4
#define	KIND_OF_ENTITY_READER_NO_KEY_BUILTIN		0xc7


struct EntityId_t
{
	octet	entity_key[3];
	octet	entity_kind;
};


static EntityId_t ENTITYID_PARTICIPANT  = {0x00,0x00,0x01,0xc1};
static EntityId_t ENTITYID_SEDP_BUILTIN_TOPIC_WRITER = {0x00,0x00,0x02,0xc2};
static EntityId_t ENTITYID_SEDP_BUILTIN_TOPIC_READER = {0x00,0x00,0x02,0xc7};
static EntityId_t ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER = {0x00,0x00,0x03,0xc2};
static EntityId_t ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER = {0x00,0x00,0x03,0xc7};
static EntityId_t ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER = {0x00,0x00,0x04,0xc2};
static EntityId_t ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER = {0x00,0x00,0x04,0xc7};
static EntityId_t ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER = {0x00,0x01,0x00,0xc2};
static EntityId_t ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER = {0x00,0x01,0x00,0xc7};
static EntityId_t ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER = {0x00,0x02,0x00,0xC2};
static EntityId_t ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER = {0x00,0x02,0x00,0xC7};


#define IS_SAME_ENTITYID(x,y)	(x[0] == y[0] && x[1] == y[1] && x[2] == y[2] && x[3] == y[3])


typedef struct KeyHash_t
{
	octet value[16];
} KeyHash_t;

typedef struct StatusInfo_t
{
	octet value[4];
} StatusInfo_t;

typedef struct TypeWithShortKey
{
	int32_t id;
	char name[6];
} TypeWithShortKey;

struct	GuidPrefix_t
{
	octet _guidprefix[12];
};

struct GUID_t
{
	GuidPrefix_t guid_prefix;
	EntityId_t	 entity_id;
} ;


#define GUIDPREFIX_UNKNOWN {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
static  EntityId_t ENTITYID_UNKNOWN = {0x00, 0x00, 0x00, 0x00};
static GUID_t GUID_UNKNOWN = { GUIDPREFIX_UNKNOWN, {0x00, 0x00, 0x00, 0x00} };


struct Locator_t
{
	int32_t kind;
	uint32_t port;
	octet address[16];
};

struct ProtocolVersion_t
{
	octet major;
	octet minor;
};


enum CHANGE_KIND
{
	ALIVE,
	NOT_ALIVE_DISPOSED,
	NOT_ALIVE_UNREGISTERED
};


struct SequenceNumber_t
{
	int32_t high;
	uint32_t low;
};


#if !defined(__RTPS_MESSAGE_H)
#define __RTPS_MESSAGE_H


typedef uint16_t ushort;


typedef enum SubmessageKind
{
	PAD = 0x01, /* Pad */
	ACKNACK = 0x06, /* AckNack */
	HEARTBEAT = 0x07, /* Heartbeat */
	GAP = 0x08, /* Gap */
	INFO_TS = 0x09, /* InfoTimestamp */
	INFO_SRC = 0x0c, /* InfoSource */
	INFO_REPLY_IP4 = 0x0d, /* InfoReplyIp4 */
	INFO_DST = 0x0e, /* InfoDestination */
	INFO_REPLY = 0x0f, /* InfoReply */
	NACK_FRAG = 0x12, /* NackFrag */
	HEARTBEAT_FRAG = 0x13, /* HeartbeatFrag */
	DATA = 0x15, /* Data */
	DATA_FRAG = 0x16, /* DataFrag */
} SubmessageKind;


typedef struct ProtocolId_t ProtocolId_t;

typedef bool SubmessageFlag;

typedef octet SubmessageKind1;

typedef int32_t Count_t;

typedef int16_t ParameterId_t;

typedef int32_t FragmentNumber_t;


struct ProtocolId_t
{
	char	_rtps[4];
};

typedef struct Header Header;
typedef struct SubmessageHeader SubmessageHeader;
typedef struct Receiver Receiver;

struct Header
{
	ProtocolId_t		protocol;
	ProtocolVersion_t	version;
	VendorId_t			vendor_id;
	GuidPrefix_t		guid_prefix;
};

struct SubmessageHeader
{
	SubmessageKind1		submessage_id;
	octet				flags;
	ushort				submessage_length;
};

struct Receiver
{
	ProtocolVersion_t	source_version;
	VendorId_t			source_vendor_id;
	GuidPrefix_t		source_guid_prefix;
	GuidPrefix_t		dest_guid_prefix;
	Locator_t**			pp_unicast_reply_locator_list;
	Locator_t**			pp_multicast_reply_locator_list;
	bool				have_timestamp;
	Time_t				timestamp;
};

typedef struct SubmessageElement SubmessageElement;
typedef struct GuidPrefix GuidPrefix;
typedef struct EntityId EntityId;
typedef struct Flags Flags;
typedef struct SequenceNumber SequenceNumber;
typedef struct SequenceNumberSet SequenceNumberSet;
typedef struct SerializedPayload SerializedPayload;
typedef struct SerializedPayloadFragment SerializedPayloadFragment;
typedef struct Timestamp Timestamp;
typedef struct Count Count;
typedef struct VendorId VendorId;
typedef struct ProtocolVersion ProtocolVersion;
typedef struct LocatorList LocatorList;
typedef struct ParameterList ParameterList;
typedef struct Parameter Parameter;
typedef struct FragmentNumber FragmentNumber;
typedef struct FragmentNumberSet FragmentNumberSet;

typedef struct SerializedPayloadForWriter SerializedPayloadForWriter;
typedef struct ParameterWithValue ParameterWithValue;


#define SUBMESSAGEELEMENT_BODY	


struct GuidPrefix
{
	SUBMESSAGEELEMENT_BODY
	GuidPrefix_t	value;
};

struct EntityId
{
	SUBMESSAGEELEMENT_BODY
	EntityId_t		value;
};

struct Flags
{
	SUBMESSAGEELEMENT_BODY
	SubmessageFlag	value;
};

struct SequenceNumber
{
	SequenceNumber_t	value;
};

struct SequenceNumberSet
{
	SequenceNumber_t	bitmap_base;
	uint32_t			numbits;
	uint32_t			bitmap[8];
};

struct SerializedPayload
{
	uint8_t*	p_value;
};

struct SerializedPayloadForWriter
{
	uint8_t*	p_value;
	
	// data size 에 해당하는 i_size Type을 uint16으로 설정하면, 65000 이상 토픽을 전송 할 수 없다.(unsigned int 범위로 인해)	
	int32_t i_size;
	GUID_t		entity_key_guid;
};

typedef struct SerializedPayloadForReader
{
	uint8_t*	p_value;
	
	// data size 에 해당하는 i_size Type을 uint16으로 설정하면, 65000 이상 토픽을 전송 할 수 없다.(unsigned int 범위로 인해)
	int32_t i_size;
	GUID_t		entity_key_guid;
} SerializedPayloadForReader;

struct SerializedPayloadFragment
{
	uint8_t*	p_value;
};

struct Timestamp
{
	Time_t		value;
};

struct Count
{
	Count_t		value;
};

struct VendorId
{
	VendorId_t	value;
};

struct ProtocolVersion
{
	ProtocolVersion_t		value;
};

struct LocatorList
{
	Locator_t**		pp_value;
};

struct ParameterList
{
	ParameterWithValue**		pp_parameters;
	int32_t						i_parameters;
};

struct Parameter
{
	ParameterId_t	parameter_id;
	uint16_t		length;
};

struct ParameterWithValue
{
	ParameterId_t	parameter_id;
	uint16_t		length;
	uint8_t*		p_value;
};

struct FragmentNumber
{
	FragmentNumber_t	value;
};

struct FragmentNumberSet
{
	FragmentNumber_t	base;
	FragmentNumber_t**	pp_set;
};

typedef struct Data Data;
typedef struct DataFrag DataFrag;
typedef struct Gap Gap;
typedef struct Heartbeat Heartbeat;
typedef struct AckNack AckNack;
typedef struct HeartbeatFrag HeartbeatFrag;
typedef struct NackFrag NackFrag;
typedef struct Pad Pad;
typedef struct InfoTimestamp InfoTimestamp;
typedef struct InfoReply InfoReply;
typedef struct InfoDestination InfoDestination;
typedef struct InfoSource InfoSource;
typedef struct DataFull DataFull;
typedef struct DataFragFull DataFragFull;


#define DATA_BODY_T	\
	uint16_t			extra_flags;			\
	short				octets_to_inline_qos;	\
	EntityId			reader_id;				\
	EntityId			writer_id;				\
	SequenceNumber		writer_sn;				\


struct Data
{
	DATA_BODY_T	
};

struct DataFull
{
	DATA_BODY_T
	ParameterList		inline_qos;
	SerializedPayload*	p_serialized_data;
};

typedef struct DataFullList
{
	DATA_BODY_T
	ParameterList		inline_qos;
	ParameterList		list;
}DataFullList;


#define DATAFRAG_BODY_T	\
	DATA_BODY_T \
	FragmentNumber		fragment_starting_num;\
	ushort				fragments_in_submessage;\
	ushort				fragment_size;\
	uint32_t			data_size;\


struct DataFrag
{
	DATAFRAG_BODY_T
};

struct DataFragFull
{
	DATAFRAG_BODY_T
	ParameterList		inline_qos;
	SerializedPayload*	p_serialized_data;
};

struct Gap
{
	EntityId			reader_id;
	EntityId			writer_id;
	SequenceNumber		gap_start;
	SequenceNumberSet	gap_list;
};

struct Heartbeat
{
	EntityId			reader_id;
	EntityId			writer_id;
	SequenceNumber		first_sn;
	SequenceNumber		last_sn;
	Count				count;
};

struct AckNack
{
	EntityId			reader_id;
	EntityId			writer_id;
	SequenceNumberSet	reader_sn_state;
	Count				count;
};

struct HeartbeatFrag
{
	EntityId			reader_id;
	EntityId			writer_id;
	SequenceNumber		writer_sn;
	FragmentNumber		last_fragment_num;
	Count				count;
};

struct NackFrag
{
	EntityId			reader_id;
	EntityId			writer_id;
	SequenceNumber		writer_sn;
	SequenceNumberSet	fragment_number_state;
	Count				count;
};

struct Pad
{
	int umm;
};

struct InfoTimestamp
{
	Timestamp	timestamp;
};

struct InfoReply
{
	LocatorList		multicast_locator_list;
	LocatorList		unicast_locator_list;
};

struct InfoDestination
{
	GuidPrefix		guid_prefix;
};

struct InfoSource
{
	ProtocolVersion	protocol_version;
	VendorId		vendor_id;
	GuidPrefix		guid_prefix;
};


#define FOUND_DATA				0x00000001 
#define FOUND_DATAFRAG			0x00000001 << 1
#define FOUND_GAP				0x00000001 << 2
#define FOUND_HEARTBEAT			0x00000001 << 3
#define FOUND_ACKNACK			0x00000001 << 4
#define FOUND_HEARTBEATFRAG		0x00000001 << 5
#define FOUND_NACKFRAG			0x00000001 << 6
#define FOUND_PAD				0x00000001 << 7
#define FOUND_INFOTIMESTAMP		0x00000001 << 8
#define FOUND_INFOREPLY			0x00000001 << 9
#define FOUND_INFODESTINATION	0x00000001 << 10
#define FOUND_INFOSOURCE		0x00000001 << 11
#define FOUND_INFOREPLY_IP4		0x00000001 << 12


#endif


typedef struct rtps_entity_t rtps_entity_t;
typedef struct rtps_endpoint_t rtps_endpoint_t;

#ifndef RTPS_PARTICIPANT_T_DEFINE
	#define RTPS_PARTICIPANT_T_DEFINE 1
	typedef struct rtps_participant_t rtps_participant_t;
#endif


typedef struct rtps_historycache_t rtps_historycache_t;


#ifndef RTPS_WRITER_T_DEFINE
	#define RTPS_WRITER_T_DEFINE 1
	typedef struct rtps_writer_t rtps_writer_t;
#endif

#ifndef RTPS_CACHECHANGE_T_DEFINE
	#define RTPS_CACHECHANGE_T_DEFINE 1
	typedef struct rtps_cachechange_t rtps_cachechange_t;
#endif


typedef struct rtps_statelesswriter_t rtps_statelesswriter_t;


#ifndef RTPS_STATEFULWRITER_T_DEFINE
	#define RTPS_STATEFULWRITER_T_DEFINE 1
	typedef struct rtps_statefulwriter_t rtps_statefulwriter_t;
#endif

#ifndef RTPS_READER_T_DEFINE
	#define RTPS_READER_T_DEFINE 1
	typedef struct rtps_reader_t rtps_reader_t;
#endif


typedef struct rtps_statelessreader_t rtps_statelessreader_t;


#ifndef RTPS_STATEFULREADER_T_DEFINE
	#define RTPS_STATEFULREADER_T_DEFINE 1
	typedef struct rtps_statefulreader_t rtps_statefulreader_t;
#endif


typedef struct rtps_readerlocator_t rtps_readerlocator_t;
typedef struct rtps_change_for_reader_t rtps_change_for_reader_t;


#ifndef RTPS_READERPROXY_T_DEFINE
	#define RTPS_READERPROXY_T_DEFINE 1
	typedef struct rtps_readerproxy_t rtps_readerproxy_t;
#endif

#ifndef RTPS_WRITERPROXY_T_DEFINE
	#define RTPS_WRITERPROXY_T_DEFINE 1
	typedef struct rtps_writerproxy_t rtps_writerproxy_t;
#endif


typedef struct rtps_change_from_writer_t rtps_change_from_writer_t;


enum CHANGE_FOR_READER_STATUS_KIND
{
	UNSENT,
	UNACKNOWLEDGED,
	REQUESTED,
	ACKNOWLEDGED,
	UNDERWAY
};

// MISSING 상태에서 ACKNACK 처리후 변경 상태인 MISSING_REQUESTED 상태 추가
enum CHANGE_FROM_WRITER_STATUS_KIND
{
	LOST,
	MISSING,
	RECEIVED,
	MISSING_REQUESTED,		// Missing NACK 보낸후 다시보내지 않도록 하기 위해 사용, 빈번한 REQUEST에 의해 성능 저하가 일어남.
	UNKNOWN
};


typedef int ChangeForReaderStatusKind;

typedef struct cache_for_guid
{
	GUID_t	guid;
	ChangeForReaderStatusKind	status;
	bool	is_relevant;
}cache_for_guid;

struct rtps_cachechange_t
{
	ChangeKind_t		kind;
	GUID_t				writer_guid;
	InstanceHandle_t	instance_handle;
	SequenceNumber_t	sequence_number;
	SerializedPayload*	p_data_value;
	// 이 부분은 statefulWriter에서만 사용되는 데, 여기 넣어도 문제 없음
	bool				b_read;
	// test_for_reliability
	int32_t				is_blockcount;
	// Presentation QoS
	Time_t				source_timestamp;
	Time_t				lifespan_duration;
	bool				is_coherent_set;
	SequenceNumber_t	coherent_set_number;
	
	// Destination Order QoS
	Time_t				received_time;
	
	bool				is_same;
	cache_for_guid**	pp_cache_for_guids;
	uint16_t			i_cache_for_guids;
	ChangeForReaderStatusKind	tmp_status;
	
	bool				b_isdisposed;
	bool				b_ref_rtps;
	bool				b_ref_dcps;
	message_t*			p_org_message;
	uint8_t				key_guid_for_reader[16];
	// RELIABLE시 READER에서 Missing 발생시 Listener에 알리지 않도록 하여 read/take를 할 수 없게 수정  
	// Missing에 대한 Request가 처리된 후인 MISSING_REQUEST 상태에서 얼마나 많은 HEARTBEAT을 받았는지 알기 위해 변수 추가
	// 해당 변수를 통해 특정 횟수 이상 Heartbeat를 받았는데도 RECEIVED가 되지 않았다면, 다시 Request 하기 위해 상태를 MISSING_REQUEST->MISSING으로 변경해야 한다.
	uint32_t			nHeartbeatCountInMissingRequested;	
	rtps_writerproxy_t*	p_rtps_writerproxy;
};

struct rtps_historycache_t  // HistoryCache
{
	rtps_cachechange_t**	pp_changes;
	
	uint16_t				i_changes;
	mutex_t					object_lock;
	rtps_reader_t*			p_rtps_reader;
	rtps_writer_t*			p_rtps_writer;
	HistoryQosPolicyKind	history_kind;
	int32_t					history_depth;
	int32_t					 history_max_length; // history
	ReliabilityQosPolicyKind reliability_kind; // reliability
	// Presentation QoS
	SequenceNumber_t	coherent_set_number;
};

	
// RTPS Entity에 domainID 추가
#define RTPS_ENTITY_T_BODY							\
	GUID_t				guid;						\
	int32_t				domainID_for_rtps_entity;	


struct rtps_entity_t
{
	RTPS_ENTITY_T_BODY
};

struct rtps_participant_t
{
	RTPS_ENTITY_T_BODY
	ProtocolVersion_t	protocol_version;
	VendorId_t			vendor_id;
	Locator_t**			pp_default_unicast_locator_list;
	Locator_t**			pp_default_multicast_locator_list;
	
	DomainParticipant*	p_participant;
	int32_t				i_endpoint;
	rtps_endpoint_t**	pp_endpoint;
	rtps_statelesswriter_t*		p_spdp_builtin_participant_writer;
	rtps_statelessreader_t*		p_spdp_builtin_participant_reader;
};


#define	RTPS_ENDPOINT_T_BODY						\
	RTPS_ENTITY_T_BODY								\
	TopicKind_t			topic_kind;					\
	ReliabilityKind_t	reliability_level;			\
	Locator_t**			pp_unicast_locator_list;	\
	Locator_t**			pp_multicast_locator_list;	\
	\
	rtps_participant_t*	p_rtps_participant;			\
	int32_t				behavior_type;				\
	int32_t				i_unicast_locator;			\
	int32_t				i_multicast_locator;		\
	int32_t				i_entity_type;				\


struct rtps_endpoint_t
{
	RTPS_ENDPOINT_T_BODY
};

typedef struct rtps_topic_t
{
	RTPS_ENDPOINT_T_BODY
	Topic*	p_topic;
}rtps_topic_t;


#define RTPS_WRITER_T_BODY	\
	RTPS_ENDPOINT_T_BODY	\
	DataWriter*				p_datawriter;\
	\
	bool				push_mode;\
	Duration_t			heartbeat_period;\
	Duration_t			nack_response_delay;\
	Duration_t			nack_suppression_duration;\
	SequenceNumber_t	last_change_sequence_number;\
	rtps_historycache_t*		p_writer_cache;\
	\
	mutex_t						object_lock;\
    cond_t						object_wait;\
	bool						b_end;\
	access_out_t*				p_accessout;\
	bool						b_has_liveliness;\
	int32_t						fragment_size;\
	int32_t						i_heartbeat_frag_count;\
	bool						is_builtin;\
	module_thread_t				thread_id;\
	int32_t						send_count;\
	int64_t						send_bytes;\
	int32_t						send_sample_count;\
	int64_t						send_sample_bytes;\
	int32_t						send_count_throughput;\
	int32_t						send_bytes_throughput;\
	int32_t						send_sample_count_throughput;\
	int32_t						send_sample_bytes_throughput;\
	bool 						b_thread_first;\
	

struct rtps_writer_t
{
	RTPS_WRITER_T_BODY
};


#define RTPS_READER_T_BODY	\
	RTPS_ENDPOINT_T_BODY\
	DataReader*			p_datareader;\
	\
	Duration_t			heartbeat_response_delay;\
	Duration_t			heartbeat_suppression_duration;\
	rtps_historycache_t*	p_reader_cache;\
	bool				expects_inline_qos;\
	\
	mutex_t						object_lock;\
    cond_t						object_wait;\
	bool						b_end;\
	data_fifo_t*				p_data_fifo;\
	module_thread_t				thread_id;\
	Count_t						count;\
	DataFragFull**				pp_datafragfull;\
	int32_t						i_datafragfull;\
	bool						is_builtin;\
	Duration_t					source_timestamp;\
	int32_t						received_count;\
	int64_t						received_bytes;\
	int32_t						received_sample_count;\
	int64_t						received_sample_bytes;\
	int32_t						received_count_throughput;\
	int32_t						received_bytes_throughput;\
	int32_t						received_sample_count_throughput;\
	int32_t						received_sample_bytes_throughput;\
	rtps_exclusive_writer_t**	pp_exclusive_writers;\
	int32_t						i_exclusive_writers;\


// ownership
typedef struct rtps_exclusive_writer_t
{
	rtps_writerproxy_t*	p_writerproxy;
	uint32_t			i_key;
	cpskey_t			keylist[MAX_KEY_NUM];
	bool				b_has_key;
	bool				b_is_owner;
} rtps_exclusive_writer_t;

struct rtps_reader_t
{
	RTPS_READER_T_BODY
};

struct rtps_statelesswriter_t
{
	RTPS_WRITER_T_BODY
	
	Duration_t				resend_data_period;
	
	rtps_readerlocator_t**	pp_reader_locators;
	
	int32_t					i_reader_locators;
};

struct rtps_statefulwriter_t
{
	RTPS_WRITER_T_BODY
	
	rtps_readerproxy_t** pp_matched_readers;
	
	int					i_matched_readers;
	Time_t				last_send_heartbeat;
	Time_t				last_nack_time;
	Count_t				heatbeat_count;
	bool				b_enable_multicast;
};

struct rtps_readerlocator_t
{	
	rtps_cachechange_t**	pp_requested_changes;
	
	rtps_cachechange_t**	pp_unsent_changes;
	
	Locator_t				locator;
	
	bool					expects_inline_qos;
	
	int32_t					i_unsent_changes;
	int32_t					i_sent_changes;
	int32_t					i_for_writer_state;
};

struct rtps_change_for_reader_t
{
	ChangeForReaderStatusKind	status;
	bool						is_relevant;
};


#define MAX_WAIT_ACK_COUNT 20


struct rtps_readerproxy_t
{
	GUID_t				remote_reader_guid;
	Locator_t**			pp_unicast_locator_list;
	Locator_t**			pp_multicast_locator_list;
	rtps_cachechange_t**	pp_changes_for_reader;
	bool				expects_inline_qos;
	bool				b_is_active;
	
	int32_t				i_changes_for_reader;
	int32_t				i_unicast_locator_list;
	int32_t				i_multicast_locator_list;
	int32_t				i_for_writer_state;
	int32_t				i_for_writer_fromReader_state;
	mutex_t				object_lock;
	rtps_writer_t*		p_rtps_writer;
	GUID_t				remote_endpoint_guid;
		
	Duration_t			deadline_base_time;
	int32_t				start;
	Duration_t			lifespan;
	
	octet				flags;
	bool				is_zero;		// ack의 base가 0인지 판별
	bool				is_ignore;
	
	int32_t				wait_ack_count;

	// ReaderProxy에 Reliablity / HisotyKind 설정값을 저장하기 위해 추가
	ReliabilityQosPolicyKind reliablility_kind;

	// 받았던 과거의 AckNack을 알 수 없기 때문에 추가
	AckNack		received_acknack;

	// 받았던 과거의 HeartBeat과 Data를 알 수 없기 때문에 추가	
	Heartbeat		sent_heartbeat;
	SequenceNumber sent_application_data;

	bool bFirstUpdateExecuted;

	// Reliable Multicast 지원 (_USE_CNU 사용시 정의됨.)
	bool		is_reliable_multicast;	
	int			n_same_acknack;
Time_t received_acknack_time;
Time_t write_time;
Time_t sent_heartbeat_time;
	int n_compare_sent_heartbeat_sec;
	int n_compare_received_acknack_sec;
	int n_not_received_acknack_sec;
};

struct rtps_statelessreader_t
{
	RTPS_READER_T_BODY
};

struct rtps_statefulreader_t
{
	RTPS_READER_T_BODY
	
	rtps_writerproxy_t**	pp_matched_writers;
	
	int32_t					i_matched_writers;
};

struct rtps_writerproxy_t
{
	GUID_t				remote_writer_guid;
	
	Locator_t**			pp_unicast_locator_list;
	
	Locator_t**			pp_multicast_locator_list;
	
	rtps_cachechange_t**	pp_changes_from_writers;
	
	int32_t					i_unicast_locator_list;
	int32_t					i_multicast_locator_list;
	int32_t					i_changes_from_writer;
	mutex_t					object_lock;
	cond_t					object_wait;		// liveliness
	int32_t					i_for_reader_state;
	Time_t				ackcheced_time;

	AckNack				last_acknack; 

	Heartbeat			a_remote_heartbeat;
	Count_t				i_ack_count;
	Count_t				i_nack_count;
	rtps_reader_t*		p_rtps_reader;

	SequenceNumber_t	last_available_seq_num;

	Duration_t			base_time;
	Duration_t			deadline_base_time;
	int32_t				start;
	Duration_t			lifespan;
	int32_t				i_for_reader_state_for_ack;
	bool				is_first_ack;
	int32_t				ownership_strength;

	int32_t				i_ref_count;
	bool				is_ignore;
	
	bool					b_is_alive;		// liveliness
	LivelinessQosPolicyKind	liveliness_kind;		// liveliness
	Time_t					liveliness_lease_duration;		// liveliness
	Time_t					liveliness_base_time;		// liveliness
	bool					b_is_first_liveliness_message;	// liveliness
	
	bool				b_is_deadline_on;		// ownership

	SequenceNumber_t	removed_cachechange_SN;

	// Missing 처리시 Dummy change를 넣기 위해 사용되는 참조 SeqNo.
	// Missing을 판단했던 Not Sequencial한 Cache의 SN이 기본적으로 이 값으로 할당 될 것이며, 이후 정상이 되기까지 들어오는 값들의 제일 큰 값을 가지게 될 것이다.
	SequenceNumber_t	max_missing_process_ref_cachechange_SN;	
	// 가장 최근 notify된 SeqNo.
	// 이 변수를 통해 Missing된 데이터가 회복되었을 때, 이를 위로 알릴 데이터들의 시작점을 알 수 있다.
	SequenceNumber_t	last_notify_cachechange_SN;	

	int n_HBCountAfterSendingNackByHB;		// HB_Last값에 의해 전송된 Missing처리 NACK이 잦지 않도록하기 위한 카운트 변수, 0=정상상태, 1~ = HB_LAST에 의한 Missing처리 필요시마다 카운트
SequenceNumberSet missing_seq_num_set;
};


typedef int32_t ChangeFromWriterStatusKind;


struct rtps_change_from_writer_t
{
	ChangeFromWriterStatusKind		status;
	bool							is_relevant;
};

typedef struct ContentFilterProperty_t
{
	char	content_filtered_topic_name[256];
	char	related_topic_name[256];
	char*	p_filter_expression;
	char**	pp_expression_parameters;
} ContentFilterProperty_t;

typedef struct _filterSignature_t
{
	int32_t	value[4];
} _filterSignature_t;


typedef int32_t** FilterResult_t;
typedef _filterSignature_t FilterSignature_t;


typedef struct ContentFilterInfo_t
{
	FilterResult_t		filter_result;
	FilterSignature_t**	pp_filter_signatures;
} ContentFilterInfo_t;

typedef struct Property_t
{
	char* p_name;
	char* p_value;
} Property_t;

typedef struct EntityName_t
{
	int32_t	i_length;
	char	name[12];
} EntityName_t;

typedef struct OriginalWriterInfo_t
{
	GUID_t original_writer_guid;
	SequenceNumber_t original_writer_sn;
	ParameterList original_writer_qos;
} OriginalWriterInfo_t;


typedef uint32_t BuiltinEndpointSet_t;


typedef struct LocatorUDPv4_t
{
	uint32_t address;
	uint32_t port;
} LocatorUDPv4_t;

typedef struct ParticipantMessageData
{
	GuidPrefix_t	participant_guid_prefix;
	octet			kind[4];
	
	octet   sequence_length[4];
	octet			data[4];
} ParticipantMessageData;

typedef struct RemoteParticipant_t
{
	GUID_t		a_remoteParticipantGuid;
	Locator_t	a_remotelocator;
	Locator_t	a_defaultLocator;
	Locator_t	a_remoteMulticastlocator;
	Locator_t	a_defaultMulticastLocator;
	bool		is_remoteAlive;
	Duration_t  a_remoteDuration;
	Time_t		a_lastsendTime;
	uint32_t count;
	bool		is_ignore;
} RemoteParticipant_t;

typedef struct SPDPdiscoveredParticipantData SPDPdiscoveredParticipantData;
typedef struct DiscoveredWriterData	DiscoveredWriterData;
typedef struct DiscoveredReaderData DiscoveredReaderData;
typedef struct DiscoveredTopicData DiscoveredTopicData;

typedef struct ParticipantProxy ParticipantProxy;


#define PARTICIPANTPROXY_BODY \
	ProtocolVersion_t	protocol_version; \
	GuidPrefix_t		guid_prefix; \
	VendorId_t			vendor_id; \
	bool				expects_inline_qos; \
	Locator_t	metatrafficUnicastLocator; \
	Locator_t	metatrafficMulticastLocator; \
	Locator_t	defaultUnicastLocator; \
	Locator_t	defaultMulticastLocator; \
	Count_t manualLivelinessCount; \


struct ParticipantProxy
{
	PARTICIPANTPROXY_BODY
	BuiltinEndpointSet_t	availableBuiltinEndpoint;
};

struct SPDPdiscoveredParticipantData 
{
	ParticipantBuiltinTopicData dds_participant_data;
	ParticipantProxy participant_proxy;
	Duration_t lease_duration;
};

struct DiscoveredWriterData 
{
	PublicationBuiltinTopicData dds_publication_data;
	rtps_writerproxy_t writer_proxy;
};

struct DiscoveredReaderData 
{
	SubscriptionBuiltinTopicData dds_subscription_data;
	rtps_readerproxy_t reader_proxy;
	ContentFilterProperty_t content_filter_property;
};

struct DiscoveredTopicData 
{
	BuiltinTopicDataTypeCode dds_topic_data;
};

typedef struct SPDPdiscoveredParticipantDataSeq 
{
	int i_size;
	SPDPdiscoveredParticipantData **pp_discoveredParticipantData;
}SPDPdiscoveredParticipantDataSeq;

typedef struct DiscoveredWriterDataSeq 
{
	int i_size;
	DiscoveredWriterData **pp_discoveredWriterData;
}DiscoveredWriterDataSeq;

typedef struct DiscoveredReaderDataSeq 
{
	int i_size;
	DiscoveredReaderData **pp_discoveredReaderData;
}DiscoveredReaderDataSeq;

typedef struct DiscoveredTopicDataSeq 
{
	int i_size;
	DiscoveredTopicData **pp_discoveredTopicData;
}DiscoveredTopicDataSeq;


static SPDPdiscoveredParticipantDataSeq INIT_DISCOVERED_PARTICIPANT_DATA_SEQ = { 0, NULL };
static DiscoveredWriterDataSeq INIT_DISCOVERED_WRITER_DATA_SEQ = { 0, NULL };
static DiscoveredReaderDataSeq INIT_DISCOVERED_READER_DATA_SEQ = { 0, NULL };
static DiscoveredTopicDataSeq INIT_DISCOVERED_TOPIC_DATA_SEQ = { 0, NULL };


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	int rtps_period_thread_start(discovery_t *p_discovery);
	DDS_DLL_API	int rtps_period_thread_end(discovery_t *p_discovery);

	DDS_DLL_API	ReturnCode_t rtps_get_SPDPdiscoveredParticipantData(SPDPdiscoveredParticipantDataSeq *discovered_participant_data_seq);
	DDS_DLL_API	ReturnCode_t rtps_get_discoveredWriterData(DiscoveredWriterDataSeq *discovered_writer_data_seq);
	DDS_DLL_API	ReturnCode_t rtps_get_discoveredReaderData(DiscoveredReaderDataSeq *discovered_writer_data_seq);
	DDS_DLL_API	ReturnCode_t rtps_get_discoveredTopicData(DiscoveredTopicDataSeq *discovered_writer_data_seq);

	DDS_DLL_API	void CreateDynamicSubTopic(dds_parameter_t *parent, TypeCode_t * pSubTypeCode, int nSubSize);

	DDS_DLL_API	void createDynamicTopic(in_mds DomainParticipant *pdp, inout_mds FooTypeSupport * pfts, in_mds BuiltinTopicDataTypeCode aBuiltinTopicData);
#ifdef __cplusplus
}
#endif


#endif // __RTPS_DISCOVERED_H