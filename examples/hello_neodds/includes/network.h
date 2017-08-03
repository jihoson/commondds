/*
	네트워크 관련 헤더
	작성자 : 
	이력
	2010-07-24 : 시작 일단 윈도우만 우선 선언 어느 정도 되면 다른 플랫폼 추가

*/

#if !defined(__NETWORK_H)
#define __NETWORK_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif

#define MAX_EMPTY_BLOCKS 200


#include <errno.h>


#ifdef HAVE_SYS_TIME_H
#    include <sys/time.h>
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT WSAEAFNOSUPPORT
#endif

#ifndef SOL_IP
#define SOL_IP IPPROTO_IP
#endif

#ifndef SOL_IPV6
#define SOL_IPV6 IPPROTO_IPV6
#endif

#ifndef IPPROTO_IPV6
#define IPPROTO_IPV6 41
#endif

#define DEFALT_UDP_PORT 8301


typedef struct network_socket_t
{
    const char*	psz_bind_addr;
    int			i_bind_port;

    const char*	psz_server_addr;
    int			i_server_port;

    int			i_ttl;

    int			v6only;
    int			i_handle;
    size_t		i_mtu;
} network_socket_t;

typedef struct virtual_socket_t
{
    void* p_sys;
    int (*pf_recv) ( void *, void *, int );
    int (*pf_send) ( void *, const void *, int );
} virtual_socket_t;


#define netStopSend( fd ) (void)shutdown( fd, SD_SEND )
#define netStopRecv( fd ) (void)shutdown( fd, SD_RECEIVE )


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	int inet_pton1(int af, const char* psz_src, void* v_dst);

	DDS_DLL_API	const char* gai_str_error(int err_num);
	DDS_DLL_API	int get_addr_info(module_object_t* p_this, const char* p_node, int i_port, const struct addrinfo* p_hints, struct addrinfo** pp_res);
	DDS_DLL_API	void free_addr_info(struct addrinfo* p_infos);

	DDS_DLL_API	int net_socket(module_object_t* p_this, int i_family, int i_sock_type, int i_protocol);
	DDS_DLL_API	void net_close(int fd);

	DDS_DLL_API	int net_open_udp(module_object_t* p_this, const char* psz_bind, int* i_bind, const char* psz_server, int i_server);
	DDS_DLL_API	int connect_udp(module_object_t* p_this, const char* psz_host, int i_port, int i_hlim, int i_fd);
	DDS_DLL_API	int net_connect_tcp(module_object_t* p_this, const char* psz_host, int i_port);
	DDS_DLL_API	int* net_listen_tcp(module_object_t* p_this, const char* psz_host, int i_port);
	DDS_DLL_API	void net_listen_close(int* pi_fd);
	DDS_DLL_API	int net_accept(module_object_t* p_this, int* pi_fd, mtime_t i_wait);
	DDS_DLL_API	int net_read(module_object_t* p_this, int fd, virtual_socket_t* p_vs, uint8_t* p_data, int i_data, bool b_retry);
	DDS_DLL_API	int net_write(module_object_t* p_this, int fd, virtual_socket_t* p_vs, const uint8_t* p_data, int i_data);
	DDS_DLL_API	int net_read_for_service(service_t* p_this, uint8_t* p_data, int i_data, bool b_retry, int spdp_fd, int sedp_fd, int data_fd, bool* p_end);

	DDS_DLL_API	const char *net_strerror(int value);
#ifdef __cplusplus
}
#endif


#ifndef EAI_BADFLAGS
#define EAI_BADFLAGS -1
#endif

#ifndef EAI_NONAME
#define EAI_NONAME -2
#endif

#ifndef EAI_AGAIN
#define EAI_AGAIN -3
#endif

#ifndef EAI_FAIL
#define EAI_FAIL -4
#endif

#ifndef EAI_NODATA
#define EAI_NODATA -5
#endif

#ifndef EAI_FAMILY
#define EAI_FAMILY -6
#endif

#ifndef EAI_SOCKTYPE
#define EAI_SOCKTYPE -7
#endif

#ifndef EAI_SERVICE
#define EAI_SERVICE -8
#endif

#ifndef EAI_ADDRFAMILY
#define EAI_ADDRFAMILY -9
#endif

#ifndef EAI_MEMORY
#define EAI_MEMORY -10
#endif

#ifndef EAI_SYSTEM
#define EAI_SYSTEM -11
#endif

#if defined (_MSC_VER) || defined (UNDER_CE)
#undef EINPROGRESS
#define EINPROGRESS WSAEWOULDBLOCK
#undef EINTR
#define EINTR WSAEINTR
#undef ETIMEDOUT
#define ETIMEDOUT WSAETIMEDOUT
#endif

#endif
