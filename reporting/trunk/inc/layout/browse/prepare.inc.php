<?php

	require INC_DIR."reporting_lib.inc";
	require LIB_DIR."date.inc";

	// Get value from _POST or _GET
	$selected_year = value_from_POST_GET ('selected_year');

	// Assign value for Display
	$DIS_Application = "Browse Reports";

	$DIS_ListYears = array ();
		//  year => [year]
		//          [weeks] => [
		//							[week] => [file]
		//							          [first_day]
		//							          [last_day]
		//							          [last_modified]
		//							          [status]
		//							          [style]
		//							          [nota]
		//

	if (isset ($year)) {
		$reporting_dirs = array ($year => yearDirname ($year) );

	} else {
		$reporting_dirs = listOfKnownYear ();
	}

	$current_weeknumber = currentWeekNumber ();
	$current_year = currentYear ();

	while (list ($k_year, $v_dirpath) = each ($reporting_dirs)) {
		if (!isset ($selected_year)) {
			$selected_year = $k_year;
		}
		if ($k_year == $selected_year) {
			$TMP_Year = array ();
			$TMP_Year['year'] = $k_year;
			$week_files = listOfWeekFilesInDirByWeekNumber ($v_dirpath);
			if (count($week_files) > 0) {
				$TMP_Weeks = array ();
				while (list ($k_week, $v_file) = each ($week_files)) {
					$TMP_ThisWeek = array (); // Data
					
					$TMP_ThisWeek['file'] = $v_file;
					$TMP_ThisWeek['first_day'] = strftime ("%d %B", firstDayOfWeek ($k_week, $k_year));
					$TMP_ThisWeek['last_day'] = strftime ("%d %B", lastDayOfWeek ($k_week, $k_year));
					$TMP_ThisWeek['last_modified'] =  date ("m/d/Y H:i", filemtime ($v_file));

					if (!is_writeable ($v_file)) {
						$TMP_ThisWeek['status'] = "Locked";
					} else {
						$TMP_ThisWeek['status'] = "";
					}

					if (($k_week == $current_weeknumber) and ($k_year == $current_year)) {
						$TMP_ThisWeek['style'] = "bgcolor=#FFFF66; ";
						$TMP_ThisWeek['nota'] = "<A HREF='$v_file'>Current Week</A>";
					} else {
						$TMP_ThisWeek['style'] = "bgcolor=#FFFFCC; ";
						$TMP_ThisWeek['nota'] = "";
					}

					$TMP_Weeks[$k_week] = $TMP_ThisWeek; // Data
				}
				$TMP_Year['weeks'] = $TMP_Weeks;
			}
		} else {
			$TMP_Year = NULL;
		}
		$DIS_ListYears[$k_year] = $TMP_Year;
	}

	$DIS_AllUsers = active_users() + inactive_users();

?>
