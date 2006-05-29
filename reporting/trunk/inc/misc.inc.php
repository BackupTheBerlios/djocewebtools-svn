<?php

	// Variables
	function value_from_GET ($param_name, $default_value=NULL){
		if (isset ($_GET[$param_name])) {
			return $_GET[$param_name];
		} else {
			return $default_value;
		}
	}

	function value_from_POST ($param_name, $default_value=NULL){
		if (isset ($_POST[$param_name])) {
			return $_POST[$param_name];
		} else {
			return $default_value;
		}
	}

	function value_from_GET_POST ($param_name, $default_value=NULL){
		$result = value_from_GET ($param_name);
		if (!isset ($result)) { 
			$result = value_from_POST ($param_name, $default_value); 
		}
		return $result;
	}

	function value_from_POST_GET ($param_name, $default_value=NULL){
		$result = value_from_POST ($param_name);
		if (!isset ($result)) { 
			$result = value_from_GET ($param_name, $default_value); 
		}
		return $result;
	}

?>
