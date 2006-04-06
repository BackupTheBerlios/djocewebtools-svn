<?php

class SiteAuthentification {
	var $config;
	var $signed_username;

	function SiteAuthentification($cfg) {
		$this->config =& $cfg;
	}

	function initialize() {
	}

	Function authentificate() {
	}

	function user() {
		return $this->signed_username;
	}

	function loginUser($u, $p) {
		return FALSE;
	}

	function logoutUser($user=NULL) {
		$signed_username = Null;
	}

}


?>
