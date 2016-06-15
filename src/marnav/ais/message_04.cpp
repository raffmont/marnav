#include "message_04.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{
message_04::message_04()
	: message_04(ID)
{
}

message_04::message_04(message_id id)
	: message(id)
{
}

std::unique_ptr<message> message_04::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_04::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_04>();
	message_04 & msg = static_cast<message_04 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_04::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, year);
	get(bits, month);
	get(bits, day);
	get(bits, hour);
	get(bits, minute);
	get(bits, second);
	get(bits, position_accuracy);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);
	get(bits, epfd_fix);
	get(bits, raim);
	get(bits, radio_status);
}

raw message_04::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, year);
	set(bits, month);
	set(bits, day);
	set(bits, hour);
	set(bits, minute);
	set(bits, second);
	set(bits, position_accuracy);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);
	set(bits, epfd_fix);
	set(bits, raim);
	set(bits, radio_status);

	return bits;
}

geo::longitude message_04::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_04::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_04::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_04::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}
}
}
