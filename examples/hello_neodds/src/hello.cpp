#include <unistd.h>
#include <core.h>
#include <cpsdcps.h>
#include <dcps_func.h>
#include "rtps/rtps.h"
#include <string>

#include "Hello.hpp"


DomainId_t domain_id = 4;


static bool b_is_quit = false;
/************************************************************************/
/* DataReader Listener �Լ� ����                                        */
/************************************************************************/
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
	FooSeq foo_seq = INIT_FOOSEQ;
	SampleInfoSeq sample_info_seq = INIT_SAMPLEINFOSEQ;
	HelloWorldData_Msg helloWorldData;
	message_t* p_message = NULL;

	p_foo_datareader->take(p_foo_datareader, &foo_seq, &sample_info_seq, 1, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);

	while (foo_seq.i_seq) {
		p_message = (message_t*)foo_seq.pp_foo[0];
		memcpy(&helloWorldData, p_message->v_data, sizeof(HelloWorldData_Msg));
		printf("\n userId : %d , Message : %s \n",helloWorldData.userId,helloWorldData.message.value);
		message_free(p_message, &foo_seq, &sample_info_seq, 0);
	}
}

void on_subscription_matched(DataReader *p_datareader, SubscriptionMatchedStatus *status)
{
	printf("on_subscription_matched.\n");
}

void* write_thread(void* p_dummy)
{

	char *typeName = strcpy(typeName,HelloWorldData_MsgTypeSupport::get_type_name());
    char* topicName = "Hello";	
	
	StatusMask mask = 0xffffffff;
	DomainParticipantFactory* p_domainparticipant_factory;
	DomainParticipant* p_domainparticipant = NULL;
	DomainParticipantQos domainparticipant_qos;
	PublisherQos publisher_qos;
	Publisher* p_publisher = NULL;

	//IDL Resource
	HelloWorldData_Msg::TypeSupport typeSupport;
	HelloWorldData_Msg::DataReader dataReader;
	HelloWorldData_Msg::DataWriter dataWriter;
	HelloWorldData_Msg::Seq seq;

	HelloWorldData_Msg p_messageInstance;

    Foo *fFoo;
	int i;

	TopicQos topic_qos;
	Topic* p_topic;

	DataWriterQos datawriter_qos;
	FooDataWriter* p_datawriter = NULL;

	//1. Create DomainParticipant.
	p_domainparticipant = DomainParticipantFactory_get_instance()->create_participant(domain_id, NULL, NULL, 0);

	//2. Create Publisher
	memset(&publisher_qos, 0, sizeof(PublisherQos));
	static_get_default_publisher_qos(&publisher_qos);
	p_publisher = p_domainparticipant->create_publisher(p_domainparticipant, &publisher_qos, NULL, mask);

	//3. Register type to the Domain Participant.
	typeSupport.register_topic_type(p_domainparticipant);

	//4. set Topic Data QoS 
	memset(&topic_qos, 0, sizeof(TopicQos));
	static_get_default_topic_qos(&topic_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&topic_qos,TOPIC, "USER_QOS_PROFILES.xml"); //Topic ����

	p_topic = p_domainparticipant->create_topic(
			p_domainparticipant,/*Domain Participnat*/
			topicName,/*topic Name*/
			typeName,/*topic type*/
			&topic_qos,/*Qos*/
			NULL,mask);	

	//5. Create DataWriter
	memset(&datawriter_qos, 0, sizeof(DataWriterQos));
	static_get_default_datawriter_qos(&datawriter_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&datareader_qos, DATAREADER, "USER_QOS_PROFILES.xml");
    datawriter_qos.reliability.kind = RELIABLE_RELIABILITY_QOS;
    datawriter_qos.history.depth = 10;

	p_datawriter = (FooDataWriter*)p_publisher->create_datawriter(p_publisher, p_topic, &datawriter_qos, NULL, mask);

    //memset(&data, 0, sizeof(ShapeType));
    memset(&p_messageInstance, 0, sizeof(HelloWorldData_Msg));

    while(1)
    {
        for(i = 0; i < 100; i++)
        {
            Sleep(1000);
			p_messageInstance.userId = i;
			p_messageInstance.message.size = 12;
			strcpy(p_messageInstance.message.value ,"helloWorld!");
            fFoo = (Foo*)&p_messageInstance;
            p_datawriter->write(p_datawriter, fFoo, 0);
        }
    }
}


