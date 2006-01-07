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

function year_week_HTML_RADIO_SELECT ($year, $week, $yearFieldName, $weekFieldName, $formName) {
	$result = "<!-- start : year_week_HTML_RADIO_SELECT -->\n";
	$result .= <<<JS
<script type="text/javascript">
<!--
	function blockDivBox(nr,state)
	{
		var displayable;
		if (document.getElementById)
		{
			document.getElementById(nr).style.display = state ? 'block' : 'none';
		} else if (document.layers)
		{
			document.layers[nr].display = state ? 'block' : 'none';
		}
		else if (document.all)
		{
			document.all[nr].style.display = state ? 'block' : 'none';
		}
	}
//-->
</script>
JS;
	$result .= '<div id="week_selector">';
	foreach (range ($year - 1, $year + 1) as $y) {
		$result .= "<input type='radio' name='$yearFieldName' value='".$y."' ";
		$result .= ' onclick="blockDivBox(\'_year'.$y.'\',true);';
		foreach (range ($year - 1, $year + 1) as $i) {
			if ($i != $y) { $result .= "blockDivBox('_year$i', false);"; }
		}
		$result .= '" ';
		if ($y == $year) { $result .= " CHECKED "; }
		$result .= "/>\n";
		if ($y == $year) {
			$result .= "<font class='selection'>".$y."</font>";
		} else {
			$result .= $y;
		}
	}
	$result .= '<div style="padding: 5px; border: dotted 1px #aaa; background-color: #fff;">';
	foreach (range($year - 1, $year + 1) as $y) {
		$result .= "\n";
		$result .= '<div id="_year'.$y.'" ';
		if ($year != $y) { $result .= 'style="display: none;"'; }
		$result .= '><Strong>Year '.$y.' : </strong>';
		$result .= week_HTML_RADIO_SELECT ($y, $week, $weekFieldName, $formName);
		$result .= '</div>';
	}
	$result .= '</div>';
	$result .= '</div>';
	$result .= "<!-- end : year_week_HTML_RADIO_SELECT -->\n";
	return $result;

}

function week_HTML_RADIO_SELECT ($year, $week, $fieldName, $formName) {
	$listFieldName = $fieldName.$year;
	$firstweeknb = firstWeekNumberOfYear ($year);
	$lastweeknb = lastWeekNumberOfYear ($year);
	foreach (range ($week - 1, $week + 1) as $w) {
		if ($w >= $firstweeknb and $w <= $lastweeknb) { 
			$result .= "<input type='radio' name='week$year-selector' value='$w' ";
			if ($w == $week) { $result .= " CHECKED "; }
			$result .= " onclick=\"";
			$result .= "document.$formName.$listFieldName.options[".($w - 1)."].selected = true;";
			$result .= "\" />\n";
			if ($w == $week) {
				$result .= "<font class='selection'>".$w."</font>";
			} else {
				$result .= $w;
			}
		}
	}
	$result .= "<br/>";
	// Choice

	$result .= "<select name='$listFieldName'>";
	$i = $firstweeknb;
	while ($i <= $lastweeknb) {
		$result .= '<option value="'.$i.'" '; 
		if ($i == $week) { $result .= " SELECTED "; }
		$result .= ">";
		$result .= "[" . $year . "] ";
		$result .= "Week $i ... ";
		$result .= strftime ("%b %d", firstDayOfWeek ($i, $year));
		$result .= " -- ";
		$result .= strftime ("%b %d", lastDayOfWeek ($i, $year));
		$result .= "</option>\n";
		$i = $i + 1;
	}
	$result .= "</select>\n";
	$result .= " &lt;&lt; Real Week value for $year (monday to sunday)\n";
//	$result .= '<br/><input type="text" name="'.$fieldName.'" value="toto" />';

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
