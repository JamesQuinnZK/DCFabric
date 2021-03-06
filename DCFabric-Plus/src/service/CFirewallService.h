/*
 * BNC SDN Controller GPL Source Code
 * Copyright (C) 2016, BNC <DCFabric-admin@bnc.org.cn>
 *
 * This file is part of the BNC SDN Controller. BNC SDN
 * Controller is a free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, , see <http://www.gnu.org/licenses/>.
 */

/******************************************************************************
*                                                                             *
*   File Name   : CFirewallService.h                                          *
*   Author      : bnc bojiang                                                 *
*   Create Date : 2017-10-30                                                  *
*   Version     : 1.0                                                         *
*   Function    :                                                             *
*                                                                             *
******************************************************************************/
#ifndef __FIREWALLSERVICE_H
#define __FIREWALLSERVICE_H

#include "L3Service.h"

class CFirewallService : public L3Service
{
public:
	CFirewallService();
	virtual ~CFirewallService();

private:
    virtual INT4 IpHandler(const CSmartPtr<CSwitch>& srcSw, CSmartPtr<CHost>& srcHost, CSmartPtr<CHost>& dstHost, ip_t* pkt, packet_in_info_t* packetIn);
    virtual INT4 GetServiceType(CSmartPtr<CHost>& srcHost, CSmartPtr<CHost>& dstHost, UINT4 srcIp, UINT4 dstIp, UINT2 srcPort, UINT2 dstPort, UINT2 proto);
};

#endif
