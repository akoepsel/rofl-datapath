/*
 * csegmsg.h
 *
 *  Created on: 13.03.2014
 *      Author: andreas
 */

#ifndef CSEGMSG_H_
#define CSEGMSG_H_

#include <inttypes.h>

#include <iostream>

#include "rofl/common/cclock.h"
#include "rofl/common/logging.h"
#include "rofl/common/openflow/messages/cofmsg_stats.h"
#include "rofl/common/openflow/messages/cofmsg_desc_stats.h"
#include "rofl/common/openflow/messages/cofmsg_flow_stats.h"
#include "rofl/common/openflow/messages/cofmsg_aggr_stats.h"
#include "rofl/common/openflow/messages/cofmsg_table_stats.h"
#include "rofl/common/openflow/messages/cofmsg_port_stats.h"
#include "rofl/common/openflow/messages/cofmsg_queue_stats.h"
#include "rofl/common/openflow/messages/cofmsg_group_stats.h"
#include "rofl/common/openflow/messages/cofmsg_group_desc_stats.h"
#include "rofl/common/openflow/messages/cofmsg_group_features_stats.h"
#include "rofl/common/openflow/messages/cofmsg_table_features_stats.h"
#include "rofl/common/openflow/messages/cofmsg_port_desc_stats.h"

namespace rofl {
namespace openflow {

class csegmsg {

	cclock				expires;	// time this cmultipart message will expire
	uint32_t 			xid;		// transaction id used by this multipart message
	cofmsg_stats*		msg;		// stitched multipart message

public:

	/**
	 *
	 */
	csegmsg(uint32_t xid);

	/**
	 *
	 */
	virtual
	~csegmsg();

	/**
	 *
	 */
	csegmsg(csegmsg const& msg);

	/**
	 *
	 */
	csegmsg&
	operator= (csegmsg const& msg);


public:

	friend std::ostream&
	operator<< (std::ostream& os, csegmsg const& msg) {
		os << rofl::indent(0) << "<csegmsg" << " >" << std::endl;
		os << rofl::indent(2) << "<expires: " << msg.expires << " >" << std::endl;
		os << rofl::indent(2) << "<xid: " << (int)msg.xid << " >" << std::endl;
		rofl::indent i(2);
		switch (msg.msg->get_version()) {
		case rofl::openflow13::OFP_VERSION: {

			switch (msg.msg->get_type()) {
			case rofl::openflow13::OFPT_MULTIPART_REQUEST: {

				switch (msg.msg->get_stats_type()) {
				case rofl::openflow13::OFPMP_DESC: {
					os << dynamic_cast<cofmsg_desc_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_FLOW: {
					os << dynamic_cast<cofmsg_flow_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_AGGREGATE: {
					os << dynamic_cast<cofmsg_aggr_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_TABLE: {
					os << dynamic_cast<cofmsg_table_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_PORT_STATS: {
					os << dynamic_cast<cofmsg_port_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_QUEUE: {
					os << dynamic_cast<cofmsg_queue_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_GROUP: {
					os << dynamic_cast<cofmsg_group_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_GROUP_DESC: {
					os << dynamic_cast<cofmsg_group_desc_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_GROUP_FEATURES: {
					os << dynamic_cast<cofmsg_group_features_stats_request const&>( *(msg.msg) );
				} break;
				// TODO: meters
				case rofl::openflow13::OFPMP_TABLE_FEATURES: {
					os << dynamic_cast<cofmsg_table_features_stats_request const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_PORT_DESC: {
					os << dynamic_cast<cofmsg_port_desc_stats_request const&>( *(msg.msg) );
				} break;
				default: {
					os << *(msg.msg);
				};
				}

			} break;
			case rofl::openflow13::OFPT_MULTIPART_REPLY: {

				switch (msg.msg->get_stats_type()) {
				case rofl::openflow13::OFPMP_DESC: {
					os << dynamic_cast<cofmsg_desc_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_FLOW: {
					os << dynamic_cast<cofmsg_flow_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_AGGREGATE: {
					os << dynamic_cast<cofmsg_aggr_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_TABLE: {
					os << dynamic_cast<cofmsg_table_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_PORT_STATS: {
					os << dynamic_cast<cofmsg_port_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_QUEUE: {
					os << dynamic_cast<cofmsg_queue_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_GROUP: {
					os << dynamic_cast<cofmsg_group_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_GROUP_DESC: {
					os << dynamic_cast<cofmsg_group_desc_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_GROUP_FEATURES: {
					os << dynamic_cast<cofmsg_group_features_stats_reply const&>( *(msg.msg) );
				} break;
				// TODO: meters
				case rofl::openflow13::OFPMP_TABLE_FEATURES: {
					os << dynamic_cast<cofmsg_table_features_stats_reply const&>( *(msg.msg) );
				} break;
				case rofl::openflow13::OFPMP_PORT_DESC: {
					os << dynamic_cast<cofmsg_port_desc_stats_reply const&>( *(msg.msg) );
				} break;
				default: {
					os << *(msg.msg);
				};
				}

			} break;
			default: {
				// oops, do nothing here
			};
			}

		} break;
		}
		return os;
	};
};

}; // end of namespace openflow
}; // end of namespace rofl

#endif /* CMULTIPART_H_ */
