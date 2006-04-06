<?php

class SiteAuthHtpasswd extends SiteAuthentification {
	var $expireTime;
	var $htpasswd_filename;

	function SiteAuthHtpasswd($cfg, $htpasswd_filename) {
		parent::SiteAuthentification (&$cfg);
		$this->htpasswd_filename = $htpasswd_filename;
	}

	function initialize() {
		$expireTime = 60*60*24*100; // 100 days
		session_set_cookie_params($expireTime);
		session_start();
	}

	Function Authentificate() {
		global $_SESSION;
//		echo "<pre>"; print_r ($_SESSION); echo "</pre>";
		if (isset($_SESSION['username'])) {
			$this->signed_username = $_SESSION['username'];
		}
	}

	function loginUser($u, $p) {
		global $_SESSION;

		if (!file_exists($this->htpasswd_filename)) {
			$this->signed_username = Null;
			unset($_SESSION['username']);
			return FALSE;
		} else {
			FMWK_include_once("pear/pear.inc.php");
			include_once "File/Passwd.php";

			$passwd = &File_Passwd::factory('Authbasic');
			$passwd->setMode('md5');
			$passwd->setFile($this->htpasswd_filename);
			$passwd->load();
			$res = $passwd->verifyPasswd($u, $p);
			if ((!is_object($res)) & $res) {
				$_SESSION['username'] = $u;
				$this->signed_username = $u;
				return TRUE;
			} else {
				$this->signed_username = Null;
				unset($_SESSION['username']);
				return FALSE;
			}
		}
	}

	function logoutUser($user) {
		// check $user == $this->user();
		$_SESSION['username'] = Null;
		$_COOKIE['username'] = Null;
		unset($_SESSION['username']);
		$this->signed_username = Null;
	}

}


?>
