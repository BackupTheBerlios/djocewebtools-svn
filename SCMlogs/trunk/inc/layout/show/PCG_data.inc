<?php

	require "conf/config.inc";
	include "lib/file.inc";
	include "inc/query.inc";

	@$commitsmonthfiles = $_POST['commitsmonthfiles'];
	if (isset ($commitsmonthfiles)) { 
		$commitsfiles = array (); 
		while (list ($y, $v_yfiles) = each ($commitsmonthfiles)) {
			while (list ($m, $v_mfiles) = each ($v_yfiles)) {
				while (list ($d, $v_file) = each ($v_mfiles)) {
					$commitsfiles[] = $v_file;
				}
			}
		}
	}
//	@$commitsfiles = $_POST['commitsfiles'];

	$DIS_GET_SelectedYear = "";
	if (isset ($_POST['selected_years'])) {
		$selected_years = $_POST['selected_years'];
		while (list ($k, $y) = each ($selected_years)) {
			$DIS_GET_SelectedYear .= "$y:";
		}
	}

	if (!isset ($commitsfiles)) { $commitsfiles = array (); }
	if (isset ($_GET['key'])) { $commitsfiles[] = $_GET['key']; };

	$user = $SCMUSER;
	$DIS_Application = "show";

	$DIS_Command = "cmd";
	
	$DIS_Result = "Result";

	if (count ($commitsfiles) > 0) {
		@$operation = $_POST['show'];
		if (!isset ($operation)) { $operation = 'ShowLogs'; }

		$DIS_Parameters = "Login used = $SCMUSER <BR>";

		@$filter = $_POST['filter'];
		if (!isset ($filter) or (strlen ($filter) == 0)) { 
			$filter = 'profil'; 
		} else {
			$DIS_Parameters .= "Filter used = $filter <BR>";
			if ($filter == 'text') {
				@$filter_text = $_POST['textfilters'];
				$filter_text = cleanedTextModule ($filter_text);

				$filter_file_tempo_name = tempnam ($SCMLOGS['tmpdir'], "FILTER_TEMPO_");
				$filter_file_tempo = fopen ($filter_file_tempo_name, "w");
				fwrite ($filter_file_tempo, $filter_text);
				fclose ($filter_file_tempo);

				$DIS_Parameters .= "Filter text = $filter_text <BR>";
			}
		}
		@$format = $_POST['format'];
		if (!isset ($format) or (strlen ($format) == 0)) { 
			$format = 'html'; 
		} else {
			$DIS_Parameters .= "Formating used = $format <BR>";
		}
		@$only_user = $_POST['only_user'];
		if (!isset ($only_user) or (strlen ($only_user) == 0)) { 
			$only_user = ''; 
		} else {
			$DIS_Parameters .= "Only commits from user = $only_user <BR>";
		}
		@$only_tag = $_POST['only_tag'];
		if (!isset ($only_tag) or (strlen ($only_tag) == 0)) { 
			$only_tag = ''; 
		} else {
			$DIS_Parameters .= "Only commits about TAG = $only_tag <BR>";
		}

		switch ($operation) {
			case 'EmailLogs':
				$DIS_Message = "Email $user all the logs <BR>(in the selected files)<BR>\n";
				$processing_fct = "EmailLogsAction";
				break;
			case 'ShowRawLogs':
				$DIS_Message = "Show the RAW logs file (selected files)<BR>\n";
				$processing_fct = "ShowRawLogsAction";
				break;
			case 'EmailMyLogs':
				$only_user = $user;
				$DIS_Message = "Email $user all the logs (in the selected files) \n";
				$DIS_Message .= " from <STRONG>$user</STRONG><BR>";
				$processing_fct = "EmailMyLogsAction";
				break;
			case 'ShowMyLogs':
				$only_user = $user;
				$DIS_Message = "Show $user all the logs (in the selected files) \n";
				$DIS_Message .= " from <STRONG>$user</STRONG><BR>\n";
				$processing_fct = "ShowMyLogsAction";
				break;
			case 'EmailOnlyLogsFor':
				$DIS_Message = "Email $user all the logs (in the selected files)\n";
				$DIS_Message .= " from user : <STRONG>$only_user</STRONG>\n";
				$DIS_Message .= " with tag  : <STRONG>$only_tag</STRONG><BR>\n";
				$processing_fct = "EmailOnlyLogsForAction";
				break;
			case 'ShowOnlyLogsFor':
				$DIS_Message = "Show $user all the logs (in the selected files)\n";
				$DIS_Message .= " from user : <STRONG>$only_user</STRONG>\n";
				$DIS_Message .= " with tag&nbsp;  : <STRONG>$only_tag</STRONG><BR>\n";
				$processing_fct = "ShowOnlyLogsForAction";
				break;
			case 'ShowLogs':
			default:
				$DIS_Message = "Show $user all the logs (in the selected files)<BR>\n";
				$processing_fct = "ShowLogsAction";
				break;
		}

		$file_tempo_name = tempnam ($SCMLOGS['tmpdir'], "TEMPO_");
		$file_tempo = fopen ($file_tempo_name, "w");
		$DIS_Files ="";
		$repo = SCMLogs_repository();
		$logsdir = $repo->logsdir;
		while (list ($k, $v_file) = each ($commitsfiles)) {
			$DIS_Files .= "<li>$v_file";
			if (preg_match("/^([0-9][0-9][0-9][0-9])-([0-9][0-9])-([0-9][0-9])$/", $v_file, $matches)) {
				$v_file = $logsdir .'/'.$matches[1].'/'.$matches[2].'/'. $v_file;
			}
			if (preg_match("/^(".SCMLogs_CurrentCommitFile().")$/", $v_file, $matches)) {
				$v_file = $logsdir .'/'.$v_file;
			}

			//$DIS_Files .= " :: <em>$v_file</em>";
			$DIS_Files .= "</li>\n";
			fwrite ($file_tempo, ContentOfFile ($v_file));
		}
		fclose ($file_tempo);
		if ($processing_fct != '') {
			ob_start ();
			$DIS_Format = $format;

			if ($filter == 'text') {
				$param_filter = $filter_file_tempo_name;
			} else {
				$param_filter = $filter;
			}
			set_time_limit(150);
			$DIS_Command = $processing_fct ($file_tempo_name, $user, $param_filter, $only_user, $only_tag, $format);
			$DIS_Result = ob_get_contents();
			ob_end_clean();
		} else {
			$DIS_Format = '';
			$DIS_Command = "Not Yet Implemented";
		}
		if (isset ($filter_file_tempo_name)) {
			RemoveFile ($filter_file_tempo_name);
		}
		RemoveFile ($file_tempo_name);
	} else {
		$DIS_Format = '';
		$DIS_Message = "Please select at least one file !!!";
		$DIS_Parameters = "...";
		$DIS_Command = "...";
		$DIS_Files = "no file selected";
		$DIS_Result = "...";
	}


?>
