/****************************************************************
 * FileName:xml_parse_event.c
 * Author:merlin
 * Version:v1
 * Time:20160613
 * Description:create and parse xml package
 * *************************************************************/
//#include <string.h>
#include "common.h"
//#include "xml_base.h"
#include "rq_xml_base.h"
#include "xmlstring.h"
#include "rq_parse_xml_api.h"

/**********************************************************************
* Description:????Ϣд???ļ???
***************************************************************/
int writeLog(char *buffer)
{
	FILE * fp = NULL;
	char path[64] = {"./ttttLog.log"};
	fp = fopen(path, "a+");	
	if(fp == NULL){
		return -3;
	}
	fwrite(buffer,strlen(buffer),1,fp);

	fclose(fp);
	
	return 0;
}

#if 0
/**************************************************************************
* Description:??xml?ļ?
**************************************************************************/
int readFileXml(char *path, char *type)
{
		return 0;
#if 0
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL, pcur = NULL;



	/*??ȡxml?ļ?*/

	xmlKeepBlanksDefault(0);//???????ϣ???ֹ??????Ԫ??ǰ???Ŀհ??ı????ŵ???һ??node
	pdoc = xmlReadFile (path, "UTF-8", XML_PARSE_RECOVER);//libxmlֻ?ܽ???UTF-8??ʽ????

	if (pdoc == NULL)
	{
		printf ("[merlin]:error:can't open file!\n");
		exit (1);
	}
	/*****************??ȡxml?ĵ??????ĸ??ڶ???********************/
	proot = xmlDocGetRootElement (pdoc);

	if (proot == NULL)
	{
		printf("[%s][merlin]:line:%d\n", __func__, __LINE__);
		exit (1);
	}
	
	/*????xml?ļ?*/
	
	/*?ͷ???Դ*/
	xmlFreeDoc (pdoc);
	xmlCleanupParser ();
	xmlMemoryDump ();
	return 0;
#endif
}

/*************************************************************************
 * description??дxml?ļ?
 ***************************************************************************/
int writeXmlFile(char *path)
{
	//?????ļ??ͽڵ?ָ??
	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"root");
	//???ø??ڵ?
	xmlDocSetRootElement(doc,root_node);
	//?ڸ??ڵ???ֱ?Ӵ????ڵ?
	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode1", BAD_CAST "newNode1 content");
	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode2", BAD_CAST "newNode2 content");
	xmlNewTextChild(root_node, NULL, BAD_CAST "newNode3", BAD_CAST "newNode3 content");
	//????һ???ڵ㣬?????????ݺ????ԣ?Ȼ????????????
	xmlNodePtr node = xmlNewNode(NULL,BAD_CAST"node2");
	xmlNodePtr content = xmlNewText(BAD_CAST"NODE CONTENT");
	xmlAddChild(root_node,node);
	xmlAddChild(node,content);
	xmlNewProp(node,BAD_CAST"attribute",BAD_CAST "yes");
	//????һ?????Ӻ????ӽڵ?
	node = xmlNewNode(NULL, BAD_CAST "son");
	xmlAddChild(root_node,node);
	xmlNodePtr grandson = xmlNewNode(NULL, BAD_CAST "grandson");
	xmlAddChild(node,grandson);
	xmlAddChild(grandson, xmlNewText(BAD_CAST "This is a grandson node"));
	//?洢xml?ļ?
	int nRel = xmlSaveFile("CreatedXml.xml",doc);
	if (nRel != -1)
	{
		printf("[%s][merlin]:line:%d\n", __func__, __LINE__);
		//coutһ??xml?ļ???????,д??"???ֽ?"	
	}
	//?ͷ??ļ??ڽڵ㶯̬???????ڴ?
	xmlFreeDoc(doc);

	return 0;
}
#endif

