/*
 * crofchan.h
 *
 *  Created on: 31.12.2013
 *      Author: andreas
 */

#ifndef CROFCHAN_H_
#define CROFCHAN_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <inttypes.h>
#ifdef __cplusplus
}
#endif

#include "ciosrv.h"
#include "crofsock.h"
#include "openflow/cofhelloelems.h"
#include "openflow/cofhelloelemversionbitmap.h"

namespace rofl {
namespace openflow {

class eRofConnBase 					: public RoflException {};
class eRofConnXidSpaceExhausted		: public eRofConnBase {};

class crofconn; // forward declaration

class crofconn_env {
public:
	virtual ~crofconn_env() {};
	virtual void handle_close(crofconn *conn) = 0;
	virtual void recv_message(crofconn *conn, cofmsg *msg) = 0;
	virtual uint32_t get_async_xid(crofconn *conn) = 0;
	virtual uint32_t get_sync_xid(crofconn *conn) = 0;
	virtual void release_sync_xid(crofconn *conn, uint32_t xid) = 0;
};


class crofconn :
		public crofsock_env,
		public ciosrv
{
	crofconn_env 					*env;
	uint8_t							auxiliary_id;
	crofsock						*rofsock;
	cofhello_elem_versionbitmap		versionbitmap; 			// supported OF versions by this entity
	cofhello_elem_versionbitmap		versionbitmap_peer;		// supported OF versions by peer entity
	uint8_t							ofp_version;

	enum msg_type_t {
		OFPT_HELLO = 0,
		OFPT_ERROR = 1,
		OFPT_ECHO_REQUEST = 2,
		OFPT_ECHO_REPLY = 3,
	};

	enum crofconn_event_t {
		EVENT_NONE				= 0,
		EVENT_CONNECTED 		= 1,
		EVENT_DISCONNECTED 		= 2,
		EVENT_HELLO_RCVD 		= 3,
		EVENT_HELLO_EXPIRED		= 4,
		EVENT_ECHO_RCVD			= 5,
		EVENT_ECHO_EXPIRED		= 6,
	};
	std::deque<enum crofconn_event_t> 	events;

	enum crofconn_state_t {
		STATE_DISCONNECTED 		= 1,
		STATE_WAIT_FOR_HELLO	= 2,
		STATE_ESTABLISHED 		= 3,
	};
	enum crofconn_state_t				state;

	enum crofconn_timer_t {
		TIMER_WAIT_FOR_HELLO	= 1,
		TIMER_SEND_ECHO			= 2,
		TIMER_WAIT_FOR_ECHO		= 3,
	};

#define DEFAULT_HELLO_TIMEOUT	5
#define DEFAULT_ECHO_TIMEOUT 	5
#define DEFAULT_ECHO_INTERVAL	5

public:

	unsigned int					hello_timeout;
	unsigned int					echo_timeout;
	unsigned int					echo_interval;

public:

	/**
	 *
	 */
	crofconn(
			crofconn_env *env,
			uint8_t auxiliary_id,
			int sd,
			caddress const& ra,
			cofhello_elem_versionbitmap const& versionbitmap);

	/**
	 *
	 */
	virtual ~crofconn();

public:

	/**
	 * @brief	Returns a reference to the versionbitmap announced by this entity
	 */
	cofhello_elem_versionbitmap&
	get_versionbitmap() { return versionbitmap; };

	/**
	 * @brief	Returns a reference to the versionbitmap seen from the peer
	 */
	cofhello_elem_versionbitmap&
	get_versionbitmap_peer() { return versionbitmap_peer; };

	/**
	 * @brief	Returns the negotiated OFP version (or OFP_UNKNOWN)
	 */
	uint8_t
	get_version() const { return ofp_version; };

private:

	virtual void
	handle_connect_refused(crofsock *rofsock);

	virtual void
	handle_open (crofsock *rofsock);

	virtual void
	handle_close(crofsock *rofsock);

	virtual void
	recv_message(crofsock *rofsock, cofmsg *msg);

private:

	/**
	 *
	 */
	virtual void
	handle_timeout(int opaque);

	/**
	 *
	 */
	void
	run_engine(enum crofconn_event_t event = EVENT_NONE);

	/**
	 *
	 */
	void
	event_connected();

	/**
	 *
	 */
	void
	event_disconnected();

	/**
	 *
	 */
	void
	event_hello_rcvd();

	/**
	 *
	 */
	void
	event_hello_expired();

	/**
	 *
	 */
	void
	event_echo_rcvd();

	/**
	 *
	 */
	void
	event_echo_expired();

	/**
	 *
	 */
	void
	action_send_hello_message();

	/**
	 *
	 */
	void
	action_disconnect();

	/**
	 *
	 */
	void
	action_send_echo_request();

private:

	/**
	 *
	 */
	void
	hello_rcvd(
			cofmsg *msg);

	/**
	 *
	 */
	void
	echo_request_rcvd(
			cofmsg *msg);

	/**
	 *
	 */
	void
	echo_reply_rcvd(
			cofmsg *msg);

	/**
	 *
	 */
	void
	error_rcvd(
			cofmsg *msg);

public:

	friend std::ostream&
	operator<< (std::ostream& os, crofconn const& conn) {
		os << indent(0) << "<crofconn >" << std::endl;
		return os;
	};
};

}; /* namespace openflow */
}; /* namespace rofl */

#endif /* CROFCHAN_H_ */