<?php
ini_set('magic_quotes_runtime', 0);
ini_set('magic_quotes_gpc', 0);
	include "../conf/config.inc";

	include INC_DIR."prepend.inc.php";
	include INC_DIR."reporting_lib.inc";

	$_POST = $HTTP_POST_VARS ;
	$_GET = $HTTP_GET_VARS ;
	$_COOKIE = $HTTP_COOKIE_VARS ;
	$_FILES = $HTTP_POST_FILES;
echo '<pre>';

	$operation = value_from_POST_GET ("op", 'none');
	switch ($operation) {
		case 'post':
			$w_overwrite = value_from_POST_GET ('overwrite');
			$w_login = value_from_POST_GET ('login');
			$w_week = value_from_POST_GET ('week');
			$w_year = value_from_POST_GET ('year');
			$w_text = value_from_POST_GET ('text');

			if (isset($w_overwrite) && $w_overwrite == 'true') {
				$is_overwriting = True;
			} else {
				$is_overwriting = False;
			}
			$report_exists = userReportExists ($w_login, $w_year, $w_week);
			if (!$report_exists || $is_overwriting) {
				$w_text = stripslashes ($w_text);
				postUserReport ($w_login, $w_year, $w_week, $w_text);
				if ($report_exists && $is_overwriting) {
					echo "MSG=report $w_login, $w_week, $w_year : overwrited\n";
				} else {
					echo "MSG=report $w_login, $w_week, $w_year : posted\n";
				}
			} elseif ($report_exists && !$is_overwriting) {
					echo "ERR=reportExists: for $w_login, $w_week, $w_year : not overwrited\n";
			}
			break;
		case 'years':
			echo "MSG=known years\n";
			$ys = listOfKnownYear ();
			foreach ($ys as $ky => $vy) {
				echo $ky ."\n";
			}
			break;
		case 'weeks':
			$w_year = value_from_POST_GET ('year');
			$w_login = value_from_POST_GET ('login');
			if (isset ($w_login)) {
				echo "MSG=reports from $w_login (year $w_year)\n";
				$ws =listOfWeekFilesForYearAndUserByWeekNumber ($w_year, $w_login);
			} else {
				echo "MSG=reports (year $w_year)\n";
				$ws = listOfWeekFilesForYearByWeekNumber ($w_year);
			}
			if (!empty($ws)) {
				foreach ($ws as $kw => $vw) {
					echo "$kw\n";
				}
			}
			break;
		case 'fetch':
			$w_login = value_from_POST_GET ('login');
			$w_week = value_from_POST_GET ('week');
			$w_year = value_from_POST_GET ('year');
			if (userReportExists ($w_login, $w_year, $w_week)) {
				echo "MSG=reports from $w_login (week $w_week of year $w_year)\n";
				echo userReportContent ($w_login, $w_year, $w_week);
			} else {
				echo "ERR=NotFound: report for $w_login, $w_week, $w_year.\n";
			}
			break;
		case 'none':
		default:
				echo "ERR=UnknownOperation: $operation\n";
			break;

	}
echo '</pre>';

?>
