<?php
	/*
	 * You should not modify anything in this file,
	 * please edit SCMconf.conf
	 *
	 */

if (! defined("_CONFIG_")) { define ("_CONFIG_", 1);

define('ROOT_DIR', realpath (dirname(__FILE__) . DIRECTORY_SEPARATOR . '..').DIRECTORY_SEPARATOR);
define ('INC_DIR', ROOT_DIR.'inc'.DIRECTORY_SEPARATOR);
define ('LIB_DIR', ROOT_DIR.'lib'.DIRECTORY_SEPARATOR);
define ('TPL_DIR', ROOT_DIR.'tpl'.DIRECTORY_SEPARATOR);

$cfg_filename = ROOT_DIR.DIRECTORY_SEPARATOR.'conf'.DIRECTORY_SEPARATOR.'SCMlogs.conf';
$cfg = parse_ini_file ($cfg_filename, true);

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
$SCMLOGS['scm_type'] = $cfg[$repo_id]['mode'];
$SCMLOGS['logsdir'] = $cfg[$repo_id]['logs_dir'];

$SCMLOGS['repository_root'] = $cfg[$repo_id]['repository_path'];

//// Dir to store users profiles
$SCMLOGS['currentcommitfile'] = 'commits.txt';
$SCMLOGS['appdir'] = $cfg['global']['SCMlogs_appdir'];
$SCMLOGS['datadir'] = $SCMLOGS['appdir'].'data/'.$repo_id;
$SCMLOGS['tmpdir'] = $SCMLOGS['datadir'].'tmp';

//// Integration to WebBrowsing
$SCMLOGS['webBrowsingUrl'] = $SCMLOGS['app.url'].'webscmlogs.php';
if (isset ($cfg['global']['browsing'])) {
	$SCMLOGS['webBrowsingApp'] = $cfg['global']['browsing'];
} else {
	$SCMLOGS['webBrowsingApp'] = $cfg['global']['browsing'];
}

$cmd = '/usr/bin/python ' . $SCMLOGS['appdir'].'bin/scm_sendlogs.py ';
$cmd .= ' -cfg '.$cfg_filename;
$cmd .= ' -repo ' . $SCMLOGS['repository_id'];

$cmd = '/usr/bin/python ' . $SCMLOGS['appdir'].'bin/scm_sendlogs.py -cfg '.$cfg_filename . ' -repo ' . $repo_id;
$SCMLOGS['sendlogs_cmd'] = $cmd;

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
	$url .= "?repname=".$SCMLOGS['repository_id'];
	if (isset ($SCMLOGS['webBrowsingApp'])) {
		$url .= "&webapp=".$SCMLOGS['webBrowsingApp'];
	}
	return $url;
}

} 

?>
