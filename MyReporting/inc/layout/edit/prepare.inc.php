<?php

	$DIS_Application = "Edit";	

	include INC_DIR."layout_helper.inc";
	include LIB_DIR."date.inc";


	$year = value_from_POST ('year', strftime ("%Y"));
	$week = value_from_POST ('week', currentWeekNumber ());

	if (isset($GLOBALS['username'])) { $username = $GLOBALS['username']; }
	if (!isset ($username)) {
		$username = value_from_POST_GET ('username');
	}
	if (strlen ($username) == 0) { unset ($username); }

	$data_filled = ((isset($_POST['year']) && isset($_POST['week'])) || ((isset($_GET['year']) && isset($_GET['week'])))); // Except Username, this is a special case
	$go_for_editing = isset ($username) && $data_filled;

	if ($go_for_editing) {
		include INC_DIR."reporting_lib.inc";
		$DIS_EditUsername = $username;
		$DIS_EditWeek = "$week";
		$DIS_EditYear = "$year";
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
					$DIS_EditReportingText .= "<H2>$val</H2>\n";
					$selected_cat = $GLOBALS['reporting']["categories"][$val];
					reset ($selected_cat);
					next ($selected_cat);
					$DIS_EditReportingText .= "<UL>\n";
					while (list ($skey, $sval) = each ($selected_cat)) {
						$DIS_EditReportingText .= "    <H3>$sval</H3>\n";
						$DIS_EditReportingText .= "    <UL>\n";
						$DIS_EditReportingText .= "       <LI>...</LI>\n";
						$DIS_EditReportingText .= "    </UL>\n";
					}
					$DIS_EditReportingText .= "</UL>\n\n";
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

		// Year
		$DIS_PostYear_HTML_3_RADIO = number_HTML_3_RADIO ('year', $year);

		// Week
		$DIS_PostWeek_HTML_3_RADIO = number_HTML_3_RADIO ('week', $week);

		$today = currentDay ();
		$firstday_of_week = firstDayOfCurrentWeek ();
		$lastday_of_week = lastDayOfCurrentWeek ();
		$DIS_PostCurrent_Week_text = "<STRONG>".currentWeekNumber()."</STRONG> [".$firstday_of_week." - ".$lastday_of_week."]";

		$DIS_PostWeek_HTML_RADIO_SELECT = week_HTML_RADIO_SELECT ($year, $week, 'week', 'postreportingForm');

		$categories = $GLOBALS['reporting']["categories"];
		$DIS_PostCategories_HTML_CHECK_LIST = categories_HTML_CHECK_LIST ($categories, 'cat_sel[]');


	}

?>