/*******************************************************************
* Description:??ȡĳ???ڵ??е???name??Ӧ??ֵ
* Return:
*********************************************************************/
int getNodeText(xmlNodePtr node, char *NodeName, char *NodeValue)
{
	char buffer[64] = {0};
	xmlNodePtr current;
	xmlChar *name = NULL, *value = NULL; 

	if(NULL == node){
		sprintf(buffer, "[%s][merlin]: line:%d\n", __func__, __LINE__);
		writeLog(buffer);
		return -1;
	}

	printf("[%s]:nodeN=%s line:%d\n", __func__, (char*)(node->name), __LINE__);
	if(xmlStrcasecmp(node->name,BAD_CAST(NodeName))!=0){
		sprintf(buffer, "[%s][merlin]: line:%d\n", __func__, __LINE__);
		writeLog(buffer);
		return -2;
	}     
	for(current=node->children;current;current=current->next){
		if(xmlStrcasecmp(current->name,BAD_CAST(NodeName))==0){
			name=xmlGetProp(current,BAD_CAST"name");
			value=xmlNodeGetContent(current);
			//memcpy(NodeValue, (char*)value, strlen((char*)value));
			sprintf(NodeValue, "%s", (char*)value);
			xmlFree(name);                       
			xmlFree(value);
		}            
	}
	return 0;
}

int readXml()
{
	xmlDocPtr doc = NULL;           //?????????ĵ?ָ??  
    xmlNodePtr curNode;      //????????ָ??(????Ҫ??Ϊ???ڸ??????????ƶ?)  
    xmlChar *szKey;          //??ʱ?ַ?????��  
    //char *szDocName;  
#if 0
    if (argc <= 1)   
    {  
       printf("Usage: %s docname/n", argv[0]);  
       return(0);  
    }  
    szDocName = argv[1];  
    doc = xmlReadFile(szDocName,"GB2312",XML_PARSE_RECOVER); //?????ļ?  
#endif
    if (NULL == doc)  
    {    
       printf("Document not parsed successfully/n");      
       return -1;  
    }  
    curNode = xmlDocGetRootElement(doc); //ȷ???ĵ???Ԫ??  
    if (NULL == curNode)  
    {  
       printf("empty document/n");  
       xmlFreeDoc(doc);  
       return -1;  
    }  
    if (xmlStrcmp(curNode->name, BAD_CAST "ioMsg"))  
    {  
       printf("document of the wrong type, root node != ioMsg/n");  
       xmlFreeDoc(doc);  
       return -1;  
    }  
    curNode = curNode->children;  
    while(curNode != NULL)  
    {  
       //ȡ???ڵ??е?????  
       szKey = xmlNodeGetContent(curNode);  
       printf("Content value =%s/n", szKey);  
       curNode = curNode->next;  
     }  
     xmlFreeDoc(doc);  
    return 0;  
}

/******************************************************************
 * Description:??ȡҽԺ??Ϣ??ֱ?Ӵ??????ļ??ж?ȡ??Ϣ
 * Outpam hospital:??????��????Ϣ
 * Return:0>-???????? 0-?ɹ?
 ******************************************************************/
