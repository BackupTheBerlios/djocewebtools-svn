<?php

	include "conf/config.inc";
	include "lib/file.inc";

	if (!isset ($user)) { echo "ERROR: user is not set !"; exit(); }
	$user_cfg = ContentOfFile ($SCMLOGS['datadir']."/".$user.".cfg");
	echo "<CENTER><BR><TEXTAREA NAME='modules' COLS='60' ROWS='30' >".$user_cfg."</TEXTAREA></CENTER>\n";

?>
