<TABLE width='100%' border='0' cellpadding=5 cellspacing=2 >
<TR><TD style="color: Blue;">
	<TABLE border=1  cellpadding=5 cellspacing=0 width="100%">
	<TR>
	<TD>
		{$VAR_ADMIN_MESSAGE}
	</TD>
	</TR>
	</TABLE>
</TD></TR>
<TR><TD>
	<TABLE border=1  cellpadding=5 cellspacing=0 width="100%">
	<TR>
	<TD align="center" >
		<H2>Send the week email</H2> <FORM ACTION='admin.php' METHOD='POST'>
		<INPUT TYPE='hidden' NAME='admin' VALUE='{$VAR_ADMIN_PASSWORD}'/>
		<INPUT TYPE='hidden' NAME='task' VALUE='SendEmail' />
		Year <input type='text' name='year' value='{$VAR_ADMIN_YEAR}'/>
		Week <input type='text' name='weeks[]' value='{$VAR_ADMIN_SEND_WEEK}'/>
		<input type='submit'  value='Send Email' />
		</FORM>
	</TD>

	<TD align="center" >
		<H2>Create the full Reports list</H2> <FORM ACTION='admin.php' METHOD='POST'>
		<INPUT TYPE='hidden' NAME='admin' VALUE='{$VAR_ADMIN_PASSWORD}'/>
		<INPUT TYPE='hidden' NAME='task' VALUE='CreateReportingList' />
		<input type='submit'  value='Create List' />
		</FORM>
	</TD></TR>
	<TR><TD COLSPAN=2 >
		<h2>Year {$VAR_ADMIN_YEAR}</h2>
		<FORM ACTION='admin.php' METHOD='POST'>
		<INPUT TYPE='hidden' NAME='admin' VALUE='{$VAR_ADMIN_PASSWORD}'/>
		<input type='hidden' name='year' value='{$VAR_ADMIN_YEAR}'/>

		{foreach from=$ListWeeks item=weekItem key=weekKey}
		<INPUT TYPE='checkbox' NAME='weeks[]' value='{$weekKey}'>week {$weekKey}  
		 - <STRONG>{$weekItem.status}</STRONG></INPUT><BR>
		{/foreach}

		<input type='submit' name='task' value='delete'/>
		<input type='submit' name='task' value='refresh'/>
		<input type='submit' name='task' value='switch-lock'/>
		</FORM>
	</TD>
	</TR>
	</TABLE>

</TD>
<TD width='1%' bgcolor='#000000'>
	<FORM ACTION='admin.php' METHOD='POST'>
	<INPUT TYPE='hidden' NAME='admin' VALUE='{$VAR_ADMIN_PASSWORD}'/>
	{foreach from=$ListYears item=yearItem key=yearKey}
	<INPUT type='submit' name='year' value='{$yearKey}'><BR>
	{/foreach}
	</FORM>
</TD>
</TR>
</TABLE>
