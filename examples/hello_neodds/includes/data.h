/*
	data 관련 헤더
	작성자 : 
	이력
	2010-08-10 : 시작

*/

#if !defined(__DATA_H)
#define __DATA_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


typedef long InstanceHandle_t;		// Linux에서는 64bit/32bit 모두 long값이 pointer 크기(8)과 같다.


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


#pragma pack(push, 1)


struct data_t
{
	data_t*			p_next;
    data_t*			p_prev;

	int				i_size;	
	uint8_t*		p_data;
	unsigned long	sequence;
	Time_t			current_time;
	
	uint8_t*		p_address;
	int				i_port;
	int				socket_id;

	//공통의 queue에서 각 데이터가 누구 것인지 알기 위한 구조	
	void*			v_rtps_reader;
	rtps_writer_t*	p_rtps_writer;
	int				priority;
	// job queue를 위한 데이터 구조 
	unsigned long 	wake_time;
	Time_t			initial_time;
	Time_t			next_wakeup_time;
	bool 			b_thread_first;
};

struct data_fifo_t
{
    mutex_t			lock;
    cond_t			wait;

    int				i_depth;
    data_t*			p_first;
    data_t**		pp_last;
    int				i_size;
	
	int				i_new_job;
};


#pragma pack(pop)


static inline data_t* data_duplicate(data_t* p_data)
{
    data_t *p_dup = (data_t *)malloc(sizeof(data_t));
    if( p_dup == NULL )
        return NULL;

	memset(p_dup,0,sizeof(data_t));

	p_dup->i_size = p_data->i_size;

	if(p_dup->i_size)
	{
		p_dup->p_data = NULL;
		p_dup->p_data = (uint8_t *)malloc(p_dup->i_size);
		if(p_dup->p_data)
			memcpy( p_dup->p_data, p_data->p_data, p_data->i_size );
	}

	p_dup->current_time = p_data->current_time;
	p_dup->sequence = p_data->sequence;
	p_dup->i_port = p_data->i_port;

    return p_dup;
}

#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	data_t* data_new(int i_size);
	DDS_DLL_API	void data_release(data_t* p_data);

	DDS_DLL_API	data_fifo_t* data_fifo_new();
	DDS_DLL_API	data_t* data_fifo_get(data_fifo_t* p_fifo);
	DDS_DLL_API	void data_fifo_empty(data_fifo_t* p_fifo);
	DDS_DLL_API	void data_fifo_release(data_fifo_t* p_fifo);
	DDS_DLL_API	int data_fifo_put(data_fifo_t* p_fifo, data_t* p_data);
	DDS_DLL_API	int data_fifo_put_first(data_fifo_t* p_fifo, data_t* p_data);

	DDS_DLL_API	data_t* timed_job_queue_data_fifo_get(data_fifo_t* p_fifo);
	DDS_DLL_API	data_t* timed_job_queue_data_fifo_get_remove_job(data_fifo_t* p_fifo);
	DDS_DLL_API	int timed_job_queue_time_compare_data_fifo_put(data_fifo_t* p_fifo, data_t* p_data);
	DDS_DLL_API	int timed_job_queue_time_compare_data_fifo_put_add_job(data_fifo_t* p_fifo, data_t* p_data);
	DDS_DLL_API	int timed_job_queue_data_fifo_put(data_fifo_t* p_fifo, data_t* p_data);
	DDS_DLL_API	int timed_job_queue_traverse(data_fifo_t* p_fifo);
	DDS_DLL_API	int get_number_new_job(data_fifo_t* p_fifo);
#ifdef __cplusplus
}
#endif

#endif