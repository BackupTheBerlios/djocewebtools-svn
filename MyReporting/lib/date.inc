<?php

if (!defined ("__LIB_DATE_INC__")) {
define ("__LIB_DATE_INC__", True);

Function firstDayOfWeek ($weeknumber, $year) {
	$tmp = mktime (0,0,0, 01, 01, $year);
	$wday = strftime ("%w", $tmp);
	if ($wday != 1) {
	  // Monday = 1
	  $tmp = mktime (0,0,0, 01, 01 - ($wday - 1), $year);
	}
	$z_year = strftime ("%Y", $tmp);
	$z_month= strftime ("%m", $tmp);
	$z_day= strftime ("%d", $tmp);
	$result = mktime (0,0,0, $z_month, $z_day + 7 * ($weeknumber - 1), $z_year);
	return $result;
}

Function lastDayOfWeek ($weeknumber, $year) {
	$tmp = firstDayOfWeek ($weeknumber, $year);
	$day = strftime ("%d", $tmp);
	$month = strftime ("%m", $tmp);
	return mktime (0,0,0,$month, $day + 6, $year);
}

Function firstDayOfWeekOn ($time) {
	$month = strftime ("%m", $time);
	$day = strftime ("%d", $time);
	$year = strftime ("%Y", $time);
	$wday = strftime ("%u", $time);
	return strftime ("%B %d, %Y",mktime (0,0,0,$month, $day-$wday + 1 + 1, $year));
}

Function lastDayOfWeekOn ($time) {
	$month = strftime ("%m", $time);
	$day = strftime ("%d", $time);
	$year = strftime ("%Y", $time);
	$wday = strftime ("%u", $time);
	return strftime ("%B %d, %Y",mktime (0,0,0,$month,$day+7-$wday + 1, $year));
}

Function firstWeekNumberOfYear ($year) {
	return weekNumberFor (mktime(0,0,0, 01, 01, $year));
}
Function lastWeekNumberOfYear ($year) {
	return weekNumberFor (mktime(0,0,0, 12, 31, $year));
}

Function weekNumberFor ($time) {
        return 1 + strftime ("%W", $time);
}

Function currentDay () {
	return getdate ();
}

Function currentWeekNumber () {
	return weekNumberFor (time ());
}

Function currentYear () {
	return strftime ("%Y");
}

Function firstDayOfCurrentWeek () {
	return firstDayOfWeekOn (time());
}

Function lastDayOfCurrentWeek () {
	return lastDayOfWeekOn (time());
}

}

?>
