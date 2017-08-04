/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:common.h
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:ä¸€äº›å…±ç”¨ç»“æž„ä½“çš„å®šä¹‰
 * History:
 * *************************************************************/

#ifndef _RQ_PARSE_API_H_
#define _RQ_PARSE_API_H_
#include "common.h"

#define HOS_FILE_PATH "/home/ubuntu/workDir/sambaDir/referenceCode/user_libxml2_20170504/bin/hospitalInformation.xml"


/*Ò½ÔºÐÅÏ¢*/
typedef struct _patient{
	char ID[32];
	char name[32];
	char birth[32];
	char procedureType[128];
	char procedureDate[32];
} PATIENT;

typedef struct _supportPerson{
	char name[32];
	char phone[32];
	char email[32];
	char logPath[64];
} SUPPORT_PERSON;

typedef struct _hospitalInfo{
	char name[64];
	char phone[32];
	char email[32];
	char logPath[64];
	SUPPORT_PERSON person[2]; /*Ö§³ÖÈËÔ±ÐÅÏ¢*/
	PATIENT patient[2]; /*»¼ÕßÐÅÏ¢*/
} HOSPITAL_INFO, *P_HOSPITAL_INFO;

/*xml²Ù×÷µÄ»ù´¡º¯Êý*/
extern void *init_file_dom_tree(parse_xml_t *parse_xml, const char *file_name);
extern void *init_dom_tree(parse_xml_t *parse_xml, const char *xml);
extern void release_dom_tree(xmlDocPtr pdoc);
extern xmlNodePtr get_children_node(xmlNodePtr curNode, const xmlChar *key);
extern int32_t get_current_node_value(char *value, int32_t value_len, xmlDocPtr pdoc,  xmlNodePtr curNode);
extern int get_current_samename_node_nums(xmlNodePtr curNode);
extern xmlNodePtr add_new_node(xmlNodePtr parent, const xmlChar *name, const xmlChar *content);
extern int	modify_node_value(xmlNodePtr cur, const xmlChar *content);
extern xmlNodePtr del_cur_node(xmlNodePtr pnode);
extern xmlAttrPtr xml_prop_set(xmlNodePtr node, const xmlChar *name, const xmlChar *value);
extern int xml_prop_del(xmlNodePtr curNode, const xmlChar *attr_name);
extern xmlNodePtr xml_add_new_child(xmlNodePtr parent, xmlNsPtr ns, const xmlChar *name, const xmlChar *content);
extern int xml_node_value_set(xmlNodePtr cur, const xmlChar *content, int len);
extern xmlNodePtr find_next_node(xmlNodePtr cur_node, const xmlChar *node_name);
extern int32_t package_add_xml_leaf(xmlNodePtr father_node, const xmlChar *key_name, const int8_t *key_value);

#endif
