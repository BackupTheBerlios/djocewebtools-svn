<?php
	// Classes


class webappUrlEngine {
	Function webappUrlEngine ($baseurl, $reponame) {
		$this->baseurl = $baseurl;
		$this->reponame = $reponame;
	}
	function urlBrowser () { return $this->baseurl; }
	function urlShowFile ($file, $dir, $r1) { return ''; }
	function urlBlameFile ($file, $dir, $r1) { return ""; }
	function urlDiffFile ($file, $dir, $r1, $r2) { return ""; }
	function urlShowDir ($dir, $r1) { return ""; }
	function urlDiffDir ($dir, $r1, $r2) { return ""; }
}

class websvnUrlEngine extends webappUrlEngine {
	Function websvnUrlEngine ($baseurl, $repository_name) {
		parent::webappUrlEngine ($baseurl, $repository_name);
	}
	function urlTmp ($op) {
		return $this->baseurl . $op.".php?repname=" . $this->reponame;
	}
	function urlBrowser () {
		return $this->urlTmp ('listing');
	}
	function urlShowFile ($file, $dir, $r1) {
		$url = $this->urlTmp ('filedetails');
		if ($r1 >= 0) { $url .= "&rev=$r1"; }
		$url .= "&sc=1";
		$url .= "&path=$dir/$file";
		return $url;
	}
	function urlBlameFile ($file, $dir, $r1) {
		$url = $this->urlTmp ('blame');
		if ($r1 >= 0) { $url .= "&rev=r1"; }
		$url .= "&sc=1";
		$url .= "&path=$dir/$file";
		return $url;
	}
	function urlDiffFile ($file, $dir, $r1, $r2) {
		$url = $this->urlTmp ('diff');
		if ($r1 >= 0) { $url .= "&rev=r1"; }
		$url .= "&sc=1";
		$url .= "&path=$dir/$file";
		return $url;
	}
	function urlShowDir ($dir, $r1) {
		$url = $this->urlTmp ('listing');
		if ($r1 >= 0) { $url .= "&rev=$r1"; }
		$url .= "&sc=1";
		$url .= "&path=$dir";
		return $url;
	}
	function urlDiffDir ($dir, $r1, $r2) {
		$url = $this->urlTmp ('comp');
		$url .= "&compare[]=$dir@$r1&compare[]=$dir@$r2";
		return $url;
	}
}

class viewcvsUrlEngine extends webappUrlEngine {
	Function viewcvsUrlEngine ($baseurl, $repository_name) {
		parent::webappUrlEngine ($baseurl, $repository_name);
	}
	function urlTmp ($dir, $file='') {
		$url = $this->baseurl . "$dir/$file";
		if (!empty($this->reponame)) {
			$url .= "?root=" . $this->reponame;
		} else {
			$url .= "?noroot";
		}
		return $url;
	}
	function urlBrowser () {
		return $this->urlTmp ('');
	}
	function urlShowFile ($file, $dir, $r1) {
		$url = $this->urlTmp ($dir, $file);
		if ($r1 >= 0) { $url .= "&rev=$r1"; }
		$url .= "&content-type=text/vnd.viewcvs-markup";
		return $url;
	}
	function urlBlameFile ($file, $dir, $r1) {
		$url = $this->urlShowFile ($file, $dir, $r1);
		$url .= "&view=annotate";
		return $url;
	}
	function urlDiffFile ($file, $dir, $r1, $r2) {
		if (count($file) > 0) {
			if ($r1 == 'NONE') {
				$url = $this->urlShowFile ($file, $dir, $r2);
			} elseif ($r2 == 'NONE') {
				$url = $this->urlShowFile ($file, $dir, $r1);
			} elseif ($r1 != 0 and $r2 != 0) {
				$url = $this->urlTmp($dir, $file);
				$url .= "&r1=$r1&r2=$r2";
			}
		} else {
			$url = $this->urlShowDir ($dir, $r1);
		}
		return $url;
	}
	function urlShowDir ($dir, $r1) {
		$url = $this->urlTmp ($dir);
		if ($r1 >= 0) { $url .= "&rev=$r1"; }
		return $url;
	}
	function urlDiffDir ($dir, $r1, $r2) {
		return $this->urlShowDir ($dir, $r1);
	}
}

