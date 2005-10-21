<?php

if (!defined ("__USERS_INC__")) {
define ("__USERS_INC__", True);

	require "conf/config.inc";
	include "inc/datamanager.inc";


function user_exists ($user) {
	return file_exists (userConfigFilename ($user));
}

}

?>