int getHospitalInfo(HOSPITAL_INFO *hospital)
{
	int valuelen = 128;
	char filePath[128] = {0};
	parse_xml_t xmldata;
	xmlNodePtr curNode,  tmp_node = NULL;

	if(NULL == hospital){
		return -1;
	}
	/*??ȡxml?ļ?*/
	sprintf(filePath, "%s", HOS_FILE_PATH);
	if(NULL == init_file_dom_tree(&xmldata, filePath)){
		return -2;
	}
	memset(hospital, 0, sizeof(HOSPITAL_INFO));
	/*ҽԺ??Ϣ*/
	curNode = get_children_node(xmldata.proot, BAD_CAST("hospital"));
	tmp_node = get_children_node(curNode, BAD_CAST("name"));
	get_current_node_value((hospital->name), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("phone"));
	get_current_node_value((hospital->phone), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("email"));
	get_current_node_value((hospital->email), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("logPath"));
	get_current_node_value((hospital->logPath), valuelen, xmldata.pdoc, tmp_node);
	/*ҽԺ֧????Ա??Ϣ*/
	curNode = get_children_node(xmldata.proot, BAD_CAST("person"));
	tmp_node = get_children_node(curNode, BAD_CAST("name"));
	get_current_node_value((hospital->person[0].name), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("phone"));
	get_current_node_value((hospital->person[0].phone), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("email"));
	get_current_node_value((hospital->person[0].email), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("logPath"));
	get_current_node_value((hospital->person[0].logPath), valuelen, xmldata.pdoc, tmp_node);
	/*??????Ϣ*/
	curNode = get_children_node(xmldata.proot, BAD_CAST("patient"));
	tmp_node = get_children_node(curNode, BAD_CAST("name"));
	get_current_node_value((hospital->patient[0].name), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("ID"));
	get_current_node_value((hospital->patient[0].ID), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("procedureType"));
	get_current_node_value((hospital->patient[0].procedureType), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("procedureDate"));
	get_current_node_value((hospital->patient[0].procedureDate), valuelen, xmldata.pdoc, tmp_node);
	tmp_node = get_children_node(curNode, BAD_CAST("birth"));
	get_current_node_value((hospital->patient[0].birth), valuelen, xmldata.pdoc, tmp_node);

#if 0 /*???Գ???*/
	char nodeValue[64] = {0}, buffer[128] = {0};
	curNode = get_children_node(xmldata.proot, BAD_CAST("patient"));
	getNodeText(curNode, "name", nodeValue);
	sprintf(buffer, "[%s]:nodeValue=%s line:%d\n", __func__, nodeValue, __LINE__);
	writeLog(buffer);
	getNodeText(curNode, "procedureDate", nodeValue);
	sprintf(buffer, "[%s]:nodeValue=%s line:%d\n", __func__, nodeValue, __LINE__);
	writeLog(buffer);
#endif

	return 0;
}

/****************************************************************
 * Description:????Ϣд??xml?ļ???
 * Inparm hospital:??Ҫд???ļ?????Ϣ
 *****************************************************************/
int setHospitalInfo(HOSPITAL_INFO *hospital)
{
	int ret = 0;
	char filePath[128] = {0};
#if 0
	//getPatientInfoFromFile

	sprintf((hospital->name), "%s", "shezhHos");
	sprintf((hospital->phone), "%s", "12345678901");
	sprintf((hospital->email), "%s", "1079843691@qq.com");
	sprintf((hospital->logPath), "%s", filePath);
	sprintf((hospital->person[0].name), "%s", "AJke");
	sprintf((hospital->person[0].phone), "%s", "11111111");
	sprintf((hospital->person[0].email), "%s", "A1079843691@qq.com2");
	sprintf((hospital->person[0].logPath), "%s", filePath);	

	sprintf((hospital->patient[0].name), "%s", "BJke");
	sprintf((hospital->patient[0].ID), "%s", "11111111");
	sprintf((hospital->patient[0].procedureDate), "%s", "B1079843691@qq.com2");
	sprintf((hospital->patient[0].procedureType), "%s", filePath);
#endif

	sprintf(filePath, "%s", HOS_FILE_PATH);
	if(NULL == hospital){
		return -1;
	}
	
	xmlNodePtr head_node = NULL, curNode = NULL;
	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST"PatientRecords");
	xmlDocSetRootElement(doc, root_node);
	/*ҽԺ??Ϣ*/
	head_node = xmlNewNode(NULL, BAD_CAST "hospital");
	if(NULL == head_node){
		xmlFreeDoc(doc);
		return -1;
	}
	xmlAddChild(root_node, head_node);
	package_add_xml_leaf(head_node, (const xmlChar *)"name", (const int8_t *)(hospital->name));
	package_add_xml_leaf(head_node, (const xmlChar *)"phone", (const int8_t *)(hospital->phone));
	package_add_xml_leaf(head_node, (const xmlChar *)"email", (const int8_t *)(hospital->email));
	package_add_xml_leaf(head_node, (const xmlChar *)"logPath", (const int8_t *)(hospital->logPath));
	/*ҽԺ֧????Ա??Ϣ*/
	curNode = xmlNewNode(NULL, BAD_CAST "person");
	if(NULL == curNode){
		xmlFreeDoc(doc);
		return -1;
	}
	xmlAddChild(root_node, curNode);
	package_add_xml_leaf(curNode, (const xmlChar *)"name", (const int8_t *)(hospital->person[0].name));
	package_add_xml_leaf(curNode, (const xmlChar *)"phone", (const int8_t *)(hospital->person[0].phone));
	package_add_xml_leaf(curNode, (const xmlChar *)"email", (const int8_t *)(hospital->person[0].email));
	package_add_xml_leaf(curNode, (const xmlChar *)"logPath", (const int8_t *)(hospital->person[0].logPath));

	/*??????Ϣ*/
	curNode = xmlNewNode(NULL, BAD_CAST "patient");
	if(NULL == curNode){
		xmlFreeDoc(doc);
		return -1;
	}
	xmlAddChild(root_node, curNode);
	package_add_xml_leaf(curNode, (const xmlChar *)"ID", (const int8_t *)(hospital->patient[0].ID));
	package_add_xml_leaf(curNode, (const xmlChar *)"name", (const int8_t *)(hospital->patient[0].name));
	package_add_xml_leaf(curNode, (const xmlChar *)"birth", (const int8_t *)(hospital->patient[0].birth));
	package_add_xml_leaf(curNode, (const xmlChar *)"procedureType", (const int8_t *)(hospital->patient[0].procedureType));
	package_add_xml_leaf(curNode, (const xmlChar *)"procedureDate", (const int8_t *)(hospital->patient[0].procedureDate));
	
	/*????xml????*/
	int rel = xmlSaveFile(filePath, doc);
	if (rel < 0){
		ret = -1;
	}

	xmlFreeDoc(doc); //?ͷ??ļ??ڽڵ㶯̬???????ڴ?

	//getHospitalInfo(hospital);
	return ret;
}

