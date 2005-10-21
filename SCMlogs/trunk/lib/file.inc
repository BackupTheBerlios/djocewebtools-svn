<?php 
if (!defined ("__LIB_FILE_INC__")) {
define ("__LIB_FILE_INC__", True);

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
		$fs = filesize ($filename);
		if ($fs > 0) {
			$result = fread ($file, filesize ($filename));
		} else {
			$result = "";
		}
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
		@chmod ($filename, 0666);
		return True;
	} else {
		return False;
	}
}

Function BackupFile ($file) {
	$content = ContentOfFile ($file);
	$index=0;
	$backup_fn = $file.'.bak';
	while (file_exists ($backup_fn)) {
		$backup_fn = $file.'.bak'.$index ;
		$index = $index + 1;
	}
	SaveTextIntoFile ($content, $backup_fn);
}

Function RemoveFile ($fn) {
	unlink ($fn);
}

Function listOfNodes ($dirname) {
    $result = array ();
    if ($dir = @opendir ($dirname)) {
		while ($node = readdir ($dir)) {
			if ($node != '.' && $node != '..') {
				$fullnodename = $dirname."/".$node;
				$result [$node] = $fullnodename;
			}
		}
    }
    return $result;
}
Function listOfFiles ($dirname) {
    $result = array ();
    if ($dir = @opendir ($dirname)) {
		while ($file = readdir ($dir)) {
			if ($file != '.' && $file != '..') {
				$fullfilename = $dirname."/".$file;
				if (is_file ($fullfilename)) {
					$result [$file] = $fullfilename;
				}
			}
		}
    //} else { echo "ERROR: can not read $dirname<BR>";
	}
    return $result;
}


Function listOfDir ($dirname) {
    $result = array ();
    if ($dir = @opendir ($dirname)) {
		while ($file = readdir ($dir)) {
			if ($file != '.' && $file != '..') {
				$fullfilename = $dirname."/".$file;
				if (is_dir ($fullfilename)) {
					$result [$file] = $fullfilename;
				}
			}
		}
    }
    return $result;
}

Function listDirFilter ($dir, $filter) {
	#echo "listDirFilter [$dir] filter[$filter] <BR>\n";
	$dirhdl = @opendir ($dir);
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

?>
