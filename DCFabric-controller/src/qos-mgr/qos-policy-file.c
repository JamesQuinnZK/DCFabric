#include "qos-policy-file.h"
#include "../conn-svr/conn-svr.h"
#include "qos-mgr.h"

/* define the global value */
ini_file_t* g_qos_file;
#define QOS_FILE "./config/qos_policy.ini"


/* by:yhy
 * 读取QOS策略
 */
void init_qos_policy_file()
{
	g_qos_file = read_ini(QOS_FILE);
    if(NULL == g_qos_file)
    {
        LOG_PROC("ERROR", "Get Qos file failed! Please check the QOS_FILE");  
    }
	else 
	{
		read_qos_policy_from_file();
	}
}

/* by:yhy
 * 将QOS策略保存至配置文件
 */
INT4 save_qos_policy_to_file(qos_policy_p policy_p)
{
	if ((NULL != policy_p) && (NULL != policy_p->sw)) 
	{
		INT1 title[48] = {0};
		INT1 dpid_str[48] = {0};
		INT1 id_str[48] = {0};
		INT1 min_speed_str[48] = {0};
		INT1 max_speed_str[48] = {0};
		INT1 burst_str[48] = {0};
		INT1 priority_str[48] = {0};
		
		sprintf(title, "[qos_id_%d]", policy_p->qos_policy_id);
		dpidUint8ToStr(policy_p->sw->dpid, dpid_str);
		sprintf(id_str, "%d", policy_p->qos_policy_id);
		sprintf(min_speed_str, "%llu", policy_p->min_speed);
		sprintf(max_speed_str, "%llu", policy_p->max_speed);
		sprintf(burst_str, "%llu", policy_p->burst_size);
		sprintf(priority_str, "%d", policy_p->priority);

		set_value(g_qos_file, title, "name", policy_p->qos_policy_name);
		set_value(g_qos_file, title, "sw", dpid_str);
		set_value(g_qos_file, title, "id", id_str);
		set_value_ip(g_qos_file, title, "dst_ip", policy_p->dst_ip);
		set_value(g_qos_file, title, "min_speed", min_speed_str);
		set_value(g_qos_file, title, "max_speed", max_speed_str);
		set_value(g_qos_file, title, "burst", burst_str);
		set_value(g_qos_file, title, "priority", priority_str);

		g_qos_file = save_ini(g_qos_file, QOS_FILE);
	}

	return 0;
}


INT4 remove_qos_policy_from_file(qos_policy_p policy_p)
{
	if ((NULL != policy_p) && (NULL != policy_p->sw)) 
	{
		INT1 title[48] = {0};
		sprintf(title, "[qos_id_%d]", policy_p->qos_policy_id);

		remove_selection(g_qos_file, title);

		g_qos_file = save_ini(g_qos_file, QOS_FILE);
	}

	return 0;
}

/* by:yhy
 * 从QOS文件中读取策略至内存
 */
INT4 read_qos_policy_from_file()
{
	INT4 seq = 1;

	for (; seq < QOS_POLICY_MAX_NUM; seq++) 
	{
		INT1 title[48] = {0};

		INT1 qos_policy_name[QOS_POLICY_NAME_LENGTH];
		INT4 qos_policy_id;
		INT1 sw_dpid[48] = {0};
		UINT4 dst_ip;
		UINT8 min_speed;
		UINT8 max_speed;
		UINT8 burst;
		UINT4 priority;
		
		sprintf(title, "[qos_id_%d]", seq);
		
		if (NULL != get_selection_by_selection(g_qos_file, title)) 
		{
			
			INT1 *value = NULL;
			value = get_value(g_qos_file, title, "name");
			if (NULL != value)
				strcpy(qos_policy_name, value);

			value = get_value(g_qos_file, title, "id");
			qos_policy_id = (NULL == value) ? 0 : atoi(value);

			value = get_value(g_qos_file, title, "sw");
			if (NULL != value)
				strcpy(sw_dpid, value);

			value = get_value(g_qos_file, title, "dst_ip");
			dst_ip = (NULL == value) ? 0 : ip2number(value);

			value = get_value(g_qos_file, title, "min_speed");
			min_speed = (NULL == value) ? 0 : strtoull(value, 0, 10);

			value = get_value(g_qos_file, title, "max_speed");
			max_speed = (NULL == value) ? 0 : strtoull(value, 0, 10);

			value = get_value(g_qos_file, title, "burst");
			burst = (NULL == value) ? max_speed : strtoull(value, 0, 10);

			value = get_value(g_qos_file, title, "priority");
			priority = (NULL == value) ? 0 : atoi(value);

			add_qos_rule_by_rest_api(qos_policy_name, qos_policy_id, SW_DPID, sw_dpid, dst_ip, min_speed, max_speed, burst, priority);
		}
	}

	return 0;
}
