<?php

	$t->setFile ("MainTemplate", "tpl/query.html");
	$t->setFile ("FilesTemplate", "tpl/query-files.html");
	$t->setFile ("FilesSelectedTemplate", "tpl/query-files-selected.html");
	$t->setFile ("FilesBrowseTemplate", "tpl/query-files-browse.html");
	$t->setFile ("CommandsTemplate", "tpl/query-commands.html");

	// Commit Files ////////////////////////////////////////////////
//	$t->setBlock ("FilesSelectedTemplate", "ListYearsBlock", "LY_B");
	$t->setBlock ("FilesSelectedTemplate", "ListMonthsBlock", "LM_B");
	$t->setBlock ("ListMonthsBlock", "ListFilesBlock", "LF_B");

	$t->setVar ("VAR_USER_FILTER", $DIS_UserFilter);
	$t->setVar ("VAR_CURRENT_COMMITS_FILENAME", $DIS_CurrentCommitFile);
	if ($DIS_CurrentCommitFileChecked) {
		$t->setVar ("VAR_CURRENT_FILE_CHECKED", "CHECKED");
	} else {
		$t->setVar ("VAR_CURRENT_FILE_CHECKED", "");
	}

	$t->setVar ("VAR_SELECTED_YEARS_GET", $DIS_GET_SelectedYear);
	while (list ($k_year, $v_months) = each ($DIS_CommitFiles)) {
		$t->setVar ("VAR_ITEM_YEAR", "$k_year");
		if (in_array ($k_year, $selected_years)) {
			while (list ($k_month, $v_files) = each ($v_months)) {
				$t->setVar ("VAR_ITEM_MONTH", "$k_month");
				while (list ($k_file, $v_checked) = each ($v_files)) {
					if ($v_checked) {
						$t->setVar ("VAR_FILE_CHECKED", "CHECKED");
					} else {
						$t->setVar ("VAR_FILE_CHECKED", "");
					}
					list ($iy, $im, $id) = split ("-", "$k_file");
					$k_day = $im."/".$id."/".$iy;
					$k_day = strtotime ($k_day);
					$k_week = strftime ("%W", $k_day);
					$k_day = date ("D", $k_day);
					$t->setVar ("VAR_FILE_ITEM_WEEK", $k_week);
					$t->setVar ("VAR_FILE_ITEM_DAY", $k_day);
					$t->setVar ("VAR_FILE_KEY_ITEM", "$k_file");
					$t->setVar ("VAR_FILE_NAME_ITEM", "$k_file");
					$t->parse ("LF_B", "ListFilesBlock", True);
				}
				$t->parse ("LM_B", "ListMonthsBlock", True);
				$t->unsetVar ("LF_B");
			}
			$t->parse ("VAR_PAGE_YEAR", "FilesSelectedTemplate", True);
			$t->unsetVar ("LM_B");
		} else {
			$t->parse ("VAR_PAGE_YEAR", "FilesBrowseTemplate", True);
		}
	}
	$t->parse ("VAR_PAGE_COMMITS_FILES", "FilesTemplate");

	// Commands ////////////////////////////////////////////////////
	$t->setVar ("VAR_ONLY_USER", $DIS_OnlyUser);
	$t->setVar ("VAR_ONLY_TAG", $DIS_OnlyTag);
	$t->parse ("VAR_PAGE_COMMANDS", "CommandsTemplate");

?>
