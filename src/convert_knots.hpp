double knots_to_miles_per_minute(int knot)
{
	const double nautical_mile = 6076.0;
	const double mile = 5280.0;
	const double hour = 60;

	double knot_calculation = knot * nautical_mile;
	double knot_to_mile = knot_calculation / mile;
	double knot_to_mpm = knot_to_mile / hour;

	return knot_to_mpm;
}
