<?php

	$DIS_Application = "Administration";

	$year = value_from_POST_GET ('year', strftime("%Y"));
	$week = value_from_POST_GET ('week');
	$weeks = value_from_POST_GET ('weeks');


	// Administration
	$admin = value_from_POST_GET('admin');
	$is_admin = isset ($admin) && isValidAdminPassword($admin);

	if ($is_admin) {
		require INC_DIR."reporting_lib.inc";

		$today_week = currentWeekNumber (); 
		$today_year = currentYear ();

		$DIS_CurrentWeek = $today_week;
		$DIS_Year = $year;

		if (!isset($task) && isset ($_POST['task'])) { $task = $_POST['task']; }
		$task_nothing = "nothing";
		$task_refresh = "refresh";
		$task_delete = "delete";
		$task_switch_lock = "switch-lock";
		$task_reportinglistcreation = "CreateReportingList";
		$task_send_email = "SendEmail";
		$task_send_reminder = "SendReminder";

		if (!isset($task)) { $task = $task_nothing; }

		switch ($task) {
			case $task_send_email:
				$cmd = sendReportsMailScript(). " " . $weeks[0] . " new ";
				$DIS_AdminMessage = "Command: $cmd<br/>\n";
				$DIS_AdminMessage .= "<hr>";
				$DIS_AdminMessage .= "<pre>";

				ob_start();
				$result = system ($cmd);
				$DIS_AdminMessage .= ob_get_contents();
				ob_end_clean();
				
				$DIS_AdminMessage .= "</pre>";
				break;
			case $task_send_reminder:
				$cmd = sendReportsMailScript(). " " . $weeks[0] . " remind ";
				$DIS_AdminMessage = "Command: $cmd<br/>\n";
				$DIS_AdminMessage .= "<hr>";
				$DIS_AdminMessage .= "<pre>";

				ob_start();
				$result = system ($cmd);
				$DIS_AdminMessage .= ob_get_contents();
				ob_end_clean();
				
				$DIS_AdminMessage .= "</pre>";
				break;
			case $task_switch_lock:
				$DIS_AdminMessage = "Switch Locks<br/>\n";
				while (list ($key, $val) = each ($weeks)) {
					$week = $val;
					if (isLocked ($year, $week)) {
						$DIS_AdminMessage .= "Task [$task]: UnLock of Reporting $week of $year ...<br/>\n";

						ob_start();
						unLockWeekFilesFor ($year, $week) ;
						$DIS_AdminMessage .= ob_get_contents();
						ob_end_clean();

						$DIS_AdminMessage .= "File for week $week of the year $year unLocked<br/>\n";
					} else {
						$DIS_AdminMessage .= "Task [$task]: lock of Reporting $week of $year ...<br/>\n";

						ob_start();
						lockWeekFilesFor ($year, $week) ;
						$DIS_AdminMessage .= ob_get_contents();
						ob_end_clean();

						$DIS_AdminMessage .= "File for week $week of the year $year locked<br/>\n";
					}
				}
				break;
			case $task_refresh:
				$DIS_AdminMessage = "Refreshing<br/>\n";
				while (list ($key, $val) = each ($weeks)) {
					$week = $val;
					$DIS_AdminMessage .= "Task [$task]: creation of Reporting $week of $year ...<br/>\n";

					ob_start();
					makeReportingWeekFileFor ($year, $week) ;
					$DIS_AdminMessage .= ob_get_contents();
					ob_end_clean();

					$urlname = weekUrl ($year, $week);
					$fname = weekUrl ($year, $week);
					$DIS_AdminMessage .= "<a href='$urlname'>$urlname refreshed</a><br/>\n";
				}
				break;
			case $task_reportinglistcreation:
				ob_start();
				createReportingList () ;
				$DIS_AdminMessage .= ob_get_contents();
				ob_end_clean();
				break;
			case $task_delete:
				$DIS_AdminMessage = "Removing ...<br/>\n";
				while (list ($key, $val) = each ($weeks)) {
					$week = $val;
					ob_start();
					removeReportingWeekFileFor ($year, $week) ;
					$DIS_AdminMessage .= ob_get_contents();
					ob_end_clean();
					$fname = weekFilename ($year, $week);
					if (!file_exists ($fname)) {
						$DIS_AdminMessage .= "File [$fname] removed\n";
					} else {
						$DIS_AdminMessage .= "File [$fname] not removed: ERROR\n";
					}
				}
				break;
			case $task_nothing:
				$DIS_AdminMessage = "Be careful with what you do ...<br/>\n";
				break;
			default:
				$DIS_AdminMessage = "Task [$task] not yet implemented ...<br/>\n";
		}

		$DIS_Weeks = array ();
		$weeks = listOfWeekFilesForYearByWeekNumber ($year);
		while (list($k_week,$v_file) = each ($weeks)) {
			$TMP_Week = array ();
			$TMP_Week['week'] = $k_week;
			if (! is_writeable ($v_file)) {
				$TMP_Week['status'] = "Locked";
			} else {
				$TMP_Week['status'] = "";
			}
			$DIS_Weeks[$k_week] = $TMP_Week;
		}

		$DIS_Years = listOfKnownYear ();
	}
	
?>
