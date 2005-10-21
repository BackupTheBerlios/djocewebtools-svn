<?php

	include "inc/users.inc";

	$DIS_Application = "pref";

	if (!isset($op) && isset ($_GET['op'])) { $op = $_GET['op']; }
	if (!isset($op) && isset ($_POST['op'])) { $op = $_POST['op']; }
	if (!isset($op)) { $op = ''; }
	if (!isset($oppref) && isset ($_GET['oppref'])) { $oppref = $_GET['oppref']; }
	if (!isset($oppref) && isset ($_POST['oppref'])) { $oppref = $_POST['oppref']; }



	$user = $SCMUSER;


	ob_start ();
		loadUserPref ($user);

		if (isset ($oppref) and ($oppref == 'SavePref')) {
			if (isset ($_POST['email'])) { $email = $_POST['email']; }
			if (isset ($_POST['activate'])) { $activate = $_POST['activate']; }
			if (isset ($_POST['sendemptylogs'])) { $sendemptylogs = $_POST['sendemptylogs']; }
			if (isset ($_POST['sendrawfile'])) { $sendrawfile = $_POST['sendrawfile']; }
			if (isset ($_POST['format'])) { $format = $_POST['format']; }
			$tmp = "";
			$tmp .= "email=".$email."\n";
			if (!isset ($activate) or ($activate != 'on')) { $activate = 'off'; }
			$tmp .= "send_email=".$activate."\n";
			if (!isset ($sendemptylogs) or ($sendemptylogs != 'on')) { $sendemptylogs = 'off'; }
			$tmp .= "send_emptylogs=".$sendemptylogs."\n";
			if (!isset ($sendrawfile) or ($sendrawfile != 'on')) { $sendrawfile = 'off'; }
			$tmp .= "send_rawfile=".$sendrawfile."\n";
			if ($format != 'html') { $format = 'text'; }
			$tmp .= "send_format=".$format."\n";

			echo "<DIV class=info>Pref Saved for $user</DIV>";
			saveUserPref ($tmp, $user);
			loadUserPref ($user);
			echo "<BR>";
		} 
		if (True) {
			echo "<FORM ACTION='$PHP_SELF' NAME='PREF-FORM' METHOD='POST' >\n";
			echo "<INPUT TYPE='hidden' NAME='op' VALUE='$op' >\n";
			echo "<INPUT TYPE='hidden' NAME='user' VALUE='$user' >\n";

			global $SCMLOGS;
			if ($SCMLOGS['email'] == '') { $SCMLOGS['email'] = $user; }
			echo "Email Address <INPUT TYPE=text NAME=email VALUE=\"".$SCMLOGS['email']."\" ><BR><BR>";

			if ($SCMLOGS['send_email'] == 'on') { $is_checked = 'CHECKED'; } else { $is_checked = '';}
			echo "<INPUT TYPE=checkbox NAME=activate $is_checked >Email sending <BR>";

			if ($SCMLOGS['send_emptylogs'] == 'on') { $is_checked = 'CHECKED'; } else { $is_checked = '';}
			echo "<INPUT TYPE=checkbox NAME=sendemptylogs $is_checked >Email empty logs <BR>";

			if ($SCMLOGS['send_rawfile'] == 'on') { $is_checked = 'CHECKED'; } else { $is_checked = '';}
			echo "<INPUT TYPE=checkbox NAME=sendrawfile $is_checked >Email raw file (Not Yet Implemented)<BR>";

			if ($SCMLOGS['send_format'] == 'html') { $is_checked = 'CHECKED'; } else { $is_checked = '';}
			echo "<INPUT TYPE=radio NAME=format VALUE=\"html\" $is_checked >HTML ";

			if ($SCMLOGS['send_format'] == 'text') { $is_checked = 'CHECKED'; } else { $is_checked = '';}
			echo "<INPUT TYPE=radio NAME=format VALUE=\"text\" $is_checked >TEXT <BR> ";

			echo "<INPUT TYPE=submit NAME=oppref VALUE=\"SavePref\" > ";
			echo "<INPUT TYPE=reset NAME=oppref VALUE=\"Reset\" > ";
			echo "</FORM>\n";
		}	

	$output = ob_get_contents();
	ob_end_clean();  

?>
