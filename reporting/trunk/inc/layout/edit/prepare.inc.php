<?php

	$DIS_Application = "Edit";	

	include INC_DIR."layout_helper.inc";
	include LIB_DIR."date.inc";


	$year = value_from_POST_GET ('year', currentYear());
	$thisweek = value_from_POST_GET ('week', currentWeekNumber ());
	$week = value_from_POST_GET ('week'.$year, $thisweek);
//	echo "[Today=".currentDayToString()."][Y=" . currentYear() . "][W=" . currentWeekNumber() . "]<br/>"; 

	if (isset($GLOBALS['username'])) { $username = $GLOBALS['username']; }
	if (!isset ($username)) {
		$username = value_from_POST_GET ('username');
	}
	if (strlen ($username) == 0) { unset ($username); }

	$data_filled = false;
	if (isset($_POST['year'])) {
		$_y = $_POST['year'];
		$data_filled = isset($_POST['week'.$_y]) || isset($_POST['week']);
	} elseif (isset ($_GET['year'])) {
		$_y = $_GET['year'];
		$data_filled = isset($_GET['week'.$_y]) || isset($_GET['week']);
	}
	$go_for_editing = isset ($username) && $data_filled;

	if ($go_for_editing) {
		include INC_DIR."reporting_lib.inc";
		$DIS_EditUsername = $username;
		$DIS_EditWeek = "$week";
		$DIS_EditYear = "$year";

		$DIS_EditRelatedDate = "";
		$DIS_EditRelatedDate .= "Week $week : ";
		$DIS_EditRelatedDate .= strftime ("%b %d", firstDayOfWeek ($week, $year));
		$DIS_EditRelatedDate .= " -- ";
		$DIS_EditRelatedDate .= strftime ("%b %d", lastDayOfWeek ($week, $year));
		$DIS_EditRelatedDate .= " of " . $year;

		$DIS_EditReportingText = "";
		$already_exists = False;
		$is_read_only = False;

		$DIS_EditMessage = "";

		$target_file = userFilename ($username, $year, $week);
		if (file_exists ($target_file)) {
			$already_exists = True;
			$DIS_EditMessage .= "Your Report already exists !!!<BR>";
			$DIS_EditMessage .= "[ link to your report :: <A target=\"_blank\"
			HREF=\"".userFilename ($username, $year, $week)."\">Reporting $week of $year of $username</A><NR>";

			if (! is_writeable ($target_file)) {
				$is_read_only = True;
				$DIS_EditMessage .= "Your Report is readonly !!! <BR>";
				$DIS_EditMessage .= "&nbsp;&nbsp;&nbsp;&nbsp;=&gt; If you really want to modify it, ask the administrator to change access on it.<BR>";

			}
			$DIS_EditReportingText = ContentOfFile ($target_file);
		} else {
			if (isset ($_POST['cat_sel'])) {
				$cat_sel = $_POST['cat_sel'];
				$DIS_EditReportingText = "";
				while (list ($key, $val) = each ($cat_sel)) {
					$DIS_EditReportingText .= "<h2>$val</h2>\n";
					$selected_cat = $GLOBALS['reporting']["categories"][$val];
					reset ($selected_cat);
					next ($selected_cat);
					$DIS_EditReportingText .= "<ul>\n";
					if (count ($selected_cat) > 1) {
						while (list ($skey, $sval) = each ($selected_cat)) {
							$DIS_EditReportingText .= "    <h3>$sval</h3>\n";
							$DIS_EditReportingText .= "    <ul>\n";
							$DIS_EditReportingText .= "       <li>...</li>\n";
							$DIS_EditReportingText .= "    </ul>\n";
						}
					} else {
						$DIS_EditReportingText .= "<li>...</li>\n";
					}
					$DIS_EditReportingText .= "</ul>\n\n";
				}
			}
		}
	} else {
		// Checking for username //
		if ($data_filled && !isset ($username)) {
			$DIS_PostWarning = "You forgot to select your username, this is required";
		}
		$users = $GLOBALS['reporting']['users'];
		@$DIS_PostUsername_HTML_SELECT = userList_HTML_SELECT ('username', $users, 'Select your username', $username);

//		// Year
//		$DIS_PostYear_HTML_3_RADIO = number_HTML_3_RADIO ('year', $year);
//
//		// Week
//		$DIS_PostWeek_HTML_3_RADIO = number_HTML_3_RADIO ('week', $week);

		$today = currentDay ();
		$firstday_of_week = firstDayOfCurrentWeek ();
		$lastday_of_week = lastDayOfCurrentWeek ();
		$DIS_PostCurrent_Week_text = "week <strong>#".currentWeekNumber()."</strong> [".$firstday_of_week." - ".$lastday_of_week."]";

		//$DIS_PostWeek_HTML_RADIO_SELECT = week_HTML_RADIO_SELECT ($year, $week, 'week', 'postreportingForm');

		$DIS_PostYearWeek_HTML_RADIO_SELECT = year_week_HTML_RADIO_SELECT ($year, $week, 'year', 'week', 'postreportingForm');

		$categories = $GLOBALS['reporting']["categories"];
		$DIS_PostCategories_HTML_CHECK_LIST = categories_HTML_CHECK_LIST ($categories, 'cat_sel[]');


	}

?>
