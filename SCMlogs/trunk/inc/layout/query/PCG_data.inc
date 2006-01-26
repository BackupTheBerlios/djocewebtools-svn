<?php


	require "conf/config.inc";
	include "lib/file.inc";
	include "inc/query.inc";

	@$commitsfiles = $_POST['commitsfiles'];
	if (!isset ($commitsfiles)) { $commitsfiles = array (); }
	@$only_user = $_POST['only_user'];
	@$only_tag = $_POST['only_tag'];

	if (isset ($_POST['selected_years'])) {
		$selected_years = $_POST['selected_years'];
		if (!is_array ($selected_years)) {
			$selected_years = split (':', $selected_years);
		}
	}
	if (isset ($_GET['selected_years'])) {
		$selected_years = split (':', $_GET['selected_years']);
	}
	if (!isset ($selected_years)) { $selected_years = array (strftime ("%Y")); }

	$DIS_GET_SelectedYear = "";
	while (list ($k, $y) = each ($selected_years)) {
		if (strlen ($y) > 0) {
			$DIS_GET_SelectedYear .= "$y:";
		}
	}

	$DIS_Application = "query";


	// Commit files
	$DIS_CurrentCommitFile = SCMLogs_CurrentCommitFile();
	$DIS_CurrentCommitFileChecked = (in_array ($DIS_CurrentCommitFile, $commitsfiles));
	$DIS_OnlyUser = $only_user;
	$DIS_OnlyTag = $only_tag;

	$DIS_UserFilter = userModulesText ($SCMUSER);
	
	$DIS_CommitFiles = array (); // [years => [month => [key=>files]]]
	$repo = SCMLogs_repository();
	$list_years = listOfDir ($repo->logsdir);
	reset ($list_years);
	krsort ($list_years);
	while (list ($k_year, $v_year_dir) = each ($list_years)) {
		if (eregi("^[0-9]+$", $k_year)) {
			$TMP_months = array ();
			$list_months = listOfDir ($v_year_dir);
			arsort ($list_months);
			while (list ($k_month, $v_month_dir) = each ($list_months)) {
				$list_files = listOfFiles ($v_month_dir);
				if (count ($list_files) > 0) {
					$TMP_files = array ();
					reset ($list_files);
					arsort ($list_files);
					while (list ($k_file, $v_filename) = each ($list_files)) {
						if (in_array ($k_file, $commitsfiles)) {
							$TMP_files[$k_file] = True;
						} else {
							$TMP_files[$k_file] = False;
						}
					}
					$TMP_months[$k_month] = $TMP_files;
				}
			}
			$DIS_CommitFiles[$k_year] = $TMP_months;
		}
	}

?>
