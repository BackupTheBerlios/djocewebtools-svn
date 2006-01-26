<?php

include "../conf/config.inc";
include INC_DIR."require.inc";
include INC_DIR."datamanager.inc";
global $SCMLOGS;

if (isset($_GET['repo'])) {
	$asked_repo = $_GET['repo'];
}
if (isset ($asked_repo)) {
	if ($asked_repo == SCMLogs_repository_id()) {
	} else {
		SCMLogs_set_repository_by_id ($asked_repo);
	}
}

$repo =& SCMLogs_repository();
$msg_exists = "<span class=\"valid\">EXISTS</span>"; 
$msg_missing = "<span class=\"error\">MISSING</span>"; 
$msg_not_found = "<span class=\"warning\">NOT FOUND</span>"; 

?>
<style>
a {
	text-decoration: none; 
	color: #009;
}
a:hover {
	text-decoration: underline; 
}
.title {
	font-weight: bold;
}
.box {
	margin-left: 40px; padding: 5px;
}
.box ul {
	margin: 0 0 10px 0;
}
.nota {
	font-size: smaller;
	font-style: italic;
}
.valid { padding-left: 10px; color: #090; font-weight: bold; }
.error { padding-left: 10px; color: #f00; font-weight: bold; }
.warning { padding-left: 10px; color: #f80; font-weight: bold; }
</style>
<?php
$last_check_had_error = false;
function adminCheckPath($path,$required=true) {
	global $msg_exists, $msg_not_found, $msg_missing;
	global $last_check_had_error;
	$last_check_had_error = false;
	$res = "$path";
	if (file_exists($path)) { 
		$res .= $msg_exists; 
	} else { 
		if ($required) {
			$res .= $msg_missing; 
			$last_check_had_error = true;
		} else {
			$res .= $msg_not_found; 
		}
	}
	return $res;
}
echo "<a href=\"..\">Back to application</a><br/><br/>";
echo "<strong>Selected repository</strong> : " . $repo->id . "<br/>";
echo '<div class="box">';
echo '- <strong>data dir</strong> : ' . adminCheckPath(dataDirectory()) . '<br/>';
echo '- <strong>repository type dir</strong> : ' . adminCheckPath(repositoryTypeDirectory()) . '<br/>';
echo '- <strong>repository config dir</strong> : ' . adminCheckPath(repositoryCfgDirectory()) . '<br/>';
if (!$last_check_had_error) {
	echo '- <strong>default user config</strong> : ' . adminCheckPath(userCfgDefaultFilename()) . '<br/>';
	echo '- <strong>default user pref</strong> : ' . adminCheckPath(userPrefDefaultFilename()) . '<br/>';
	echo '<br/>';
	echo '- <strong>Users </strong> : <br/>';
	echo '<ul>';
		$users = listOfUsers();
		foreach ($users as $u ) {
			echo '<li>';
			echo $u;
			echo '<ul>';
			echo adminCheckPath(userConfigFilename($u));
			echo '<br/>';
			echo adminCheckPath(userPrefFilename($u),false);
			echo '</ul>';
			echo '</li>';
		}
	echo '</ul>';
}
echo '</div>';

foreach ($SCMLOGS['repositories'] as $k_id => $repo) {
	echo '- <a class="title" href="?repo='.$repo->id.'">'.$repo->id . "</a>";
	echo ' (<a class="nota" href="?repo='.$repo->id.'">browse</a>)';
	echo '<div style="margin-left: 40px; padding: 5px;">';
	echo '- <strong>type</strong> : ' . $repo->mode . '<br/>';
	echo '- <strong>path</strong> : ' . adminCheckPath($repo->path) . '<br/>';
	echo '- <strong>logs</strong> : ' . adminCheckPath($repo->logsdir) . '<br/>';
	echo '</div>';
}


?>
