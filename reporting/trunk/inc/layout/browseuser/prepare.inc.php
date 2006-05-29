<?php

	require INC_DIR."reporting_lib.inc";
	require LIB_DIR."date.inc";
	include INC_DIR."layout_helper.inc";


	$current_year = currentYear ();
	// Get value from _POST or _GET
	$selected_user = value_from_POST_GET ('selected_user');
	$selected_year = value_from_POST_GET ('selected_year', $current_year);

	// Assign value for Display
	$DIS_Application = "Browse User Reports";

	$DIS_ListYears = array ();

	$reporting_dirs = listOfKnownYear ();
	$listUserReports = array ();

	$weeks_range = range (1,52);
	while (list ($k_week, $v) = each ($weeks_range)) {
		if (strlen ($k_week) <2) { $k_week = '0' . $k_week; }
		if (userReportExists($selected_user, $selected_year, $k_week)) {
			$ufn = userFilename ($selected_user, $selected_year, $k_week);
			$listUserReports[$k_week] = ContentOfFile ($ufn);
		}
	}
	krsort ($listUserReports);

	$DIS_AllUsers = active_users() + inactive_users();
	@$DIS_PostUsername_HTML_SELECT = userList_HTML_SELECT ('selected_user', $DIS_AllUsers, 'Select username', $selected_user);


?>
