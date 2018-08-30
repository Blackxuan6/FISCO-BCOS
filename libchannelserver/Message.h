/*
 * Message.h
 *
 *  Created on: 2018年8月14日
 *      Author: monan
 */

#pragma once

#include <string>
#include <thread>
#include <queue>
#include <memory>
#include <boost/lexical_cast.hpp>
#include <libdevcore/FixedHash.h>
#include <libdevcore/Common.h>
#include <libdevcore/easylog.h>
#include "ChannelException.h"

namespace dev {

namespace channel {

class Message: public std::enable_shared_from_this<Message> {
public:
	typedef std::shared_ptr<Message> Ptr;

	Message() {
		_data = std::make_shared<bytes>();
	}
	virtual ~Message() {};

	virtual void encode(bytes &buffer) = 0;

	virtual ssize_t decode(const byte* buffer, size_t size) = 0;

	virtual uint32_t length() { return _length; }

	virtual uint16_t type() { return _type; }
	virtual void setType(uint16_t type) { _type = type; }

	virtual std::string seq() { return _seq; }
	virtual void setSeq(std::string seq) { _seq = seq; }

	virtual int result() { return _result; }
	virtual void setResult(int result) { _result = result; }

	virtual byte* data() { return _data->data(); }
	virtual size_t dataSize() { return _data->size(); }

	virtual void setData(const byte *p, size_t size) { _data->assign(p, p + size); }

	virtual void clearData() { _data->clear(); }

protected:
	uint32_t _length = 0;
	uint16_t _type = 0;
	std::string _seq = std::string(32, '0');
	int _result = 0;

	std::shared_ptr<bytes> _data;
};

class MessageFactory: public std::enable_shared_from_this<MessageFactory> {
public:
	typedef std::shared_ptr<MessageFactory> Ptr;

	virtual ~MessageFactory() {};
	virtual Message::Ptr buildMessage() = 0;
};

}

}
