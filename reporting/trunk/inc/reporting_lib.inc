<?php
if (!defined ("__REPORTING_LIB_INC__")) {
define ("__REPORTING_LIB_INC__", True);

//require "conf/config.inc";
require LIB_DIR."file.inc";
require LIB_DIR."date.inc";

Function myreporting_url () {
	return MyReportingUrl();
}
Function myreporting_edit_url ($user, $year, $week) {
	$result = myreporting_url();
	$result .= "/edit.php";
	$result .= "?username=$user";
	$result .= "&year=$year";
	$result .= "&week=$week";
	return $result;
}

Function createReportingList () {
	global $reporting_list_filename;
	global $reporting_list_url;
	$date = "(".strftime ("%d/%m/%Y %H:%M").")";
	$html = "<H1>Complete list of Reports $date</H1>\n";
	$years = listOfKnownYear ();
	while (list ($y_key, $y_val) = each ($years)) {
		$html .= "<strong>$y_key</strong><BR><UL>\n";
		$weeks = listOfWeekFilesForYearByWeekNumber ($y_key);
		while (list ($w_key, $w_val) = each ($weeks)) {
			$url = "../../" . $w_val;
			$html .= "<LI><A HREF=\"$url\">Week $w_key</A></LI>\n";
		}
		$html .= "</UL>\n";
	}
	SaveTextIntoFile ($html, $reporting_list_filename);
	echo "(*) List created : <A HREF=\"$reporting_list_url\">$reporting_list_url</A><br>\n";
}

Function listOfKnownYear () {
	$result = array ();
	if ($dir = @opendir (REPORT_DIR)) {
		while ($file = readdir ($dir)) {
			//if ($file != '.' && $file != '..') {
			if (eregi ("^[0-9]+$", $file)) {
				$result [$file] = REPORT_URL.$file;
			}
		}
	}
	@closedir ($dir);

	arsort ($result);
	reset ($result);
	return $result;
}

Function removeReportingWeekFileFor ($year, $week) {
	RemoveFile (weekFilename ($year, $week));
}

Function isLocked ($year, $week) {
	$week_filename = weekFilename ($year, $week);
	if (file_exists ($week_filename)) {
		return !is_writeable ($week_filename);
	} else {
		return False;
	}
}

Function unLockWeekFilesFor ($year, $week) {
	global $reporting;
	$dirname = REPORT_DIR.$year;
	$user_reports_to_use = listOfUserFilesInDirForWeekByLogin ($dirname, $week);
	$week_filename = weekFilename ($year, $week);

	echo "<HR>\n";
	echo "UnLocking ".$week_filename." ...";
	chmod ($week_filename, 0666);
	echo " done<BR>\n";
	while (list ($key, $val) = each ($user_reports_to_use)) {
		echo "UnLocking user file [".$val."] ...";
		chmod ($val, 0666);
		echo " done<BR>\n";
	}

}
Function lockWeekFilesFor ($year, $week) {
	global $reporting;
	$dirname = REPORT_DIR.$year;
	$user_reports_to_use = listOfUserFilesInDirForWeekByLogin ($dirname, $week);
	$week_filename = weekFilename ($year, $week);

	echo "<HR>\n";
	echo "Locking ".$week_filename." ...";
	chmod ($week_filename, 0444);
	echo " done<BR>\n";
	while (list ($key, $val) = each ($user_reports_to_use)) {
		echo "Locking user file [".$val."] ...";
		chmod ($val, 0444);
		echo " done<BR>\n";
	}

}

Function makeReportingWeekFileFor ($year, $week, $include_missing_reporter=True) {
	global $stylesheet_viewer_src;
	global $reporting;

	require_once SMARTY_DIR.'Smarty.class.php';

	$dirname = REPORT_DIR.$year;
	$week_filename = weekFilename ($year, $week);
	if (isLocked ($year, $week)) {
		echo "Sorry but the reports for the week $week of year $year is LOCKED\n";
	} else {

		$missing_log = "Missing reports from :<ul>";
		$reporter_log = "Using reports from :<ul>";

		$previous_week_filename = weekRelativePreviousUrl ($year, $week);
		$next_week_filename = weekRelativeNextUrl ($year, $week);
		$user_reports_to_use = listOfUserFilesInDirForWeekByLogin ($dirname, $week);
		reset ($user_reports_to_use);
		$DIS_Teams = array ();
		while (list ($k_login, $v_file) = each ($user_reports_to_use)) {
			$current_user = $reporting["users"][$k_login];
			$reporter_log .= "<li>".$current_user->name."</li>\n";

			$DIS_User = array (
					"login" => $k_login,
					"name" => $current_user->name,
					"team" => $current_user->team,
					"homepage" => $current_user->homepage,
					"state" => $current_user->state,
					"week_filename" => $v_file,
					"week_url" => $v_file
				);
			$team = $current_user->team;
			if (!isset ($DIS_Teams[$team])) {
				$TMP_Teams = array ();
			} else {
				$TMP_Teams = $DIS_Teams[$team];
			}
			$TMP_Teams[$k_login] = $DIS_User;
			$DIS_Teams[$team] = $TMP_Teams;
		}

		$missing_users = missing_reporters ($user_reports_to_use);
		ksort ($DIS_Teams);
		reset ($missing_users);
		ksort ($missing_users);
		$TMP_missing = array ();
		while (list ($k_login, $val) = each ($missing_users)) {
			$current_user = $reporting["users"][$k_login];

			$missing_log .= "<li>".$current_user->name."</li>\n";
			$DIS_User = array (
					"login" => $k_login,
					"name" => $current_user->name,
					"team" => $current_user->team,
					"homepage" => $current_user->homepage,
					"state" => $current_user->state
				);
			$TMP_missing[$k_login] = $DIS_User;
		}
		$DIS_Teams['Missing'] = $TMP_missing;

		//asort ($DIS_Teams);

		// Display .. output reports
		$report_output = "";

		$smarty = new Smarty;
		$smarty->template_dir = 'tpl'. DIRECTORY_SEPARATOR;
		$smarty->compile_dir = TMP_DIR . '_compiled' . DIRECTORY_SEPARATOR;

		$smarty->assign("VAR_REPORTING_CSS_STYLE","../../../$stylesheet_viewer_src");
		$smarty->assign("VAR_YEAR","$year");
		$smarty->assign("VAR_WEEK","$week");
		$smarty->assign("VAR_WEEK_FILE_PREVIOUS", "$previous_week_filename");
		$smarty->assign("VAR_WEEK_FILE_NEXT", "$next_week_filename");
		$smarty->assign("VAR_START_DATE", strftime ("%d/%m/%Y", firstDayOfWeek ($week, $year)));
		$smarty->assign("VAR_END_DATE", strftime ("%d/%m/%Y", lastDayOfWeek ($week, $year)));
		$smarty->assign("VAR_CREATION_DATE_TIME", strftime ("%d/%m/%Y %H:%M"));
		$smarty->assign("VAR_REPORTING_URL", MyReportingUrl());

		$smarty->assign("ListTeams", $DIS_Teams);

		$log = "Creating ".$week_filename." ... <BR><BR>";
		$log .= $reporter_log;
		$log .= "</ul>\n";

		$log .= $missing_log;
		$log .= "</ul>\n";
		echo $log;

		$report_output = $smarty->fetch ("generate/reporting_week.tpl");
		SaveTextIntoFile ($report_output, $week_filename);
	}
}

Function listDirFilter ($dir, $filter) {
	#echo "listDirFilter [$dir] filter[$filter] <BR>\n";
	$dirhdl = opendir ($dir);
	if ($dirhdl) {
		$result = array ();
		while ($file = readdir ($dirhdl)) {
			if (eregi ($filter, $file)) {
				$result[$file] = $dir."/".$file;
			}
		}
	}
	return $result;
}

Function listOfWeekFilesForYearByWeekNumber ($year) {
	$dirname = REPORT_DIR.$year;
	$filter = "week-.*\..*";
	$ls_result = listDirFilter ($dirname, $filter);
	$weeks= array ();
	while (list ($key, $val) = each ($ls_result)) {
		$pos = strrpos ($val, '-');
		$key = substr ($val, $pos + 1);
		$pos = strrpos ($key, '.');
		$key = substr ($key, 0, $pos);
		if (strlen($val) > 0) { 
			$weeks[$key] = $val;
		}
	}
	arsort ($weeks);
	reset ($weeks);
	return $weeks;
}

Function listOfWeekFilesForYearAndUserByWeekNumber ($year, $user){
	$dirname = REPORT_DIR.$year;
	$filter = $user.'_'.'.*\..*';
	$ls_result = listDirFilter ($dirname, $filter);
	$weeks= array ();
	while (list ($key, $val) = each ($ls_result)) {
		$pos = strrpos ($val, '_');
		$key = substr ($val, $pos + 1);
		$pos = strrpos ($key, '.');
		$key = substr ($key, 0, $pos);
		if (strlen($val) > 0) { 
			$weeks[$key] = $val;
		}
	}
	arsort ($weeks);
	reset ($weeks);
	return $weeks;

}

Function listOfWeekFilesInDirByWeekNumber ($dirname) {
	$filter = "week-.*\..*";
	$ls_result = listDirFilter ($dirname, $filter);
	$weeks= array ();
	while (list ($key, $val) = each ($ls_result)) {
		$pos = strrpos ($val, '-');
		$key = substr ($val, $pos + 1);
		$pos = strrpos ($key, '.');
		$key = substr ($key, 0, $pos);
		if ($val != "") { 
			if (!isset($weeks[$key])) { $weeks[$key] = ""; };
			$weeks[$key] .= $val;
		}
	}
	arsort ($weeks);
	reset ($weeks);
	return $weeks;
}

Function listOfUserFilesInDirForWeekByLogin ($dirname, $week) {
	if (strlen ($week) < 2) { $week = '0' . $week; }
	$filter = ".+_".$week."\..*";
	$ls_result = listDirFilter ($dirname, $filter);
	$users= array ();
	while (list ($key, $val) = each ($ls_result)) {
		$pos = strrpos ($val, '/');
		$key = substr ($val, $pos + 1);
		$pos = strrpos ($key, '_');
		$key = substr ($key, 0, $pos);
		if ($val != "") { 
			if (!isset ($users[$key])) { $users[$key] = ""; }
			$users[$key] .= $val;
		}
	}
	asort ($users);
	reset ($users);
	return $users;
}

Function userReportExists ($user, $year, $week) {
	return file_exists (userFilename($user, $year, $week));
}

Function userReportContent ($user, $year, $week) {
	return ContentOfFile (userFilename ($user, $year, $week));
}
Function postUserReport ($user, $year, $week, $text) {
	$target_file = userFilename ($user, $year, $week);
	SaveTextIntoFile ($text, $target_file);
	makeReportingWeekFileFor ($year, $week) ;
}

Function userFilename ($user, $year, $week) {
	if (strlen ($week) <2) { $week = '0' . $week; }
	return REPORT_DIR.DIRECTORY_SEPARATOR.$year.DIRECTORY_SEPARATOR.$user."_".$week.".html";
}


Function yearDirname ($year) {
	return REPORT_DIR.$year;
}

Function weekFileToUrl ($s) {
	return ereg_replace(DIRECTORY_SEPARATOR, '/',$s);
}	
Function weekFilename ($year, $week) {
	if (strlen ($week) <2) { $week = '0' . $week; }
	return yearDirname ($year).DIRECTORY_SEPARATOR."week-".$week.".html";
}

Function yearUrl ($year) {
	return REPORT_URL.$year;
}
Function weekUrl ($year, $week) {
	if (strlen ($week) <2) { $week = '0' . $week; }
	return yearUrl ($year)."/week-".$week.".html";
}

Function weekRelativePreviousUrl ($year, $week) {
	if (strlen ($week) <2) { $week = '0' . $week; }
	switch ($week) {
		case 1:
			return "../".($year - 1)."/week-52.html";
			break;
		default:
			$week = $week - 1;
			if (strlen ($week) <2) { $week = '0' . $week; }
			return "week-".$week.".html";
			break;
	}
}

Function weekRelativeNextUrl ($year, $week) {
	if (strlen ($week) <2) { $week = '0' . $week; }
	switch ($week) {
		case 52:
			return "../".($year + 1)."/week-01.html";
			break;
		default:
			$week = $week + 1;
			if (strlen ($week) <2) { $week = '0' . $week; }
			return "week-".$week.".html";
			break;
	}
}

Function dataDirForYear ($year) {
	return REPORT_DIR . $year;
}

Function createDirIfNotExists ($year) {
	$dirname = dataDirForYear ($year);
	if (! file_exists ($dirname)) {
		echo "Creating $dirname...";
		mkdir ($dirname, 0755);
		echo " done .<BR>\n";
	}
	else { 
		@chmod ($dirname, 0777);
	}
}

Function active_users () {
	global $reporting;
	$users = $reporting['users'];
	$result = array ();
	while (list ($k_name, $v_user) = each ($users)) {
		if ($v_user->state) {
			$result[$k_name]=$v_user;
		}
	}
	return $result;
}
Function inactive_users () {
	global $reporting;
	$users = $reporting['users'];
	$result = array ();
	while (list ($k_name, $v_user) = each ($users)) {
		if (!($v_user->state)) {
			$result[$k_name]=$v_user;
		}
	}
	return $result;
}
Function missing_reporters ($good_reporters) {
	$full_list = active_users ();
	$result = array ();
	while (list ($k_name, $v_user) = each ($full_list)) {
		if (!isset ($good_reporters[$k_name])) {
			$result[$k_name] = $v_user;
		}
	}
	return $result;
}

}

?>
