#include "wnc.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(wnc)

constexpr const char * wnc::TAG;

wnc::wnc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

wnc::wnc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in wnc"};

	read(*(first + 0), distance_nm);
	read(*(first + 1), distance_nm_unit);
	read(*(first + 2), distance_km);
	read(*(first + 3), distance_km_unit);
	read(*(first + 4), waypoint_to);
	read(*(first + 5), waypoint_from);
}

void wnc::set_distance_nm(double t) noexcept
{
	distance_nm = t;
	distance_nm_unit = unit::distance::nm;
}

void wnc::set_distance_km(double t) noexcept
{
	distance_km = t;
	distance_km_unit = unit::distance::km;
}

std::vector<std::string> wnc::get_data() const
{
	return {to_string(distance_nm), to_string(distance_nm_unit), to_string(distance_km),
		to_string(distance_km_unit), to_string(waypoint_to), to_string(waypoint_from)};
}
}
}
