/*
	Foo ���� ���
	�ۼ��� : 
	�̷�
	2010-08-7 : ����

*/

#if !defined(__FOO_H)
#define __FOO_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif

 
struct Foo
{
	int32_t dummy;
};

typedef struct FooSeq
{
	int32_t i_seq;
	Foo** pp_foo;
} FooSeq;


static FooSeq INIT_FOOSEQ = {0, NULL};


typedef struct TypeSupport TypeSupport;


#ifndef FOOTYPESUPPORT_DEFINE
	#define FOOTYPESUPPORT_DEFINE 1
	typedef struct FooTypeSupport FooTypeSupport;
#endif


typedef struct FooDataWriter FooDataWriter;
typedef struct FooDataReader FooDataReader;


// SUPPORT TYPE �߰�(Unsigned long, longlong, long double)
typedef enum SUPPORT_TYPE
{
	DDS_String,
	DDS_Boolean,
	DDS_Byte,
	DDS_Char,
	DDS_WChar,
	DDS_Int16,
	DDS_UInt16,
	DDS_Int32,
	DDS_UInt32,
	DDS_Float32,
	DDS_Int64,
	DDS_UInt64,
	DDS_Double64,
	DDS_Double128,
	DDS_Struct,
	DDS_Array_Boolean,
	DDS_Array_Byte,
	DDS_Array_Char,
	DDS_Array_WChar,
	DDS_Array_Int16,
	DDS_Array_UInt16,
	DDS_Array_Int32,
	DDS_Array_UInt32,
	DDS_Array_Float32,
	DDS_Array_Int64,
	DDS_Array_UInt64,
	DDS_Array_Double64,
	DDS_Array_Double128,
	DDS_Array_Struct,
	DDS_Array_String
} SUPPORT_TYPE;


#define DDS_STRING_TYPE		DDS_String
#define DDS_INTEGER_TYPE	DDS_Int32
#define DDS_FLOAT_TYPE		DDS_Float32
#define DDS_CHARACTER_TYPE	DDS_Char8
#define DDS_STRUCT_TYPE		DDS_Struct
#define DDS_SHORT_TYPE		DDS_Int16
#define DDS_ARRAY_INTEGER_TYPE	DDS_Array_Int32
#define DDS_ARRAY_FLOAT_TYPE	DDS_Array_Float32
#define DDS_ARRAY_CHARACTER_TYPE	DDS_Array_Char8
#define DDS_Char8			DDS_Char
#define DDS_Char16			DDS_WChar
#define DDS_Array_Char8		DDS_Array_Char
#define DDS_Array_Char16	DDS_Array_WChar


// Sub StructŸ�� �ʵ� ���� ���� �߰�
struct dds_parameter_t
{
	SUPPORT_TYPE	type;
	int				i_size;
	char*			p_field_name;
	union
	{
		char*		string_mds;
		long		integer;
		double		real;
		char		character;
	} value;
	bool			is_key;
	long			id;
	int				offset;

	int				i_subParameters;
	int				nAlignValue;
	int				nArraySize;

	dds_parameter_t ** pp_ddsSubParameters;
};


