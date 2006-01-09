<?php

if (!defined ("__LIB_DATE_INC__")) {
define ("__LIB_DATE_INC__", True);

Function firstDayOfWeek ($weeknumber, $year) {
	$tmp = mktime (12,0,0, 02, 01 , $year);
	$wn = weekNumberFor ($tmp);
	$wndiff = $weeknumber - $wn;
	if ($wndiff > 0) {
		$tmp = strtotime("+". $wndiff . " week", $tmp);
	} elseif ($wndiff < 0) {
		$tmp = strtotime($wndiff . " week", $tmp);
	}

	$z_year = strftime ("%Y", $tmp);
	$z_month= strftime ("%m", $tmp);
	$z_day= strftime ("%d", $tmp);
	$wday = strftime ("%w", $tmp);
	if ($wday != 1) {
	  // Monday == 1
	  $tmp = mktime (12,0,0, $z_month, $z_day - ($wday - 1), $z_year);
	}
	return $tmp;
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
	$wn = weekNumberFor (mktime(12,0,0, 01, 01, $year));
//	print ("firstWeekNumberOfYear($year) = $wn <br/>");
	return $wn;
}
Function lastWeekNumberOfYear ($year) {
	$wn = weekNumberFor (mktime(12,0,0, 12, 31, $year));
	if ($wn < 50) { $wn = weekNumberFor (mktime(12,0,0, 12, 31 - 7, $year)); }
//	print ("lastWeekNumberOfYear($year) = $wn <br/>");
	return $wn;
}

Function weekNumberFor ($t) {
	return date ("W", $t);
}

Function currentTime() {
//	return mktime(12,0,0, 5, 15, 2009);
	return time();
}
Function currentYear () {
	return currentISOYear(currentTime());
}
Function currentISOYear ($t) {
	$res = date ("Y", $t);
	$ISOwn = date("W", $t);
	$wn = strftime("%W", $t);
//	print ("<br/>[[ISOwn=$ISOwn ~ wn=$wn]]<br/>");
	if ($ISOwn > 50 && $wn  < 5) {
		$res = $res - 1;
	} elseif ($ISOwn < 5 && $wn  > 50 ) {
		$res = $res + 1;
	}
	return $res;
}
Function currentDay () {
	return getdate (currentTime());
}
Function currentDayToString () {
	return strftime ("%Y/%m/%d",currentTime());
}
Function currentWeekNumber () {
	$wn = weekNumberFor (currentTime ());
	if ($wn == 0) {
		return lastWeekNumberOfYear(realCurrentYear() - 1);
	} else {
		return $wn;
	}
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
