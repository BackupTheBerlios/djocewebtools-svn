<table width='100%' border='0' cellpadding=5 cellspacing=2 >
<tr><td style="color: Blue;">
	<table border=1  cellpadding=5 cellspacing=0 width="100%">
	<tr>
	<td>
		{$VAR_ADMIN_MESSAGE}
	</td>
	</tr>
	</table>
</td></tr>
<tr><td>
	<table border=1  cellpadding=5 cellspacing=0 width="100%">
	<tr>
	<td align="center" >
		<h2>Emailing ...</h2> <form action='admin.php' method='POST'>
		<input TYPE='hidden' name='admin' value='{$VAR_ADMIN_PASSWORD}'/>
		<input TYPE='hidden' name='task' value='SendEmail' />
		Year <input type='text' name='year' value='{$VAR_ADMIN_YEAR}'/>
		Week <input type='text' name='weeks[]' value='{$VAR_ADMIN_SEND_WEEK}'/>
		<input type='submit' name="task" value='SendEmail' />
		<input type='submit' name="task" value='SendReminder' />
		</form>
	</td>

	<td align="center" >
		<h2>Create the full Reports list</h2> <form action='admin.php' method='POST'>
		<input TYPE='hidden' name='admin' value='{$VAR_ADMIN_PASSWORD}'/>
		<input TYPE='hidden' name='task' value='CreateReportingList' />
		<input type='submit'  value='Create List' />
		</form>
	</td></tr>
	<tr><td COLSPAN=2 >
		<h2>Year {$VAR_ADMIN_YEAR}</h2>
		<form action='admin.php' method='POST'>
		<input TYPE='hidden' name='admin' value='{$VAR_ADMIN_PASSWORD}'/>
		<input type='hidden' name='year' value='{$VAR_ADMIN_YEAR}'/>

		{foreach from=$ListWeeks item=weekItem key=weekKey}
		<input TYPE='checkbox' name='weeks[]' value='{$weekKey}'>week {$weekKey}  
		 - <strong>{$weekItem.status}</strong></input><br/>
		{/foreach}

		<input type='submit' name='task' value='delete'/>
		<input type='submit' name='task' value='refresh'/>
		<input type='submit' name='task' value='switch-lock'/>
		</form>
	</td>
	</tr>
	</table>

</td>
<td width='1%' bgcolor='#000000'>
	<form action='admin.php' method='POST'>
	<input TYPE='hidden' name='admin' value='{$VAR_ADMIN_PASSWORD}'/>
	{foreach from=$ListYears item=yearItem key=yearKey}
	<input type='submit' name='year' value='{$yearKey}'><br/>
	{/foreach}
	</form>
</td>
</tr>
</table>
