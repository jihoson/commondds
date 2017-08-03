#include <unistd.h>
#include <core.h>
#include <cpsdcps.h>
#include <dcps_func.h>
#include "rtps/rtps.h"

#include "Hello.hpp"
int main(){

	DomainId_t domain_id = 0;

	StatusMask mask = 0xffffffff;

	DomainParticipantFactory* p_domainparticipant_factory;
	DomainParticipant* p_domainparticipant = NULL;
	DomainParticipantQos domainparticipant_qos = {};
	PublisherQos publisher_qos = {};
	Publisher* p_publisher = NULL;

	//IDL Resource
	HelloWorldData_Msg::TypeSupport typeSupport = {};
	HelloWorldData_Msg::DataWriter* p_dataWriter = NULL;
	HelloWorldData_Msg::Seq seq = {};
	HelloWorldData_Msg* p_messageInstance = NULL;

	char* typeName = strdup(HelloWorldData_MsgTypeSupport::get_type_name());
	char* topicName = "Hello";	

	Topic* p_topic = NULL;
	TopicQos topic_qos = {};
	DataWriterQos datawriter_qos = {};

	//1. Create DomainParticipant.
	p_domainparticipant = DomainParticipantFactory_get_instance()->create_participant(domain_id, NULL, NULL, 0);

	//2. Create Publisher
	static_get_default_publisher_qos(&publisher_qos);
	p_publisher = p_domainparticipant->create_publisher(p_domainparticipant, &publisher_qos, NULL, mask);

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

	//5. Create DataWriter
	static_get_default_datawriter_qos(&datawriter_qos);
	//Set_qos_xml("DefaultLibrary","EventQoS",&datareader_qos, DATAREADER, "USER_QOS_PROFILES.xml");
	datawriter_qos.reliability.kind = RELIABLE_RELIABILITY_QOS;
	datawriter_qos.history.depth = 10;

	p_dataWriter = (FooDataWriter*)p_publisher->create_datawriter(
			p_publisher,
			p_topic,
			&datawriter_qos,
			NULL,
			mask);

	//6.Create Message Instance .
	Foo *fFoo = NULL;
	int i = 0;

	p_messageInstance = (HelloWorldData_Msg*)calloc(1, sizeof(HelloWorldData_Msg));

 	char* message = "helloworld!";
	while(1){
		for(i=0;i<100;i++){
			Sleep(1000);
			p_messageInstance->userId = i;
			p_messageInstance->message.size = sizeof(message);
			strcpy(p_messageInstance->message.value,message);
			fFoo = (Foo*)p_messageInstance;
			p_dataWriter->write(p_dataWriter, fFoo, 0);
			printf("[Send] userId : %d , message : %s\n",p_messageInstance->userId,p_messageInstance->message.value);
		}
	}

	return 0;
}


