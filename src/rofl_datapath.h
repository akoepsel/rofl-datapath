/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
* @file rofl_datapath.h
* @author Marc Sune<marc.sune (at) bisdn.de>
* @author Andreas Koepsel <andreas.koepsel (at) bisdn.de>
*
* @brief Main Revised OpenFlow Library datapath (ROFL-datapath) header
*/

#ifndef __ROFL_DP_H__
#define __ROFL_DP_H__

#include "rofl_datapath_conf.h"
#include <stdlib.h>

/**
* Common return codes
*/
typedef enum rofl_result {
	ROFL_SUCCESS	= EXIT_SUCCESS,
	ROFL_FAILURE	= EXIT_FAILURE,

	//Add more here... if they are common!
}rofl_result_t;

/**
* ROFL-datapath version number (git tag) 
*/
extern const char ROFL_DATAPATH_VERSION[];

/**
* ROFL-datapath build number (git hash) 
*/
extern const char ROFL_DATAPATH_BUILD_NUM[];

/**
* Branch where ROFL-datapath was compiled in (git branch) 
*/
extern const char ROFL_DATAPATH_BUILD_BRANCH[];

/**
* ROFL-datapath describe summary (git describe) 
*/
extern const char ROFL_DATAPATH_BUILD_DESCRIBE[];

/*
* Extern C wrappings
*/
#ifdef __cplusplus
	# define ROFL_BEGIN_DECLS extern "C" {
	# define ROFL_END_DECLS   }
#else
	# define ROFL_BEGIN_DECLS
	# define ROFL_END_DECLS
#endif //__cplusplus

#endif //ROFL-DP
