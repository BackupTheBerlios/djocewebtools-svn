<?php

	$DIS_Application = "Save";

	include INC_DIR."layout_helper.inc";
	include LIB_DIR."date.inc";
	require INC_DIR."reporting_lib.inc";

	$username = value_from_POST('username');
	$week = value_from_POST('week');
	$year = value_from_POST('year');

	$op = value_from_POST('op');
	if (isset($op)) { 

//		echo "<BR>###".$op."###<BR>";
		$has_confirmation = ($op == "Confirmation");

		if ($has_confirmation) {

			$report_content = stripslashes ($_POST['report_content']);
			createDirIfNotExists ($year);
			$target_file = userFilename ($username, $year, $week);
			$DIS_SaveMessage = "Saving to $target_file <br/>";

			#ob_start("ReportSaving"); 
			ob_start();
			SaveTextIntoFile ($report_content, $target_file);
			makeReportingWeekFileFor ($year, $week) ;
			$DIS_SaveMessage .= ob_get_contents();
			ob_end_clean();

			$week_filename = weekFilename ($year, $week);

			$DIS_SaveMessage .= "<BR><A HREF='$week_filename'>$week_filename</A><BR>\n";
		} else {
			switch ($op) {
				case "SaveUrl" :
					@$reporturl = $_POST['reporturl'];
					if (!isset ($reporturl) or $reporturl != "http://" or strlen ($reporturl) > 0) {
						$report_content = ContentOfUrl ($reporturl);
					}
					break;
				case "SaveFile" :
					@$reportlocalfile = $_FILES['reportlocalfile']['tmp_name'];
					if (!isset ($reportlocalfile) or strlen($reportlocalfile) > 0) {
						//echo "LOCALFILE = $reportlocalfile...<BR>";
						$report_content = ContentOfFile ($reportlocalfile);
					}
					break;
				case "SaveText" :
					$report_content = stripslashes ($_POST['report_content']);
					break;
				default:
					break;
			}

			$DIS_Username = $username;
			$DIS_Year = $year;
			$DIS_Week = $week;
			$DIS_PreviewText = $report_content;

			if (strlen($report_content) == 0) {
				$DIS_SaveMessage = "ERROR ... the content of your report is empty.<BR>";
				$DIS_SaveMessage .= "<UL>";
				$DIS_SaveMessage .= "<LI>Check you enter a correct URL</LI>\n";
				$DIS_SaveMessage .= "<LI>Check you enter a local file</LI>\n";
				$DIS_SaveMessage .= "<LI>Check you enter a text in the text area</LI>\n";
				$DIS_SaveMessage .= "<BR>";
				$DIS_SaveMessage .= "<LI>Check you click on the correct button ...</LI>\n";
				$DIS_SaveMessage .= "</UL>";
				$DIS_SaveMessage .= "Click on your [BACK] button to go to the previous page\n";
				//exit ();
			} else {
				$target_file = userFilename ($username, $year, $week);
				$DIS_SaveMessage = "Saving to $target_file";

				$week_filename = weekFilename ($year, $week);
				#ob_start("ReportSaving"); 
				ob_start(); 

//				$backup = ContentOfFile ($target_file);
//				SaveTextIntoFile ($report_content, $target_file);
//				makeReportingWeekFileFor ($year, $week);
//				SaveTextIntoFile ($report_output, $week_filename);
//
//				SaveTextIntoFile ($backup, $target_file);

				$DIS_SaveMessage .= ob_get_contents();
				ob_end_clean();

				$DIS_SaveMessage .= "<BR><A HREF='$week_filename'>$week_filename</A><BR>\n";
			}
		}
	}

?>
