/*
	메시지 관련 헤더
	작성자 : 
	이력
	2010-08-8 : 시작

*/

#if !defined(__MESSAGE_H)
#define __MESSAGE_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


typedef long InstanceHandle_t;		// Linux에서는 64bit/32bit 모두 long값이 pointer 크기(8)과 같다.


#ifndef DATAWRITER_DEFINE
        #define DATAWRITER_DEFINE 1
        typedef struct DataWriter DataWriter;
#endif

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

#ifndef SAMPLEINFO_DEFINE
		typedef struct SampleInfo SampleInfo;
		#define SAMPLEINFO_DEFINE 1
#endif
		

struct message_t
{
	message_t*		p_next;
    message_t*		p_prev;

	int				i_datasize;	
	void*			v_data;
	uint32_t		sequence;
	Time_t			current_time;
	char*			p_topic_name;
	char*			p_type_name;
	InstanceHandle_t handle;
	InstanceHandle_t publication_handle;
	SampleInfo		sampleInfo;
	void*			v_related_rtps_reader;
	uint32_t		i_key;
	cpskey_t		keylist[MAX_KEY_NUM];
	void*			v_related_cachechange;
	uint8_t			key_guid[16];

	// Presentation QoS
	bool				is_coherent_set;
	Time_t				coherent_set_number;
	Time_t				lifespan_duration;
	
	// DestinationOrder QoS
	Time_t			received_time;
};

struct message_fifo_t
{
    mutex_t			lock;
    cond_t			wait;

    int32_t			i_depth;
    message_t*		p_first;
    message_t**		pp_last;
    int32_t			i_size;
};


static inline message_t* message_duplicate(message_t* p_message)
{
    message_t *p_dup = (message_t *)malloc(sizeof(message_t));
    if( p_dup == NULL )
        return NULL;

	memset(p_dup,0,sizeof(message_t));

	p_dup->i_datasize = p_message->i_datasize;
	p_dup->sequence = p_message->sequence;
	if(p_dup->i_datasize)
	{
		p_dup->v_data = malloc(p_dup->i_datasize);

		if(p_dup->v_data)
			memcpy( p_dup->v_data, p_message->v_data, p_message->i_datasize );
	}

	if(p_message->p_topic_name) 
		p_dup->p_topic_name = strdup(p_message->p_topic_name);
	if(p_message->p_type_name) 
		p_dup->p_type_name = strdup(p_message->p_type_name);

	p_dup->current_time = p_message->current_time;
	p_dup->sampleInfo = p_message->sampleInfo;
	p_dup->v_related_rtps_reader = p_message->v_related_rtps_reader;
	p_dup->v_related_cachechange = p_message->v_related_cachechange;

	// Presentation QoS
	p_dup->is_coherent_set = p_message->is_coherent_set;
	p_dup->received_time = p_message->received_time;

    return p_dup;
}


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	void datawriter_write_timestamp(DataWriter* p_foo_datawriter, void* v_data, InstanceHandle_t handle, Time_t source_timestamp);
	DDS_DLL_API	void datawriter_write(DataWriter* p_foo_datawriter, void *v_data, InstanceHandle_t handle);
	DDS_DLL_API	void datawriter_dispose_timestamp(DataWriter* p_datawriter, void* v_data, InstanceHandle_t handle, Time_t source_timestamp);
	DDS_DLL_API	void datawriter_dispose(DataWriter* p_datawriter, void* v_data, InstanceHandle_t handle);
	DDS_DLL_API	void datawriter_unregister_timestamp(DataWriter* p_datawriter, void* v_data, InstanceHandle_t handle, Time_t source_timestamp);
	DDS_DLL_API	void datawriter_unregister(DataWriter* p_datawriter, void* v_data, InstanceHandle_t handle, bool b_dispose);
	DDS_DLL_API	message_t* message_new_for_builtin_reader(DataReader* p_datareader, void* v_data, int i_reader_data_size);
	DDS_DLL_API	message_t* message_new(DataWriter* p_datawriter, void* v_data);
	DDS_DLL_API	void message_release(message_t* p_message);

	DDS_DLL_API void message_free(message_t* p_message, FooSeq *p_fseq, SampleInfoSeq *p_sSeq, unsigned int num);

	DDS_DLL_API	message_fifo_t* message_fifo_new();
	DDS_DLL_API	message_t* message_fifo_get(message_fifo_t* p_fifo);
	DDS_DLL_API	void message_fifo_empty(message_fifo_t* p_fifo);
	DDS_DLL_API	void message_fifo_release(message_fifo_t* p_fifo);
	DDS_DLL_API	int message_fifo_put(message_fifo_t* p_fifo, message_t* p_message);
#ifdef __cplusplus
}
#endif

#endif
