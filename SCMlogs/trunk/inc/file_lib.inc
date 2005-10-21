<?php 

if (! defined("_FILE_LIB_")) { define ("_FILE_LIB_", 1);

Function ContentOfUrl ($url) {
	$file = fopen ($url, "r");
	$step = 1000;
	if ($file != null) {
		while (!feof ($file)) {
			$result .= fread ($file, $step);
		}
		fclose ($file);
	} else { 
		echo "Error while reading $filename...<BR>\n";
	}
	return $result;
}
Function ContentOfFile ($filename) {
	$file = fopen ($filename, "r");
	if ($file != null) {
		$result = fread ($file, filesize ($filename));
		fclose ($file);
	} else { 
		echo "Error while reading $filename...<BR>\n";
	}
	return $result;
}
Function SaveTextIntoFile ($text, $filename) {
	$file = fopen ($filename, "w");
	if ($file != null) {
		fwrite ($file, $text);
		fclose ($file);
		chmod ($filename, 0666);  // rw_ rw_ rw_
		return True;
	} else {
		return False;
	}
}

Function RemoveFile ($fn) {
	unlink ($fn);
	//echo "$fn is removed";
}

Function listDirOf ($dirname) {
    $result = array ();
    if ($dir = @opendir ($dirname)) {
                while ($file = readdir ($dir)) {
                        if (is_dir ($dirname."/".$file) and ($file != '.' && $file != '..')) {
                                $result [$file] = $dirname."/".$file;
                        }
                }
        }
    return $result;
}

Function listFileOf ($dirname) {
    $result = array ();
    if ($dir = @opendir ($dirname)) {
                while ($file = readdir ($dir)) {
                        if (($file != '.' && $file != '..')) {
				$filename = $dirname."/".$file;
				if (is_file ($filename)) {
					$result [$file] = $dirname."/".$file;
				}
                        }
                }
        }
    return $result;
}


Function listDirFilter ($dir, $filter) {
	#echo "listDirFilter [$dir] filter[$filter] <BR>\n";
	$dirhdl = opendir ($dir);
	if ($dirhdl) {
		$result = array ();
		while ($file = readdir ($dirhdl)) {
			if (eregi ($filter, $file)) {
				$result[] = $dir."/".$file;
			}
		}
	}
	return $result;
}

}
//else { echo "_FILE_LIB_ Already loaded .."; }

?>
