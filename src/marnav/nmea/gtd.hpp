#ifndef __MARNAV__NMEA__GTD__HPP__
#define __MARNAV__NMEA__GTD__HPP__

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(gtd)

/// @brief GTD - Geographic Location in Time Differences
///
/// @code
///        1   2   3   4   5
///        |   |   |   |   |
/// $--GTD,x.x,x.x,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. time difference
/// 2. time difference
/// 3. time difference
/// 4. time difference
/// 5. time difference
///
class gtd : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(gtd)

public:
	constexpr static const sentence_id ID = sentence_id::GTD;
	constexpr static const char * TAG = "GTD";

	constexpr static const int max_time_diffs = 5;

	gtd();
	gtd(const gtd &) = default;
	gtd & operator=(const gtd &) = default;
	gtd(gtd &&) = default;
	gtd & operator=(gtd &&) = default;

protected:
	gtd(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	std::array<double, max_time_diffs> time_diffs;

	void check_index(int index) const;

public:
	double get_time_diff(int index) const;

	void set_time_diff(int index, double value);
};
}
}

#endif