Function url_for_operation_on_browser ($op, $appUrlEngine){
	switch ($op) {
		case 'fileshow':
		case 'fileblame':
			$path = $_GET['path'];
			$dir = dirname ($path);
			$file = basename ($path);
			$rev = $_GET['rev'];
			if ($op == 'fileblame') {
				$url = $appUrlEngine->urlBlameFile($file, $dir, $rev);
			} else {
				$url = $appUrlEngine->urlShowFile($file, $dir, $rev);
			}
			break;
		case 'filediff':
			$path = $_GET['path'];
			$dir = dirname ($path);
			$file = basename ($path);
			$r1 = $_GET['r1'];
			$r2 = $_GET['r2'];
			$url = $appUrlEngine->urlDiffFile($file, $dir, $r1, $r2);
			break;
		case 'dirshow':
			$dir = $_GET['path'];
			$rev = $_GET['rev'];
			$url = $appUrlEngine->urlShowDir($dir, $rev);
			break;
		case 'dirdiff':
			$dir = $_GET['path'];
			$r1 = $_GET['r1'];
			$r2 = $_GET['r2'];
			$url = $appUrlEngine->urlDiffDir($dir, $r1, $r2);
			break;
		default:
			$url = $appUrlEngine->urlBrowser();
			break;
		}
	return $url;
}

Function url_for_browser ($appUrlEngine){
	//echo "<PRE>"; print_r ($_SERVER); echo "</PRE>";
	return $_SERVER['REQUEST_URI'] . "&webapp=" . $appUrlEngine . "&remindwebapp=1";
}

	// Config
	
	$delay = 1;
	$cookie_id = "scmlogs_webapp_cookie";

	if (!isset ($_GET['webapp'])) {
		if (isset ($_COOKIE[$cookie_id])) {
			$cookie = $_COOKIE[$cookie_id];
			@$webapp = $cookie['webapp'];
			$delay = 1;
		}
	} else {
		$delay = 0;
		$webapp = $_GET['webapp'];
	}
	if (isset ($webapp)) {
		if (isset ($_GET['remindwebapp'])) {
			setcookie($cookie_id."[webapp]", $webapp, 
				time() + 24 * 3600 * 7
				);
		}
	} else {
		$delay = 3;
		$webapp = 'websvn';
		$webapp = 'viewcvs';
	}
	
	// Start operation
	@$op = $_GET['op'];
	@$reponame = $_GET['repname'];
	$urlEngineIds = array ('websvn' => Null, 'viewcvs' => Null);
	$urlEngineIds['websvn'] = new websvnUrlEngine ("http://www.ise/websvn/", $reponame);
	$urlEngineIds['viewcvs'] = new viewcvsUrlEngine ("http://www.ise/viewcvs/", $reponame);
	$appUrlEngine = $urlEngineIds[$webapp];
	$url = url_for_operation_on_browser ($op, $appUrlEngine);
	echo '<meta http-equiv="refresh" content="'.$delay.'; url='.$url.'">';
	echo '<div style="text-align: center;">';
	if ($delay > 0) {
		echo 'In '.$delay.' seconds, you will be redirected to <br/>';
	} else {
		echo 'Redirected to <br/>';
	}
	echo '<a href="'.$url.'">"'.$url . '</a>';
	echo '</div><br/>';

	echo '<ul>';
	foreach ($urlEngineIds as $ids => $eng) {
		$url = url_for_browser ($ids);
		//$url = url_for_operation_on_browser ($op, $urlEngineIds[$ids]);
		echo '<li>Click to use  <a href="'.$url.'">'.$ids . '</a> ';
		if ($ids == $webapp) { echo "(default)"; }
		echo '</li>';
	}
	echo '</ul>';
//	echo $url;
	#header ("Location: $url");

	exit;

?>
