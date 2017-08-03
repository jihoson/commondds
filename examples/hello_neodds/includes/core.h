/*
코어의 메인 헤더파일

작성자 :
이력
2010-07-12 : 시작
*/

#if !defined(__CORE_H)
#define __CORE_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif

#define QOS_EF
#define QOS_RL
#define QOS_H_R
#define QOS_O
#define QOS_L


#include <malloc.h>

#include <string.h>
#include <stdarg.h>


#ifdef _MSC_VER
#define msleep(delay)		Sleep( (int) (delay / 1000) )
#else

#ifdef Android
#define msleep(delay)		usleep(delay);
#else

#define msleep(delay)		{\
								struct timespec ts_delay;\
								ts_delay.tv_sec = delay / 1000000;\
								ts_delay.tv_nsec = (delay % 1000000) * 1000;\
								nanosleep( &ts_delay, NULL );\
							}
#ifdef _LINUX_VER
#define Sleep(delay)        usleep(delay * 1000);
#endif

#endif
#endif
#define CLOCK_FREQ			1000000
#define DEFAULT_PTS_DELAY   (mtime_t)(.3*CLOCK_FREQ)
#define THREAD_SLEEP		((mtime_t)(0.010*CLOCK_FREQ))

#ifdef _MSC_VER
#define inline __inline
#pragma warning(disable : 4996)
#define strcasecmp stricmp
#define snprintf _snprintf
#endif

#define net_errno (WSAGetLastError())

#if defined( _MSC_VER )
#	if defined(UNDER_CE) && defined(sockaddr_storage)
#       undef sockaddr_storage
#	endif
#   if defined(UNDER_CE)
#       define HAVE_STRUCT_ADDRINFO
#	else
//#       include <io.h>
#   endif
#   include <winsock2.h>
#   include <ws2tcpip.h>
#   include <iphlpapi.h>
#	ifndef ENETUNREACH
#		if _MSC_VER < 1600
#		define ENETUNREACH WSAENETUNREACH
#		endif
#	endif
#   define net_errno (WSAGetLastError())

#else
#   if HAVE_SYS_SOCKET_H
#      include <sys/socket.h>
#   endif
#   if HAVE_NETINET_IN_H
#      include <netinet/in.h>
#   endif
#   if HAVE_ARPA_INET_H
#      include <arpa/inet.h>
#   elif defined( SYS_BEOS )
#      include <net/netdb.h>
#   endif
#   include <netdb.h>
#   define net_errno errno
#ifndef _LINUX_VER
#   define net_strerror strerror
#endif
#endif

#include <fcntl.h>

#ifdef _MSC_VER
#	include <io.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	void *tracemalloc(const char *p_funcname, const char *p_name, size_t size);
	DDS_DLL_API	void tracefree(const char *p_funcname, const char *p_name, void *ptr);
	DDS_DLL_API	char *tracestrdup(const char *p_funcname, const char *p_name, const char *psz);
	DDS_DLL_API	void *tracerealloc(const char *p_funcname, const char *p_name, void *ptr, size_t size);
#ifdef __cplusplus
}
#endif


#ifndef __cplusplus
#define _DDS_MALLOCZERO
#endif


#ifndef __cplusplus
#ifndef bool
#define bool char
#endif
#endif


#ifndef __cplusplus
#define false 0
#define true  1
#endif

#define FREE(x) if(x) {free(x); x=NULL;}


enum TRACE_TYPE
{
	TRACE_NORMAL,
	TRACE_ERROR,
	TRACE_WARM,
	TRACE_DEBUG,
	TRACE_TRACE,
	TRACE_TRACE2,
	TRACE_TRACE3,
	TRACE_LOG
};


//////////  struct define /////////////////////////

typedef struct module_object_t module_object_t;
typedef struct module_bank_t module_bank_t;
typedef struct libmodule_t libmodule_t;
typedef struct module_t module_t;
typedef struct moduleload_t moduleload_t;
typedef struct module_config_t module_config_t;
typedef struct module_list_t module_list_t;

typedef struct trace_t trace_t;
typedef struct service_t service_t;
typedef struct typesupport_t typesupport_t;
typedef struct discovery_t discovery_t;
typedef struct qos_policy_t qos_policy_t;			// qos module

typedef struct trace_sys_t trace_sys_t;

typedef struct variable_t variable_t;
typedef struct callback_entry_t callback_entry_t;

#define DOMAINPARTICIPANT_DEFINE 1
typedef struct DomainParticipant DomainParticipant;

#define WAITSET_DEFINE 1
typedef struct WaitSet WaitSet;

typedef struct message_t message_t;
typedef struct message_fifo_t message_fifo_t;
typedef struct management_t management_t;
typedef struct access_t access_t;
typedef struct access_out_t access_out_t;
typedef struct data_t data_t;
typedef struct data_fifo_t data_fifo_t;
typedef struct dds_string dds_string;

typedef unsigned int dds_wchar;
typedef struct dds_longdouble dds_longdouble;


#include <thread.h>
#include <module_common.h>
#include <module_config.h>
#include <trace.h>
#include <service.h>
#include <configuration.h>
#include <util.h>
#include <typesupport.h>

#include <management.h>
#include <network.h>
#include <access.h>
#include <data.h>
#include <discovery.h>
#include <qos_policy.h>			// qos module

#include <stdlib.h>
#include <assert.h>

#ifndef THREAD_PRIORITY_HIGHEST
#   define THREAD_PRIORITY_HIGHEST 0
#endif

// port setting regard to domain id.
// port setting algorithm for specification
typedef struct Domain_port Domain_port;

struct Domain_port 
{
	int spdp;
	int sedp;
	int data;
};

#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	void domain_port_set(int domain_id);	// Network Port Setting regard to Domain ID 
	DDS_DLL_API	Domain_port domain_port_get();			// get the Network Port already setting.
#ifdef __cplusplus
}
#endif

// end
#endif


// MultiDomain 지원을 위한 상수 추가
#define MAX_MULTI_DOMAIN_SIZE				255		// Max multi domain count, 최대가능한 domainID가 255까지라고 함(도메인에 따른 포트결정식에 따라 포트할당가능영역이 제한됨)
#define BUILTIN_DOMAIN_ID_CHANGE_CONSTANT	1000	// BuiltinDomainParticipant DomainID = UserDomainPacitipant DomainID - BUILTIN_DOMAIN_ID_CHANGE_CONSTANT
#define NOT_ASSGINED_DOMAIN_ID				-9999	// 초기 domainID
#define ROOT_DOMAIN_ID						-10000	// root 모듈을 위한 domainID

#define EJ_CDR	1
//#define CONTENT_TOPIC 
//#define DURABILITY
//#define DATAREADER_LIFE 
//#define WIN_XP
//#define _DMS_PERFORMANCE_