/************************************************************************/
/* Read ���� Thread                                                     */
/************************************************************************/
void* read_thread(void* p_dummy)
{
    char* topicName = "Hello";	
	char *typeName = strcpy(typeName,HelloWorldData_MsgTypeSupport::get_type_name());
	StatusMask mask = 0xffffffff;
	DomainParticipantFactory* p_domainparticipant_factory;

	//p_domainparticipant = NULL;
	//DomainId_t domain_id = get_global_domain_id();
	DomainParticipantQos domainparticipant_qos;
	DomainParticipant* p_domainparticipant = NULL;

	SubscriberQos subscriber_qos;
	SubscriberListener* p_subscriber_listener = NULL;
	Subscriber* p_subscriber = NULL;

	HelloWorldData_MsgTypeSupport helloWorldTypeSupport;
	TopicQos topic_qos;
	Topic* p_topic;

	DataReaderQos datareader_qos;
	DataReaderListener* p_datareader_listener = NULL;
	FooDataReader* p_datareader = NULL; //DomainParticipantFactory ����

	//1. Create DomainParticipant
	p_domainparticipant = DomainParticipantFactory_get_instance()->create_participant(domain_id, NULL, NULL, 1);

	//2. Create Subscriber
	memset(&subscriber_qos, 0, sizeof(SubscriberQos));
	static_get_default_subscriber_qos(&subscriber_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&subscriber_qos, SUBSCRIBER, "USER_QOS_PROFILES.xml");
	p_subscriber = p_domainparticipant->create_subscriber(p_domainparticipant, &subscriber_qos, p_subscriber_listener, mask);

	//3. Register type to the DomainParticipant.
	helloWorldTypeSupport.register_topic_type(p_domainparticipant);

	//4. Create Topic
	memset(&topic_qos, 0, sizeof(TopicQos));
	static_get_default_topic_qos(&topic_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&topic_qos,TOPIC, "USER_QOS_PROFILES.xml");
	p_topic = p_domainparticipant->create_topic(
			p_domainparticipant,topicName,
			typeName,
			&topic_qos,
			NULL,mask);	

	//5. Create DataReader
	memset(&datareader_qos, 0, sizeof(DataReaderQos));
	static_get_default_datareader_qos(&datareader_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&datareader_qos, DATAREADER, "USER_QOS_PROFILES.xml");
    datareader_qos.reliability.kind = RELIABLE_RELIABILITY_QOS;
    datareader_qos.history.depth = 10;

	//DataReader Listener ����
	p_datareader_listener = (DataReaderListener*)malloc(sizeof(DataReaderListener));
	p_datareader_listener->on_data_available = on_data_available;
	p_datareader_listener->on_liveliness_changed = NULL;
	p_datareader_listener->on_requested_deadline_missed = on_requested_deadline_missed;
	p_datareader_listener->on_requested_incompatible_qos = NULL;//on_requested_incompatible_qos;
	p_datareader_listener->on_sample_lost = NULL;
	p_datareader_listener->on_sample_rejected = NULL;
	p_datareader_listener->on_subscription_matched = NULL;

	//DataReader ����
	p_datareader = (FooDataReader*)p_subscriber->create_datareader(p_subscriber, p_topic, &datareader_qos, p_datareader_listener, mask);
}

/************************************************************************/
/* main �Լ�                                                            */
/************************************************************************/
int main()
{
	
	
	StatusMask mask = 0xffffffff;
	DomainParticipantFactory* p_domainparticipant_factory;
	DomainParticipant* p_domainparticipant = NULL;
	DomainParticipantQos domainparticipant_qos;
	PublisherQos publisher_qos;
	Publisher* p_publisher = NULL;

	//IDL Resource
	HelloWorldData_Msg::TypeSupport typeSupport;
	HelloWorldData_Msg::DataReader dataReader;
	HelloWorldData_Msg::DataWriter* p_dataWriter;
	HelloWorldData_Msg::Seq seq;

	HelloWorldData_Msg* p_messageInstance;

	char *typeName = strdup(HelloWorldData_MsgTypeSupport::get_type_name());
    char* topicName = "Hello";	
    Foo *fFoo;
	int i;

	Topic* p_topic;
	TopicQos topic_qos;
	DataWriterQos datawriter_qos;

	//1. Create DomainParticipant.
	p_domainparticipant = DomainParticipantFactory_get_instance()->create_participant(domain_id, NULL, NULL, 0);

	//2. Create Publisher
	memset(&publisher_qos, 0, sizeof(PublisherQos));
	static_get_default_publisher_qos(&publisher_qos);
	p_publisher = p_domainparticipant->create_publisher(p_domainparticipant, &publisher_qos, NULL, mask);
	
	//3.Register Topic Type
	typeSupport.register_topic_type(p_domainparticipant);

	//4. set Topic Data QoS 
	memset(&topic_qos, 0, sizeof(TopicQos));
	static_get_default_topic_qos(&topic_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&topic_qos,TOPIC, "USER_QOS_PROFILES.xml"); //Topic ����

	p_topic = p_domainparticipant->create_topic(
			p_domainparticipant,/*Domain Participnat*/
			topicName,/*topic Name*/
			typeName,/*topic type*/
			&topic_qos,/*Qos*/
			NULL,mask);	

	//5. Create DataWriter
	memset(&datawriter_qos, 0, sizeof(DataWriterQos));
	static_get_default_datawriter_qos(&datawriter_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&datareader_qos, DATAREADER, "USER_QOS_PROFILES.xml");
    datawriter_qos.reliability.kind = RELIABLE_RELIABILITY_QOS;
    datawriter_qos.history.depth = 10;

	p_dataWriter = (FooDataWriter*)p_publisher->create_datawriter(p_publisher, p_topic, &datawriter_qos, NULL, mask);
	//6.Create Message Instance .
	p_messageInstance = (HelloWorldData_Msg*)malloc(sizeof(HelloWorldData_Msg));
    memset(p_messageInstance, 0, sizeof(HelloWorldData_Msg));
 	p_messageInstance->userId = i;
	char* message = "helloworld!";
	p_messageInstance->message.size = sizeof(message);
	strcpy(p_messageInstance->message.value,message);
    fFoo = (Foo*)&p_messageInstance;
    p_dataWriter->write(p_dataWriter, fFoo, 0);

	printf("Success!");
	getchar();

// 	pthread_t thread_id;
// 	pthread_create(&thread_id, NULL, &write_thread, NULL);
//	pthread_create(&thread_id, NULL, &read_thread, NULL);


	return 0;
	//quit();
}
