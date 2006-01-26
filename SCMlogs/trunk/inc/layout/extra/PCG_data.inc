<?php

	$DIS_Application = "extra";
	@$extra_op = $_POST['extra_op'];
	@$commitsfiles = $_POST['commitsfiles'];
	@$only_user = $_POST['only_user'];
	@$only_tag = $_POST['only_tag'];

	$user = $SCMUSER;
	ob_start ();
	include "inc/extra.inc";
	$output = ob_get_contents();
	ob_end_clean();  

?>
