/*
 * ctransactions.h
 *
 *  Created on: 04.01.2014
 *      Author: andi
 */

#ifndef CTRANSACTIONS_H_
#define CTRANSACTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <inttypes.h>
#ifdef __cplusplus
}
#endif

#include <map>

#include "rofl/common/thread_helper.h"
#include "rofl/common/ciosrv.h"
#include "rofl/common/ctransaction.h"
#include "rofl/platform/unix/crandom.h"

namespace rofl {
namespace openflow {

class ctransactions;

class ctransactions_env {
public:
	virtual ~ctransactions_env() {};
	virtual void ta_expired(ctransactions& tas, ctransaction& ta) = 0;
};

class ctransactions :
		public std::list<ctransaction>,
		public rofl::ciosrv
{
	ctransactions_env			*env;
	uint32_t					nxid;			// next xid
	unsigned int				work_interval; 	// time interval for checking work-queue
	PthreadRwLock				queuelock;		// rwlock for work-queue

	enum ctransactions_timer_t {
		TIMER_WORK_ON_TA_QUEUE 	= 1,	// lookup all expired TAs in list
	};

public:

	/**
	 *
	 */
	ctransactions(ctransactions_env *env);

	/**
	 *
	 */
	virtual
	~ctransactions();

public:

	/**
	 *
	 */
	uint32_t
	add_ta(
			cclock const& delta = cclock(0, 0), uint8_t msg_type = 0, uint16_t msg_subtype = 0);

	/**
	 *
	 */
	void
	drop_ta(
			uint32_t xid);

	/**
	 *
	 */
	uint32_t
	get_async_xid() { return ++nxid; };

private:

	/**
	 *
	 */
	ctransactions(
			ctransactions const& tas) : env(0), nxid(0), work_interval(0) {};

	/**
	 *
	 */
	ctransactions& operator= (ctransactions const& tas) { return *this; };

private:

	/**
	 *
	 */
	virtual void
	handle_timeout(
			int opaque);

	/**
	 *
	 */
	void
	work_on_ta_queue();

public:

	friend std::ostream&
	operator<< (std::ostream& os, ctransactions const& tas) {
		os << indent(0) << "<transactions #ta:" << tas.size() << " >" << std::endl;
		indent i(2);
		for (std::list<ctransaction>::const_iterator
				it = tas.begin(); it != tas.end(); ++it) {
			os << (*it);
		}
		return os;
	};
};

}; // namespace openflow
}; // namespace rofl



#endif /* CTRANSACTIONS_H_ */