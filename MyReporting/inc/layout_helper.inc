<?php

include LIB_DIR."date.inc";

function userList_HTML_SELECT ($name, $users, $title=NULL, $selected_key=NULL) {
	$result = "<select name=\"$name\">";
	if (isset ($title) and (strlen($title) > 0)) {
		$result .= "<option value=''>"." -- $title --"."</option>\n";
	}
	while (list ($key, $val) = each ($users) ) {
		$result .= "<option value='$key' ";
		if (isset ($selected_key) and $selected_key == $key) {
			$result .= " SELECTED " ;
		}
		$result .= " >".$val->name."</option>\n";
	}
	$result .= "</select>\n";

	return $result;
}

function number_HTML_3_RADIO ($name, $number) {
	$result = "<INPUT type='radio' name='$name' value='".($number - 1)."'/>\n";
	$result .= ($number - 1);

	$result .= "<INPUT type='radio' name='$name' value='".($number)."' CHECKED />\n";
	$result .= "<FONT class='selection'>".($number)."</FONT>";

	$result .= "<INPUT type='radio' name='$name' value='".($number + 1)."'/>\n";
	$result .= ($number + 1);

	return $result;
}

function week_HTML_RADIO_SELECT ($year, $week, $fieldName, $formName) {
		// Previous Week
	if ($week == 1) { 
		$this_week = 52; 
	} else {
		$this_week = $week - 1;
	}
	$result = "<INPUT type='radio' name='week-selector' value='$this_week' onclick=\"document.$formName.$fieldName.options[".($this_week - 1)."].selected = true\"/>\n";
	$result .= $this_week;

		// Current Week
	$this_week = $week ;
	$result .= "<INPUT CHECKED type='radio' name='week-selector' value='$this_week' onclick=\"document.$formName.$fieldName.options[".($this_week - 1)."].selected = true\"/>\n";
	$result .= "<FONT class='selection'>".($this_week)."</FONT>";

		// Next Week
	if ($week == 52) { 
		$this_week = 1; 
	} else {
		$this_week = $week + 1;
	}
	$result .= "<INPUT type='radio' name='week-selector' value='$this_week' onclick=\"document.$formName.$fieldName.options[".($this_week - 1)."].selected = true\"/>\n";
	$result .= $this_week;

	$result .= "<BR>";
	// Choice

	$result .= "<select name='$fieldName'>";
	$i = 1;
	while ($i < 53) {
		$result .= "<option value='$i' "; 
		if ($i == $week) { 
			$result .= " SELECTED ";
		}
		$result .= ">Week $i ... ";
		$result .= strftime ("%b %d", firstDayOfWeek ($i, $year));
		$result .= " -- ";
		$result .= strftime ("%b %d", lastDayOfWeek ($i, $year));
		$result .= "</option>\n";
		$i = $i + 1;
	}
	$result .= "</select>\n";
	$result .= " &lt;&lt; Real Week value for $year (monday to sunday)\n";

	return $result;
}

function categories_HTML_CHECK_LIST ($categories, $fieldName) {
	$result = "";
	while (list ($key, $val) = each ($categories) ) {
		$result .= "<INPUT type='checkbox' name='$fieldName' value='$key' CHECKED /><STRONG>$key</STRONG><BR>\n";
		if (count ($val) > 0 && isset ($val[0])) {
			$result .= "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<EM class=genmed>".$val[0]."</EM><BR>\n";
		}
	}
	return $result;
}


?>
