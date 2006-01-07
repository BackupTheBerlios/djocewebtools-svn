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

Function firstDayOfWeekOn ($t) {
	$month = strftime ("%m", $t);
	$day = strftime ("%d", $t);
	$year = strftime ("%Y", $t);
	$wday = strftime ("%u", $t);
	return strftime ("%B %d, %Y",mktime (0,0,0,$month, $day-$wday + 1 + 1, $year));
}

Function lastDayOfWeekOn ($t) {
	$month = strftime ("%m", $t);
	$day = strftime ("%d", $t);
	$year = strftime ("%Y", $t);
	$wday = strftime ("%u", $t);
	return strftime ("%B %d, %Y",mktime (0,0,0,$month,$day+7-$wday + 1, $year));
}

Function firstWeekNumberOfYear ($year) {
	return weekNumberFor (mktime(0,0,0, 01, 01, $year));
}
Function lastWeekNumberOfYear ($year) {
	return weekNumberFor (mktime(0,0,0, 12, 31, $year));
}

Function weekNumberFor ($t) {
        return strftime ("%W", $t);
}

Function currentDay () {
	return getdate (currentTime());
}

Function currentWeekNumber () {
	$wn = weekNumberFor (currentTime ());
	if ($wn == 0) {
		return lastWeekNumberOfYear(realCurrentYear() - 1);
	} else {
		return $wn;
	}
}

Function currentTime() {
//	return mktime(12,0,0, 1, 1, 2006);
	return time();
}

Function currentYear () {
	$t = currentTime();
	$res = strftime ("%Y", $t);
	$wn = weekNumberFor($t);
	if ($wn == 0) {
		$res = $res - 1;
	}
	return $res;
}
Function realCurrentYear () {
	return strftime ("%Y", currentTime());
}

Function firstDayOfCurrentWeek () {
	return firstDayOfWeekOn (currentTime());
}

Function lastDayOfCurrentWeek () {
	return lastDayOfWeekOn (currentTime());
}

}

?>
