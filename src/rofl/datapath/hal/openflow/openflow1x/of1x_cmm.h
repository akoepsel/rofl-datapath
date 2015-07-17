/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef OF1X_CMM_H
#define OF1X_CMM_H 

#include <inttypes.h>
#include <rofl/datapath/pipeline/common/packet_matches.h>
#include <rofl/datapath/pipeline/switch_port.h>
#include <rofl/datapath/pipeline/openflow/openflow1x/of1x_switch.h>
#include <rofl/datapath/pipeline/openflow/openflow1x/pipeline/of1x_flow_entry.h>
#include "../../hal.h"
#include "../../hal_utils.h"

/**
* @file of1x_cmm.h
* @author Marc Sune<marc.sune (at) bisdn.de>
*
* @brief HAL cmm (control and management module) OpenFlow specific notifications interface
*/

//C++ extern C
HAL_BEGIN_DECLS

/**
 * @brief   Instructs the CMM to process a PACKET_IN event comming from the DP
 * @ingroup hal_cmm_of1x
 *
 * @param dpid OpenFlow switch DPID
 * @param table_id ID of the table that produced PACKET_IN
 * @param reason one of the OFPR_ ... constants
 * @param in_port Incomming packet port 
 * @param buffer_id  Buffer ID. Must be different from 0 or OF1XP_NO_BUFFER
 * @param pkt_buffer Buffer containing the packet. Shall only be used for reading.
 * @param buf_len Buffer length (may be shorter than the packet stored in buffer)
 * @param total_len total length of buffer
 * @param matches Packet matches
 */
hal_result_t hal_cmm_process_of1x_packet_in(uint64_t dpid, 
					uint8_t table_id, 
					uint8_t reason,
					uint32_t in_port,
					uint32_t buffer_id,
					uint64_t cookie,
					uint8_t* pkt_buffer,
					uint32_t buf_len,
					uint16_t total_len,
					packet_matches_t* matches);

/**
 * @brief   Instructs the CMM to process a FLOW_REMOVED event comming from the DP
 * @ingroup hal_cmm_of1x
 *
 * @param dpid OpenFlow switch DPID
 * @param removed_flow_entry The entry shall ONLY be used for reading, and shall NEVER be
 * removed (of1x_remove_flow_entry). This is done by the fwd_module itself.
 */
hal_result_t hal_cmm_process_of1x_flow_removed(uint64_t dpid, 	
					uint8_t reason, 
					of1x_flow_entry_t* removed_flow_entry);

//C++ extern C
HAL_END_DECLS

#endif /* OF1X_CMM_H */


