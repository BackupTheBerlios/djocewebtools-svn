<?php

require "conf/config.inc";
include "lib/file.inc";

include "inc/query.inc";

$this_script = $_SERVER['PHP_SELF']; 
$this_script .= "?user=$user";

if (!isset ($extra_op)) {

	echo "<FORM ACTION=\"$this_script\" NAME=\"EXTRA_FORM\" METHOD=\"POST\">\n";
	echo "<TABLE><TR><TD class=text>";
	echo "<TABLE border=0 cellpadding='5' cellspacing='5' >";
	echo "<TR><TD class='subtitle' COLSPAN=2 >Current log file</TD></TR>";
	echo "<TR><TD class=text>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD><TD class='inlist'>";
	echo "<INPUT TYPE=checkbox NAME='commitsfiles[]' VALUE='".$SCMLOGS['logsdir']."/commits.txt'>";
	echo "Current commit file";
	echo "</TD></TR>";

	$list_years = listOfDir ($SCMLOGS['logsdir']);
	reset ($list_years);
	krsort ($list_years);
	while (list ($key, $val) = each ($list_years)) {
		echo "<TR><TD class='subtitle' COLSPAN=2 >$key</TD></TR>";
		$list_months = listOfDir ($val);
		arsort ($list_months);

		while (list ($kmonth, $vmonth) = each ($list_months)) {
			$list_files = listOfFiles ($vmonth);
			arsort ($list_files);
			if (count ($list_files) > 0) {
				echo "<TR><TD colspan=2 class='inlist'><STRONG>$kmonth</STRONG></TD></TR>";
				echo "<TR><TD class=text>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</TD><TD class='inlist'>";
				while (list ($skey, $sval) = each ($list_files)) {
					echo "<INPUT TYPE=checkbox NAME='commitsfiles[]' VALUE='$skey'>";
					echo $skey;
					echo "<BR>\n";
				}
				echo "</TD></TR>";
			}
		}
	}
	echo "</TABLE>\n";
	echo "</TD><TD STYLE=\"vertical-align: top;\">";
	echo "Show me the RAW logs file<BR><BR>\n";
	echo "<INPUT TYPE=submit NAME=extra_op VALUE='ShowRawLogs'><BR>\n";
	echo "<HR>\n";
	echo "Email me [$user] the logs filtred according to my profile<BR><BR>\n";
	echo "<INPUT TYPE=submit NAME=extra_op VALUE='EmailLogs'> &middot; ";
	echo "<INPUT TYPE=submit NAME=extra_op VALUE='ShowLogs'><BR>\n";
	echo "<HR>\n";
	echo "Email me [$user] only my commits<BR><BR>\n";
	echo "<INPUT TYPE=submit NAME=extra_op VALUE='EmailMyLogs'> &middot; ";
	echo "<INPUT TYPE=submit NAME=extra_op VALUE='ShowMyLogs'><BR>\n";
	echo "<HR>\n";
	echo "Email me [$user] only commits from a specify user<BR>";
	echo "<BR>\n";
	echo "<INPUT TYPE=submit NAME=extra_op VALUE='EmailOnlyLogsFor'> &middot; ";
	echo "<INPUT TYPE=submit NAME=extra_op VALUE='ShowOnlyLogsFor'><BR>\n";
	echo " Author : <INPUT TYPE=text NAME=only_user VALUE=$user> and/or ";
	echo " Tag : <INPUT TYPE=text NAME=only_tag VALUE=''><BR>\n";
	echo "<HR>\n";
	echo "</TD></TR>";
	echo "</TABLE>\n";
	echo "</FORM>\n";
} else {
	//echo "<H1>$extra_op</H1>";
	if (isset ($commitsfiles)) {
		if (!isset ($only_user)) { $only_user = ''; }
		if (!isset ($only_tag)) { $only_tag = ''; }
		if ($extra_op == 'EmailLogs') {
			echo "Email $user all the logs <BR>(in the selected files)<BR>\n";
			$processing_fct = "EmailLogsAction";
		} elseif ($extra_op == 'ShowLogs') {
			echo "Show $user all the logs <BR>(in the selected files)<BR>\n";
			$processing_fct = "ShowLogsAction";
		} elseif ($extra_op == 'ShowRawLogs') {
			echo "Show the RAW logs file <BR>(selected files)<BR>\n";
			$processing_fct = "ShowRawLogsAction";
		} elseif ($extra_op == 'EmailMyLogs') {
			$only_user = $user;
			echo "Email $user all the logs (in the selected files)<BR>\n";
			echo " -&gt; from $user<BR>\n";
			$processing_fct = "EmailMyLogsAction";
		} elseif ($extra_op == 'ShowMyLogs') {
			$only_user = $user;
			echo "Show $user all the logs (in the selected files)<BR>\n";
			echo " -&gt; from $user<BR>\n";
			$processing_fct = "ShowMyLogsAction";
		} elseif ($extra_op == 'EmailOnlyLogsFor') {
			echo "Email $user all the logs (in the selected files)<BR>\n";
			echo " -&gt; from user : $only_user<BR>\n";
			echo " -&gt; with tag&nbsp;  : $only_tag<BR>\n";
			$processing_fct = "EmailOnlyLogsForAction";
		} elseif ($extra_op == 'ShowOnlyLogsFor') {
			echo "Show $user all the logs (in the selected files)<BR>\n";
			echo " -&gt; from user : $only_user<BR>\n";
			echo " -&gt; with tag&nbsp;  : $only_tag<BR>\n";
			$processing_fct = "ShowOnlyLogsForAction";
		}
		echo "<HR>";
		$file_tempo_name = tempnam ($SCMLOGS['tmpdir'], "TEMPO_");
		$file_tempo = fopen ($file_tempo_name, "w");
		echo "Selected files: ";
		echo "<UL>\n";
		while (list ($k, $v_file) = each ($commitsfiles)) {
			if (preg_match("/([0-9][0-9][0-9][0-9])-([0-9][0-9])-([0-9][0-9])/", $v_file, $matches)) {
				$v_file = $SCMLOGS['logsdir'] .'/'.$matches[1].'/'.$matches[2].'/'. $v_file;
			}

			fwrite ($file_tempo, ContentOfFile ($v_file));
			echo "<LI>File <STRONG>[$v_file]</STRONG>";
			echo "</LI>\n";
			
		}
		echo "</UL>\n";
		fclose ($file_tempo);
		if ($processing_fct != '') {
			$processing_fct ($file_tempo_name, $user, $only_user, $only_tag);
		} else {
			echo "Not Yet Implemented";
			echo "<PRE>";
			echo ContentOfFile ($file_tempo_name);
			echo "</PRE>";
		}
		RemoveFile ($file_tempo_name);
	} else {
		echo "You selected no file !!!<BR>";
	}

}

?>
