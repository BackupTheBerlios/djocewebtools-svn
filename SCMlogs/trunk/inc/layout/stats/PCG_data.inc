<?php

	$DIS_Application = "stats";

	ob_start ();
	include "inc/stats.inc";
	$output = ob_get_contents();
	ob_end_clean();  

?>
