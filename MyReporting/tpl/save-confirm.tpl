Confirmation :

<FORM ACTION="save.php" METHOD="POST">
<DIV style="margin-left: 10pt">
<INPUT TYPE=submit VALUE="Confirm">
<BR>
<TABLE width=80% border=0 cellpadding=1 cellspacing=0 bgcolor=Black><TR><TD>
<TABLE width=100% border=0 cellpadding=3 cellspacing=0 bgcolor=White><TR><TD>
{$VAR_SAVE_PREVIEW}
</TD></TR></TABLE>
</TD></TR></TABLE>
<BR>
<INPUT TYPE=hidden NAME="op" VALUE="Confirmation">
<INPUT TYPE=hidden NAME="username" VALUE="{$VAR_SAVE_USERNAME}">
<INPUT TYPE=hidden NAME="year" VALUE="{$VAR_SAVE_YEAR}">
<INPUT TYPE=hidden NAME="week" VALUE="{$VAR_SAVE_WEEK}">
<INPUT TYPE=submit VALUE="Confirm">
</DIV>

<TEXTAREA STYLE="visibility:hidden;" cols='0' rows='0' name='report_content'>{$VAR_SAVE_TEXT}</TEXTAREA>

</FORM>
