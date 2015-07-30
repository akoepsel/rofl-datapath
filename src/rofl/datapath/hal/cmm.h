/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef CMM__H
#define CMM__H 

#include "hal.h"
#include "hal_utils.h"
#include <rofl/datapath/pipeline/monitoring.h>
#include <rofl/datapath/pipeline/switch_port.h>


/**
* @file cmm.h
* @author Marc Sune<marc.sune (at) bisdn.de>
*
* @brief HAL cmm (control and management module) notifications interface
*/

//C++ extern C
HAL_BEGIN_DECLS

/**
* @brief   Notify the CMM that a port has been added to the system. This function shall NOT be called when an exisiting port attachment status changes. When a new port is automatically attached to an LSI, then the port_add message implicitely means an attachment to an LSI.
* @param port_snapshot Snapshot of the current state of a switch port. The snapshot MUST be deleted using switch_port_destroy_snapshot()
* @ingroup hal_cmm
*/
hal_result_t hal_cmm_notify_port_add(switch_port_snapshot_t* port_snapshot);

/**
* @brief   Notifies the CMM that port has been deleted from the platform. This function shall NOT be called when a port attachment status changes. When a port deletion happens on an attached port, then the port deletion of an attached port implicitly means a detachment of the port from the LSI.
* @param port_snapshot Snapshot of the current state of a switch port. The snapshot MUST be deleted using switch_port_destroy_snapshot()
* @ingroup hal_cmm
*/
hal_result_t hal_cmm_notify_port_delete(switch_port_snapshot_t* port_snapshot);

/**
* @brief   Notify the CMM of a port status change. This function shall NOT be called when a port attachment status changes.
* @param port_snapshot Snapshot of the current state of a switch port. The snapshot MUST be deleted using switch_port_destroy_snapshot()
* @ingroup hal_cmm
*/
hal_result_t hal_cmm_notify_port_status_changed(switch_port_snapshot_t* port_snapshot);

/**
* @brief   Notify a monitoring state change to CMM 
* @param monitoring_snapshot Snapshot of the current monitoring state. The snapshot MUST be deleted using monitoring_destroy_snapshot()
* @ingroup hal_cmm
*/
hal_result_t hal_cmm_notify_monitoring_state_changed(monitoring_snapshot_state_t* monitoring_snapshot);

//C++ extern C
HAL_END_DECLS

/* OpenFlow related events */
#include "openflow/openflow1x/of1x_cmm.h"
//TODO: Add more versions here...

#endif /** CMM__H */
