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
		$url .= "&path=/$dir/$file";
		return $url;
	}
	function urlBlameFile ($file, $dir, $r1) {
		$url = $this->urlTmp ('blame');
		if ($r1 >= 0) { $url .= "&rev=r1"; }
		$url .= "&sc=1";
		$url .= "&path=/$dir/$file";
		return $url;
	}
	function urlDiffFile ($file, $dir, $r1, $r2) {
		$url = $this->urlTmp ('diff');
		if ($r1 >= 0) { $url .= "&rev=r1"; }
		$url .= "&sc=1";
		$url .= "&path=/$dir/$file";
		return $url;
	}
	function urlShowDir ($dir, $r1) {
		$url = $this->urlTmp ('listing');
		if ($r1 >= 0) { $url .= "&rev=$r1"; }
		$url .= "&sc=1";
		$url .= "&path=/$dir";
		return $url;
	}
	function urlDiffDir ($dir, $r1, $r2) {
		$url = $this->urlTmp ('comp');
		$url .= "&compare[]=/$dir@$r1&compare[]=/$dir@$r2";
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

	
	// Conﬁg
	
	@$webapp = $_GET['webapp'];
	if (!isset ($webapp)) {
		$webapp = 'websvn';
		$webapp = 'viewcvs';
	}
	
	// Start operation
	@$op = $_GET['op'];
	@$reponame = $_GET['repname'];

	switch ($webapp) {
		case 'websvn':
			$appUrlEngine = new websvnUrlEngine ("http://localhost:8000/~jfiat/websvn/trunk/", $reponame);
			break;
		case 'viewcvs':
			$appUrlEngine = new viewcvsUrlEngine ("http://localhost:8000/cgi-bin/viewcvs.cgi/", $reponame);
		default:
			break;
	}

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
//	echo $url;
	header ("Location: $url");
	exit;

?>
