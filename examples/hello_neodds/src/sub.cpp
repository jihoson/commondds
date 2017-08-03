#include <core.h>
#include <cpsdcps.h>
#include <dcps_func.h>
#include "rtps/rtps.h"
#include "Hello.hpp"

void on_requested_deadline_missed(DataReader* p_datareader, RequestedDeadlineMissedStatus* status)

{

	RequestedDeadlineMissedStatus* temp_status;
	temp_status = (RequestedDeadlineMissedStatus*)malloc(sizeof(RequestedDeadlineMissedStatus));

	if(p_datareader->p_datareader_listener)
		printf("Requested Deadline missed\n");

	if(p_datareader->p_subscriber->p_subscriber_listener)
		printf("Requested Deadline missed for Subscriber\n");

	p_datareader->get_requested_deadline_missed_status(p_datareader, temp_status);
	printf("Total count = %d\n",temp_status->total_count);
	printf("Last Instance handle = %d\n",temp_status->last_instance_handle);
	printf("Total count change = %d\n",temp_status->total_count_change);
	FREE(temp_status);
}



void on_data_available(DataReader* p_datareader)
{
	FooDataReader* p_foo_datareader = (FooDataReader*)p_datareader;
	FooSeq foo_seq = INIT_FOOSEQ;//{seq : 0, foo ** : NULL}
	SampleInfoSeq sample_info_seq = INIT_SAMPLEINFOSEQ;
	HelloWorldData_Msg *helloWorldData = NULL;
	helloWorldData = (HelloWorldData_Msg*) malloc(sizeof(HelloWorldData_Msg));
	message_t* p_message = NULL;

	p_foo_datareader->take(p_foo_datareader, &foo_seq, &sample_info_seq, 1, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);

	while (foo_seq.i_seq) {
		//dump
		p_message = (message_t*)foo_seq.pp_foo[0];
		memcpy(helloWorldData, p_message->v_data, sizeof(HelloWorldData_Msg));
		printf("\n[Seq:%d] userId : %d , Message : %s \n",foo_seq.i_seq,helloWorldData->userId,helloWorldData->message.value);
		message_free(p_message, &foo_seq, &sample_info_seq, 0);
	}

}

void on_subscription_matched(DataReader *p_datareader, SubscriptionMatchedStatus *status)
{
	printf("on_subscription_matched.\n");
}

int main(){
	DomainId_t domain_id = 0;
	StatusMask mask = 0xffffffff;
	DomainParticipantFactory* p_domainparticipant_factory = NULL;
	DomainParticipant* p_domainparticipant = NULL;
	DomainParticipantQos domainparticipant_qos = {};
	SubscriberQos subscriber_qos = {};
	Subscriber* p_subscriber = NULL;

	//IDL Resource
	HelloWorldData_Msg::TypeSupport typeSupport = {};
	HelloWorldData_Msg::DataReader* p_dataReader = NULL;
	//HelloWorldData_Msg::DataWriter* p_dataWriter;
	HelloWorldData_Msg::Seq seq={};
	HelloWorldData_Msg* p_messageInstance = NULL;

	char* typeName = strdup(HelloWorldData_MsgTypeSupport::get_type_name());
	char* topicName = "Hello";	

	Topic* p_topic = NULL;
	TopicQos topic_qos = {};

	DataReaderQos datareader_qos = {};
	DataReaderListener* p_datareader_listener = NULL;

	//1. Create DomainParticipant.
	p_domainparticipant = DomainParticipantFactory_get_instance()->create_participant(domain_id, NULL, NULL, 0);


	//2. Create Subscriber
	static_get_default_subscriber_qos(&subscriber_qos);
	p_subscriber = p_domainparticipant->create_subscriber(p_domainparticipant, &subscriber_qos, NULL, mask);

	//3.Register Topic Type
	typeSupport.register_topic_type(p_domainparticipant);

	//4. set Topic Data QoS 
	static_get_default_topic_qos(&topic_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&topic_qos,TOPIC, "USER_QOS_PROFILES.xml"); //Topic ����

	p_topic = p_domainparticipant->create_topic(
			p_domainparticipant,/*Domain Participnat*/
			topicName,/*topic Name*/
			typeName,/*topic type*/
			&topic_qos,/*Qos*/
			NULL,
			mask);	
	//5. Create DataReader
	static_get_default_datareader_qos(&datareader_qos);
	datareader_qos.reliability.kind =RELIABLE_RELIABILITY_QOS; 
	datareader_qos.history.depth = 10;


	//6.DataReader Listener 
	p_datareader_listener = (DataReaderListener*)malloc(sizeof(DataReaderListener));
	p_datareader_listener->on_data_available = on_data_available;
	p_datareader_listener->on_liveliness_changed = NULL;
	p_datareader_listener->on_requested_deadline_missed = on_requested_deadline_missed;
	p_datareader_listener->on_requested_incompatible_qos = NULL;//on_requested_incompatible_qos;
	p_datareader_listener->on_sample_lost = NULL;
	p_datareader_listener->on_sample_rejected = NULL;
	p_datareader_listener->on_subscription_matched = NULL;


	//7.Create DataReader
	p_dataReader = (FooDataReader*)p_subscriber->create_datareader(
			p_subscriber,
			p_topic,
			&datareader_qos,
			p_datareader_listener,
			mask);

	getchar();

	return 0;
}
