/*
	환경 설정 헤더파일

	작성자 : 
	이력
	2010-08-5: 시작
*/


#if !defined(__CONFIGURATION_H)
#define __CONFIGURATION_H

#ifdef _MSC_VER
#define DDS_DLL_API	__declspec(dllexport)
#else
#define DDS_DLL_API
#endif


#pragma pack(push, 1)

struct callback_entry_t
{
    module_callback_t	pf_callback;
    void*				v_data;
};

struct variable_t
{
    value_t			val;

    char*			psz_name;
    uint32_t		i_hash;
    int				i_type;

    char*			psz_text;

    int				(*pf_cmp)(value_t, value_t);
    void			(*pf_dup)(value_t *);
    void			(*pf_free)(value_t *);

    int				i_usage;

    value_t			min, max, step;
    int				i_default;
    module_list_t	choices;
    module_list_t	choices_text;

    bool			b_incallback;

    int                i_entries;
    callback_entry_t*  p_entries;
};

#pragma pack(pop)


#ifdef __cplusplus
extern "C" {
#endif
	DDS_DLL_API	void config_dup(moduleload_t* p_moduleload, module_config_t* p_orig);
	DDS_DLL_API	void config_free(moduleload_t* p_moduleload);
	DDS_DLL_API	void configuration(module_t* p_module);

	DDS_DLL_API	int var_create(module_object_t* p_this, const char* psz_name, int i_type);
	DDS_DLL_API	int var_destroy(module_object_t* p_this, const char* psz_name);
	DDS_DLL_API	int var_get(module_object_t* p_this, const char* psz_name, value_t* p_val);
	DDS_DLL_API	int var_set(module_object_t* p_this, const char* psz_name, value_t val);

	DDS_DLL_API	char* config_get_psz(module_object_t* p_this, const char* psz_name);
	DDS_DLL_API	float config_get_float(module_object_t* p_this, const char* psz_name);
	DDS_DLL_API	int config_get_int(module_object_t* p_this, const char* psz_name);
	DDS_DLL_API	module_config_t* config_find_config(module_object_t* p_this, const char* psz_name);	
#ifdef __cplusplus
}
#endif

static inline int var_create_get_bool(module_object_t* p_obj, const char* psz_name)
{
    value_t val;

    var_create(p_obj, psz_name, VAR_BOOL | VAR_DOINHERIT);
    if( !var_get(p_obj, psz_name, &val ) )
        return val.b_bool;
    else
        return false;
}

static inline float var_create_get_float(module_object_t* p_obj, const char* psz_name)
{
    value_t val;

    var_create(p_obj, psz_name, VAR_FLOAT | VAR_DOINHERIT);
    if( !var_get(p_obj, psz_name, &val ) )
        return val.f_float;
    else
        return 0.0;
}

static inline int var_create_get_integer(module_object_t* p_obj, const char* psz_name)
{
    value_t val;

    var_create(p_obj, psz_name, VAR_INTEGER | VAR_DOINHERIT);
    if( !var_get(p_obj, psz_name, &val ) )
        return val.i_int;
    else
        return 0;
}

static inline char *var_create_get_string(module_object_t* p_obj, const char* psz_name)
{
    value_t val;

    var_create( p_obj, psz_name, VAR_STRING | VAR_DOINHERIT );
    if( !var_get( p_obj, psz_name, &val ) )
        return val.psz_string;
    else
        return strdup( "" );
}

#endif