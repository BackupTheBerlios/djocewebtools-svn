{if isset ($VAR_EDIT_WARNING)}
<SPAN class=warning >{$VAR_EDIT_WARNING}</SPAN>
{/if}
<FORM action='edit.php' name='postreportingForm' method='POST'>
<TABLE>
<TR><TD class='requiredfield'>Username</TD><TD class='requiredfield'>
{$VAR_EDIT_USERNAME_HTML_SELECT} * Required : Please do not forget to set your username !!
</TD></TR>
<TR><TD colspan=2>&nbsp;</TD></TR>
<!-- /////////// Year /////////////// -->
<TR><TD class=field>Year</TD><TD>
{$VAR_EDIT_YEAR_HTML_3_RADIO}
</TD></TR>
<!-- /////////// Week /////////////// -->
<TR><TD class=field>Week</TD><TD>
<EM>Current week {$VAR_EDIT_CURRENT_WEEK_TEXT}</EM> <BR>
{$VAR_EDIT_WEEK_HTML_RADIO_SELECT}
</TD></TR>
</TABLE>
<BR>Please select the categories you want to fill, this is just to help you,<BR>
you are free to add any category you want<BR>
<UL>{$VAR_EDIT_CATEGORIES_CHECK_LIST}</UL>
<STRONG>NB</STRONG> : <EM>If you already have an existing Report, it will NOT be overridden by this selection</EM><BR><BR>
<INPUT type='submit' value='edit'/>
<INPUT type='reset'  value='reset'/>
</FORM>

