<?php

Function displayFetchLoginWeekYear ($l, $w, $y) {
	echo '<a href="index.php?op=fetch&login='.$l.'&week='.$w.'&year='.$y.'">';
	echo "Fetch user=$l week=$w year=$y";
	echo '</a> <br/>';
}
Function displayGetYears () {
	echo '<a href="index.php?op=years">';
	echo "List of Known years";
	echo '</a> <br/>';
}
Function displayGetWeeks ($y) {
	echo '<a href="index.php?op=weeks&year='.$y.'">';
	echo "List of weeks file for year=$y";
	echo '</a> <br/>';
}
Function displayGetWeeksForUser ($y, $l) {
	echo '<a href="index.php?op=weeks&year='.$y.'&login='.$l.'">';
	echo "List of $l's week files for year=$y";
	echo '</a> <br/>';
}
Function displayPostReport ($l, $w, $y, $t) {
	echo '<form action="index.php" method="POST" >';
	echo '<input type="hidden" name="op" value="post" />';
	echo '<input type="text" name="login" value="'.$l.'" />';
	echo '<input type="text" name="week" value="'.$w.'" />';
	echo '<input type="text" name="year" value="'.$y.'" />';
	echo '<br/>';
	echo '<input type="checkbox" name="overwrite" value="true" >Overwrite if exists ?</input>';
	echo '<input type="reset" value="Reset" />';
	echo '<input type="submit" value="Submit" /><br/>';
	echo '<textarea name="text" cols="70" rows="10" >'.$t.'</textarea>';
	echo '</form><br/>';
}

displayFetchLoginWeekYear ('jfiat', 10, 2005);
displayFetchLoginWeekYear ('devuser', 41, 2005);
displayFetchLoginWeekYear ('devuser', 30, 2005);
displayGetYears();
displayGetWeeks(2005);
displayGetWeeksForUser(2005, 'devuser');
displayPostReport ('devuser', 30, 2005, "one upon a time I was building this reporting tool\nThat's it");

?>
