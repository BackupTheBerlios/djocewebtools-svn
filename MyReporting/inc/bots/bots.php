<?php

function processed_bots_html ($txt) {
	$engine =& new Bots_engine();
	return $engine->processed_bots_html ($txt);
}

class Bot_agent {
	function url_for ($id) {
		return '';
	}
	function html_url_for ($id, $name) {
		return "<a href=\"".$this->url_for ($id)."\">$name</a>";
	}
}

class Bots_engine {
	var $bots_dir;
	function Bots_engine() {
		$this->bots_dir =realpath (dirname(__FILE__)).DIRECTORY_SEPARATOR ;
	}
	function processed_bots_html($txt) {
		$html = $txt;
		$res = preg_match_all ("(([a-zA-Z]+)#([a-zA-Z0-9_]+))", $html, $matches, PREG_SET_ORDER);
		if ($res > 0) {
			foreach ($matches as $val) {
				$url = $this->html_url_for ($val[1], $val[2], $val[0]);
				if (strlen($url) > 0) {
					$html = str_replace ($val[0], $url, $html);
				}
			}
		}
		return $html;
	}

	function bot_filename($bot) {
		return $this->bots_dir . $bot . '.php';
	}
	function bot_classname($bot) {
		return "bots_" . $bot;
	}
	function html_url_for($bot,$id,$name) {
		$classname = $this->bot_classname ($bot);
		if (!class_exists($classname)) {
			$bfn = $this->bot_filename ($bot);
			if (file_exists ($bfn)) {
				require_once $bfn;
			}
		}
		if (class_exists($classname)) {
			$botobj =& new $classname();
			return $botobj->html_url_for($id, $name);
		} else {
			return '';
		}
	}
}
?>
