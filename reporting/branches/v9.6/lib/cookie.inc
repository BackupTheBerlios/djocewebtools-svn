<?php

if (!defined ("__LIB_COOKIE_INC__")) {
define ("__LIB_COOKIE_INC__", True);

global $HTTP_COOKIE_VARS ;
$_COOKIE = $HTTP_COOKIE_VARS; 
global $_COOKIES;

function store_array_in_cookie($cookiename, $array2store) { 
	$tmpstring = serialize($array2store); 
	setcookie($cookiename, $tmpstring, time()+3600*50000); 
	unset($tmpstring); 
} 

function get_array_from_cookie($cookiename) { 
	global $_COOKIE;
	if (isset($_COOKIE[$cookiename])) { 
		$tmparray=unserialize(stripslashes($_COOKIE[$cookiename])); 
	} else { 
		$tmparray = array(); 
	} 
	return $tmparray; 
} 

function check_cookies ($cookiename, $id_name) {
	global $_COOKIE;
	if (isset ($GLOBALS[$id_name])) {
		if (isset ($_COOKIE[$cookiename])) {
			$cookie_array = get_array_from_cookie ($cookiename);
		} else {
			$cookie_array = array ();
		}
		$the_array[$id_name] = $GLOBALS[$id_name];
		store_array_in_cookie ($cookiename, $the_array);
	} else {
		if (isset ($_COOKIE[$cookiename])) {
			$cookie_array = get_array_from_cookie ($cookiename);
			$GLOBALS[$id_name] = $cookie_array[$id_name];
		}
	}
}

}
?>