/*******************************************************************************
* Descriptin:
*******************************************************************************/
int getHosInfoTest()
{
	int ret = 0;
	char filePath[128] = {0}, nodeValue[64] = {0};
	parse_xml_t xmldata;
	xmlNodePtr curNode,  tmp_node = NULL;
	//HOSPITAL_INFO hospital;
	
	/*��ȡxml�ļ��е���Ϣ*/
	sprintf(filePath, "%s", HOS_FILE_PATH);
	if(NULL == init_file_dom_tree(&xmldata, filePath)){
		return -2;
	}
	//memset(&hospital, 0, sizeof(HOSPITAL_INFO));
	curNode = get_children_node(xmldata.proot, BAD_CAST("hospital"));
	ret = getNodeText(curNode, "name", nodeValue);
	printf("[%s]:nodeValue=%s line:%d\n", __func__, nodeValue, __LINE__);
	
	return 0;
}

int main(int argc, const char *argv[])
{
	char buffer[64] = {0};
	int ret = 0, i =0;
	HOSPITAL_INFO hospital;

	memset(&hospital, 0, sizeof(hospital));
	ret = getHospitalInfo(&hospital);
	ret = setHospitalInfo(&hospital);
	memset(&hospital, 0, sizeof(hospital));
	ret = getHospitalInfo(&hospital);
	printf("[%s]:ret=%d line:%d\n", __func__, ret, __LINE__);

	for(i=0; i<300;i++){
		i++;
	}

	sprintf(buffer, "3-%s", (hospital.name));
	sprintf((hospital.name), "%s", buffer);
	printf("[%s]:name=%s line:%d\n", __func__, (hospital.name), __LINE__);
	sprintf(buffer, "3-%s", (hospital.patient[0].name));
	sprintf((hospital.patient[0].name), "%s", buffer);
	printf("[%s]:name=%s line:%d\n", __func__, (hospital.patient[0].name), __LINE__);
	sprintf(buffer, "3-%s", (hospital.person[0].name));
	sprintf((hospital.person[0].name), "%s", buffer);
	printf("[%s]:name=%s line:%d\n", __func__, (hospital.person[0].name), __LINE__);
	sprintf((hospital.patient[0].birth), "%s", buffer);
	ret = setHospitalInfo(&hospital);

	getHosInfoTest();
	
	return 0;
}
