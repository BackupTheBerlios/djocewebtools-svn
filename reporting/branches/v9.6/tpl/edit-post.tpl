{if isset ($VAR_EDIT_WARNING)}
<span class="warning" >{$VAR_EDIT_WARNING}</span>
{/if}
<form action="edit.php" name="postreportingForm" method="POST">
<table>
<tr><td class="requiredfield">Username</td><td class="requiredfield">
{$VAR_EDIT_USERNAME_HTML_SELECT} * Required : Please do not forget to set your username !!
</td></tr>
<tr><td colspan=2>&nbsp;</td></tr>
<tr><td class=field>Today's week : </td><td>
	<em>{$VAR_EDIT_CURRENT_WEEK_TEXT}</em>
</td></tr>
<tr><td class=field>Select a week : </td><td>
{$VAR_EDIT_YEAR_WEEK_HTML_RADIO_SELECT}
</td></tr>
</table>
<br/>Please select the categories you want to fill, this is just to help you,<br/>
you are free to add any category you want<br/>
<ul>{$VAR_EDIT_CATEGORIES_CHECK_LIST}</ul>
<strong>NB</strong> : <em>If you already have an existing Report, it will NOT be overridden by this selection</em><br/><br/>
<input type="submit" value="edit"/>
<input type="reset"  value="reset"/>
</form>

