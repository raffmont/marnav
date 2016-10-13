#include "bod.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(bod)

constexpr const char * bod::TAG;

bod::bod()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bod::bod(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in bod"};

	read(*(first + 0), bearing_true);
	read(*(first + 1), type_true);
	read(*(first + 2), bearing_magn);
	read(*(first + 3), type_magn);
	read(*(first + 4), waypoint_to);
	read(*(first + 5), waypoint_from);
}

void bod::set_bearing_true(double t) noexcept
{
	bearing_true = t;
	type_true = reference::TRUE;
}

void bod::set_bearing_magn(double t) noexcept
{
	bearing_magn = t;
	type_magn = reference::MAGNETIC;
}

std::vector<std::string> bod::get_data() const
{
	return {to_string(bearing_true), to_string(type_true), to_string(bearing_magn),
		to_string(type_magn), to_string(waypoint_to), to_string(waypoint_from)};
}
}
}
