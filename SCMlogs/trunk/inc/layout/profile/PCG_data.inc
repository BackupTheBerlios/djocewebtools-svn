<?php

	include "inc/show_config_tree.inc";
	$user_modules = userModules ($SCMUSER);
	ob_start ();
	showUserTree ($user_modules);
	$output_user_tree = ob_get_contents();
	ob_end_clean();

	ob_start ();
	displayModules ($user_modules);
	$output_modules = ob_get_contents();
	ob_end_clean();


?>
