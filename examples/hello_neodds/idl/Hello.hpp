#ifndef _NEO_DDS_IDL_GEN_Hello
#define _NEO_DDS_IDL_GEN_Hello
#include <core.h>
#include <cpsdcps.h>
#include <dcps_func.h>
#if defined(_MSC_VER)
#define STRUCT_ALIGNED_(x) struct __declspec(align(x))
#elif defined(__GNUC__)
#define STRUCT_ALIGNED_(x) struct __attribute__ ((aligned(x)))
#else
#define STRUCT_ALIGNED_(x) struct
#endif

class HelloWorldData_MsgTypeSupport;
typedef STRUCT_ALIGNED_(1) HelloWorldData_Msg {
	typedef FooDataReader DataReader;
	typedef FooDataWriter DataWriter;
	typedef FooSeq Seq;
	typedef HelloWorldData_MsgTypeSupport TypeSupport;
	int32_t userId;
	dds_string message;
} HelloWorldData_Msg;

class HelloWorldData_MsgTypeSupport
{
public:
	FooTypeSupport	*fooTS;
public:
	static const char * get_type_name(){
		return "HelloWorldData_Msg";
	}
	void register_topic_type(DomainParticipant *p_Participant)
	{
		
		if(p_Participant == NULL) return;
		{
			fooTS = get_new_foo_type_support();
		 	insert_topic_parameters(fooTS);
		 	fooTS->i_size = sizeof(struct HelloWorldData_Msg);
		 	fooTS->register_type(fooTS, p_Participant, "HelloWorldData_Msg");
		}
	}

	void insert_topic_parameters(FooTypeSupport *fooTS)
	{ 
		{
			dds_parameter_t *p_para = get_new_parameter("userId", DDS_Int32, sizeof(int32_t));
			//INSERT_PARAM(fooTS->pp_parameters, fooTS->i_parameters, fooTS->i_parameters, p_para, dds_parameter_t**);
			INSERT_PARAM(fooTS->pp_parameters, fooTS->i_parameters, fooTS->i_parameters, p_para);
		}

		{
			dds_parameter_t *p_para = 
				get_new_struct_parameter("message", DDS_String, sizeof(dds_string),GET_ALIGN_VALUE(dds_string),1);
			//INSERT_PARAM(fooTS->pp_parameters, fooTS->i_parameters, fooTS->i_parameters, p_para, dds_parameter_t**);
			INSERT_PARAM(fooTS->pp_parameters, fooTS->i_parameters, fooTS->i_parameters, p_para);
		}
	}
};

#endif