// ���뿡�� �̿�� ��ũ�� ������ �޸𸮸� �Ҵ��� �� ��������� Ÿ���� ����
// DIDE-5
#define I_PARAMETER(foots, p_field_name, type, size) \
	{\
		dds_parameter_t *p_para = get_new_parameter(p_field_name, type, size);\
		INSERT_PARAM(##foots->pp_parameters,##foots->i_parameters, ##foots->i_parameters, p_para);\
	}

#define I_STRUCT_PARAMETER(foots, p_field_name, type, size, alignvalue, arraysize) \
	{\
		dds_parameter_t *p_para = get_new_struct_parameter(p_field_name, type, size, alignvalue, arraysize);\
		INSERT_PARAM(##foots->pp_parameters,##foots->i_parameters, ##foots->i_parameters, p_para);\
	}


static inline dds_parameter_t* get_new_parameter(char* p_field_name, SUPPORT_TYPE type, int i_size)
{

	dds_parameter_t *p_parameter = (dds_parameter_t *)malloc(sizeof(dds_parameter_t));
	 
	if (p_parameter == NULL)
	{
		printf("Error : Memory allocation Fail in malloc() - foo 258\n");
		exit(1);
	 }
	memset(p_parameter, 0, sizeof(dds_parameter_t));

	p_parameter->i_size = i_size;
	p_parameter->type = type;

	p_parameter->is_key = false;
	p_parameter->offset = 0;
	
	if(p_field_name)
		p_parameter->p_field_name = strdup(p_field_name);
	else 
		p_parameter->p_field_name = NULL;

	// Sub Parameter �ʱ�ȭ
	p_parameter->i_subParameters = 0;
	p_parameter->pp_ddsSubParameters = NULL;

	p_parameter->nAlignValue = 1;

	p_parameter->nArraySize = 1;

	return p_parameter;
}


#define GET_ALIGN_VALUE(type) __alignof(type)


static inline dds_parameter_t* get_new_struct_parameter(char* p_field_name, SUPPORT_TYPE type, int i_totalsize, int i_alignvalue, int i_arraysize)
{
	dds_parameter_t *p_parameter = get_new_parameter(p_field_name, type, i_totalsize);
	p_parameter->nAlignValue = i_alignvalue;
	p_parameter->nArraySize = i_arraysize;

	return p_parameter;
}


static long PARAMETERKEY = 0;


static inline dds_parameter_t *get_new_parameter_key(char* p_field_name, SUPPORT_TYPE type, int i_size)
{
	dds_parameter_t *p_parameter = (dds_parameter_t *)malloc(sizeof(dds_parameter_t));

	if (p_parameter == NULL)
	{
		printf("Error : Memory allocation Fail in malloc() - foo 318\n");
		exit(1);
	}
	memset(p_parameter, 0, sizeof(dds_parameter_t));

	p_parameter->i_size = i_size;
	p_parameter->type = type;
	p_parameter->is_key = true;
	
	if (p_field_name) 
		p_parameter->p_field_name = strdup(p_field_name);
	else 
		p_parameter->p_field_name = NULL;

	p_parameter->id = ++PARAMETERKEY;

	// Sub Parameter �ʱ�ȭ
	p_parameter->i_subParameters = 0;
	p_parameter->pp_ddsSubParameters = NULL;
	
	p_parameter->nAlignValue=1;
	
	p_parameter->nArraySize = 1;

	return p_parameter;
}

static inline dds_parameter_t* get_new_struct_parameter_key(char* p_field_name, SUPPORT_TYPE type, int i_totalsize, int i_alignvalue, int i_arraysize)
{
	dds_parameter_t *p_parameter = get_new_parameter_key(p_field_name, type, i_totalsize);
	p_parameter->nAlignValue = i_alignvalue;
	p_parameter->nArraySize = i_arraysize;

	return p_parameter;
}


// SUB Parameter �߰� ��ũ�� �Լ� �߰�, �� ����� �ʿ�� ���� �� ������ �ϴ� �߰���.
#ifndef _LINUX_VER
#define I_SUB_PARAMETER(p_struct_dds_param, p_insert_field_param) \
{\
	INSERT_PARAM(##p_struct_dds_param->pp_ddsSubParameters,##p_struct_dds_param->i_subParameters, ##p_struct_dds_param->i_subParameters, p_insert_field_param);\
}
#else
#define I_SUB_PARAMETER(p_struct_dds_param, p_insert_field_param) \
{\
	INSERT_PARAM(p_struct_dds_param->pp_ddsSubParameters, p_struct_dds_param->i_subParameters, p_struct_dds_param->i_subParameters, p_insert_field_param);\
}
#endif

struct FooTypeSupport
{
	TYPESUPPORT_BODY
	ReturnCode_t (*register_type)(FooTypeSupport *p_fooTypeSupport, in_mds DomainParticipant *p_participant, in_mds string_mds type_name);
	string_mds (*get_type_name)(FooTypeSupport *p_fooTypeSupport);
};

struct FooDataWriter
{
	DATAWRITER_BODY
	bool b_write_blocked;		// Reliable�� �����Ǿ����� HistoryCache�� ��������, block�� ���� ǥ���ϱ� ���� �÷���
	InstanceHandle_t (*register_instance)(FooDataWriter *p_fooDataWriter, in_mds Foo *p_instance_data);
	InstanceHandle_t (*register_instance_w_timestamp)(FooDataWriter *p_fooDataWriter,in_mds Foo *instance_data,in_mds Time_t source_timestamp);
	ReturnCode_t (*unregister_instance)(FooDataWriter *p_fooDataWriter, in_mds Foo *instance_data, in_mds InstanceHandle_t handle);
	ReturnCode_t (*unregister_instance_w_timestamp)(FooDataWriter *p_fooDataWriter, in_mds Foo *instance_data, in_mds InstanceHandle_t handle, in_mds Time_t source_timestamp);
	ReturnCode_t (*write)(FooDataWriter *p_fooDataWriter, in_mds Foo *p_instance_data, in_mds InstanceHandle_t handle);
	ReturnCode_t (*write_w_timestamp)(FooDataWriter *p_fooDataWriter, in_mds Foo *instance_data, in_mds InstanceHandle_t handle, in_mds Time_t source_timestamp);
	ReturnCode_t (*dispose)(FooDataWriter *p_fooDataWriter, in_mds Foo *instance_data, in_mds InstanceHandle_t instance_handle);
	ReturnCode_t (*dispose_w_timestamp)(FooDataWriter *p_fooDataWriter, in_mds Foo *instance_data, in_mds InstanceHandle_t instance_handle, in_mds Time_t source_timestamp);
	ReturnCode_t (*get_key_value)(FooDataWriter *p_fooDataWriter,inout_mds Foo *key_holder, in_mds InstanceHandle_t handle);
	InstanceHandle_t (*lookup_instance)(FooDataWriter *p_fooDataWriter,in_mds Foo *key_holder);
};

struct FooDataReader
{
	DATAREADER_BODY
	ReturnCode_t (*read)(FooDataReader *p_fooDataReader, inout_mds FooSeq *p_data_values, inout_mds SampleInfoSeq *p_sample_infos, in_mds long max_samples, in_mds SampleStateMask sample_states, in_mds ViewStateMask view_states, in_mds InstanceStateMask instance_states);
	ReturnCode_t (*take)(FooDataReader *p_fooDataReader, inout_mds FooSeq *p_data_values, inout_mds SampleInfoSeq *p_sample_infos, in_mds long max_samples, in_mds SampleStateMask sample_states, in_mds ViewStateMask view_states, in_mds InstanceStateMask instance_states);
	ReturnCode_t (*read_w_condition)(FooDataReader *p_fooDataReader, inout_mds FooSeq *p_data_values,inout_mds SampleInfoSeq *p_sample_infos, in_mds long max_samples, in_mds ReadCondition *p_condition);
	ReturnCode_t (*take_w_condition)(FooDataReader *p_fooDataReader, inout_mds FooSeq *p_data_values,inout_mds SampleInfoSeq *p_sample_infos,in_mds long max_samples,in_mds ReadCondition *p_condition);
	ReturnCode_t (*read_next_sample)(FooDataReader *p_fooDataReader, inout_mds Foo **data_value,inout_mds SampleInfo **sample_info);
	ReturnCode_t (*take_next_sample)(FooDataReader *p_fooDataReader, inout_mds Foo **data_value,inout_mds SampleInfo **sample_info);
	ReturnCode_t (*read_instance)(FooDataReader *p_fooDataReader, inout_mds FooSeq *data_values,inout_mds SampleInfoSeq *sample_infos,in_mds long max_samples,in_mds InstanceHandle_t a_handle,in_mds SampleStateMask sample_states,in_mds ViewStateMask view_states, in_mds InstanceStateMask instance_states);
	ReturnCode_t (*take_instance)(FooDataReader *p_fooDataReader, inout_mds FooSeq *data_values,inout_mds SampleInfoSeq *sample_infos,in_mds long max_samples,in_mds InstanceHandle_t a_handle,in_mds SampleStateMask sample_states,in_mds ViewStateMask view_states,in_mds InstanceStateMask instance_states);
	ReturnCode_t (*read_next_instance)(FooDataReader *p_fooDataReader, inout_mds FooSeq *data_values,inout_mds SampleInfoSeq *sample_infos,in_mds long max_samples,in_mds InstanceHandle_t *previous_handle,in_mds SampleStateMask sample_states,in_mds ViewStateMask view_states,in_mds InstanceStateMask instance_states);
	ReturnCode_t (*take_next_instance)(FooDataReader *p_fooDataReader, inout_mds FooSeq *data_values,inout_mds SampleInfoSeq *sample_infos,in_mds long max_samples,in_mds InstanceHandle_t *previous_handle,in_mds SampleStateMask sample_states,in_mds ViewStateMask view_states,in_mds InstanceStateMask instance_states);
	// DDSE_F_DCPS_0188, DDSE_F_DCPS_0189
	ReturnCode_t(*read_next_instance_w_condition)(FooDataReader *p_fooDataReader, inout_mds FooSeq *data_values, inout_mds SampleInfoSeq *sample_infos, in_mds long max_samples, in_mds InstanceHandle_t *previous_handle, in_mds ReadCondition *p_condition);
	ReturnCode_t(*take_next_instance_w_condition)(FooDataReader *p_fooDataReader, inout_mds FooSeq *data_values, inout_mds SampleInfoSeq *sample_infos, in_mds long max_samples, in_mds InstanceHandle_t *previous_handle, in_mds ReadCondition *p_condition);
	// DDSE_F_DCPS_0190
	ReturnCode_t (*return_loan)(FooDataReader *p_fooDataReader, inout_mds FooSeq *data_values, inout_mds SampleInfoSeq *sample_infos);
	ReturnCode_t (*get_key_value)(FooDataReader *p_fooDataReader, inout_mds Foo *key_holder, in_mds InstanceHandle_t handle);
	InstanceHandle_t (*lookup_instance)(FooDataReader *p_fooDataReader, in_mds Foo *key_holder);
};


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	Duration_t current_duration();
	DDS_DLL_API	Time_t currenTime();

	DDS_DLL_API	void init_foo_type_support(FooTypeSupport* p_foo_type_support);
	DDS_DLL_API	void init_foo_datawriter(FooDataWriter* p_foo_datawriter);
	DDS_DLL_API	void init_foo_datareader(FooDataReader* p_foo_datareader);
	DDS_DLL_API	FooTypeSupport* get_new_foo_type_support();

	DDS_DLL_API	void  register_type(module_object_t* p_this, FooTypeSupport* p_foo_type_support, in_mds DomainParticipant* p_participant, in_mds string_mds type_name);
	DDS_DLL_API	string_mds get_type_name(module_object_t* p_this, FooTypeSupport* p_foo_type_support);
	DDS_DLL_API	FooTypeSupport* domain_participant_find_support_type(module_object_t* p_this, DomainParticipant* p_participant, string_mds type_name);
	DDS_DLL_API	FooTypeSupport* get_type_support(string_mds type_name);
	DDS_DLL_API	void remove_foo_seq(FooSeq* p_fseq, int index);
	DDS_DLL_API	void remove_sample_seq(SampleInfoSeq* p_sampleseq, int index);
#ifdef __cplusplus
}
#endif

#endif


// TypeCode �� struct �� char[]�� ����
//- DIDE-1
typedef struct TypeCode_t TypeCode_t;

struct TypeCode_t 
{
	int key_id;
	int type_size;
	SUPPORT_TYPE type_kind;
	int array_size;
	int name_size;

	int align_value;

	// Nested Struct�� ���� �Ӽ� �߰�
	int nSubtype_Count;
	int nSubtype_Size;

	char *name;
	// Nested Struct�� ���� �Ӽ� �߰�
	TypeCode_t * pSubTypeCode;
};

typedef struct BuiltinTopicDataTypeCode 
{
	TopicBuiltinTopicData data;

	int nTotalTopicTypeSize;	// DynamicTopic���� Type Support�� ���� ���ڷ� ���� Topic ��ü ũ��

	int	typecode_size;
	TypeCode_t *type_code;
} BuiltinTopicDataTypeCode;


