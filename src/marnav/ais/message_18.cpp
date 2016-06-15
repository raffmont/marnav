#include "message_18.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{
message_18::message_18()
	: message_18(ID)
{
}

message_18::message_18(message_id id)
	: message(id)
{
}

std::unique_ptr<message> message_18::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_18::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_18>();
	message_18 & msg = static_cast<message_18 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_18::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, sog);
	get(bits, position_accuracy);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);
	get(bits, cog);
	get(bits, hdg);
	get(bits, timestamp);
	get(bits, cs_unit);
	get(bits, display_flag);
	get(bits, dsc_flag);
	get(bits, band_flag);
	get(bits, message_22_flag);
	get(bits, assigned);
	get(bits, raim);
	get(bits, radio_status);
}

raw message_18::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, sog);
	set(bits, position_accuracy);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);
	set(bits, cog);
	set(bits, hdg);
	set(bits, timestamp);
	set(bits, cs_unit);
	set(bits, display_flag);
	set(bits, dsc_flag);
	set(bits, band_flag);
	set(bits, message_22_flag);
	set(bits, assigned);
	set(bits, raim);
	set(bits, radio_status);

	return bits;
}

geo::longitude message_18::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_18::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_18::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_18::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}
}
}
