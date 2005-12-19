<?php
	/*
	 * You should not modify anything in this file,
	 * please edit SCMconf.conf
	 */

if (! defined("_CONFIG_")) { define ("_CONFIG_", 1);
	// Php.ini settings
//	ini_set ("session.use_trans_sid", 1);
	ini_set('magic_quotes_runtime', 0);
	ini_set('magic_quotes_gpc', 0);

	// Defines
	define('ROOT_DIR', realpath (dirname(__FILE__) . DIRECTORY_SEPARATOR . '..').DIRECTORY_SEPARATOR);
	define ('INC_DIR', ROOT_DIR.'inc'.DIRECTORY_SEPARATOR);
	define ('LIB_DIR', ROOT_DIR.'lib'.DIRECTORY_SEPARATOR);
	define ('TPL_DIR', ROOT_DIR.'tpl'.DIRECTORY_SEPARATOR);

	$cfg_filename = ROOT_DIR.DIRECTORY_SEPARATOR.'conf'.DIRECTORY_SEPARATOR.'SCMlogs.conf';
	$cfg = parse_ini_file ($cfg_filename, true);

	$SCMLOGS['cfg.filename'] = $cfg_filename;
	$SCMLOGS['cfg.data'] = $cfg;

	$SCMLOGS['style.css'] = 'base.css';
	$SCMLOGS['app.url'] = $cfg['global']['SCMlogs_appurl'];

	if (isset ($cfg['global']['SCM_repositories'])) {
		$repo_list_id = split (',' , $cfg['global']['SCM_repositories']);
		$repo_id = $repo_list_id[1];
	}
	if (isset ($cfg['global']['SCM_default_repository'])) {
		$repo_id = $cfg['global']['SCM_default_repository'];
	}
	$SCMLOGS['repository_list_id'] = $repo_list_id;
	$SCMLOGS['repository_id'] = $repo_id;


	//// Dir to store users profiles
	$SCMLOGS['tmpdir'] = $SCMLOGS['datadir'].'tmp';
	$SCMLOGS['currentcommitfile'] = 'commits.txt';
	$SCMLOGS['appdir'] = $cfg['global']['SCMlogs_appdir'];
	$SCMLOGS['datadir'] = $SCMLOGS['appdir'].'data'.DIRECTORY_SEPARATOR;

	/// Misc
	if (isset($cfg['users']['cfg_extension'])) {
		$SCMLOGS['user.cfg.ext'] = $cfg['users']['cfg_extension'];
	} else {
		$SCMLOGS['user.cfg.ext'] = '.cfg';
	}
	if (isset($cfg['users']['pref_extension'])) {
		$SCMLOGS['user.pref.ext'] = $cfg['users']['pref_extension'];
	} else {
		$SCMLOGS['user.pref.ext'] = '.pref';
	}

	//// Integration to WebBrowsing
	$SCMLOGS['webBrowsingUrl'] = $SCMLOGS['app.url'].'webscmlogs.php';
	if (isset ($cfg['global']['browsing'])) {
		$SCMLOGS['webBrowsingApp'] = $cfg['global']['browsing'];
	} else {
		$SCMLOGS['webBrowsingApp'] = $cfg['global']['browsing'];
	}


	function SCMLogs_set_repository_id ($repo_id) {
		global $SCMLOGS;
		$repo_section = 'repo:'.$repo_id;
		$cfg = $SCMLOGS['cfg.data'];
		$SCMLOGS['repository_id'] = $repo_id;
		$SCMLOGS['scm_mode'] = $cfg[$repo_section]['mode'];
		$SCMLOGS['logsdir'] = $cfg[$repo_section]['logs_dir'];
		$SCMLOGS['repository_root'] = $cfg[$repo_section]['repository_path'];
	}

	function SCMLogs_logs_dir () {
		global $SCMLOGS;
		return $SCMLOGS['logsdir'];
	}
	function SCMLogs_repository_mode () {
		global $SCMLOGS;
		return $SCMLOGS['scm_mode'];
	}
	function SCMLogs_repository_id () {
		global $SCMLOGS;
		return $SCMLOGS['repository_id'];
	}
	function SCMLogs_sendlogs_cmd ($repo=NULL) {
		global $SCMLOGS;
		$cmd = 'python ' . $SCMLOGS['appdir'].'bin/scm_sendlogs.py ';
		$cmd .= ' -cfg '.$SCMLOGS['cfg.filename'];
		if (isset ($repo)) {
			$cmd .= ' -repo ' . $repo;
		} else {
			$cmd .= ' -repo ' . SCMLogs_repository_id();
		}
		return $cmd;
	}

	function SCMLogs_CurrentCommitFile () {
		global $SCMLOGS;
		return $SCMLOGS['currentcommitfile'];
	}
	function SCMLogs_Repository () {
		global $SCMLOGS;
		return $SCMLOGS['repository_root'];
	}
	function SCMLogs_WebBrowsing () {
		global $SCMLOGS;
		$url = $SCMLOGS['webBrowsingUrl'];
		$url .= "?repname=".SCMLogs_repository_id();
		if (isset ($SCMLOGS['webBrowsingApp'])) {
			$url .= "&webapp=".$SCMLOGS['webBrowsingApp'];
		}
		return $url;
	}

	SCMLogs_set_repository_id ($SCMLOGS['repository_id']);
} 

?>
